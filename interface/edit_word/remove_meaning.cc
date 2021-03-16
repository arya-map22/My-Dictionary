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
#include "my_dictionary/interface/edit.h"

namespace my_dictionary {

// Prompt user to enter meanings to removed from word w
// Remove that meanings from word w
void RemoveMeaning(Word& w) {
  ClearScreen();
  std::cout << "Removing meanings to word \"" << w.get_name() << "\"";

  std::vector<std::string> meanings_removed;  // All meanings that successfully removed

  PromptForMeaning();
  std::string word_meaning;
  while (true) {
    int get_word_meaning{GetWordMeaning(word_meaning)};

    if (get_word_meaning == kBreak) break;
    else if (get_word_meaning == kContinue) continue;

    // Remove word_meaning from w
    try {
      meanings_removed.push_back(word_meaning);
      w.RemoveMeaning(word_meaning);
    } catch (Error& e) {
      e.Handle();
      meanings_removed.pop_back();
      WaitForButton();
      ClearScreen();
      PromptForMeaning();
    }
  }

  w.SortMeaning();  // Maintain lexicographical order for meanings

  // Report removed meanings
  std::cout << "\n\n" << meanings_removed.size() << " meanings removed :\n";
  for (const auto& wm : meanings_removed) {
    std::cout << std::setw(4) << "- " << wm << "\n";
  }
  ClearNewline();
  WaitForButton();
}

} // my_dictionary