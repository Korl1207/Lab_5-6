#ifndef Book_h
#define Book_h

#include <iostream>

class Book {
  std::string title;
  std::string author;
  int year;
  std::string isbn;
  bool isAvaible;
  std::string borrowedBy;

 public:
  Book(std::string title, std::string autor, int year, std::string isbn,
       bool isAbaible, std::string borrowedBy);
  // Getters
  std::string getTitle() const;
  std::string getAuthor() const;
  int getYear() const;
  std::string getIsbn() const;
  bool getIsAvaible() const;
  std::string getBorrowedBy() const;

  void borrowBook(const std::string& userName);
  void returnBook();
  void displayInfo();
};

#endif  // Book_h