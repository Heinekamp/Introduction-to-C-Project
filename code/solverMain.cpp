/**
 * @file solverMain.cpp
 * @author Max Heinekamp
 * @brief Allows executuion of the solver based on input files
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
 * @brief Main function for solverMain program
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
    return 10;
  }

  // Solve Model (Function has integrated check)
  int solveModel = model.solve();
  if (solveModel == 20 || solveModel == 30) {
    return 20;
  }

  // Print Model
  int printModel = model.print();
  if (printModel) {
    return 10;
  }

  std::cout << "\033[1;32mCOMPLETE\033[0m\n";

  return 0;
}