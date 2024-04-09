/**
 * @file checkerTest.cpp
 * @author Max Heinekamp
 * @brief Contains tests for the CHECKER class
 * @version 1.0
 * @date 24-07-2023
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "checker.hpp"
#include "model.hpp"

///////////////////////////////////////////////////////////////////////////////
// Helper Functions                                                         //
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief tests the CHECKER::checkInputFiles() function
 *
 * @return true if tests pass
 * @return false if tests fail
 */
bool testInputFiles() {
  PROBLEM test = PROBLEM("test.options", "test.constraints"); // Sample problem
  PROBLEM *p = &test; // Pointer to sample problem
  int result;         // Temporarily stores result

  std::vector<std::vector<std::string>> optionsValid = {
      {"CategoryA", "Element1", "Element2"},
      {"CategoryB", "ElementA", "ElementB", "ElementC"},
      {"CategoryC", "ElementX", "ElementY", "ElementZ"}};

  std::vector<std::vector<std::string>> optionsBarelyValid = {
      {"CategoryA", "Element1", "Element2"},
      {"CategoryB", "ElementA", "ElementB", "ElementC"},
      {"CategoryC", "ElementX"}};

  std::vector<std::vector<std::string>> optionsInvalid = {
      {"CategoryA", "Element1", "Element2"},
      {"CategoryB", "ElementA", "ElementB", "ElementC"},
      {"CategoryC"}};

  std::vector<std::vector<std::string>> constraintsValid = {
      {"CategoryA", "Element1", "CategoryC", "ElementX", "CategoryB",
       "ElementA"},
      {"CategoryB", "ElementB", "CategoryA", "Element2", "CategoryC",
       "ElementX"},
      {"CategoryA", "Element1", "CategoryC", "ElementX", "CategoryB",
       "ElementC"}};

  std::vector<std::vector<std::string>> constraintsmissingElement = {
      {"CategoryA", "Element1", "CategoryC", "ElementX", "CategoryB",
       "ElementA"},
      {"CategoryB", "ElementB", "CategoryA", "Element2", "CategoryC"},
      {"CategoryA", "Element1", "CategoryC", "ElementY", "Category B",
       "ElementC"}};

  std::vector<std::vector<std::string>> constraintsInvalidCategory = {
      {"CategoryA", "Element1", "CategoryC", "ElementX", "CategoryB",
       "ElementA"},
      {"CategoryB", "ElementB", "CategoryA", "Element2", "CategoryC",
       "ElementZ"},
      {"CategoryA", "Element1", "CategoryC", "ElementY", "InvalidCategory",
       "ElementC"}};

  std::vector<std::vector<std::string>> constraintsInvalidElement = {
      {"CategoryA", "Element1", "CategoryC", "ElementX", "CategoryB",
       "ElementA"},
      {"CategoryB", "ElementB", "CategoryA", "Element2", "CategoryC",
       "ElementZ"},
      {"CategoryA", "Element1", "CategoryC", "ElementY", "CategoryB",
       "InvalidElement"}};

  // Test with valid options and constraints
  p->setOptions(optionsValid);
  p->setConstraints(constraintsValid);
  std::cout << "Testing with valid optionts and constraints file: "
            << std::endl;
  result = CHECKER::checkInputFiles(p);
  if (result != 0) {
    std::cout << "\033[1;31mFAILED\033[0m\n";
    return false;
  }
  std::cout << "\033[1;32mPASSED\033[0m\n";

  // Test with barely valid options
  p->setOptions(optionsBarelyValid);
  p->setConstraints(constraintsValid);
  std::cout << "Testing with barely valid options file: " << std::endl;
  result = CHECKER::checkInputFiles(p);
  if (result != 100) {
    std::cout << "\033[1;31mFAILED\033[0m\n";
    return false;
  }
  std::cout << "\033[1;32mPASSED\033[0m\n";

  // Test with invalid options
  p->setOptions(optionsInvalid);
  p->setConstraints(constraintsValid);
  std::cout << "Testing with invalid options file: " << std::endl;
  result = CHECKER::checkInputFiles(p);
  if (result != 20) {
    std::cout << "\033[1;31mFAILED\033[0m\n";
    return false;
  }
  std::cout << "\033[1;32mPASSED\033[0m\n";

  // Test with missing constraints element
  p->setOptions(optionsValid);
  p->setConstraints(constraintsmissingElement);
  std::cout << "Testing with missing constraints element: " << std::endl;
  result = CHECKER::checkInputFiles(p);
  if (result != 30) {
    std::cout << "\033[1;31mFAILED\033[0m\n";
    return false;
  }
  std::cout << "\033[1;32mPASSED\033[0m\n";

  // Test with invalid constraints category
  p->setOptions(optionsValid);
  p->setConstraints(constraintsInvalidCategory);
  std::cout << "Testing with invalid constraints category: " << std::endl;
  result = CHECKER::checkInputFiles(p);
  if (result != 30) {
    std::cout << "\033[1;31mFAILED\033[0m\n";
    return false;
  }
  std::cout << "\033[1;32mPASSED\033[0m\n";

  // Test with invalid constraints element
  p->setOptions(optionsValid);
  p->setConstraints(constraintsInvalidElement);
  std::cout << "Testing with invalid constraints element: " << std::endl;
  result = CHECKER::checkInputFiles(p);
  if (result != 30) {
    std::cout << "\033[1;31mFAILED\033[0m\n";
    return false;
  }
  std::cout << "\033[1;32mPASSED\033[0m\n";

  return true;
}

