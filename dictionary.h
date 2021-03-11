/*
* M. ARYA PRAYOGA
* THURSTDAY, 4 MARCH 2021
*
* Dictionary class contains several Words.
* Maintain order of Words and implemented using
* map containers (key : word-name, value : Word).
*/

#ifndef MY_DICTIONARY_DICTIONARY_H_
#define MY_DICTIONARY_DICTIONARY_H_

#include "my_dictionary/word.h"

#include <iostream>
#include <map>
#include <string>

namespace my_dictionary {

// Store several Words
class Dictionary {
  friend std::ostream& PrintDictionary(const Dictionary& dict, std::ostream& os);
  friend std::ostream& ShowDictionary(const Dictionary& dict, std::ostream& os);

 public:
  using size_type = std::map<std::string, Word>::size_type;

  Dictionary() = default;   // Synthetized default constructor

  // Construct dictionary with name dn
  Dictionary(const::std::string& dn) : dict_name_(dn) { }

  // Return the name of dictionary
  std::string get_name() const { return dict_name_; }

  // Change the name of dictionary to s
  void set_name(const std::string& s) { dict_name_ = s; }

  // Return the number of Words
  size_type WordCount() const { return words_.size(); }

  // Return reference to Word at word-name w
  // Throw Error if w not found
  Word& get_word(const std::string& w);

  // Return const reference to Word at word-name w
  // Throw Error if w not found
  const Word& get_word(const std::string& w) const;

  // Add Word w, throw Error if w already exist
  void AddWord(const Word& w);

  // Remove Word w, throw Error if w doesn't exist
  void RemoveWord(const std::string& w);

 private:
  std::string dict_name_{"dictionary"};       // Name of dictionary
  std::map<std::string, Word> words_;         // (key : word-name, value : Word)
  bool WordExist(const std::string& w) const; // Check if Word w exist or not
};

// Print formatted (human read) Dictionay to os, return os
std::ostream& PrintDictionary(const Dictionary& dict, std::ostream& os);

// Show quick list of Words in Dictionary, return os
std::ostream& ShowDictionary(const Dictionary& dict, std::ostream& os);

} // my_dictionary

#endif  // MY_DICTIONARY_DICTIONARY_H_