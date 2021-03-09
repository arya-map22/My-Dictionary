/*
* M. ARYA PRAYOGA
* MONDAY, 8 MARCH 2021
*
* Operation : add meanings to spesific word
*/

#include "my_dictionary/interface/edit_word/add_meaning.h"

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "my_dictionary/error.h"
#include "my_dictionary/word.h"

#include "my_dictionary/interface/auxiliary.h"

namespace my_dictionary {

// Prompt user to enter new meanings for word w
// Add that meanings to word w
void AddMeaning(Word& w) {
  ClearScreen();
  std::cout << "Adding meanings to word \"" << w.get_name() << "\"";

  // Prompt user to input new meanings
  std::cout << "\n\nEnter new meanings (1 meaning per line | '.' to finish) :\n"; 
  static const char kFinishAdding{'.'};     // Finish adding
  size_t meanings_count{0};                 // The number of meanings that successfully added
  std::vector<std::string> meanings_added;  // All meanings that successfully added
  while (true) {
    char opt{};
    std::string word_meaning;   // To read word-meaning
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

      // Add word_meaning to w
      try {
        w.AddMeaning(word_meaning);
        ++meanings_count;
        meanings_added.push_back(word_meaning);
      } catch (Error& e) {
        e.Handle();
        --meanings_count;
        meanings_added.pop_back();
      }
    }
  }

  // Report added meanings
  std::cout << "\n\n" << meanings_count << " meanings added :\n";
  for (const auto& wm : meanings_added) {
    std::cout << std::setw(4) << "- " << wm << "\n";
  }
  WaitForButton();
}

} // my_dictionary