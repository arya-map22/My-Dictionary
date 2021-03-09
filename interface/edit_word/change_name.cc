/*
* M. ARYA PRAYOGA
* MONDAY, 8 MARCH 2021
*
* Operation : change the name of spesific word
*/

#include "my_dictionary/interface/edit_word/change_name.h"

#include <iostream>
#include <string>

#include "my_dictionary/error.h"
#include "my_dictionary/word.h"

#include "my_dictionary/interface/auxiliary.h"

namespace my_dictionary {

// Prompt user to enter a new word-name
// Change the name of w to word-name entered by user
void ChangeName(Word& w) {
  ClearScreen();
  std::cout << "Changing the name of word \"" << w.get_name() << "\"";

  const std::string old_word_name{w.get_name()};  // Old name

  // Prompt user to input a new word-name
  std::cout << "\n\nEnter a new word-name : ";
  std::string new_word_name;
  std::cin.ignore();  // Ignore previous newline
  std::getline(std::cin, new_word_name);
  if (!std::cin)
    throw BadInput("Error while reading input from user", std::cin);

  w.set_name(new_word_name);  // Change word-name to new_word_name

  // Report changed word
  std::cout << "\n\nOld name  : " << old_word_name
            << "\nNew name  : " << new_word_name
            << "\n";
  WaitForButton();
}

} // my_dictionary