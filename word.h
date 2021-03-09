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
#define MY_DICTIONARY_WORD_H_

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
    kVerb = 1,
    kNoun,
    kAdjective,
    kAdverb
  };

  Word() = default; // Synthetized default constructor

  // Construct Word from string and initialize its name
  // *explicit constructor
  explicit Word(const std::string& wn)
    : name_(wn) { }

  // Construct Word from string and WordClass enumerator
  // initialize its name and classification
  Word(const std::string& wn, WordClass wc)
    : name_(wn), classification_(wc) { }

  // Construct Word from string and int
  // initialize its name and classification (from int)
  Word(const std::string& wn, int wc);

  std::string get_name() const { return name_; }
  void set_name(const std::string& wn) { name_ = wn; }

  std::string get_meanings() const;           // Return formatted meanings in string
  void AddMeaning(const std::string& wm);     // Add new meaning, throw Error if meaning already exists
  void RemoveMeaning(const std::string& wm);  // Remove meaning, throw Error if meaning exists or not

  WordClass get_class() const { return classification_; }
  void set_class(WordClass wc) { classification_ = wc; }

  int WordClassToInt() const;         // Return Word::WordClass as int
  std::string WordClassToStr() const; // Return Word::Wordclass as string

 private:
  std::string name_;
  std::vector<std::string> meanings_;              // Support multiple meaning
  WordClass classification_;                       // Representing word-class
  bool MeaningExist(const std::string& wm) const;  // Check if meaning m exist
};

// Print formatted (human read) Word to os, return os
std::ostream& PrintWord(const Word& w, std::ostream& os);

// Print Word in default format
std::ostream& operator<<(std::ostream& os, const Word& w);

// Read Word in default format
std::istream& operator>>(std::istream& is, Word& w);

// Convert int to Word::WordClass
Word::WordClass IntToWordClass(int n);

} // my_dictionary

#endif  // MY_DICTIONARY_WORD_H_