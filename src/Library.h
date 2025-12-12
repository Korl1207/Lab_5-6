#ifndef Library_h
#define Library_h

#include <iostream>
#include <vector>

#include "Book.h"
#include "User.h"

class Library {
  std::vector<Book> books;
  std::vector<User> users;
  std::string dataFile;

 public:
  Library(std::string dataFile);
  void addBook(const Book& book);
  void addUser(const User& user);
  void returnBook(const std::string& isbn);
  Book* findBookByISBN(const std::string& isbn);
  User* findUserByName(const std::string& name);
  User* findUserByUserID(const std::string& UserId);
  void borrowBook(const std::string& userName, const std::string& isbn);
  void displayAllBooks();
  void displayAllUsers();
  void saveToFile();
  void loadFromFile();
};

#endif  // Library_h