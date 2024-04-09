/**
 * @file checkerMain.cpp
 * @author Max Heinekamp
 * @brief Allows executuion of the checker based on input files
 * @version 1.0
 * @date 24-07-2023
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "model.hpp"
#include "problem.hpp"
#include "logger.hpp"
#include <iostream>

/**
 * @brief Main function for checkerMain program
 *
 * @param argc argument count
 * @param argv argument values
 * @arg \c optionsFile Filename for .options file
 * @arg \c constraintsFile Filename for .constraints file
 * @arg \c modelsFile Filename for .models file
 * @return \c int status code (see documentation)
 */
int main(int argc, char **argv) {
  //Set this to true to enable verbose logging to console
  LOGGER::SetVerboseMode(false);

  // Check if correct number of arguments were supplied
  if (argc != 4) {
    std::cout << "Invalid number of arguments supplied" << std::endl;
    return 10;
  }

  // Create instance of problem and model class using given file locations /
  // arguments
  PROBLEM problem = PROBLEM(argv[1], argv[2]);
  MODEL model = MODEL(&problem, argv[3]);

  // Parse problem
  int parseProblem = problem.parse();
  if (parseProblem) {
    return parseProblem;
  }

  // Parse model
  int parseModel = model.parse();
  if (parseModel) {
    return 40;
  }

  // Check model
  int checkModel = model.check();
  // Translate return codes
  if (checkModel == 20) {
    return 10;
  }
  if (checkModel == 30) {
    return 20;
  }
  if (checkModel == 40) {
    return 30;
  }
  // If the only issue is that the options file contains useless elements
  // that is still a pass
  if (checkModel == 100) {
    std::cout << "\033[1;32mVERIFIED\033[0m\n";
    return 0;
  }
  // If there are other issues, fail the model
  else if (checkModel) {
    std::cout << "\033[1;31mUNVERIFIED\033[0m\n";
    return checkModel;
  }

  std::cout << "\033[1;32mVERIFIED\033[0m\n";

  return 0;
}