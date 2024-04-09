/**
 * @file parser.cpp
 * @author Max Heinekamp
 * @brief Contains function definitions for PARSER class
 * @version 1.0
 * @date 24-07-2023
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "parser.hpp"
#include "model.hpp"
#include "problem.hpp"

PARSER::PARSER() {}
PARSER::~PARSER() {}

///////////////////////////////////////////////////////////////////////////////
// Function Definitions                                                     //
/////////////////////////////////////////////////////////////////////////////

// The parser for the Options and Constraints files were intentionally
// seperated, as the way this data is stored may eventually be different
// for each

int PARSER::parseOptions(PROBLEM *p) {
  // Create vector to store parsed Data and get filename
  std::string filename = p->getOptionsFileIn();
  std::vector<std::vector<std::string>> parsedData;

  // Call parse function
  int status = parse(&filename, &parsedData);
  if (status) {
    return status;
  }

  // Write parsed Data back to problem
  p->setOptions(parsedData);
  return 0;
}

int PARSER::parseConstraints(PROBLEM *p) {
  // Create vector to store parsed Data and get filename
  std::string filename = p->getConstraintsFileIn();
  std::vector<std::vector<std::string>> parsedData;

  // Call parse function
  int status = parse(&filename, &parsedData);
  if (status) {
    return status;
  }

  // Write parsed Data back to problem
  p->setConstraints(parsedData);
  return 0;
}

int PARSER::parseModel(MODEL *m) {
  // Create vector to store parsed Data and get filename
  std::vector<std::vector<std::string>> parsedData;
  std::string filename = m->getModelsFile();

  // Call parse function
  int status = parse(&filename, &parsedData);
  if (status) {
    return status;
  }

  // Write parsed Data back to model
  m->setModel(parsedData);
  return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Helper Functions                                                         //
/////////////////////////////////////////////////////////////////////////////

int PARSER::parse(std::string *filename,
                  std::vector<std::vector<std::string>> *parsedData) {
  std::ifstream file(*filename);

  // Attempt to open file, if impossible return error message & error code
  if (!file.is_open()) {
    LOGGER() << "Error opening file: " << filename << std::endl;
    return 10;
  }

  // Temporary Storage Variables
  std::string entry;
  std::vector<std::string> row;
  char c;
  bool insideQuotes = false;

  while (file.get(c)) { // Iterate file, char by char

    if (!insideQuotes &&
        (c == ',' || c == '\n')) // If c is separator and not inside quotes
    {
      row.push_back(entry);         // Push string to row vector
      entry.clear();                // and clear string for next loop
      if (c == '\n') {              // If separator is newline
        parsedData->push_back(row); // Push row to final vector
        row.clear();                // and clear row for next loop
      }
    }

    else if (c == '"') { // If c is a quotation mark
      if (insideQuotes) {
        if (file.peek() == '"') { // Check for double quotation marks to handle
                                  // quotes within quotes
          entry += c;             // Add single quote to the entry
          file.get(c);            // Skip the second quotation mark
        } else {
          insideQuotes = false; // End of quoted entry
        }
      }

      else {
        insideQuotes = true; // Start of quoted entry
      }
    }

    else {        // Otherwise
      entry += c; // Add each character to string
    }
  }

  if (!entry.empty()) {   // If string not empty when complete
    row.push_back(entry); // Push string to row
  }

  if (!row.empty()) {           // If row not empty when complete
    parsedData->push_back(row); // Push row to final vector
  }

  file.close();

  return 0;
}