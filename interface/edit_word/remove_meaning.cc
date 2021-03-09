/*
* M. ARYA PRAYOGA
* TUESDAY, 9 MARCH 2021
*
* Operation : remove meanings for spesific word
*/

#include "my_dictionary/interface/edit_word/remove_meaning.h"

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "my_dictionary/error.h"
#include "my_dictionary/word.h"

#include "my_dictionary/interface/auxiliary.h"

namespace my_dictionary {

// Prompt user to enter meanings to removed from word w
// Remove that meanings from word w
void RemoveMeaning(Word& w) {
  ClearScreen();
  std::cout << "Removing meanings to word \"" << w.get_name() << "\"";

  // Prompt user to input new meanings
  std::cout << "\n\nEnter meanings to remove (1 meaning per line | '.' to finish) :\n"; 
  static const char kFinishRemoving{'.'};     // Finish removing
  size_t meanings_count{0};                   // The number of meanings that successfully removed
  std::vector<std::string> meanings_removed;  // All meanings that successfully removed
  while (true) {
    char opt{};
    std::string word_meaning;   // To read word-meaning
    std::cin >> opt;
    if (!std::cin) {
      throw BadInput("Error while reading input from user", std::cin);
    } else if (opt == kFinishRemoving) {
      break;
    } else {
      std::cin.unget();
      std::getline(std::cin, word_meaning);
      if (!std::cin)
        throw BadInput("Error while reading input from user", std::cin);

      // Remove word_meaning from w
      try {
        w.RemoveMeaning(word_meaning);
        ++meanings_count;
        meanings_removed.push_back(word_meaning);
      } catch (Error& e) {
        e.Handle();
        --meanings_count;
        meanings_removed.pop_back();
      }
    }
  }

  // Report removed meanings
  std::cout << "\n\n" << meanings_count << " meanings removed :\n";
  for (const auto& wm : meanings_removed) {
    std::cout << std::setw(4) << "- " << wm << "\n";
  }
  WaitForButton();
}

} // my_dictionary