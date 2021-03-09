/*
* M. ARYA PRAYOGA
* WEDNESDAY, 3 MARCH 2021
*
* Implementation file for Word class from word.h
*/

#include "my_dictionary/word.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "my_dictionary/error.h"

namespace my_dictionary {

// Construct Word from string and int
// initialize its name and classification (from int)
Word::Word(const std::string& wn, int wc)
  : name_(wn), classification_(IntToWordClass(wc)) { }

// Check if meaning wm already exist
bool Word::MeaningExist(const std::string& wm) const { 
  // Find meaning wm in the meanings vector
  if (std::find(meanings_.cbegin(), meanings_.cend(), wm) ==
      meanings_.cend()) {
    return false;   // Meaning m not found
  } else {
    return true;
  }
}

// Add meaning wm to Word
// Throw Error if meaning wm already exist
void Word::AddMeaning(const std::string& wm) {
  // Check if meaning m already exist
  if (MeaningExist(wm)) 
    throw Error("Meaning \""+wm+"\" already in word \""+name_+"\"");  // Throw Error
  
  meanings_.push_back(wm);  // Add meaning m
}

// Remove meaning wm from word
// Throw Error if meaning wm doesn't exist
void Word::RemoveMeaning(const std::string& wm) {
  for (auto it = meanings_.cbegin(); it != meanings_.cend(); ++it) {
    if (*it == wm) meanings_.erase(it);  // Remove meaning m
    return;
  }
  // Meaning m doesn't exist, throw Error
  throw Error("Meaning \""+wm+"\" doesn't exist in word \""+name_+"\"");
}

/* Return formatted meanings in string
* Format:
* - meaning 1
* - meaning 2
* ...
*/
std::string Word::get_meanings() const {
  std::ostringstream oss;   // Output string stream

  // Write formatted meanings to output string stream
  for (const auto& wm : meanings_) {
    oss << std::setw(4) << "- " << wm << "\n";
  }

  return oss.str();
}

// Return Word::WordClass as string
// kVerb == "Verb", kNoun == "Noun"
// kAdjective == "Adjective", kAdverb == "Adverb"
std::string Word::WordClassToStr() const {
  switch (classification_) {
    case Word::WordClass::kVerb:
      return "Verb";
    case Word::WordClass::kNoun:
      return "Noun";
    case Word::WordClass::kAdjective:
      return "Adjective";
    case Word::WordClass::kAdverb:
      return "Adverb";
    default:
      throw Error("Unknown word-class");
  }
}

/* Print formatted (human read) Word to os, return os
* Output format :
* word-name       (word-class)  :
*   - meaning 1
*   - meaning 2
*   ...
*/
std::ostream& PrintWord(const Word& w, std::ostream& os) {
  std::ostringstream oss;   // Output string stream
  oss << w.get_name() << std::setw(3)
    << "(" << w.WordClassToStr() << ") :\n"
    << w.get_meanings();

  os << oss.str();  // Write to ostream os
  return os;
}

// Return Word::WordClass as int
// kVerb == 1, kNoun == 2
// kAdjective == 3, kAdverb == 4
int Word::WordClassToInt() const {
  switch (classification_) {
    case Word::WordClass::kVerb:
      return 1;
    case Word::WordClass::kNoun:
      return 2;
    case Word::WordClass::kAdjective:
      return 3;
    case Word::WordClass::kAdverb:
      return 4;
    default:
      throw Error("Unknown word-class");
  }
}

/* Print Word in default format
* Default format:
* { word-name : word-class (int) : 
*   ( meaning 1 : meaning 2 : ... )
* }
*/
std::ostream& operator<<(std::ostream& os, const Word& w) {
  std::ostringstream oss;   // Output string stream
  
  // Print word-name and word-class
  oss << "{ " << w.name_ << " : " << w.WordClassToInt()
    << " :\n  ( ";

  // Print meanings
  for (decltype(w.meanings_.size()) ind = 0;
        ind != w.meanings_.size(); ++ind) {
    oss << w.meanings_[ind];
    if (ind != w.meanings_.size()-1) {   // Not last meaning
      oss << " : ";   // Print separator
    }
  }

  oss << " )\n}";
  os << oss.str();  // Write to ostream os
  return os;
}

// Convert int to Word::WordClass
// 1 == kVerb, 2 == kNoun, 
// 3 == kAdjective, 4 == kAdverb
Word::WordClass IntToWordClass(int n) {
  switch (n) {
    case 1:
      return Word::WordClass::kVerb;
    case 2:
      return Word::WordClass::kNoun;
    case 3:
      return Word::WordClass::kAdjective;
    case 4:
      return Word::WordClass::kAdverb;
    default:
      throw Error("Unknown word-class");
  }
}

// Auxiliary class for reading Word
struct Reading {
  std::string name;
  std::vector<std::string> meanings;
  Word::WordClass classification;
};

/* Read Word in default format
* Maintain meanings in lexicographical order
* Default format:
* { word-name : word-class (int) :
*   ( meaning 1 : meaning 2 : ... )
* }
*/
std::istream& operator>>(std::istream& is, Word& w) {
  Reading rw;           // Auxiliary class
  std::string text;     // Temporary string for reading input
  char sep{};           // Temporary char for reading input

  // Reading separator for start of the Word
  is >> sep;
  if (!is) return is;
  if (sep != '{') {
    is.clear(std::ios_base::failbit);
    throw BadInput("Bad start of Word", is);
  }

  // Reading word-name
  while (true) {
    is >> text;
    if (!is) return is;
    rw.name += text;

    is >> sep;
    if (!is) return is;

    if (sep == ':') break;  // Separator between word-name and word-class
    else is.unget();

    rw.name += " ";
  }

  // Reading word-class (int)
  int wc{};
  is >> wc;
  if (!is) return is;
  rw.classification = IntToWordClass(wc);

  // Reading separator between word-class and start of meanings
  is >> sep;
  if (!is) return is;
  if (sep != ':') {
    is.clear(std::ios_base::failbit);
    throw BadInput("Bad separator", is);
  }

  // Reading separator for start of the meanings
  is >> sep;
  if (!is) return is;
  if (sep != '(') {
    is.clear(std::ios_base::failbit);
    throw BadInput("Bad start of meanings", is);
  }

  // Reading meanings
  std::string meaning;
  while (true) {
    is >> text;
    if (!is) return is;
    meaning += text;

    is >> sep;
    if (!is) return is;
    if (sep == ')') {   // End of meanings
      rw.meanings.push_back(meaning);   // Save readed meaning
      break;
    } else if (sep == ':') {   // Separator between meanings
      rw.meanings.push_back(meaning);   // Save readed meaning
      meaning.clear();  // Empty string to read a new meaning
    } else {
      is.unget();
      meaning += " ";   // Meaning doesn't complete yet
    }
  }

  // Reading separator for end of the Word
  is >> sep;
  if (!is) return is;
  if (sep != '}')
    throw BadInput("Bad end of Word", is);

  w.name_ = rw.name; // Copy name from Reading to Word

  // Copy meanings from Reading to Word
  // Skip for the same meaning
  meaning.clear();
  for (const auto& wm : rw.meanings) {
    if (meaning == wm) continue;
    w.meanings_.push_back(wm);
    meaning = wm;
  }
  std::sort(w.meanings_.begin(), w.meanings_.end());  // Sort meanings

  // Copy classification from Reading to Word
  w.classification_ = rw.classification;
  return is;
}

} // my_dictionary