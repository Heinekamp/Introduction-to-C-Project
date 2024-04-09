/**
 * @file checker.cpp
 * @author Max Heinekamp
 * @brief contains function definitions for CHECKER class
 * @version 1.0
 * @date 23-07-2023
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "checker.hpp"
#include "model.hpp"

CHECKER::CHECKER() {}

CHECKER::~CHECKER() {}

///////////////////////////////////////////////////////////////////////////////
// Function Definitions                                                     //
/////////////////////////////////////////////////////////////////////////////

int CHECKER::check(MODEL *m, PROBLEM *p) {
  // Run all subchecks and return result
  int inputFiles = checkInputFiles(p);
  if (inputFiles) {
    return inputFiles;
  }

  int optionsValid = checkOptionsValid(m, p);
  if (optionsValid) {
    return optionsValid;
  }

  int optionCoverage = checkOptionCoverage(m, p);
  if (optionCoverage) {
    return optionCoverage;
  }

  int constraints = checkConstraints(m, p);
  if (constraints) {
    return constraints;
  }
  return 0;
}

int CHECKER::checkFiles(PROBLEM *p) {
  int result = checkInputFiles(p);
  return result;
}

///////////////////////////////////////////////////////////////////////////////
// Helper Functions                                                         //
/////////////////////////////////////////////////////////////////////////////

int CHECKER::checkInputFiles(PROBLEM *p) {
  // Fetch options and constraints
  std::vector<std::vector<std::string>> options = p->getOptions();
  std::vector<std::vector<std::string>> constraints = p->getConstraints();

  int i = 0; // used to count rows for error messages
  int warning = 0;

  // check each row of options has atleast a name and two choices
  // we don want to outright deny a file because it contains useless options
  // so this only sets a warning flag, which wil be returned if no other errors
  // are found by the checker. The solver can then interpret this information.
  for (const auto row : options) {
    i++;
    if (row.size() < 3) {
      LOGGER() << "Warning in row " << i << " of " << p->getOptionsFileIn()
                << ": Each row should contain at least one category name "
                   "and two elements"
                << std::endl;
      warning = 100;
    }
    if (row.size() < 2) {
      LOGGER() << "Error in row " << i << " of " << p->getOptionsFileIn()
                << ": Each row must contain at least one category name "
                   "and one element"
                << std::endl;
      return 20;
    }
  }

  // Create a map to store valid categories and their corresponding elements
  // from the options
  std::unordered_map<std::string, std::unordered_set<std::string>>
      validCategoryElements;

  // Fill the map with categories and their corresponding elements from the
  // options
  for (const auto &row : options) {
    // Get the category name from the first element of the row
    std::string category = row[0];

    // Add the elements of the category to the set in the map
    for (size_t i = 1; i < row.size(); ++i) {
      validCategoryElements[category].insert(row[i]);
    }
  }

  // Reset row counter
  i = 0;
  // Loop through the constraints and check for valid categories and elements
  for (const auto &row : constraints) {
    i++;
    // The constraints should contain an even number of elements
    if (row.size() % 2 != 0) {
      LOGGER() << "Error in row " << i << " of " << p->getConstraintsFileIn()
                << ": For each element there must be a category" << std::endl;
      return 30;
    }

    // Check each category and its corresponding element
    for (size_t j = 0; j < row.size(); j += 2) {
      const std::string &category = row[j];
      const std::string &element = row[j + 1];

      // Check if the category exists in the map of valid categories
      auto categoryElementsIter = validCategoryElements.find(category);
      if (categoryElementsIter == validCategoryElements.end()) {
        LOGGER() << "Error in row " << i << " of " << p->getConstraintsFileIn()
                  << ": Invalid category name at position " << (j + 1)
                  << std::endl;
        return 30;
      }

      // Check if the element belongs to the category
      const std::unordered_set<std::string> &validElements =
          categoryElementsIter->second;
      if (validElements.find(element) == validElements.end()) {
        LOGGER() << "Error in row " << i << " of " << p->getConstraintsFileIn()
                  << ": Invalid element at position " << (j + 2) << std::endl;
        return 30;
      }
    }
  }

  return warning;
}

int CHECKER::checkOptionCoverage(MODEL *m, PROBLEM *p) {
  std::vector<std::vector<std::string>> options = p->getOptions();
  std::vector<std::vector<std::string>> models = m->getModels();
  // Get filename from model
  std::string filename = m->getModelsFile();

  // Create a map to store the elements for each category in options
  std::unordered_map<std::string, std::vector<std::string>> categoryToElements;

  // Populate the map with data from options
  for (const auto &row : options) {
    if (row.size() >= 2) {
      std::string category = row[0];
      for (size_t i = 1; i < row.size(); i++) {
        categoryToElements[category].push_back(row[i]);
      }
    }
  }

  int row = 0;
  // Check if each row in models contains an element and a category from options
  for (const auto &modelRow : models) {
    row++;
    if (modelRow.size() % 2 != 0) {
      // Each row in models must have an even number of elements (category,
      // element, category, element, etc.)
      std::cerr << "Error in row " << row << " of " << filename
                << ". Each category must be paired with an element."
                << std::endl;
      return 40;
    }

    // Check if the number of categories in the current row matches the number
    // of rows in options
    if (modelRow.size() / 2 != options.size()) {
      std::cerr << "Error in row " << row << " of " << filename
                << ". Each row must contain the same amount of "
                   "categories, as are defined in the options file."
                << std::endl;
      return 40;
    }

    std::unordered_set<std::string> uniqueCategoriesInRow;

    for (size_t i = 0; i < modelRow.size(); i += 2) {
      std::string category = modelRow[i];
      std::string element = modelRow[i + 1];

      // Check if the category exists in options
      if (categoryToElements.find(category) == categoryToElements.end()) {
        std::cerr << "Error in row " << row << " of " << filename
                  << ". Category at position " << (i + 1)
                  << " is not part of options file." << std::endl;
        return 40; // Category not found in options
      }

      // Check if the element is present in the specified category
      if (std::find(categoryToElements[category].begin(),
                    categoryToElements[category].end(),
                    element) == categoryToElements[category].end()) {
        std::cerr << "Error in row " << row << " of " << filename
                  << ". Element at position " << (i + 2)
                  << " is not part of category " << category << "."
                  << std::endl;
        return 40; // Element not found in the specified category
      }

      // Check if the category is unique in the current row
      if (uniqueCategoriesInRow.find(category) == uniqueCategoriesInRow.end()) {
        uniqueCategoriesInRow.insert(category);
      } else {
        std::cerr << "Error in row " << row << " of " << filename
                  << ". Category at position " << (i + 1)
                  << " is a duplicate of another category in this row."
                  << std::endl;
        return 40; // Duplicate category found in the current row
      }
    }
  }

  return 0;
}

int CHECKER::checkConstraints(MODEL *m, PROBLEM *p) {
  std::vector<std::vector<std::string>> constraints = p->getConstraints();
  std::vector<std::vector<std::string>> models = m->getModels();
  // Get filename from model
  std::string filename = m->getModelsFile();

  for (const std::vector<std::string> &constraintRow : constraints) {
    std::unordered_set<std::string> constraintSet(constraintRow.begin(),
                                                  constraintRow.end());

    int row = 0;
    for (const std::vector<std::string> &modelRow : models) {
      row++;
      std::unordered_set<std::string> modelSet(modelRow.begin(),
                                               modelRow.end());

      bool containsAll = true;
      for (const std::string &str : constraintSet) {
        if (modelSet.find(str) == modelSet.end()) {
          containsAll = false;
          break;
        }
      }

      if (containsAll) {
        std::cerr << "Error in row " << row << " of " << filename
                  << ". Row contains match for a combination from the "
                     "constraints file."
                  << std::endl;
        return 40; // Found a row in 'models' that contains a combination from a
                   // row of 'constraints'
      }
    }
  }
  return 0;
}

int CHECKER::checkOptionsValid(MODEL *m, PROBLEM *p) {
  // Get vectors from classes
  std::vector<std::vector<std::string>> options = p->getOptions();
  std::vector<std::vector<std::string>> models = m->getModels();
  // Get filename from model
  std::string filename = m->getModelsFile();

  // Create a map to store the options for each category
  std::unordered_map<std::string, std::vector<std::string>> categoryToElements;

  // Populate the categoryToElements map with data from options
  for (const auto &row : options) {
    if (row.size() >= 2) {
      std::string category = row[0];
      for (size_t i = 1; i < row.size(); i++) {
        categoryToElements[category].push_back(row[i]);
      }
    }
  }

  // Check if each row in models contains a category and element from options
  int row = 0;
  for (const auto &modelRow : models) {
    row++;
    // Each row in models must have an even number of elements (category,
    // element, category, element, etc.)
    if (modelRow.size() % 2 != 0) {
      std::cerr << "Error in row " << row << " of " << filename
                << ". Each category must be paired with an element."
                << std::endl;
      return 40;
    }

    for (size_t i = 0; i < modelRow.size(); i += 2) {
      std::string category = modelRow[i];
      std::string element = modelRow[i + 1];

      // Check if the category exists in options and if the element is present
      // in that category
      if (categoryToElements.find(category) == categoryToElements.end()) {
        std::cerr << "Error in row " << row << " of " << filename
                  << ". Category at position " << i
                  << " is not part of options file." << std::endl;
        return 40; // Category not found in options
      }

      bool elementFound = false;
      for (const auto &optionElement : categoryToElements[category]) {
        if (element == optionElement) {
          elementFound = true;
          break;
        }
      }

      if (!elementFound) {
        std::cerr << "Error in row " << row << " of " << filename
                  << ". Element at position " << i
                  << " is not part of options file." << std::endl;
        return 40; // Element not found in the specified category
      }
    }
  }

  return 0;
}
