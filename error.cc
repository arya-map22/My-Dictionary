/*
* M. ARYA PRAYOGA
* WEDNESDAY, 3 MARCH 2021
*
* Implementation for Error handle classes from error.h
*/

#include "my_dictionary/error.h"

#include <iostream>

#include "my_dictionary/interface/auxiliary.h"

namespace my_dictionary {

// Only display error message
void Error::Handle() const {
  std::cerr << "Error : " << what() << std::endl;
  WaitForButton();
}

// Clear the state of input_stream,
// if badbit set for input_stream then exit program
void BadInput::Handle() const {
  std::cerr << "BadInput : " << what() << std::endl;

  // If input_stream corrupt give up
  if (input_stream_.bad()) {
    std::cerr << "Input stream corrupted!\n"
              << "Program terminated..." << std::endl;
    exit(EXIT_FAILURE);
  }

  input_stream_.clear();   // Clear the state of input_stream
  WaitForButton();
}

} // my_dictionary