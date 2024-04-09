/**
 * @file checker.hpp
 * @author Max Heinekamp
 * @brief Contains definitions for CHECKER class
 * @version 1.0
 * @date 18-07-2023
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef PAIRWISE_CHECKER
#define PAIRWISE_CHECKER

#include "problem.hpp"
#include "logger.hpp"

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// Forward declaration
class MODEL;

/**
 * @brief Checks validity of generated soltuions
 *
 */
class CHECKER {
public:
  CHECKER();
  ~CHECKER();

  /**
   * @brief Checks if a model is valid based on the input files soted in the
   * problem
   *
   * @param m reference to instance of model class containing model
   * @param p reference to instance of problem class containting options and
   * constraints
   * @return int status code (see documentation)
   */
  static int check(MODEL *m, PROBLEM *p);

  /**
   * @brief Allows access to the internal checkInputFiles() function
   * @note The choice to create this function instead of exposiong the internal
   * function as public was made so that future changes to the behaviour of the
   * checkInputFiles function can be translated here to keep the current
   * behaviour and prevent other parts of the programm from breaking.
   *
   * @param p reference to instance of problem class containting options and
   * constraints
   * @return int status code (see documentation)t
   */
  static int checkFiles(PROBLEM *p);

  // Friends
  friend bool testInputFiles();
  friend bool testOptionsCoverage();
  friend bool testConstraints();
  friend bool testOptionsValid();

private:
  /**
   * @brief checks if option and constraint files are valid
   *
   * @param p reference to instance of problem class containting options and
   * constraints
   * @return int status code (see documentation)
   */
  static int checkInputFiles(PROBLEM *p);

  /**
   * @brief check if each Mdoel contains all options
   *
   * @param p reference to instance of problem class containting options and
   * constraints
   * @param m reference to instance of model class containing model
   * @return ints tatus code (see documentation)
   */
  static int checkOptionCoverage(MODEL *m, PROBLEM *p);

  /**
   * @brief check if each Mdoel contains only valid categories and options
   *
   * @param m reference to instance of model class containing model
   * @param p reference to instance of problem class containting options and
   * constraints
   * @return int status code (see documentation)
   */
  static int checkOptionsValid(MODEL *m, PROBLEM *p);

  /**
   * @brief checks if all Models obeys the constraints
   *
   * @param p reference to instance of problem class containting options and
   * constraints
   * @param m reference to instance of model class containing model
   * @return int status code (see documentation)
   */
  static int checkConstraints(MODEL *m, PROBLEM *p);
};

#endif