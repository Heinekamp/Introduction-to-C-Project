/**
 * @file solverTest.cpp
 * @author Max Heinekamp
 * @brief Contains tests for the SOLVER class
 * @version 1.0
 * @date 24-07-2023
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "solver.hpp"
#include "model.hpp"

#include <unordered_map>

///////////////////////////////////////////////////////////////////////////////
// Helper Functions                                                         //
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief tests the SOLVER::generatePairs() function
 *
 * @return true if tests pass
 * @return false if tests fail
 */
bool testGeneratePairs() {
  std::vector<std::tuple<std::string, std::string, std::string, std::string>>
      result; // Temporarily stores result

  std::vector<std::vector<std::string>> optionsValid = {
      {"CategoryA", "Element1", "Element2"},
      {"CategoryB", "ElementA", "ElementB"}};

  std::vector<std::tuple<std::string, std::string, std::string, std::string>>
      expected = {{
          std::make_tuple("CategoryA", "Element1", "CategoryB", "ElementA"),
          std::make_tuple("CategoryA", "Element1", "CategoryB", "ElementB"),
          std::make_tuple("CategoryA", "Element2", "CategoryB", "ElementA"),
          std::make_tuple("CategoryA", "Element2", "CategoryB", "ElementB"),
      }};

  std::vector<std::vector<std::string>> optionsValid2 = {
      {"CategoryA", "Element1", "Element2", "Element3"},
      {"CategoryB", "ElementA", "ElementB"}};

  std::vector<std::tuple<std::string, std::string, std::string, std::string>>
      expected2 = {{
          std::make_tuple("CategoryA", "Element1", "CategoryB", "ElementA"),
          std::make_tuple("CategoryA", "Element1", "CategoryB", "ElementB"),
          std::make_tuple("CategoryA", "Element2", "CategoryB", "ElementA"),
          std::make_tuple("CategoryA", "Element2", "CategoryB", "ElementB"),
          std::make_tuple("CategoryA", "Element3", "CategoryB", "ElementA"),
          std::make_tuple("CategoryA", "Element3", "CategoryB", "ElementB"),
      }};


  // Test with 2 categories with 2 elements each
  std::cout << "Testing with 2 categories with 2 elements each: " << std::endl;
  result = SOLVER::generatePairs(optionsValid);
  if (result != expected) {
    std::cout << "\033[1;31mFAILED\033[0m\n";
    return false;
  }
  std::cout << "\033[1;32mPASSED\033[0m\n";

  // Test with 2 categories with different amounts of elements
  std::cout << "Testing with 2 categories with different amounts of elelemtns: " << std::endl;
  result = SOLVER::generatePairs(optionsValid2);
  if (result != expected2) {
    std::cout << "\033[1;31mFAILED\033[0m\n";
    return false;
  }
  std::cout << "\033[1;32mPASSED\033[0m\n";

  return true;
}

/**
 * @brief tests the SOLVER::generateRow() funtion
 *
 * @return true if tests pass
 * @return false if tests fail
 */
