#include <iostream>
#include <string>
#include <vector>

#include "Library.h"

/* printMenu: Вывод меню */
void printMenu();
/* getCommand: Получает номер команды из списка меню*/
int getCommand();
/* run; цикл с меню */
void run(Library& lib);
/* addBook: считывание и добавление книги */
void addBook(Library& lib);
/* addUser: считывание и добавление пользователя */
void addUser(Library& lib);
/* BookToUser: выдать книгу пользователю */
void BookToUser(Library& lib);
/* returnBook: вернуть книгу в библиотеку */
void returnBook(Library& lib);
/* searchByIsbn: поиск книги по ISBN */
void searchByIsbn(Library& lib);
/* searchByIsbn: поиск книги по ISBN */
void searchByName(Library& lib);
/* clearCin: очищает cin от лишних символов */
void clearCin();

int main() {
  try {
    Library lib("../data/library_data.txt");
    run(lib);
  } catch (std::exception& e) {
    std::cerr << "Критическая ошибка: " << e.what() << std::endl;
    return 1;
  } catch (...) {
    std::cerr << "Критическая ошибка" << std::endl;
    return 2;
  }
}

void run(Library& lib) {
  int cmd;
  while (true) {
    cmd = getCommand();
    switch (cmd) {
      case 1:
        std::cout << std::endl;
        lib.displayAllBooks();
        break;
      case 2:
        std::cout << std::endl;
        lib.displayAllUsers();
        break;
      case 3:
        addBook(lib);
        break;
      case 4:
        addUser(lib);
        break;
      case 5:
        BookToUser(lib);
        break;
      case 6:
        returnBook(lib);
        break;
      case 7:
        searchByIsbn(lib);
        break;
      case 8:
        searchByName(lib);
        break;
      case 9:
        lib.saveToFile();
        break;
      case 10:
        return;
      default:
        break;
    }
  }
}

void searchByName(Library& lib) {
  std::string name;
  std::cout << std::endl << "<--- ПОИСК ПОЛЬЗОВАТЕЛЯ --->" << std::endl;
  clearCin();
  std::cout << "Введите имя пользователя: ";
  std::getline(std::cin, name);
  try {
    User* b = lib.findUserByName(name);
    if (b)
      b->displayProfile();
    else
      std::cout << "Пользователь не найден!" << std::endl << std::endl;

  } catch (std::exception& e) {
    std::cout << "Ошибка поиска пользователя: " << e.what() << std::endl;
  }
}

void searchByIsbn(Library& lib) {
  std::string isbn;
  std::cout << std::endl << "<--- ПОИСК КНИГИ --->" << std::endl;
  clearCin();
  std::cout << "Введите ISBN книги: ";
  std::getline(std::cin, isbn);
  try {
    Book* b = lib.findBookByISBN(isbn);
    if (b)
      b->displayInfo();
    else
      std::cout << "Книга не найдена!" << std::endl << std::endl;

  } catch (std::exception& e) {
    std::cout << "Ошибка поиска книги: " << e.what() << std::endl;
  }
}

void BookToUser(Library& lib) {
  std::string isbn, name;
  std::cout << std::endl << "<--- ВЫДАЧА КНИГИ --->" << std::endl;
  clearCin();
  std::cout << "Введите имя пользователя: ";
  std::getline(std::cin, name);
  std::cout << "Введите ISBN книги: ";
  std::getline(std::cin, isbn);
  try {
    lib.borrowBook(name, isbn);
  } catch (std::exception& e) {
    std::cerr << "Ошибка выдачи книги: " << e.what() << std::endl << std::endl;
    return;
  }
  std::cout << "Книга выдана успешно!" << std::endl << std::endl;
}

void returnBook(Library& lib) {
  std::string isbn;
  std::cout << std::endl << "<--- ВОЗВРАТ КНИГИ --->" << std::endl;
  clearCin();
  std::cout << "Введите ISBN книги: ";
  std::getline(std::cin, isbn);
  try {
    lib.returnBook(isbn);
  } catch (std::exception& e) {
    std::cout << "Ошибка возврата книги: " << e.what() << std::endl;
  }
}

