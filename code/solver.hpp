/**
 * @file solver.hpp
 * @author Max Heinekamp
 * @brief Contatins declarations for SOLVER class
 * @version 1.0
 * @date 24-07-2023
 *
 * @copyright Copyright (c) 2023
 */

#ifndef PAIRWISE_SOLVER
#define PAIRWISE_SOLVER

#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <tuple>
#include <unordered_set>

#include "problem.hpp"
#include"logger.hpp"

// Forward declaration
class MODEL;

/**
 * @brief This class finds solutions based on the options and constraints in the
 * PROBLEM class and saves them to the MODEL class
 */
class SOLVER {

public:
  SOLVER();
  ~SOLVER();

  /**
   * @brief Generate possible solutions to the Problem and save them to the
   * model
   *
   * @param p Pointer to instance of PROBLEM class with required data for
   * solving
   * @param m Pointer to instance of MODEL class too which result will be
   * written
   * @return int int status code (see documentation)
   */
  static int solve(PROBLEM *p, MODEL *m);

  friend bool testGeneratePairs();
  friend bool testGenerateRow();
  friend bool testCheckRowValid();
  friend bool testSolver();

private:
  /**
   * @brief generates vecotr filled with unique pairs of elements based on
   * categories from options vector
   *
   * @param options options vector used to generate pairs
   * @return std::vector<std::tuple<std::string, std::string, std::string,
   * std::string>> vector of touples containing pairs of elements with their
   * categories
   */
  static std::vector<
      std::tuple<std::string, std::string, std::string, std::string>>
  generatePairs(const std::vector<std::vector<std::string>> &options);

  /**
   * @brief generates a random row based on the supplied options and pairs
   * vecotrs
   *
   * @param options options vector used to generate pairs
   * @param pairs pairs to fill row with
   * @param allPairs vector of all orgiginally calculatd pairs, used so that
   * program does not infinitely loop when no more pairs are left to cover
   * remaining categories
   * @param toDelete Reference to vector where iterators of pairs that were
   * used to create the row will be stored so that they can be deleted if row
   * turns out to be valid
   * @return std::vector<std::string> vector representing row
   */
  static std::vector<std::string>
  generateRow(const std::vector<std::vector<std::string>> &options,
              std::vector<std::tuple<std::string, std::string, std::string,
                                     std::string>> &pairs,
              std::vector<std::tuple<std::string, std::string, std::string,
                                     std::string>> &allPairs,
              std::vector<int> &toDelete);

  /**
   * @brief Checks if a row complies with all constraints
   *
   * @param constraints vector containing constraints to check against
   * @param row vector containing row to be checked
   * @return true row complies with constraints
   * @return false row does not comply with constraints
   */
  static bool
  checkRowValid(const std::vector<std::vector<std::string>> &constraints,
                std::vector<std::string> &row);
};

#endif