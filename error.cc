/*
* M. ARYA PRAYOGA
* WEDNESDAY, 3 MARCH 2021
*
* Implementation for Error handle classes from error.h
*/

#include "my_dictionary/error.h"

#include <iostream>

namespace my_dictionary {

// Only display error message
bool Error::Handle() const {
  std::cerr << what() << endl;

  if (std::cerr) return true;
  else return false;
}

// Clear the state of input_stream,
// if badbit set for input_stream then return false
bool BadInput::Handle() const {
  std::cerr << what() << endl;

  // If input_stream corrupt give up
  if (input_stream.bad()) return false;

  input_stream.clear();   // Clear the state of input_stream
  return true;
}

} // my_dictionary