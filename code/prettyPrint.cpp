/**
 * @file prettyPrint.cpp
 * @author Max Heinekamp
 * @brief Contains function definitions for PRETTYPRINT class
 * @version 1.0
 * @date 24-07-2023
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "prettyPrint.hpp"
#include "model.hpp"
#include "problem.hpp"

PRETTYPRINT::PRETTYPRINT() {}
PRETTYPRINT::~PRETTYPRINT() {}

///////////////////////////////////////////////////////////////////////////////
// Function Definitions                                                     //
/////////////////////////////////////////////////////////////////////////////

int PRETTYPRINT::printOptions(PROBLEM *p) {
  // Get required information from problem
  std::string filename = p->getOptionsFileOut();
  std::vector<std::vector<std::string>> options = p->getOptions();

  // Call print function
  int status = print(&filename, &options);
  if (status) {
    return status;
  }

  return 0;
}

int PRETTYPRINT::printConstraints(PROBLEM *p) {

  // Get required information from problem
  std::string filename = p->getConstraintsFileOut();
  std::vector<std::vector<std::string>> constraints = p->getConstraints();

  // Call print function
  int status = print(&filename, &constraints);
  if (status) {
    return status;
  }

  return 0;
}

int PRETTYPRINT::printModels(MODEL *m) {
  // Get required information from problem
  std::string filename = m->getModelsFile();
  std::vector<std::vector<std::string>> models = m->getModels();

  // Call print function
  int status = print(&filename, &models);
  if (status) {
    return status;
  }

  return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Helper Functions                                                         //
/////////////////////////////////////////////////////////////////////////////

int PRETTYPRINT::print(std::string *filename,
                       std::vector<std::vector<std::string>> *vector) {
  std::ofstream file(*filename);

  // Check if opening file was succesfull, otherwise return error message & code
  if (!file.is_open()) {
    std::cout << "Error opening file: " << filename << std::endl;
    return 10;
  }

  // Iterate through vector and print to file
  for (const auto &row : *vector) {
    for (std::size_t i = 0; i < row.size(); ++i) {
      if (row[i].find(',') != std::string::npos) {
        // If the string contains a comma, enclose it in quotes
        file << '"' << row[i] << '"';
      } else {
        file << row[i];
      }
      if (i != row.size() - 1) {
        file << ",";
      }
    }
    file << "\n";
  }

  file.close();
  return 0;
}
