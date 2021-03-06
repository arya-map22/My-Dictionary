/*
* M. ARYA PRAYOGA
* TUESDAY, 9 MARCH 2021
*
* Main function for my_dictionary program
*/

#include <iostream>

#include "my_dictionary/error.h"

#include "my_dictionary/interface/auxiliary.h"
#include "my_dictionary/interface/main_interface.h"

int main() {
  char opt{};
  while (true) {
    try {
      my_dictionary::ShowMenu();      // Prompt user to chose option
      std::cin >> opt;                // Read user input
      my_dictionary::CheckIstream();
      my_dictionary::EvalOption(opt); // Chose spesific operation based on chosen option
    } catch (my_dictionary::Error& e) {
      e.Handle();
      my_dictionary::ClearNewline();
      my_dictionary::WaitForButton();
    } catch (my_dictionary::BadInput& e) {
      e.Handle();
      my_dictionary::WaitForButton();
    } catch (...) {
      std::cerr << "ERROR!!!" << "\nProgram terminated..." << std::endl;
      exit(EXIT_FAILURE);
    }
  }
}