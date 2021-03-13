/*
* M. ARYA PRAYOGA
* FRIDAY, 5 MARCH 2021
*
* User interface for my_dictionary program
* Operations :
*   - Show quick list of words and their class(verb, noun, adjective, or adverb)
*   - Show complete list of words, their class, and their meanings
*   - Search for spesific word by name
*   - Edit dictionary :
*     - Add word
*     - Remove word
*     - Edit spesific word :
*       - Change its name
*       - Change its class
*       - Add meaning
*       - Remove meaning
*/

#ifndef MY_DICTIONARY_MAIN_INTERFACE_H_
#define MY_DICTIONARY_MAIN_INTERFACE_H_

#include "my_dictionary/dictionary.h"

namespace my_dictionary {

const char kExit = 'q';     // To exit some operation or exit program
extern Dictionary my_dict;  // Dictionary used through program
                            // Defined in main_interface.cc

// Show menu for my_dictionary program
void ShowMenu();

// Eval chosen option by user
void EvalOption(char opt);

} // my_dictionary

#endif // MY_DICTIONARY_MAIN_INTERFACE_H_