/**
 * @brief tests CHECKER::checkOptionCoverage() function
 *
 * @return true if tests pass
 * @return false if tests fail
 */
bool testOptionsCoverage() {
  PROBLEM test = PROBLEM("test.options", "test.constraints"); // Sample problem
  PROBLEM *p = &test;                        // Pointer to sample problem
  MODEL testModel = MODEL(p, "test.models"); // Sample model
  MODEL *m = &testModel;                     // Pointer to test model
  int result;                                // Temporarily stores result

  std::vector<std::vector<std::string>> optionsValid = {
      {"CategoryA", "Element1", "Element2"},
      {"CategoryB", "ElementA", "ElementB", "ElementC"},
      {"CategoryC", "ElementX", "ElementY", "ElementZ"}};

  std::vector<std::vector<std::string>> constraintsValid = {
      {"CategoryA", "Element1", "CategoryC", "ElementX", "CategoryB",
       "ElementA"},
      {"CategoryB", "ElementB", "CategoryA", "Element2", "CategoryC",
       "ElementZ"},
      {"CategoryA", "Element1", "CategoryC", "ElementY", "CategoryB",
       "ElementC"}};

  std::vector<std::vector<std::string>> modelValid = {
      {"CategoryA", "Element1", "CategoryC", "ElementX", "CategoryB",
       "ElementA"},
      {"CategoryB", "ElementB", "CategoryA", "Element2", "CategoryC",
       "ElementZ"},
      {"CategoryA", "Element1", "CategoryC", "ElementY", "CategoryB",
       "ElementC"}};

  std::vector<std::vector<std::string>> modelMissingElement = {
      {"CategoryA", "Element1", "CategoryC", "ElementX", "CategoryB",
       "ElementA"},
      {"CategoryB", "ElementB", "CategoryA", "Element2", "CategoryC"},
      {"CategoryA", "Element1", "CategoryC", "ElementY", "Category B",
       "ElementC"}};

  std::vector<std::vector<std::string>> modelWrongElement = {
      {"CategoryA", "Element1", "CategoryC", "ElementX", "CategoryB",
       "ElementA"},
      {"CategoryB", "ElementB", "CategoryA", "Element2", "CategoryC",
       "ElementZ"},
      {"CategoryA", "Element1", "CategoryC", "ElementY", "CategoryB",
       "Element1"}};

  std::vector<std::vector<std::string>> modelMissingCategory = {
      {"CategoryA", "Element1", "CategoryC", "ElementX", "CategoryB",
       "ElementA"},
      {"CategoryB", "ElementB", "CategoryA", "Element2", "CategoryC",
       "ElementZ"},
      {"CategoryA", "Element1", "CategoryC", "ElementY"}};

  std::vector<std::vector<std::string>> modelDuplicateCategory = {
      {"CategoryA", "Element1", "CategoryC", "ElementX", "CategoryB",
       "ElementA"},
      {"CategoryB", "ElementB", "CategoryB", "ElementC", "CategoryC",
       "ElementZ"},
      {"CategoryA", "Element1", "CategoryC", "ElementY", "CategoryB",
       "ElementC"}};

  // Test with valid options and constraints
  p->setOptions(optionsValid);
  p->setConstraints(constraintsValid);
  m->setModel(modelValid);
  std::cout << "Testing with valid optionts and model file: " << std::endl;
  result = CHECKER::checkOptionCoverage(m, p);
  if (result != 0) {
    std::cout << "\033[1;31mFAILED\033[0m\n";
    return false;
  }
  std::cout << "\033[1;32mPASSED\033[0m\n";

  // Test with missing element
  p->setOptions(optionsValid);
  p->setConstraints(constraintsValid);
  m->setModel(modelMissingElement);
  std::cout << "Testing with missing element in model file: " << std::endl;
  result = CHECKER::checkOptionCoverage(m, p);
  if (result != 40) {
    std::cout << "\033[1;31mFAILED\033[0m\n";
    return false;
  }
  std::cout << "\033[1;32mPASSED\033[0m\n";

  // Test with missing category
  p->setOptions(optionsValid);
  p->setConstraints(constraintsValid);
  m->setModel(modelMissingCategory);
  std::cout << "Testing with missing category in model file: " << std::endl;
  result = CHECKER::checkOptionCoverage(m, p);
  if (result != 40) {
    std::cout << "\033[1;31mFAILED\033[0m\n";
    return false;
  }
  std::cout << "\033[1;32mPASSED\033[0m\n";

  // Test with wrong element
  p->setOptions(optionsValid);
  p->setConstraints(constraintsValid);
  m->setModel(modelWrongElement);
  std::cout << "Testing with wrong element for category in model file: "
            << std::endl;
  result = CHECKER::checkOptionCoverage(m, p);
  if (result != 40) {
    std::cout << "\033[1;31mFAILED\033[0m\n";
    return false;
  }
  std::cout << "\033[1;32mPASSED\033[0m\n";

  // Test with duplicate category
  p->setOptions(optionsValid);
  p->setConstraints(constraintsValid);
  m->setModel(modelDuplicateCategory);
  std::cout << "Testing with duplicate category in model file: " << std::endl;
  result = CHECKER::checkOptionCoverage(m, p);
  if (result != 40) {
    std::cout << "\033[1;31mFAILED\033[0m\n";
    return false;
  }
  std::cout << "\033[1;32mPASSED\033[0m\n";

  return true;
}

