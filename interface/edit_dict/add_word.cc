/*
* M. ARYA PRAYOGA
* SUNDAY, 7 MARCH 2021
*
* Operation : add word to dictionary
*/

#include "my_dictionary/interface/edit_dict/add_word.h"

#include <iostream>
#include <string>

#include "my_dictionary/dictionary.h"
#include "my_dictionary/error.h"
#include "my_dictionary/word.h"

#include "my_dictionary/interface/auxiliary.h"

namespace my_dictionary {

// Prompt user to enter a new word-name, word-class, and word-meanings
// Add a new word specified by user to dict
void AddWord(Dictionary& dict) {
  ClearScreen();
  std::cout << "Adding word to dictionary \"" << dict.get_name() << "\"";

  // Prompt user to input word-name
  std::cout << "\n\nEnter a new word-name : ";
  std::string word_name;
  ClearNewline();   // Ignore previous newline
  std::getline(std::cin, word_name);
  if (!std::cin)
    throw BadInput("Error while reading input from user", std::cin);

  // Prompt user to input word class
  std::cout << "\nEnter a new word-class"
            << "\n1 = Verb; 2 = Noun; 3 = Adjective; 4 = Adverb"
            << "\n: ";
  int word_class{};
  std::cin >> word_class;
  if (!std::cin)
    throw BadInput("Error while reading input from user", std::cin);

  Word new_word(word_name, word_class);   // A new word

  // Prompt user to input word-meanings
  std::cout << "\nEnter word-meanings (1 meaning per line | '.' to finish) :\n";
  static const char kFinishAdding{'.'};
  while (true) {
    char opt{};
    std::string word_meaning;
    std::cin >> opt;
    if (!std::cin) {
      throw BadInput("Error while reading input from user", std::cin);
    } else if (opt == kFinishAdding) {
      break;
    } else {
      std::cin.unget();
      std::getline(std::cin, word_meaning);
      if (!std::cin)
        throw BadInput("Error while reading input from user", std::cin);

      // Adding word_meaning to new_word
      try {
        new_word.AddMeaning(word_meaning);
      } catch (Error& e) {
        e.Handle();
        WaitForButton();
        ClearScreen();
        std::cout << "\nEnter word-meanings (1 meaning per line | '.' to finish) :\n";
      }
    }
  }

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