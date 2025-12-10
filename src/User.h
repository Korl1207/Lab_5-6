#ifndef User_h
#define User_h

#include <iostream>
#include <vector>

class User {
  std::string name;
  std::string userId;
  std::vector<std::string> borrowedBooks;
  int maxBooksAllowed;

 public:
  User(std::string name, std::string userId,
       std::vector<std::string> borrowedBooks, int maxBooksAllowed);

  // Getters
  std::string getName() const;
  std::string getUserId() const;
  std::vector<std::string> getBorrowedBooks() const;
  int getMaxBooksAllowed() const;

  bool canBorrowMore();
  void addBook(const std::string& isbn);
  void removeBook(const std::string isbn);
  void displayProfile();
};

#endif  // User_h