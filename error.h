/*
* M. ARYA PRAYOGA
* WEDNESDAY, 3 MARCH 2021
*
* Error handle classes for my_dictionary project
*/

#ifndef MY_DICTIONARY_ERROR_H_
#define MY_DICTIONARY_ERROR_H_

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
  virtual void Handle() const;
};

// Handle for input error in stream is
class BadInput : public Error {
 public:
  BadInput(const std::string& msg, std::istream& is)
    : Error(msg), input_stream_(is) { }

  // Handle error in input_stream
  void Handle() const override;

 private:
  std::istream& input_stream_;
};

} // my_dictionary

#endif  // MY_DICTIONARY_ERROR_H_