/*
* M. ARYA PRAYOGA
* SUNDAY, 7 MARCH 2021
*
* Implementation file for main_interface.h
* Operations :
*   - Show quick list of words and their class(verb, noun, adjective, or adverb)
*   - Show complete list of words, their class, and their meanings
*   - Search for spesific word by name
*   - Edit dictionary :
*     - Add word
*     - Remove word
*     - Edit spesific word :
*       - Change its name
*       - Change its class
*       - Add meaning
*       - Remove meaning
*/

#include "my_dictionary/interface/main_interface.h"

#include <cctype>

#include <iostream>
#include <string>

#include "my_dictionary/dictionary.h"
#include "my_dictionary/error.h"

#include "my_dictionary/interface/auxiliary.h"
#include "my_dictionary/interface/edit.h"

#include "my_dictionary/interface/edit_dict/add_word.h"
#include "my_dictionary/interface/edit_dict/remove_word.h"
#include "my_dictionary/interface/edit_dict/save_modification.h"

#include "my_dictionary/interface/edit_word/add_meaning.h"
#include "my_dictionary/interface/edit_word/change_name.h"
#include "my_dictionary/interface/edit_word/change_class.h"
#include "my_dictionary/interface/edit_word/remove_meaning.h"

namespace my_dictionary {

Dictionary my_dict("my_dict.txt");

// Show menu for my_dictionary program
void ShowMenu() {
  ClearScreen();
  std::cout << "******************| Welcome to my_dictionary v1.1! |******************"
            << "\n\nMain menu : "
            << "\n1.) Show quick list"
            << "\n2.) Show complete list"
            << "\n3.) Find a word"
            << "\n4.) Edit"
            << "\n\nEnter your option ('q' to exit program) : ";
}

void ShowQuickList(const Dictionary& dict = my_dict);
void ShowCompleteList(const Dictionary& dict = my_dict);
void FindAWord(const Dictionary& dict = my_dict);
void EditDict(Dictionary& dict = my_dict);
void ExitProgram();

// Eval chosen option by user
void EvalOption(char opt) {
  switch(std::tolower(opt)) {
    case '1':
      ShowQuickList();
      break;
    case '2':
      ShowCompleteList();
      break;
    case '3':
      FindAWord();
      break;
    case '4':
      EditDict();
      break;
    case kExit:
      ExitProgram();
      break;
    default:
      throw Error("Invalid option");
  }
}

/**************************************************************************************************/

/* Show quick list of words
* Output format :
*   1.) word-name   (word-class)
*   ...
*   Dictionary : dict-name
*   Word       : dict-word_count words
*/
void ShowQuickList(const Dictionary& dict) {
  ClearScreen();
  ShowDictionary(dict, std::cout);
  std::cout << "\nDictionary : " << dict.get_name()
            << "\nWord       : " << dict.WordCount() << " words\n";
  ClearNewline();
  WaitForButton();
}

/* Show complete list of words
* Output format :
*   1.) word-name   (word-class) :
*      - meaning 1
*      - meaning 2
*     ...
*   Dictionary : dict-name
*   Word       : dict-word_count words
*/
void ShowCompleteList(const Dictionary& dict) {
  ClearScreen();
  PrintDictionary(dict, std::cout);
  std::cout << "\nDictionary : " << dict.get_name()
            << "\nWord       : " << dict.WordCount() << " words\n";
  ClearNewline();
  WaitForButton();
}

// Prompt user for word-name and show its content from dictionary dict
// Throw Error if word-name doesn't exist
void FindAWord(const Dictionary& dict) {
  try {
    ClearScreen();
    std::string word_name;
    GetWordName(word_name);

    std::cout << "\n* ";
    PrintWord(dict.get_word(word_name), std::cout);
    WaitForButton();
  } catch (Error& e) {
    e.Handle();
    WaitForButton();
  }
}

// Print good bye message and exit program
// Warn user if dictionary modified
void ExitProgram() {
  ClearScreen();
  if (my_dict.Modified()) {
    std::cout << "Warning : you have unsaved modification"
              << "\nDo you want to save before exit? (y/n) : ";
    char opt{};
    std::cin >> opt;
    CheckIstream();
    if (std::tolower(opt) == 'y')
      SaveModification(my_dict);
    else if (std::tolower(opt) != 'n')
      throw Error("Invalid option");
  }

  ClearScreen();
  std::cout << "***********| Thank you for using my_dictionary v1.1, see you! |**********\n"
            << "***********|              by M. Arya Prayoga                  |**********\n";
  exit(EXIT_SUCCESS);
}

/**************************************************************************************************/

void EditWord(Dictionary& dict);

// Print menu for editting dictionary dict
void ShowMenuEditDict(const Dictionary& dict) {
  ClearScreen();
  std::cout << "Dictionary    : " << dict.get_name()
            << "\nWord          : " << dict.WordCount() << " words"
            << "\nModified      : " << (dict.Modified() ? "Yes" : "No")
            << "\n\nMenu for editting dictionary : "
            << "\n1.) Add word"
            << "\n2.) Remove word"
            << "\n3.) Edit word"
            << "\n4.) Save modification"
            << "\n5.) Preview dictionary"
            << "\n\nEnter your option ('q' to quit editting dictionary) : ";
}

// Print menu for editting dictionary dict and
// perform spesific operation based on chosen option by user
void EditDict(Dictionary& dict) {
  while (true) {
    try {
      ShowMenuEditDict(dict);
      char opt{};
      std::cin >> opt;
      CheckIstream();

      switch (std::tolower(opt)) {
        case '1':
          AddWord(dict);
          DictionaryModified(dict);
          break;
        case '2':
          RemoveWord(dict);
          DictionaryModified(dict);
          break;
        case '3':
          EditWord(dict);
          break;
        case '4':
          SaveModification(dict);
          break;
        case '5':
          ShowCompleteList(dict);
          break;
        case kExit:
          return;
        default:
          throw Error("Invalid option");
      }
    } catch (Error& e) {
      e.Handle();
      ClearNewline();
      WaitForButton();
    } catch (BadInput& e) {
      e.Handle();
      WaitForButton();
    }
  }
}

// Print menu for editting word w
void ShowMenuEditWord(const Word& w) {
  ClearScreen();
  std::cout << "Word-name   : " << w.get_name()
            << "\nWord-class  : " << w.WordClassToStr()
            << "\n\nMenu for editting word : "
            << "\n1.) Change name"
            << "\n2.) Change class"
            << "\n3.) Add meaning"
            << "\n4.) Remove meaning"
            << "\n5.) Preview word"
            << "\n\nEnter your option ('q' to quit editting word) : ";
}

// Print menu for editiing word w and
// perform spesific operation based on chosen option by user
void EditWord(Dictionary& dict) {
  std::string word_name;
  GetWordName(word_name);

  Word& w{dict.get_word(word_name)};
  while (true) {
    try {
      ShowMenuEditWord(w);
      char opt{};
      std::cin >> opt;
      CheckIstream();

      switch (std::tolower(opt)) {
        case '1':
          ChangeName(w);
          DictionaryModified(dict);
          break;
        case '2':
          ChangeClass(w);
          DictionaryModified(dict);
          break;
        case '3':
          AddMeaning(w);
          DictionaryModified(dict);
          break;
        case '4':
          RemoveMeaning(w);
          DictionaryModified(dict);
          break;
        case '5':
          ClearScreen();
          std::cout << "* ";
          PrintWord(w, std::cout) << "\n";
          ClearNewline();
          WaitForButton();
          break;
        case kExit:
          return;
        default:
          throw Error("Invalid option");
      }
    } catch (Error& e) {
      e.Handle();
      ClearNewline();
      WaitForButton();
    } catch (BadInput& e) {
      e.Handle();
      WaitForButton();
    }
  }
}

} // my_dictionary