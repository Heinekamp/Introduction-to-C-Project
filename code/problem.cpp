
/**
 * @file problem.cpp
 * @author Max Heinekamp
 * @brief contains function definitions for PROBLEM class
 * @version 1.0
 * @date 24-07-2023
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "problem.hpp"
#include "parser.hpp"
#include "prettyPrint.hpp"

PROBLEM::PROBLEM()
    : m_optionFileIn{"Error"}, m_constrainFileIn{"Error"},
      m_optionFileOut("Error"), m_constrainFileOut{"Error"} {}

PROBLEM::PROBLEM(std::string optionsI, std::string constraintsI,
                 std::string optionsO, std::string constraintsO)
    : m_optionFileIn{optionsI}, m_constrainFileIn{constraintsI},
      m_optionFileOut(optionsO), m_constrainFileOut{constraintsO} {}

PROBLEM::~PROBLEM() {}

///////////////////////////////////////////////////////////////////////////////
// Function Definitions                                                     //
/////////////////////////////////////////////////////////////////////////////

int PROBLEM::parse() {
  // Run Parse
  int statusO = PARSER::parseOptions(this);
  int statusC = PARSER::parseConstraints(this);

  // Check status codes and report accordingly
  if (statusO + statusC == 0)
    return 0;
  else
    return 10;
}

int PROBLEM::print() {
  // Run printer
  int statusO = PRETTYPRINT::printOptions(this);
  int statusC = PRETTYPRINT::printConstraints(this);

  // Check status codes and report accordingly
  if (statusO + statusC == 0)
    return 0;
  else
    return 10;
}

std::vector<std::vector<std::string>> PROBLEM::getOptions() const {
  return m_options;
}

std::vector<std::vector<std::string>> PROBLEM::getConstraints() const {
  return m_constraints;
}

void PROBLEM::setOptions(std::vector<std::vector<std::string>> options) {
  m_options = options;
}

void PROBLEM::setConstraints(
    std::vector<std::vector<std::string>> constraints) {
  m_constraints = constraints;
}

std::string PROBLEM::getOptionsFileIn() const { return m_optionFileIn; }

std::string PROBLEM::getConstraintsFileIn() const { return m_constrainFileIn; }

std::string PROBLEM::getOptionsFileOut() const { return m_optionFileOut; }

std::string PROBLEM::getConstraintsFileOut() const {
  return m_constrainFileOut;
}
