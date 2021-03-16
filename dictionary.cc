/*
* M. ARYA PRAYOGA
* THURSTDAY, 4 MARCH 2021
*
* Implementation for Dictionary class in file Dictionary.h
*/

#include "my_dictionary/dictionary.h"

#include <iomanip>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <utility>

#include "my_dictionary/error.h"
#include "my_dictionary/word.h"

namespace my_dictionary {

// Fill the dictionary dict from file file_name
void LoadDictFromFile(Dictionary& dict, const std::string& file_name) {
  std::ifstream dict_file{file_name};
  if (!dict_file)
    throw FileError("Can't open file", file_name);

  while (true) {
    Word tmp;
    dict_file >> tmp;
    if (dict_file.eof())
      break;
    else if (!dict_file)
      throw FileError("Error while reading file", dict.get_file_name());

    dict.AddWord(tmp);
  }
}

// Save modification in dictionary dict to file file_name
void SaveDictToFIle(Dictionary& dict, const std::string& file_name) {
  if (!dict.Modified()) return;

  std::ofstream dict_file(file_name);
  if (!dict_file)
    throw FileError("Can't open file", file_name);

  std::ostringstream oss;
  for (const auto& p : dict.words_) {
    oss << p.second << "\n";
    if (!oss)
      throw FileError("Error while writing to file", file_name);
  }

  dict_file << oss.str();
  if (!dict_file)
    throw FileError("Error while writing to file", file_name);

  dict.set_mod(false);
}

// Remove suffix from string str
inline std::string RemoveSuffix(const std::string& str) {
  auto pos{str.find('.')};
  return str.substr(0, pos);
}

// Construct dictionary with name dn from file fn
Dictionary::Dictionary(const std::string& dn, const std::string& fn)
    : dict_name_(dn), file_name_(fn) {
  try {
    LoadDictFromFile(*this, file_name_);
  } catch (FileError& e) {
    e.Handle();
  }
}

// Default constructor
Dictionary::Dictionary()
    : Dictionary("dictionary", "dictionary.txt") { }

// Construct dictionary from file name fn
Dictionary::Dictionary(const std::string& fn)
    : Dictionary(RemoveSuffix(fn), fn) { }

// Check if Word w exist or not
bool Dictionary::WordExist(const std::string& w) const {
  if (words_.find(w) == words_.cend()) return false;
  else return true;
}

// Return reference to Word at word-name w
// Throw Error if w not found
Word& Dictionary::get_word(const std::string& w) {
  if (!WordExist(w))
    throw Error("Word \""+w+"\" doesn't exist");
  return words_.at(w);
}

// Return const reference to Word at word-name w
// Throw Error if w not found
const Word& Dictionary::get_word(const std::string& w) const {
  if (!WordExist(w))
    throw Error("Word \""+w+"\" doesn't exist");
  return words_.at(w);
}

// Add Word w, throw Error if w already exist
void Dictionary::AddWord(const Word& w) {
  if (WordExist(w.get_name()))
    throw Error("Word \""+w.get_name()+"\" already exist"); // w already exist
  words_.insert(std::pair<std::string, Word>(w.get_name(), w));
}

// Remove Word w, throw Error if w doesn't exist
void Dictionary::RemoveWord(const std::string& w) {
  if (!WordExist(w))
    throw Error("Word \""+w+"\" doesn't exist");  // w doesn't exist
  words_.erase(w);
}

/* Print formatted (human read) Dictionay to os, return os
* Output format : 
* 1.) word-name   (word-class) :
*   - meaning 1
*   - meaning 2
*   ...
*/
std::ostream& PrintDictionary(const Dictionary& dict, std::ostream& os) {
  std::ostringstream oss;       // Output string stream
  Dictionary::size_type cnt{1}; // The number of Word
  for (const auto& p : dict.words_) {
    oss << std::setw(3) << std::left << cnt++ << ") ";
    PrintWord(p.second, oss) << "\n";
  }

  os << oss.str();  // Write to os
  return os;
}

/* Show quick list of Words in Dictionary, return os
* Output format :
* 1.) word-name  (word-class)
* ...
*/
std::ostream& ShowDictionary(const Dictionary& dict, std::ostream& os) {
  std::ostringstream oss;       // Output string stream
  Dictionary::size_type cnt{1}; // The number of Word
  for (const auto& p : dict.words_) {
    oss << std::setw(3) << std::left << cnt++ << ") "
      << std::setw(30) << p.second.get_name()
      <<"(" << p.second.WordClassToStr() << ")" << "\n";
  }

  os << oss.str();  // Write to os
  return os;
}

} // my_dictionary