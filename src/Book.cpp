#include "Book.h"

Book::Book(std::string title, std::string author, int year, std::string isbn,
           bool isAvaible, std::string borrowedBy)
    : title(title),
      author(author),
      year(year),
      isbn(isbn),
      isAvaible(isAvaible),
      borrowedBy(borrowedBy) {
  if (year < 1450 || year > 2025)
    throw std::invalid_argument("Некорректный год издания у книги " + title +
                                " автора " + author);
}

// Getters
std::string Book::getTitle() const { return title; };
std::string Book::getAuthor() const { return author; };
int Book::getYear() const { return year; };
std::string Book::getIsbn() const { return isbn; };
bool Book::getIsAvaible() const { return isAvaible; };
std::string Book::getBorrowedBy() const { return borrowedBy; };

void Book::borrowBook(const std::string& userName) {
  this->isAvaible = false;
  this->borrowedBy = userName;
}

void Book::returnBook() {
  if (isAvaible)
    throw std::invalid_argument(
        "Книга " + title +
        " не может быть возвращена, так как никому не выдана");
  borrowedBy = "";
  isAvaible = true;
}

void Book::displayInfo() {
  std::cout << "=== КНИГА ===" << std::endl;
  std::cout << "Название: " << title << std::endl;
  std::cout << "Автор: " << author << std::endl;
  std::cout << "год издания: " << year << std::endl;
  std::cout << "ISBN: " << isbn << std::endl;
  std::cout << "Можно ли взять: " << ((isAvaible) ? "yes" : "no") << std::endl;
  std::cout << "Кто взял: " << ((isAvaible) ? "" : borrowedBy) << std::endl
            << std::endl;
}