/*
* M. ARYA PRAYOGA
* SUNDAY, 7 MARCH 2021
*
* Auxiliary function used in interface
*/

#ifndef MY_DICTIONARY_INTERFACE_AUXILIARY_H_
#define MY_DICTIONARY_INTERFACE_AUXILIARY_H_

#include <iostream>
#include <string>

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

} // my_dictionary

#endif  // MY_DICTIONARY_INTERFACE_AUXILIARY_H_