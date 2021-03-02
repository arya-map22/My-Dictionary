/*
* M.ARYA PRAYOGA
* TUESDAY, 2 MARCH 2021
* 
* Word class representing a single word
* to stored in Dictionary class.
* Attributes:
* - Name
* - Meanings
* - Classification (verb, noun, adjective, or adverb)
*/

#ifndef MY_DICTIONARY_WORD_H_
#define MY_DICTIONARY_WORD_H

#include <iostream>
#include <string>
#include <vector>

namespace my_dictionary {

// Representing each word in dictionary
class Word {
  friend std::istream& operator>>(std::istream&,Word&);
  friend std::ostream& operator<<(std::ostream&,const Word&);

 public:
  // Representing each word-class
  enum class WordClass {
    kVerb,
    kNoun,
    kAdjective,
    kAdverb
  };

  Word() = default; // Synthetized default constructor

  // Construct Word from string and initialize its name
  // *explicit constructor
  explicit Word(const std::string& wn)
    : name(wn) { }

  // Construct Word from string and WordClass enumerator
  // initialize its name and classification
  Word(const std::string& wn, WordClass wc)
    : name(wn), classification(wc) { }

  std::string get_name() const { return name; }
  void set_name(const std::string& wn) { name = wn; }

  std::string get_meanings() const;           // Return formatted meanings in string
  void AddMeaning(const std::string& wm);     // Add new meaning, check if meaning already exists
  void RemoveMeaning(const std::string& wm);  // Remove meaning, check if meaning exists or not

  WordClass get_class() const { return classification; }
  void set_class(WordClass wc) { classification = wc; }

 private:
  std::string name;
  std::vector<std::string> meanings;  // Support multiple meaning
  WordClass classification;           // Representing word-class
};

// Print formatted (human read) Word to os,
// return os
std::ostream& PrintWord(const Word& w, std::ostream& os);

// Print Word in default format
std::ostream& operator<<(std::ostream& os, const Word& w);

// Read Word in default format
std::istream& operator>>(std::istream& is, Word& w);

} // my_dictionary

#endif  // MY_DICTIONARY_WORD_H_