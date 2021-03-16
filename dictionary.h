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

#include <fstream>
#include <iostream>
#include <map>
#include <string>

namespace my_dictionary {

// Store several Words
class Dictionary {
  friend std::ostream& PrintDictionary(const Dictionary& dict, std::ostream& os);
  friend std::ostream& ShowDictionary(const Dictionary& dict, std::ostream& os);
  friend void SaveDictToFIle(Dictionary& dict, const std::string& file_name);

 public:
  using size_type = std::map<std::string, Word>::size_type;

  // Default constructor
  Dictionary();

  // Construct dictionary from file fn
  explicit Dictionary(const std::string& fn);

  // Construct dictionary with name dn from file fn
  Dictionary(const std::string& dn, const std::string& fn);

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

  // Get modification state of dictionary
  bool Modified() const { return modified_; }

  // Set modification state of dictionary
  void set_mod(bool b) { modified_ = b; }

  // Get file name associated with Dictionary
  std::string get_file_name() const { return file_name_; }

  // Set file name associated with dictionary
  void set_file_name(const std::string& fn) { file_name_ = fn; }

  // Save modification in dictionary to file associated with it
  void Save();

 private:
  std::string dict_name_;                     // Name of dictionary
  std::string file_name_;                     // Name of file associated with dictionary
  std::map<std::string, Word> words_;         // (key : word-name, value : Word)
  bool modified_{false};                      // Dictionary has been modified or not
  bool WordExist(const std::string& w) const; // Check if Word w exist or not
};

// Print formatted (human read) Dictionay to os, return os
std::ostream& PrintDictionary(const Dictionary& dict, std::ostream& os);

// Show quick list of Words in Dictionary, return os
std::ostream& ShowDictionary(const Dictionary& dict, std::ostream& os);

// Fill the dictionary dict from file file_name
void LoadDictFromFile(Dictionary& dict, const std::string& file_name);

// Save modification in dictionary dict to file file_name
void SaveDictToFIle(Dictionary& dict, const std::string& file_name);

} // my_dictionary

#endif  // MY_DICTIONARY_DICTIONARY_H_