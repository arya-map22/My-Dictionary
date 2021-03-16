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
#include "my_dictionary/interface/edit.h"

namespace my_dictionary {

// Prompt the user to choose a new word-class
// Change the classification of w to word-class chosen by user
void ChangeClass(Word& w) {
  ClearScreen();
  std::cout << "Changing the classification of word \"" << w.get_name() << "\"";

  const Word::WordClass old_word_class{w.get_class()};  // Old classification
  const std::string old_word_class_str{w.WordClassToStr()}; // Old classification as string

  int new_word_class{};
  GetWordClass(new_word_class);

  if (IntToWordClass(new_word_class) == old_word_class)
    throw Error("The new word-class can't be same with the old word-class");
  else
    w.set_class(IntToWordClass(new_word_class));  // Change word-class to new_word_class

  // Report changed class
  std::cout << "\n\nOld class : " << old_word_class_str
            << "\nNew class : " << w.WordClassToStr()
            << "\n";
  ClearNewline();
  WaitForButton();
}

} // my_dictionary