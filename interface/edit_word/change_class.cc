/*
* M. ARYA PRAYOGA
* TUESDAY, 9 MARCH 2021
*
* Operation : change classification for spesific word
*/

#include "my_dictionary/interface/edit_word/change_class.h"

#include <iostream>
#include <string>

#include "my_dictionary/error.h"
#include "my_dictionary/word.h"

#include "my_dictionary/interface/auxiliary.h"

namespace my_dictionary {

// Prompt the user to choose a new word-class
// Change the classification of w to word-class chosen by user
void ChangeClass(Word& w) {
  ClearScreen();
  std::cout << "Changing the classification of word \"" << w.get_name() << "\"";

  std::string old_word_class{w.WordClassToStr()};  // Old classification

  // Prompt user to choose new word-class
  std::cout << "\n\nChoose a new word-class :"
            << "\n1 = Verb; 2 = Noun; 3 = Adjective; 4 = Adverb"
            << "\n: ";
  int new_word_class{};
  std::cin >> new_word_class;
  if (!std::cin)
    throw BadInput("Error while reading input from user", std::cin);

  w.set_class(IntToWordClass(new_word_class));  // Change word-class to new_word_class

  // Report changed class
  std::cout << "\n\nOld class : " << old_word_class
            << "\nNew class : " << w.WordClassToStr()
            << "\n";
  WaitForButton();
}

} // my_dictionary