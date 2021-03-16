/*
* M. ARYA PRAYOGA
* SUNDAY, 7 MARCH 2021
*
* Operation : remove word from dictionary
*/

#include "my_dictionary/interface/edit_dict/remove_word.h"

#include <iostream>
#include <string>

#include "my_dictionary/dictionary.h"
#include "my_dictionary/error.h"

#include "my_dictionary/interface/auxiliary.h"
#include "my_dictionary/interface/edit.h"

namespace my_dictionary {

// Prompt user to enter word-name
// Remove that word from dict
void RemoveWord(Dictionary& dict) {
  ClearScreen();
  std::cout << "Removing word from dictionary \"" << dict.get_name() << "\"";

  std::string word_name;
  GetWordName(word_name);

  try {
    dict.RemoveWord(word_name);     // Remove word from dict
    if (!dict.Modified())
      dict.set_mod(true);

    // Report removed word
    std::cout << "\n\nWord \"" << word_name << "\" removed";
    WaitForButton();
  } catch (Error& e) {
    e.Handle();
    WaitForButton();
  }
}

} // my_dictionary