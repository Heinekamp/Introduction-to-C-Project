/**
 * @file solver.cpp
 * @author Max Heinekamp
 * @brief Contains function definitions for SOLVER class
 * @version 1.0
 * @date 24-07-2023
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "solver.hpp"
#include "checker.hpp"
#include "model.hpp"

SOLVER::SOLVER() {}

SOLVER::~SOLVER() {}

///////////////////////////////////////////////////////////////////////////////
// Member Functions                                                         //
/////////////////////////////////////////////////////////////////////////////
int SOLVER::solve(PROBLEM *p, MODEL *m) {
  // If the input contains single element categories, these have to be filtered
  // and added back to the model later.
  bool containsUselessOptions = false;
  bool containsUsefulOptions = true;
  std::vector<std::string> uselessOptions;

  // Check problem contains valid input files
  int result = CHECKER::checkFiles(p);
  if (result = 100) {
    containsUselessOptions = true;
  } else if (result) {
    return result;
  }

  // Grab data from problem
  auto options = p->getOptions();
  auto constraints = p->getConstraints();

  // Strip useless Categories from options
  if (containsUselessOptions) {
    std::vector<std::vector<std::string>> deleteLater;
    for (auto row : options) {
      if (row.size() <= 2) {
        // Add category and its element to uselessOptions vector
        uselessOptions.push_back(row[0]);
        uselessOptions.push_back(row[1]);

        deleteLater.push_back(row);
      }
    }
    // Remove useless rows once loop has completed
    for (auto row : deleteLater) {
      // Remove row from options vector
      options.erase(std::remove(options.begin(), options.end(), row),
                    options.end());
    }

    // Check if any uselful categories remain
    if (options.empty()) {
      containsUsefulOptions = false;
      LOGGER() << "INFO: This programm does very little if your options file "
                   "only contains categories with one element..."
                << std::endl;
    }
  }

  // Create vector to store models
  std::vector<std::vector<std::string>> models;
  // Create vector for pairs that will be deletd if row is valid
  std::vector<int> toDelete;

  // Only do solveing if there are useful options to solve with...
  if (containsUsefulOptions) {
    // generate unique pairs
    auto pairs = generatePairs(options);
    // store current pair list for later, as pairs will later be removed
    auto allpairs = pairs;

    int invalidRowCounter = 0;
    while (pairs.size() > 0) {
      // clear toDelelete vector at the start of each cycle
      toDelete.clear();
      // generate row
      auto row = generateRow(options, pairs, allpairs, toDelete);

      // check row is valid and add to models
      bool isValid = checkRowValid(constraints, row);
      // bool isValid = true;
      if (isValid) {
        // add row to model
        models.push_back(row);
        // delete pairs used to create row
        for (auto iterator : toDelete) {
          pairs.erase(pairs.begin() + iterator);
        }

      }
      // if row is not Valid,
      else if (isValid == false) {
        invalidRowCounter++;
      }

      // after 1000 invalid rows, break out of loop
      if (invalidRowCounter > 1000) {
        break;
      }
    }
  }
  // add uselessOptions back into solution
  if (containsUselessOptions) {
    for (auto useless : uselessOptions) {
      for (auto &row : models) {
        // Add category and its element to uselessOptions vector
        row.push_back(useless);
      }
    }
    // remove constraints violations caused by adding uselessOptions
    std::vector<std::vector<std::string>> invalid;
    for (auto row : models) {
      if (checkRowValid(constraints, row) == false) {
        invalid.push_back(row);
      }
    }
    for (auto row : invalid) {
      models.erase(std::remove(models.begin(), models.end(), row),
                   models.end());
    }
  }

  // write models to model
  m->setModel(models);
  return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Helper Functions                                                         //
/////////////////////////////////////////////////////////////////////////////
// Function to generate all possible unique pairs
std::vector<std::tuple<std::string, std::string, std::string, std::string>>
SOLVER::generatePairs(const std::vector<std::vector<std::string>> &options) {
  // Create vector for storing output
  std::vector<std::tuple<std::string, std::string, std::string, std::string>>
      pairs;

  // Iterate through each category
  for (size_t i = 0; i < options.size(); ++i) {
    // Iterate through each element in the current category
    for (size_t j = 1; j < options[i].size(); ++j) {
      // Iterate through other categories
      for (size_t k = i + 1; k < options.size(); ++k) {
        // Iterate through each element in the other category
        for (size_t l = 1; l < options[k].size(); ++l) {
          // Create a pair with elements from different categories only if i < k
          pairs.push_back(std::make_tuple(options[i][0], options[i][j],
                                          options[k][0], options[k][l]));
        }
      }
    }
  }

  return pairs;
}

std::vector<std::string> SOLVER::generateRow(
    const std::vector<std::vector<std::string>> &options,
    std::vector<std::tuple<std::string, std::string, std::string, std::string>>
        &pairs,
    std::vector<std::tuple<std::string, std::string, std::string, std::string>>
        &allPairs,
    std::vector<int> &toDelete) {
  // create vector to store output
  std::vector<std::string> row;

  // Fetch all categories from the options vecotr
  std::unordered_set<std::string> remainingCategories;
  for (const auto &option : options) {
    remainingCategories.insert(option[0]);
  }

  // Initialize randomizer
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  srand(seed); // Set seed for randomiser

  // add random pairs to row until no more pairs can fit
  while (remainingCategories.size() > 1) {

    // Choose random path
    int path = rand() % 100;

    // With high probability
    if ((pairs.size() > 0) && (path > 1 / pairs.size())) {
      // Choose a random pair from pairs
      int iterator = rand() % pairs.size();

      // Check if both categories in the pair are still part of the remaining
      // pairs if they are, add pair to row and remove categories and pair form
      // each list
      auto pair = pairs[iterator];
      std::string category1 = std::get<0>(pair);
      std::string category2 = std::get<2>(pair);
      auto check1 = remainingCategories.find(category1);
      auto check2 = remainingCategories.find(category2);
      if ((check1 != remainingCategories.end()) &&
          (check2 != remainingCategories.end())) {
        // Doing this with a for loop would have been quite messy, as the
        // compiler did not like accessing it with a iterator, unless that
        // iterator was based on the size of the touple
        row.push_back(std::get<0>(pair));
        row.push_back(std::get<1>(pair));
        row.push_back(std::get<2>(pair));
        row.push_back(std::get<3>(pair));

        toDelete.push_back(iterator);
        remainingCategories.erase(check1);
        remainingCategories.erase(check2);
      }
    }
    // otherwise
    else {
      // Choose a random pair from allPairs
      int iterator = rand() % allPairs.size();

      // Check if both categories in the pair are still part of the remaining
      // pairs if they are, add pair to row and remove categories and pair form
      // each list
      auto pair = allPairs[iterator];
      std::string category1 = std::get<0>(pair);
      std::string category2 = std::get<2>(pair);
      auto check1 = remainingCategories.find(category1);
      auto check2 = remainingCategories.find(category2);
      if ((check1 != remainingCategories.end()) &&
          (check2 != remainingCategories.end())) {
        // Doing this with a for loop would have been quite messy, as the
        // compiler did not like accessing it with a iterator, unless that
        // iterator was based on the size of the touple
        row.push_back(std::get<0>(pair));
        row.push_back(std::get<1>(pair));
        row.push_back(std::get<2>(pair));
        row.push_back(std::get<3>(pair));

        remainingCategories.erase(check1);
        remainingCategories.erase(check2);
      }
    }
  }
  // if number of categories was uneven, add one more element from remaining
  // category
  if (remainingCategories.size() != 0) {
    // Get remaining category name
    std::string category = *(remainingCategories.begin());

    // Find row with category name in options
    int i;
    for (i = 0; i < options.size(); ++i) {
      if (options[i].size() > 0 && options[i][0] == category) {
        break;
      }
    }

    // Choose random element from row in options
    //int j = (rand() % (options.size() - 1)) + 1;
    int j = (rand() % (options[i].size()));
    std::string element = options[i][j];

    // Add category & element to output row
    row.push_back(category);
    row.push_back(element);
  }
  // return filled row
  return row;
}

bool SOLVER::checkRowValid(
    const std::vector<std::vector<std::string>> &constraints,
    std::vector<std::string> &row) {
  for (const std::vector<std::string> &constraint : constraints) {
    std::unordered_set<std::string> constraintSet;
    for (size_t i = 0; i < constraint.size(); i += 2) {
      // Collecting pairs of category names and respective elements from
      // constraints
      std::string category = constraint[i];
      std::string element = constraint[i + 1];
      constraintSet.insert(category + element);
    }

    // Checking if pairs from the current constraint exist in the model
    for (size_t i = 0; i < row.size(); i += 2) {
      std::string category = row[i];
      std::string element = row[i + 1];
      if (constraintSet.find(category + element) != constraintSet.end()) {
        // If the pair is found, remove it from the constraint set
        constraintSet.erase(category + element);
      }
    }

    // If the constraint set is empty, return false (invalid model)
    if (constraintSet.empty()) {
      return false;
    }
  }
  return true;
}
