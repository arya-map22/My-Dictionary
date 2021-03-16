/*
* M. ARYA PRAYOGA
* MONDAY, 8 MARCH 2021
*
* Operation : add meanings to spesific word
*/

#include "my_dictionary/interface/edit_word/add_meaning.h"

#include <cctype>

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "my_dictionary/error.h"
#include "my_dictionary/word.h"

#include "my_dictionary/interface/auxiliary.h"
#include "my_dictionary/interface/edit.h"

namespace my_dictionary {

// Prompt user to enter new meanings for word w
// Add that meanings to word w
void AddMeaning(Word& w) {
  ClearScreen();
  std::cout << "Adding meanings to word \"" << w.get_name() << "\"";

  size_t meanings_added_count{0};           // The number of meanings that successfully added
  std::vector<std::string> meanings_added;  // All meanings that successfully added
  
  PromptForMeaning();
  while (true) {
    std::string word_meaning;
    int get_word_meaning{GetWordMeaning(word_meaning)};

    if (get_word_meaning == kBreak) break;
    else if (get_word_meaning == kContinue) continue;

    // Add word_meaning to w
    try {
      w.AddMeaning(word_meaning);
      ++meanings_added_count;
      meanings_added.push_back(word_meaning);
    } catch (Error& e) {
      e.Handle();
      --meanings_added_count;
      meanings_added.pop_back();
      WaitForButton();
      ClearScreen();
      PromptForMeaning();
    }
  }

  // Report added meanings
  std::cout << "\n\n" << meanings_added_count << " meanings added :\n";
  for (const auto& wm : meanings_added) {
    std::cout << std::setw(4) << "- " << wm << "\n";
  }
  ClearNewline();
  WaitForButton();
}

} // my_dictionary