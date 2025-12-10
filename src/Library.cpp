#include "Library.h"

#include <algorithm>
#include <fstream>
#include <sstream>

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
void Library::saveToFile() {}
void Library::loadFromFile() {
  std::ifstream inputFile(dataFile);
  if (!inputFile.is_open()) {
    throw std::invalid_argument("Не удалось открыть файл с именем " + dataFile);
  }
  std::string buf;
  while (std::getline(inputFile, buf)) {
    std::istringstream sbuf(buf);
    std::string word;
  }
}
int main() {}