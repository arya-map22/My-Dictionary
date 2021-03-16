/*
* M. ARYA PRAYOGA
* TUESDAY, 16 MARCH 2021
*
* Operation : save modification in dictionary
*/

#ifndef MY_DICTIONARY_INTERFACE_EDIT_DICT_SAVE_MODIFICATION_H_
#define MY_DICTIONARY_INTERFACE_EDIT_DICT_SAVE_MODIFICATION_H_

#include "my_dictionary/dictionary.h"

namespace my_dictionary {

// Save modification in dictionary to file associated with it
void SaveModification(Dictionary& dict);

}  // my_dictionary

#endif  // MY_DICTIONARY_INTERFACE_EDIT_DICT_SAVE_MODIFICATION_H_