void addBook(Library& lib) {
  std::string title, author, strYear, isbn, strIsAvaible, BorrowedBy;
  std::string line;

  std::cout << std::endl << "<--- ДОБАВЛЕНИЕ КНИГИ --->" << std::endl;
  clearCin();
  std::cout << "Введите название: ";
  std::getline(std::cin, title);
  std::cout << "Введите автора: ";
  std::getline(std::cin, author);
  std::cout << "Введите год издания: ";
  std::getline(std::cin, strYear);
  std::cout << "Введите ISBN: ";
  std::getline(std::cin, isbn);
  std::cout << "Введите strIsAvaible (yes/no): ";
  std::getline(std::cin, strIsAvaible);

  // Трансформация isAvaible
  bool isAvaible = false;
  std::transform(strIsAvaible.begin(), strIsAvaible.end(), strIsAvaible.begin(),
                 [](char c) { return std::tolower(c); });
  if (strIsAvaible == "yes") {
    isAvaible = true;
  }
  if (!isAvaible) {
    std::cout << "Введите имя пользователя-обладателя: ";
    std::getline(std::cin, BorrowedBy);
  }

  // Трансформация year
  int year = 0;
  try {
    year = stoi(strYear);
  } catch (...) {
    year = 0;
  }
  std::cout << std::endl;
  try {
    Book newBook(title, author, year, isbn, isAvaible, BorrowedBy);
    lib.addBook(newBook);
  } catch (std::exception& e) {
    std::cerr << "Ошибка добавления книги: " << e.what() << std::endl
              << std::endl;
  }
}

void addUser(Library& lib) {
  std::string name, userId, strMaxBooks, strCountBooks;
  std::string line;

  std::cout << std::endl
            << std::endl
            << "<--- РЕГИСТРАЦИЯ ПОЛЬЗОВАТЕЛЯ --->" << std::endl;
  clearCin();
  std::cout << "Введите имя: ";
  std::getline(std::cin, name);
  std::cout << "Введите ID: ";
  std::getline(std::cin, userId);
  std::cout << "Введите макс. кол-во книг, которое может взять: ";
  std::getline(std::cin, strMaxBooks);
  int maxBooks = 3;
  try {
    maxBooks = stoi(strMaxBooks);
  } catch (...) {
    maxBooks = 3;
  }

  std::cout << "Введите количество книг, которое взял пользователь: ";
  std::getline(std::cin, strCountBooks);
  int countBooks = 0;
  try {
    countBooks = stoi(strCountBooks);
  } catch (...) {
    countBooks = 0;
  }
  if (countBooks > maxBooks)
    throw "Количество имеющихся книг у пользователя больше максимально разрешенного";
  std::string tmp;
  std::vector<std::string> borrowedBooks;
  for (int i = 0; i < countBooks; i++) {
    std::cout << "Введите ISBN (каждый с новой строки): ";
    std::getline(std::cin, tmp);
    borrowedBooks.push_back(tmp);
  }
  try {
    User newUser(name, userId, borrowedBooks, maxBooks);
    lib.addUser(newUser);
  } catch (std::exception& e) {
    std::cerr << "Ошибка добавления пользователя: " << e.what() << std::endl
              << std::endl;
  }
}

int getCommand() {
  std::string word;
  int val = -1;
  while (val == -1) {
    printMenu();
    std::cin >> word;
    try {
      val = stoi(word);
    } catch (...) {
      val = -1;
    }
  }
  return val;
}

void clearCin() {
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void printMenu() {
  std::cout << "=== БИБЛИОТЕКА ===" << std::endl;
  std::cout << "1. Просмотреть все книги" << std::endl;
  std::cout << "2. Просмотреть всех пользователей" << std::endl;
  std::cout << "3. Добавить новую книгу" << std::endl;
  std::cout << "4. Зарегистрировать пользователя" << std::endl;
  std::cout << "5. Выдать книгу пользователю" << std::endl;
  std::cout << "6. Принять книгу от пользователя" << std::endl;
  std::cout << "7. Поиск книги по ISBN" << std::endl;
  std::cout << "8. Просмотреть профиль пользователя" << std::endl;
  std::cout << "9. Сохранить данные в файл" << std::endl;
  std::cout << "10. Выход" << std::endl;
  std::cout << "Ваш выбор: ";
}