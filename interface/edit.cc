/*
* M. ARYA PRAYOGA
* TUESDAY, 16 MARCH 2021
*
* Implementation file for edit.h
*/

#include "my_dictionary/interface/edit.h"

#include <iostream>
#include <string>

#include "my_dictionary/dictionary.h"
#include "my_dictionary/error.h"
#include "my_dictionary/word.h"

#include "my_dictionary/interface/auxiliary.h"

namespace my_dictionary {

// Get word-name from user
void GetWordName(std::string& word_name) {
  std::cout << "\n\nEnter a new word-name : ";
  char first_word{};

  ClearNewline();   // Ignore previous newline
  std::cin >> first_word;
  CheckIstream();

  // If start of word-name isn't an alphabet then throw BadInput
  if (!std::isalpha(first_word)) {
    std::cin.clear(std::ios_base::failbit);
    throw BadInput("Start of word-name must be an alphabet", std::cin);
  } else {
    std::cin.unget();   // Putback readed char
  }

  std::getline(std::cin, word_name);  // Read the word-name
  CheckIstream();
}

// Get word-class (int) from user
// 1 == kVerb, 2 == kNoun
// 3 == kAdjective, 4 == kAdverb
void GetWordClass(int& word_class) {
  std::cout << "\n\nEnter a new word-class"
            << "\n1 = Verb; 2 = Noun; 3 = Adjective; 4 = Adverb"
            << "\n: ";
  std::cin >> word_class;
  CheckIstream();
}

// Get word-meanings from user and add them to new_word
int GetWordMeaning(std::string& word_meaning) {
  char opt{};
  std::cin >> opt;
  CheckIstream();

  if (opt == kFinishEditMeaning) {
    return kBreak;
  } else if (!std::isalpha(opt)) {  // If start of word-meaning isn't an alphabet then throw BadInput
    try {
      std::cin.clear(std::ios_base::failbit);
      throw BadInput("Start of word-meaning must be an alphabet", std::cin);
    } catch (BadInput& e) {
      e.Handle();
      WaitForButton();
      ClearScreen();
      PromptForMeaning();
      return kContinue;   // Start from the beginning of loop
    }
  } else {
    std::cin.unget();
    std::getline(std::cin, word_meaning);
    CheckIstream();
    return 0;
  }
}

} // my_dictionary