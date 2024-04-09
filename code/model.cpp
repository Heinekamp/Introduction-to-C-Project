/**
 * @file model.cpp
 * @author Max Heinekamp
 * @brief Contains function definitions for model class
 * @version 1.0
 * @date 24-07-2023
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "model.hpp"
#include "checker.hpp"
#include "parser.hpp"
#include "prettyPrint.hpp"
#include "solver.hpp"

MODEL::MODEL() { m_problem = nullptr; }

MODEL::MODEL(PROBLEM *p, std::string filename) {
  m_problem = p;
  m_modelsFileName = filename;
}

MODEL::~MODEL() {}

///////////////////////////////////////////////////////////////////////////////
// Function Definitions                                                     //
/////////////////////////////////////////////////////////////////////////////

int MODEL::solve() {
  // Run solver and checker and report status
  int solveStatus = SOLVER::solve(m_problem, this);
  if (solveStatus) {
    return solveStatus;
  }
  int checkStatus = check();
  // If only issue is that options contains uselles categories, ignore
  if (checkStatus == 100) {
    return 0;
  }
  // Otherwiese return that verfication failed
  else if (checkStatus) {
    std::cout << "\033[1;31mERROR: VERIFICATION FAILED\033[0m\n";
    return checkStatus;
  } 
  
  return 0;

}

void MODEL::setModel(std::vector<std::vector<std::string>> model) {
  m_models = model;
}

int MODEL::parse() {
  int status = PARSER::parseModel(this);
  return status;
}

int MODEL::check() {
  int status = CHECKER::check(this, m_problem);
  return status;
}

int MODEL::print() {
  int status = PRETTYPRINT::printModels(this);
  return status;
}

void MODEL::setModelsFile(std::string filename) { m_modelsFileName = filename; }

std::string MODEL::getModelsFile() const { return m_modelsFileName; }

std::vector<std::vector<std::string>> MODEL::getModels() const {
  return m_models;
}
