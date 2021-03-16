/*
* M. ARYA PRAYOGA
* SUNDAY, 7 MARCH 2021
*
* Operation : add word to dictionary
*/

#include "my_dictionary/interface/edit_dict/add_word.h"

#include <cctype>

#include <iostream>
#include <string>

#include "my_dictionary/dictionary.h"
#include "my_dictionary/error.h"
#include "my_dictionary/word.h"

#include "my_dictionary/interface/auxiliary.h"
#include "my_dictionary/interface/edit.h"

namespace my_dictionary {

// Prompt user to enter a new word-name, word-class, and word-meanings
// Add a new word specified by user to dict
void AddWord(Dictionary& dict) {
  ClearScreen();
  std::cout << "Adding word to dictionary \"" << dict.get_name() << "\"";

  std::string word_name;
  GetWordName(word_name);

  int word_class{};
  GetWordClass(word_class);

  Word new_word(word_name, word_class);   // A new word

  PromptForMeaning();
  std::string word_meaning;
  while (true) {
    int get_word_meaning{GetWordMeaning(word_meaning)};

    if (get_word_meaning == kBreak) break;
    else if (get_word_meaning == kContinue) continue;

    // Adding word_meaning word w
    try {
      new_word.AddMeaning(word_meaning);
    } catch (Error& e) {
      e.Handle();
      WaitForButton();
      ClearScreen();
      PromptForMeaning();
    }
  }

  new_word.SortMeaning();   // Maintain lexicographical order for meanings

  try {
    dict.AddWord(new_word);    // Add a new word to dict

    // Report added word
    std::cout << "\n\nAdded word :" 
              << "\n* ";
    PrintWord(new_word, std::cout) << "\n";
    ClearNewline();
    WaitForButton();
  } catch (Error& e) {
    e.Handle();
    ClearNewline();
    WaitForButton();
  }
}

} // my_dictionary