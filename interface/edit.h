/*
* M. ARYA PRAYOGA
* TUESDAY, 16 MARCH 2021
*
* Helper function used for editting in my_dictionary program
*/

#ifndef MY_DICTIONARY_INTERFACE_EDIT_H_
#define MY_DICTIONARY_INTERFACE_EDIT_H_

#include <string>

#include "my_dictionary/word.h"

namespace my_dictionary {

const char kFinishEditMeaning{'.'};
const int kBreak{1};
const int kContinue{2};

// Get word-name from user
void GetWordName(std::string& word_name);

// Get word-class (int) from user
void GetWordClass(int& word_class);

// Get word-meanings from user and add them to new_word
int GetWordMeaning(std::string& word_meaning);

// Prompt for get word-meaning
inline void PromptForMeaning() {
  std::cout << "\nEnter word-meanings (1 meaning per line | "
            << kFinishEditMeaning << " to finish) :\n";
}

} // my_dictionary

#endif // MY_DICTIONARY_INTERFACE_EDIT_H_