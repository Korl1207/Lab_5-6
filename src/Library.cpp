#include "Library.h"

#include <algorithm>
#include <fstream>
#include <sstream>

Book readBook(std::istringstream& sbook);
User readUser(std::istringstream& suser);
std::string prefixDrop(std::string& str, std::string pref);

Library::Library(std::string dataFile) : dataFile(dataFile) {
  try {
    loadFromFile();
  } catch (const std::exception& e) {
    std::cerr << "Ошибка чтения из файла: " << e.what() << std::endl;
    throw;
  }
}
Library::~Library() {
  try {
    saveToFile();
  } catch (const std::exception& e) {
    std::cerr << "Ошибка записи в файл: " << e.what() << std::endl;
  }
}

void Library::addBook(const Book& book) { books.push_back(book); }
void Library::addUser(const User& user) { users.push_back(user); }
void Library::borrowBook(const std::string& userName, const std::string& isbn) {

}
void Library::returnBook(const std::string& isbn) {}
Book* Library::findBookByISBN(const std::string& isbn) {
  auto it = std::find_if(books.begin(), books.end(), [&isbn](const Book& book) {
    return book.getIsbn() == isbn;
  });
  if (it == books.end()) {
    throw std::invalid_argument("Книги " + isbn + " нет в библиотеке");
  }
  return &(*it);
}

User* Library::findUserByName(const std::string& name) {
  auto it = std::find_if(users.begin(), users.end(), [&name](const User& user) {
    return user.getName() == name;
  });
  if (it == users.end()) {
    throw std::invalid_argument("Пользователя " + name + " не существует");
  }
  return &(*it);
}

void Library::displayAllBooks() {
  for (auto it = books.begin(); it != books.end(); ++it) it->displayInfo();
}
void Library::displayAllUsers() {
  for (auto it = users.begin(); it != users.end(); ++it) it->displayProfile();
}

void Library::saveToFile() {
  std::ofstream outputFile(dataFile);
  if (!outputFile.is_open()) {
    throw std::runtime_error("Не удалось открыть файл с именем " + dataFile);
  }

  for (auto it = books.begin(); it != books.end(); ++it) {
    outputFile << "BOOK" << std::endl;
    outputFile << "Title: " << it->getTitle() << std::endl;
    outputFile << "Author: " << it->getAuthor() << std::endl;
    outputFile << "Year: " << it->getYear() << std::endl;
    outputFile << "ISBN: " << it->getIsbn() << std::endl;
    outputFile << "Avaible: " << ((it->getIsAvaible()) ? "yes" : "no");
    outputFile << "BorrowedBy: " << it->getBorrowedBy() << std::endl;
  }
  outputFile << "---USERS---" << std::endl;
  for (auto it = users.begin(); it != users.end(); ++it) {
    outputFile << "USER" << std::endl;
    outputFile << "Name: " << it->getName() << std::endl;
    outputFile << "UserID" << it->getUserId() << std::endl;
    outputFile << "BorrowedBooks: ";
    for (size_t i = 0; i < it->getBorrowedBooks().size(); ++i) {
      if (i + 1 != it->getBorrowedBooks().size())
        outputFile << it->getBorrowedBooks()[i] << "|";
      else
        outputFile << it->getBorrowedBooks()[i] << std::endl;
    }
    outputFile << "MaxBooks: " << it->getMaxBooksAllowed() << std::endl;
  }
  outputFile.close();
}

void Library::loadFromFile() {
  std::ifstream inputFile(dataFile);
  if (!inputFile.is_open()) {
    throw std::runtime_error("Не удалось открыть файл с именем " + dataFile);
  }

  std::string buf;
  std::stringstream sbooks, susers;
  while (std::getline(inputFile, buf)) {
    if (buf == "BOOK") {
      while (std::getline(inputFile, buf)) {
        sbooks << buf << std::endl;
        if (buf.find("---USERS---") == 0) {
          break;
        }
      }
    } else if (buf == "USER") {
      while (std::getline(inputFile, buf)) {
        susers << buf << std::endl;
      }
    }
  }
  inputFile.close();

  std::istringstream issBooks(sbooks.str()), issUsers(susers.str());
  std::string buf;
  while (std::getline(issBooks, buf)) {
    std::stringstream sbook;
    while (std::getline(issBooks, buf) && buf != "BOOK") {
      sbook << buf << std::endl;
    }
    std::istringstream issbook(sbook.str());
    Book newBook = readBook(issbook);
    books.push_back(newBook);
  }
  while (std::getline(issUsers, buf)) {
    std::stringstream suser;
    while (std::getline(issUsers, buf)) {
      suser << buf << std::endl;
    }
    std::istringstream issuser(suser.str());
    User newUser = readUser(issuser);
    users.push_back(newUser);
  }
}

std::string prefixDrop(std::string& str, std::string pref) {
  int begin = str.find(pref);
  if (begin + pref.size() < str.size()) {
    return str.substr(begin + pref.size());
  }
}

Book readBook(std::istringstream& sbook) {
  std::string title, author, strYear, isbn, strIsAvaible, BorrowedBy;
  std::string line;
  while (sbook >> line) {
    if (line.find("Title: ") == 0) {
      title = prefixDrop(line, "Title: ");
    } else if (line.find("Author: ") == 0) {
      author = prefixDrop(line, "Author ");
    } else if (line.find("Year: ") == 0) {
      strYear = prefixDrop(line, "Year: ");
    } else if (line.find("ISBN: ") == 0) {
      isbn = prefixDrop(line, "ISBN: ");
    } else if (line.find("BorrowedBy: ") == 0) {
      BorrowedBy = prefixDrop(line, "BorrowedBy");
    }
  }
  // Трансформация year
  int year = 0;
  try {
    year = stoi(strYear);
  } catch (...) {
    year = 0;
  }

  // Трансформация isAvaible
  bool isAvaible = false;
  std::transform(strIsAvaible.begin(), strIsAvaible.end(), strIsAvaible.begin(),
                 [](char c) { return std::tolower(c); });
  if (strIsAvaible == "yes" || strIsAvaible == "true" || strIsAvaible == "1") {
    isAvaible = true;
  }
  return Book(title, author, year, isbn, isAvaible, BorrowedBy);
}

User readUser(std::istringstream& suser) {
  std::string name, userId, strBorrowedBooks, strMaxBooks;
  std::string line;
  while (suser >> line) {
    if (line.find("Name: ")) {
      name = prefixDrop(line, "Name: ");
    } else if (line.find("UserID: ") == 0) {
      userId = prefixDrop(line, "UserID: ");
    } else if (line.find("BorrowedBooks: ") == 0) {
      strBorrowedBooks = prefixDrop(line, "BorrowedBooks: ");
    } else if (line.find("MaxBooks: ") == 0) {
      strMaxBooks = prefixDrop(line, "MaxBooks: ");
    }
  }
  std::vector<std::string> borrowedBooks;
  {
    std::string isbn;
    std::istringstream iss(strBorrowedBooks);
    while (std::getline(iss, isbn, '|')) {
      if (!isbn.empty()) {
        borrowedBooks.push_back(isbn);
      }
    }
  }
  int maxBooks = 3;
  try {
    maxBooks = stoi(strMaxBooks);
  } catch (...) {
    maxBooks = 3;
  }
  return User(name, userId, borrowedBooks, maxBooks);
}