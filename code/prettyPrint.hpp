/**
 * @file prettyPrint.hpp
 * @author Max Heinekamp
 * @brief Contains declarations for PRETTYPRINT class
 * @version 1.0
 * @date 24-07-2023
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#ifndef PAIRWISE_PRETTYPRINT
#define PAIRWISE_PRETTYPRINT

class PROBLEM;
class MODEL;

/**
 * @brief This class prints the data from the PROBLEM and MODEL class to CSV
 * files
 */
class PRETTYPRINT {
public:
  PRETTYPRINT();
  ~PRETTYPRINT();

  /**
   * @brief Sort the parsed data
   */
  static void sort(PROBLEM *p);

  /**
   * @brief Print Options to specified output file
   *
   * @param p reference to instance of PROBLEM class contianing options and
   * filename
   * @return int status code (see documetnation)
   */

  static int printOptions(PROBLEM *p);
  /**
   * @brief Print Constraints to specified output file
   *
   * @param p reference to instance of PROBLEM class contianing constraints and
   * filename
   * @return int status code (see documetnation)
   */

  static int printConstraints(PROBLEM *p);

  /**
   * @brief Print models to specified output file
   *
   * @param p reference to instance of MODEL class models constraints and
   * filename
   * @return int status code (see documetnation)
   */
  static int printModels(MODEL *m);

private:
  /**
   * @brief Helper function to print a 2-dimensional vecotr to a CSV file
   *
   * @param filename filename for the output file
   * @param vector vector to be printed to the output file
   * @return int status code (see documentation)
   */
  static int print(std::string *filename,
                   std::vector<std::vector<std::string>> *vector);
};

#endif