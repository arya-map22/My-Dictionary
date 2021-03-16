/*
* M. ARYA PRAYOGA
* TUESDAY, 16 MARCH 2021
*
* Operation : save modification in dictionary
*/

#include "my_dictionary/interface/edit_dict/save_modification.h"

#include <iostream>

#include "my_dictionary/dictionary.h"
#include "my_dictionary/error.h"

#include "my_dictionary/interface/auxiliary.h"

namespace my_dictionary {

// Save modification in dictionary to file associated with it
void SaveModification(Dictionary& dict) {
  try {
    SaveDictToFIle(dict, dict.get_file_name());
    std::cout << "\n\nDictionary \"" << dict.get_name() << "\" successfully saved";
    WaitForButton();
  } catch (FileError& e) {
    e.Handle();
  }
}

} // my_dictionary