bool testGenerateRow() {
  std::vector<std::string> result; // Temporarily stores result
  // Create a map to store the options for each category
  std::unordered_map<std::string, std::vector<std::string>> categoryToElements;
  int initialPairsSize;
  std::vector<int> toDelete;

  std::vector<std::vector<std::string>> options1 = {
      {"CategoryA", "Element1", "Element2"},
      {"CategoryB", "ElementA", "ElementB", "ElementC"},
      {"CategoryC", "ElementX", "ElementY", "ElementZ"}};

  auto pairs1 = SOLVER::generatePairs(options1);
  auto allPairs1 = pairs1;

  std::vector<std::vector<std::string>> options2 = {
      {"CategoryA", "Element1", "Element2"},
      {"CategoryB", "ElementA", "ElementB", "ElementC"},
      {"CategoryC", "ElementX", "ElementY", "ElementZ"},
      {"CategoryD", "Element4", "Element5", "Element6", "Element7"}};

  auto pairs2 = SOLVER::generatePairs(options2);
  auto allPairs2 = pairs2;

  // Test three times with options 1
  std::cout << "Testing with options1: " << std::endl;
  // Populate the categoryToElements map with data from options
  for (const auto &row : options1) {
    if (row.size() >= 2) {
      std::string category = row[0];
      for (size_t i = 1; i < row.size(); i++) {
        categoryToElements[category].push_back(row[i]);
      }
    }
  }
  for (int i = 1; i < 4; i++) {
    std::cout << "Run " << i << " of 3: ";
    initialPairsSize = pairs1.size();
    result = SOLVER::generateRow(options1, pairs1, allPairs1, toDelete);

    // Check row has correct size
    if (result.size() != (2 * options1.size())) {
      std::cout << "\033[1;31mFAILED\033[0m\n";
      std::cout << "Row contains incorrect number of strings" << std::endl;
      return false;
    }
    // Check all categories are valid
    std::vector<std::string> categories;
    for (size_t i = 0; i < result.size(); i += 2) {
      categories.push_back(result[i]);
    }
    for (size_t i = 0; i < result.size(); i += 2) {
      std::string category = result[i];
      std::string element = result[i + 1];

      // Check if the category exists in options and if the element is present
      // in that category
      if (categoryToElements.find(category) == categoryToElements.end()) {
        std::cout << "\033[1;31mFAILED\033[0m\n";
        std::cout << "Row contains invalid categories" << std::endl;
        return false;
      }

      bool elementFound = false;
      for (const auto &optionElement : categoryToElements[category]) {
        if (element == optionElement) {
          elementFound = true;
          break;
        }
      }

      if (!elementFound) {
        std::cout << "\033[1;31mFAILED\033[0m\n";
        std::cout << "Element in row does not match category" << std::endl;
        return false; // Element not found in the specified category
      }
    }
    std::cout << "\033[1;32mPASSED\033[0m\n";
  }

  // Test three times with options 2
  std::cout << "Testing with options2: " << std::endl;
  // Populate the categoryToElements map with data from options
  for (const auto &row : options2) {
    if (row.size() >= 2) {
      std::string category = row[0];
      for (size_t i = 1; i < row.size(); i++) {
        categoryToElements[category].push_back(row[i]);
      }
    }
  }
  for (int i = 1; i < 4; i++) {
    std::cout << "Run " << i << " of 3: ";
    initialPairsSize = pairs2.size();
    // Chech row has correct size
    result = SOLVER::generateRow(options2, pairs2, allPairs2, toDelete);
    if (result.size() != (2 * options2.size())) {
      std::cout << "\033[1;31mFAILED\033[0m\n";
      std::cout << "Row contains incorrect number of strings" << std::endl;
      return false;
    }
    // Check all categories are valid
    std::vector<std::string> categories;
    for (size_t i = 0; i < result.size(); i += 2) {
      categories.push_back(result[i]);
    }
    for (size_t i = 0; i < result.size(); i += 2) {
      std::string category = result[i];
      std::string element = result[i + 1];

      // Check if the category exists in options and if the element is present
      // in that category
      if (categoryToElements.find(category) == categoryToElements.end()) {
        std::cout << "\033[1;31mFAILED\033[0m\n";
        std::cout << "Row contains invalid categories" << std::endl;
        return false;
      }

      bool elementFound = false;
      for (const auto &optionElement : categoryToElements[category]) {
        if (element == optionElement) {
          elementFound = true;
          break;
        }
      }

      if (!elementFound) {
        std::cout << "\033[1;31mFAILED\033[0m\n";
        std::cout << "Element in row does not match category" << std::endl;
        return false; // Element not found in the specified category
      }
    }

    std::cout << "\033[1;32mPASSED\033[0m\n";
  }

  return true;
}

/**
 * @brief tests the SOLVER::checkRowValid() function
 *
 * @return true if tests pass
 * @return false if tests fail
 */
