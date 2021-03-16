/*
* M. ARYA PRAYOGA
* MONDAY, 15 MARCH 2021
*
* File interface for my_dictionary program
* Operations :
    - Load file
    - Save file
*/

#ifndef MY_DICTIONARY_FILE_INTERFACE_FILE_INTERFACE_H_
#define MY_DICTIONARY_FILE_INTERFACE_FILE_INTERFACE_H_

#include <string>

#include "my_dictionary/dictionary.h"

namespace my_dictionary {

// Load the contents of dictionary dict from file file_name
void LoadDictFromFile(Dictionary& dict, const std::string& file_name);

// Save the contents of dictionary dict to file file_name
void SaveDictToFile(const Dictionary& dict, const std::string& file_name);

} // my_dictionary

#endif // MY_DICTIONARY_FILE_INTERFACE_FILE_INTERFACE_H_