/**
 * @file parsePrintMain.cpp
 * @author Max Heinekamp
 * @brief  main file
 * @version 1.0
 * @date 24-07-2023
 *
 * @copyright Copyright (c) 2023
 */

#include "problem.hpp"
#include <iostream>
#include "logger.hpp"

/**
 * @brief main function for parsePrint Program
 *
 * @param argc argument count
 * @param argv argument values
 * @arg \c optionsFileIn Filename for .options input file
 * @arg \c constraintsFileIn Filename for .constraints input file
 * @arg \c optionsFileOut Filename for .options output file
 * @arg \c constraintsFileOut Filename for .constraints output file
 * @return \c int status code (see documentation)
 */
int main(int argc, char **argv) {
  //Set this to true to enable verbose logging to console
  LOGGER::SetVerboseMode(false);

  // Check if correct number of arguments were supplied
  if (argc != 5) {
    std::cout << "Invalid number of arguments supplied" << std::endl;
    return 10;
  }

  // Create instance of problem class using given file locations / arguments
  PROBLEM problem = PROBLEM(argv[1], argv[2], argv[3], argv[4]);

  // Parse problem
  int parseStatus = problem.parse();
  if (parseStatus) {
    return parseStatus;
  }
  // Print problem
  int printStatus = problem.print();
  if (printStatus) {
    return printStatus;
  }

  std::cout << "\033[1;32mCOMPLETE\033[0m\n";

  return 0;
}