bool testCheckRowValid() {
  bool result; // Temporarily stores result

  std::vector<std::vector<std::string>> constraints1 = {
      {"CategoryA", "Element1", "CategoryC", "ElementX", "CategoryB",
       "ElementA"},
  };

  std::vector<std::string> row1Valid = {"CategoryA", "Element1",  "CategoryC",
                                        "ElementY",  "CategoryB", "ElementA"};

  std::vector<std::string> row1Invalid = {"CategoryA", "Element1",  "CategoryB",
                                          "ElementA",  "CategoryC", "ElementX"};

  std::vector<std::vector<std::string>> constraints2 = {
      {"CategoryA", "Element1", "CategoryC", "ElementX", "CategoryB",
       "ElementA"},
      {"CategoryA", "Element2", "CategoryC", "ElementY"},
  };

  std::vector<std::string> row2Valid = {"CategoryA", "Element1",  "CategoryC",
                                        "ElementY",  "CategoryB", "ElementA"};

  std::vector<std::string> row2Invalid = {"CategoryA", "Element2",  "CategoryB",
                                          "ElementA",  "CategoryC", "ElementY"};

  std::vector<std::vector<std::string>> constraints3 = {
      {"CategoryA", "Element1", "CategoryC", "CategoryA", "CategoryB",
       "ElementA"},
      {"CategoryA", "Element2", "CategoryC", "ElementY", "CategoryB",
       "ElementA"},
  };

  std::vector<std::string> row3Valid = {"CategoryA", "Element1",  "CategoryC",
                                        "ElementY",  "CategoryB", "ElementA"};

  std::vector<std::string> row3Invalid = {"CategoryA", "Element1",
                                          "CategoryB", "ElementA",
                                          "CategoryC", "CategoryA"};

  // Test with valid cobnination of row and constraints (1 constraint, equal
  // number of categories)
  std::cout << "Test 1 with valid combination of row and constraints: "
            << std::endl;
  result = SOLVER::checkRowValid(constraints1, row1Valid);
  if (result != true) {
    std::cout << "\033[1;31mFAILED\033[0m\n";
    return false;
  }
  std::cout << "\033[1;32mPASSED\033[0m\n";

  // Test with invalid cobnination of row and constraints (1 constraint, equal
  // number of categories)
  std::cout << "Test 1 with invalid combination of row and constraints: "
            << std::endl;
  result = SOLVER::checkRowValid(constraints1, row1Invalid);
  if (result != false) {
    std::cout << "\033[1;31mFAILED\033[0m\n";
    return false;
  }
  std::cout << "\033[1;32mPASSED\033[0m\n";

  // Test with valid cobnination of row and constraints (multiple constraint,
  // non-equal number of categories)
  std::cout << "Test 2 with valid combination of row and constraints: "
            << std::endl;
  result = SOLVER::checkRowValid(constraints2, row2Valid);
  if (result != true) {
    std::cout << "\033[1;31mFAILED\033[0m\n";
    return false;
  }
  std::cout << "\033[1;32mPASSED\033[0m\n";

  // Test with invalid cobnination of row and constraints (multiple constraint,
  // non-equal number of categories)
  std::cout << "Test 2 with invalid combination of row and constraints: "
            << std::endl;
  result = SOLVER::checkRowValid(constraints2, row2Invalid);
  // result = false;
  if (result != false) {
    std::cout << "\033[1;31mFAILED\033[0m\n";
    return false;
  }
  std::cout << "\033[1;32mPASSED\033[0m\n";

  // Test with valid cobnination of row and constraints (Element named after
  // other Catgory)
  std::cout << "Test 3 with valid combination of row and constraints: "
            << std::endl;
  result = SOLVER::checkRowValid(constraints3, row3Valid);
  if (result != true) {
    std::cout << "\033[1;31mFAILED\033[0m\n";
    return false;
  }
  std::cout << "\033[1;32mPASSED\033[0m\n";

  // Test with invalid cobnination of row and constraints (Element named after
  // other Catgory)
  std::cout << "Test 3 with invalid combination of row and constraints: "
            << std::endl;
  result = SOLVER::checkRowValid(constraints3, row3Invalid);
  if (result != false) {
    std::cout << "\033[1;31mFAILED\033[0m\n";
    return false;
  }
  std::cout << "\033[1;32mPASSED\033[0m\n";

  return true;
}

/**
 * @brief tests the SOLVER::solve() function
 *
 * @return true if tests pass
 * @return false if tests fail
 */