/**
 * @brief tests CHECKER::checkConstraints() function
 *
 * @return true if tests pass
 * @return false if tests fail
 */
bool testConstraints() {
  PROBLEM test = PROBLEM("test.options", "test.constraints"); // Sample problem
  PROBLEM *p = &test;                        // Pointer to sample problem
  MODEL testModel = MODEL(p, "test.models"); // Sample model
  MODEL *m = &testModel;                     // Pointer to test model
  int result;                                // Temporarily stores result

  std::vector<std::vector<std::string>> optionsValid = {
      {"CategoryA", "Element1", "Element2"},
      {"CategoryB", "ElementA", "ElementB", "ElementC"},
      {"CategoryC", "ElementX", "ElementY", "ElementZ"}};

  std::vector<std::vector<std::string>> constraints1 = {
      {"CategoryA", "Element1", "CategoryC", "ElementX", "CategoryB",
       "ElementA"},
  };

  std::vector<std::vector<std::string>> constraints2 = {
      {"CategoryA", "Element1"},
  };

  std::vector<std::vector<std::string>> model1Valid = {
      {"CategoryA", "Element1", "CategoryC", "ElementY", "CategoryB",
       "ElementA"},
      {"CategoryB", "ElementB", "CategoryA", "Element2", "CategoryC",
       "ElementZ"},
      {"CategoryA", "Element1", "CategoryC", "ElementY", "CategoryB",
       "ElementC"}};

  std::vector<std::vector<std::string>> model1Invalid = {
      {"CategoryA", "Element1", "CategoryC", "ElementX", "CategoryB",
       "ElementA"},
      {"CategoryB", "ElementB", "CategoryA", "Element2", "CategoryC",
       "ElementZ"},
      {"CategoryA", "Element1", "CategoryC", "ElementY", "CategoryB",
       "ElementC"}};

  std::vector<std::vector<std::string>> model1InvalidJumbled = {
      {"CategoryB", "ElementB", "CategoryA", "Element2", "CategoryC",
       "ElementZ"},
      {"CategoryA", "Element1", "CategoryC", "ElementY", "CategoryB",
       "ElementC"},
      {"CategoryB", "ElementA", "CategoryA", "Element1", "CategoryC",
       "ElementX"}};

  std::vector<std::vector<std::string>> model2ValidJumbled = {
      {"CategoryB", "ElementB", "CategoryA", "Element2", "CategoryC",
       "ElementZ"},
      {"CategoryA", "Element2", "CategoryC", "ElementY", "CategoryB",
       "ElementC"},
      {"CategoryB", "ElementA", "CategoryA", "Element2", "CategoryC",
       "ElementX"}};
  
  std::vector<std::vector<std::string>> model2InvalidJumbled = {
      {"CategoryB", "ElementB", "CategoryA", "Element2", "CategoryC",
       "ElementZ"},
      {"CategoryA", "Element1", "CategoryC", "ElementY", "CategoryB",
       "ElementC"},
      {"CategoryB", "ElementA", "CategoryA", "Element1", "CategoryC",
       "ElementX"}};

  // Test with valid cobnination of model and constraints
  p->setOptions(optionsValid);
  p->setConstraints(constraints1);
  m->setModel(model1Valid);
  std::cout << "Test with valid constraints and model cobination: "
            << std::endl;
  result = CHECKER::checkConstraints(m, p);
  if (result != 0) {
    std::cout << "\033[1;31mFAILED\033[0m\n";
    return false;
  }
  std::cout << "\033[1;32mPASSED\033[0m\n";

  // Test with invalid combination of model and constraints
  p->setOptions(optionsValid);
  p->setConstraints(constraints1);
  m->setModel(model1Invalid);
  std::cout << "Test with invalid constraints and model cobination: "
            << std::endl;
  result = CHECKER::checkConstraints(m, p);
  if (result != 40) {
    std::cout << "\033[1;31mFAILED\033[0m\n";
    return false;
  }
  std::cout << "\033[1;32mPASSED\033[0m\n";

  // Test with junmbled invalid combination of model and constraints
  p->setOptions(optionsValid);
  p->setConstraints(constraints1);
  m->setModel(model1InvalidJumbled);
  std::cout << "Test with jumbled invalid constraints and model cobination: "
            << std::endl;
  result = CHECKER::checkConstraints(m, p);
  if (result != 40) {
    std::cout << "\033[1;31mFAILED\033[0m\n";
    return false;
  }
  std::cout << "\033[1;32mPASSED\033[0m\n";

  // Test with junmbled valid combination of model and single constraint
  p->setOptions(optionsValid);
  p->setConstraints(constraints2);
  m->setModel(model2ValidJumbled);
  std::cout << "Test with jumbled valid cobination of model and single constraint: "
            << std::endl;
  result = CHECKER::checkConstraints(m, p);
  if (result != 0) {
    std::cout << "\033[1;31mFAILED\033[0m\n";
    return false;
  }
  std::cout << "\033[1;32mPASSED\033[0m\n";

  // Test with junmbled invalid combination of model and single constraint
  p->setOptions(optionsValid);
  p->setConstraints(constraints2);
  m->setModel(model2InvalidJumbled);
  std::cout << "Test with jumbled invalid cobination of model and single constraint: "
            << std::endl;
  result = CHECKER::checkConstraints(m, p);
  if (result != 40) {
    std::cout << "\033[1;31mFAILED\033[0m\n";
    return false;
  }
  std::cout << "\033[1;32mPASSED\033[0m\n";

  return true;
}

