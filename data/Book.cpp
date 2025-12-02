#include "Book.h"

#include <iostream>

Book::Book(std::string title, std::string autor, int year, std::string isbn,
           bool isAvaible, std::string borrowedBy)
    : title(title),
      author(author),
      year(year),
      isbn(isbn),
      isAvaible(isAvaible),
      borrowedBy(borrowedBy) {
  if (year < 1450 || year > 2025)
    throw std::invalid_argument("Некорректный год издания у книги " + title +
                                " автора " + autor);
}

// Getters
std::string& Book::getTitle() { return title; };
std::string Book::getTitle() const { return title; };
std::string& Book::getAuthor() { return author; };
std::string Book::getAuthor() const { return author; };
int& Book::getYear() { return year; };
int Book::getYear() const { return year; };
std::string& Book::getIsbn() { return isbn; };
std::string Book::getIsbn() const { return isbn; };
bool& Book::getIsAvaible() { return isAvaible; };
bool Book::getIsAvaible() const { return isAvaible; };
std::string& Book::getBorrowedBy() { return borrowedBy; };
std::string Book::getBorrowedBy() const { return borrowedBy; };

void Book::borrowBook(const std::string& userName) {
  if (!isAvaible)
    throw std::invalid_argument("Книга " + title + " не доступна для выдачи");
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
  std::cout << "BOOK" << std::endl;
  std::cout << "Title: " << title << std::endl;
  std::cout << "Author: " << author << std::endl;
  std::cout << "Year: " << year << std::endl;
  std::cout << "ISBN: " << isbn << std::endl;
  std::cout << "Avaible: " << ((isAvaible) ? "yes" : "no") << std::endl;
  std::cout << "BorrowedBy" << ((isAvaible) ? "" : borrowedBy) << std::endl;
}