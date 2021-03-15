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
void Error::Handle() const {
  std::cerr << "\nError : " << what() << std::endl;
}

// Clear the state of input_stream,
// if badbit set for input_stream then exit program
void BadInput::Handle() const {
  std::cerr << "\nBadInput : " << what() << std::endl;

  // If input_stream corrupt give up
  if (input_stream_.bad()) {
    std::cerr << "Input stream corrupted!\n"
              << "Program terminated..." << std::endl;
    exit(EXIT_FAILURE);
  }

  input_stream_.clear();   // Clear the state of input_stream
  char ch{};
  while (input_stream_.get(ch) && ch != '\n') { }  // Discard up to newline
}

// Display error message then exit program
void FileError::Handle() const {
  std::cerr << "\nFileError : " << what() 
            << "\nIn file   : " << file_name_<< std::endl;
  exit(EXIT_FAILURE);   // Exit program
}

} // my_dictionary