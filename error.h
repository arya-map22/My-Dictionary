/*
* M. ARYA PRAYOGA
* WEDNESDAY, 3 MARCH 2021
*
* Error handle classes for my_dictionary project
*/

#ifndef MY_DICTIONARY_ERROR_H_
#define MY_DICTIONARY_ERROR_H_

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

namespace my_dictionary {

// General error handle
class Error : public std::runtime_error {
 public:
  explicit Error(const std::string& msg)
    : std::runtime_error(msg) { }

  // Handle error
  void Handle() const;
};

// Handle for input error in istream is
class BadInput : public std::runtime_error {
 public:
  BadInput(const std::string& msg, std::istream& is)
    : std::runtime_error(msg), input_stream_(is) { }

  // Handle error in input_stream
  void Handle() const;

 private:
  std::istream& input_stream_;
};

// Handle I/O error in file
class FileError : public std::runtime_error {
 public:
  FileError(const std::string& msg, const std::string& fn)
    : std::runtime_error(msg), file_name_(fn) { }

  // Handle error
  void Handle() const; 

 private:
  std::string file_name_;
};

} // my_dictionary

#endif  // MY_DICTIONARY_ERROR_H_