/*
* M. ARYA PRAYOGA
* SUNDAY, 7 MARCH 2021
*
* Auxiliary function used in interface
*/

#ifndef MY_DICTIONARY_INTERFACE_AUXILIARY_H_
#define MY_DICTIONARY_INTERFACE_AUXILIARY_H_

#include <fstream>
#include <iostream>
#include <string>

#include "my_dictionary/dictionary.h"
#include "my_dictionary/error.h"

namespace my_dictionary {

// Read up to newline (discard newline)
inline void ClearNewline() {
  char ch{};
  while (std::cin.get(ch) && ch != '\n') { }
}

// Wait for user's respond
inline void WaitForButton() {
  std::cout << "\nPress Enter to continue!";
  char ch{};
  while (std::cin.get(ch) && ch != '\n') { }  // Read up to newline
}

// Clear screen (print 50 newlines)
inline void ClearScreen() {
  std::cout << std::string(50, '\n');
}

// Check the state of istream is after reading from is
// Throw BadInput with error message msg if is not in a good state
inline void CheckIstream(std::istream& is = std::cin, 
                         const std::string& msg = "Error while reading input from user") {
  if (!is)
    throw BadInput(msg, is);
}

inline void DictionaryModified(Dictionary& dict) {
  if (!dict.Modified())
    dict.set_mod(true);
}

} // my_dictionary

#endif  // MY_DICTIONARY_INTERFACE_AUXILIARY_H_