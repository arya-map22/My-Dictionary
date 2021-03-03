/*
* M. ARYA PRAYOGA
* WEDNESDAY, 3 MARCH 2021
*
* Implementation file for Word class from word.h
*/

#include "my_dictionary/word.h"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "my_dictionary/error.h"

namespace my_dictionary {

// Check if meaning m already exist
bool Word::MeaningExist(const std::string& m) const { 
  // Find meaning m in the meanings vector
  if (std::find(meanings.cbegin(), meanings.cend(), m) ==
      meanings.cend()) {
    return false;   // Meaning m not found
  } else {
    return true;
  }
}

// Add meaning m to Word
// Check if meaning m already exist
void Word::AddMeaning(const std::string& m) {
  // Check if meaning m already exist
  if (MeaningExist(m)) 
    throw Error("Meaning \""+m+"\" already in word \""+name+"\"");  // Throw Error
  
  meanings.push_back(m);  // Add meaning m
}

// Remove meaning m from word
// Check if meaning m exist or not
void Word::RemoveMeaning(const std::string& m) {
  for (auto it = meanings.cbegin(); it != meanings.cend(); ++it) {
    if (*it == m) meanings.erase(it);  // Remove meaning m
  }

  // Meaning m doesn't exist, throw Error
  throw Error("Meaning \""+m+"\" doesn't exist in word \""+name+"\"");
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
  for (const auto& m : meanings) {
    oss << " - " << m << "\n";
  }

  return oss.str();
}

// Convert Word::WordClass to string
std::string WordClassToStr(Word::WordClass wc) {
  switch (wc) {
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
  oss << w.get_name() << "\t\t"
    << "(" << WordClassToStr(w.get_class()) << ") :\n"
    << w.get_meanings();

  os << oss.str();  // Write to ostream os
  return os;
}

// Convert Word::WordClass to int
// kVerb == 1, kNoun == 2
// kAdjective == 3, kAdverb == 4
int WordClassToInt(Word::WordClass wc) {
  switch (wc) {
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
*   ( meaning 1 : meaning 2 : ...: )
* }
*/
std::ostream& operator<<(std::ostream& os, const Word& w) {
  std::ostringstream oss;   // Output string stream
  
  // Print word-name and word-class
  oss << "{ " << w.name << " : " << WordClassToInt(w.classification)
    << " :\n  ( ";

  // Print meanings
  for (const auto& m : w.meanings) {
    oss << m << " : ";
  }

  oss << ")\n}";
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

// Auxiliary type for reading Word
struct Reading {
  std::string name;
  std::vector<std::string> meanings;
  Word::WordClass classification;
};

/* Read Word in default format
* Default format:
* { word-name : word-class (int) :
*   ( meaning 1 : meaning 2 : ... : )
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

  // Reading Word.name
  while (true) {
    is >> text;
    if (!is) return is;
    rw.name += text;

    is >> sep;
    if (!is) return is;

    if (sep == ':') break;
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
    if (sep == ':') {   // Separator between meanings
      rw.meanings.push_back(meaning);   // Save readed meaning

      is >> sep;
      if (!is) return is;
      if (sep == ')') break;  // End of meanings
      else is.unget();

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

  w.name = rw.name; // Copy name from Reading to Word

  // Copy meanings from Reading to Word
  // Skip for the same meaning
  meaning.clear();
  for (const auto& m : rw.meanings) {
    if (meaning == m) continue;
    w.meanings.push_back(m);
    meaning = m;
  }

  // Copy classification from Reading to Word
  w.classification = rw.classification;
  return is;
}

} // my_dictionary