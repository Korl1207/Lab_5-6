#include "User.h"

User::User(std::string name, std::string userId,
           std::vector<std::string> borrowedBooks, int maxBooksAllowed = 3)
    : name(name),
      userId(userId),
      borrowedBooks(borrowedBooks),
      maxBooksAllowed(maxBooksAllowed) {};

// Getters
std::string User::getName() const { return name; }
std::string User::getUserId() const { return userId; }
std::vector<std::string> User::getBorrowedBooks() const {
  return borrowedBooks;
}
int User::getMaxBooksAllowed() const { return maxBooksAllowed; }

bool User::canBorrowMore() { return (maxBooksAllowed > borrowedBooks.size()); }

void User::addBook(const std::string& isbn) { borrowedBooks.push_back(isbn); }

void User::removeBook(const std::string isbn) {
  auto it = std::find(borrowedBooks.begin(), borrowedBooks.end(), isbn);
  if (it != borrowedBooks.end()) {
    borrowedBooks.erase(it);
    return;
  }
  throw std::runtime_error("У пользователя " + name + " нет книги " + isbn);
}
void User::displayProfile() {
  std::cout << "=== ПОЛЬЗОВАТЕЛЬ ===" << std::endl;
  std::cout << "Имя: " << name << std::endl;
  std::cout << "ID: " << userId << std::endl;
  std::cout << "Список взятых книг: ";
  if (borrowedBooks.size() == 0) {
    std::cout << "Список пуст" << std::endl;
  } else {
    for (size_t i = 0; i < borrowedBooks.size(); ++i)
      std::cout << borrowedBooks[i] << std::endl;
  }
  std::cout << "Максимум книг, которые может взять: " << maxBooksAllowed
            << std::endl
            << std::endl;
}