bool testSolver() {
  PROBLEM test = PROBLEM("test", "test"); // Sample problem
  PROBLEM *p = &test;                     // Pointer to sample problem
  int result;                             // Temporarily stores result
  MODEL testModel = MODEL(p, "test");     // Sample model
  MODEL *m = &testModel;                  // Pointer to test model

  std::vector<std::vector<std::string>> optionsValid = {
      {"CategoryA", "Element1", "Element2"},
      {"CategoryB", "ElementA", "ElementB", "ElementC"},
      {"CategoryC", "ElementX", "ElementY", "ElementZ"}};

  std::vector<std::vector<std::string>> optionsBarelyValid = {
      {"CategoryA", "Element1"},
      {"CategoryB", "ElementA", "ElementB", "ElementC"},
      {"CategoryC", "ElementX", "ElementY", "ElementZ"}};

  std::vector<std::vector<std::string>> constraintsEmpty = {};

  std::vector<std::vector<std::string>> constraintsValid = {
      {"CategoryA", "Element1", "CategoryC", "ElementX", "CategoryB",
       "ElementA"},
      {"CategoryB", "ElementB", "CategoryA", "Element1", "CategoryC",
       "ElementZ"},
      {"CategoryA", "Element1", "CategoryC", "ElementY", "CategoryB",
       "ElementC"}};

  // Test solving for problem with no constraints
  p->setOptions(optionsValid);
  p->setConstraints(constraintsEmpty);
  std::cout << "Testing with problem 1 (no constraints) " << std::endl;
  // Generate result
  result = m->solve();
  if (result != 0) {
    std::cout << "\033[1;31mFAILED\033[0m\n";
    return false;
  }
  // Output solution to file for instpection
  m->setModelsFile("solverTest1.models");
  m->print();
  // check result is valid
  result = m->check();
  if (result != 0) {
    std::cout << "\033[1;31mFAILED\033[0m\n";
    return false;
  }
  std::cout << "\033[1;32mPASSED\033[0m\n";

  // Test solving for problem with constraints
  p->setOptions(optionsValid);
  p->setConstraints(constraintsValid);
  std::cout << "Testing with problem 2 (contains conststaints): " << std::endl;
  // Generate result
  result = m->solve();
  if (result != 0) {
    std::cout << "\033[1;31mFAILED\033[0m\n";
    return false;
  }
  // Uncomment to output solution to file for instpection
  // m->setModelsFile("solverTest2.models");
  // m->print();

  // check result is valid
  result = m->check();
  if (result != 0) {
    std::cout << "\033[1;31mFAILED\033[0m\n";
    return false;
  }
  std::cout << "\033[1;32mPASSED\033[0m\n";

  // Test solving for problem with constraints and category with single option
  p->setOptions(optionsBarelyValid);
  p->setConstraints(constraintsValid);
  std::cout << "Testing with problem 3 (contains conststaints & category with single element): " << std::endl;
  // Generate result
  result = m->solve();
  if (result != 0) {
    std::cout << "\033[1;31mFAILED\033[0m\n";
    return false;
  }
  // Uncomment to output solution to file for instpection
  // m->setModelsFile("solverTest2.models");
  // m->print();

  // check result is valid
  result = m->check();
  if ((result != 0) && (result != 100)) {
    std::cout << "\033[1;31mFAILED\033[0m\n";
    return false;
  }
  std::cout << "\033[1;32mPASSED\033[0m\n";


  return true;
}

///////////////////////////////////////////////////////////////////////////////
// Main Function                                                            //
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief runs all tests for SOLVER
 *
 * @return int status code (see documentation)
 */
int main() {
  //Set this to true to enable verbose logging to console
  LOGGER::SetVerboseMode(false);

  int counter = 0;
  bool input = 0;
  std::cout << "Solver Test" << std::endl;
  std::cout << "-------------------------------------" << std::endl;
  std::cout << "-------------------------------------" << std::endl;

  std::cout << "Starting test of generatePairs()" << std::endl;
  input = testGeneratePairs();
  if (input) {
    counter++;
  }

  std::cout << "-------------------------------------" << std::endl;

  std::cout << "Starting test of testGenerateRow()" << std::endl;
  input = testGenerateRow();
  if (input) {
    counter++;
  }

  std::cout << "-------------------------------------" << std::endl;

  std::cout << "Starting test of checkRowValid()" << std::endl;
  input = testCheckRowValid();
  if (input) {
    counter++;
  }

  std::cout << "-------------------------------------" << std::endl;

  std::cout << "Starting test of solver()" << std::endl;
  input = testSolver();
  if (input) {
    counter++;
  }

  std::cout << "-------------------------------------" << std::endl;

  std::cout << "Testing complete, passed " << counter << " of 4 test groups"
            << std::endl;
  return 0;
}