/**
 * @brief tests CHECKER::checkOptionsValid() function
 *
 * @return true if tests pass
 * @return false if tests fail
 */
bool testOptionsValid() {
  PROBLEM test = PROBLEM("test.options", "test.constraints"); // Sample problem
  PROBLEM *p = &test;                        // Pointer to sample problem
  MODEL testModel = MODEL(p, "test.models"); // Sample model
  MODEL *m = &testModel;                     // Pointer to test model
  int result;                                // Temporarily stores result

  std::vector<std::vector<std::string>> optionsValid = {
      {"CategoryA", "Element1", "Element2"},
      {"CategoryB", "ElementA", "ElementB", "ElementC"},
      {"CategoryC", "ElementX", "ElementY", "ElementZ"}};

  std::vector<std::vector<std::string>> constraintsValid = {
      {"CategoryA", "Element1", "CategoryC", "ElementX", "CategoryB",
       "ElementA"},
      {"CategoryB", "ElementB", "CategoryA", "Element2", "CategoryC",
       "ElementZ"},
      {"CategoryA", "Element1", "CategoryC", "ElementY", "CategoryB",
       "ElementC"}};

  std::vector<std::vector<std::string>> modelValid = {
      {"CategoryA", "Element1", "CategoryC", "ElementX", "CategoryB",
       "ElementA"},
      {"CategoryB", "ElementB", "CategoryA", "Element2", "CategoryC",
       "ElementZ"},
      {"CategoryA", "Element1", "CategoryC", "ElementY", "CategoryB",
       "ElementC"}};

  std::vector<std::vector<std::string>> modelMissingElement = {
      {"CategoryA", "Element1", "CategoryC", "ElementX", "CategoryB",
       "ElementA"},
      {"CategoryB", "ElementB", "CategoryA", "Element2", "CategoryC"},
      {"CategoryA", "Element1", "CategoryC", "ElementY", "Category B",
       "ElementC"}};

  std::vector<std::vector<std::string>> modelInvalidElement = {
      {"CategoryA", "Element1", "CategoryC", "ElementX", "CategoryB",
       "ElementA"},
      {"CategoryB", "ElementB", "CategoryA", "Element2", "CategoryC",
       "ElementZ"},
      {"CategoryA", "Element1", "CategoryC", "ElementY", "CategoryB",
       "INVALID"}};

  std::vector<std::vector<std::string>> modelInvalidCategory = {
      {"CategoryA", "Element1", "CategoryC", "ElementX", "CategoryB",
       "ElementA"},
      {"INVALID", "ElementB", "CategoryB", "ElementC", "CategoryC", "ElementZ"},
      {"CategoryA", "Element1", "CategoryC", "ElementY", "CategoryB",
       "ElementC"}};

  // Test with valid options and constraints
  p->setOptions(optionsValid);
  p->setConstraints(constraintsValid);
  m->setModel(modelValid);
  std::cout << "Testing with valid optionts and model file: " << std::endl;
  result = CHECKER::checkOptionsValid(m, p);
  if (result != 0) {
    std::cout << "\033[1;31mFAILED\033[0m\n";
    return false;
  }
  std::cout << "\033[1;32mPASSED\033[0m\n";

  // Test with missing element
  p->setOptions(optionsValid);
  p->setConstraints(constraintsValid);
  m->setModel(modelMissingElement);
  std::cout << "Testing with missing element in model file: " << std::endl;
  result = CHECKER::checkOptionsValid(m, p);
  if (result != 40) {
    std::cout << "\033[1;31mFAILED\033[0m\n";
    return false;
  }
  std::cout << "\033[1;32mPASSED\033[0m\n";

  // Test with invalid element
  p->setOptions(optionsValid);
  p->setConstraints(constraintsValid);
  m->setModel(modelInvalidElement);
  std::cout << "Testing with invalid category in model file: " << std::endl;
  result = CHECKER::checkOptionsValid(m, p);
  if (result != 40) {
    std::cout << "\033[1;31mFAILED\033[0m\n";
    return false;
  }
  std::cout << "\033[1;32mPASSED\033[0m\n";

  // Test with invlaid category
  p->setOptions(optionsValid);
  p->setConstraints(constraintsValid);
  m->setModel(modelInvalidCategory);
  std::cout << "Testing with invalid category in model file: " << std::endl;
  result = CHECKER::checkOptionsValid(m, p);
  if (result != 40) {
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
 * @brief runs all tests for CHECKER
 *
 * @return int status code (see documentation)
 */
int main() {
  //Set this to true to enable verbose logging to console
  LOGGER::SetVerboseMode(false);
  
  int counter = 0;
  bool input = 0;
  std::cout << "Checker Test" << std::endl;
  std::cout << "-------------------------------------" << std::endl;
  std::cout << "-------------------------------------" << std::endl;

  std::cout << "Starting test of checkInputFiles()" << std::endl;
  input = testInputFiles();
  if (input) {
    counter++;
  }

  std::cout << "-------------------------------------" << std::endl;

  std::cout << "Starting test of checkOptionsCoverage()" << std::endl;
  input = testOptionsCoverage();
  if (input) {
    counter++;
  }

  std::cout << "-------------------------------------" << std::endl;

  std::cout << "Starting test of checkConstraints()" << std::endl;
  input = testConstraints();
  if (input) {
    counter++;
  }

  std::cout << "-------------------------------------" << std::endl;

  std::cout << "Starting test of checkOptionsValid()" << std::endl;
  input = testOptionsValid();
  if (input) {
    counter++;
  }

  std::cout << "-------------------------------------" << std::endl;

  std::cout << "Testing complete, passed " << counter << " of 4 test groups"
            << std::endl;
  return 0;
}