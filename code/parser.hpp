/**
 * @file parser.hpp
 * @author Max Heinekamp
 * @brief TContains declarations for the PARSER class
 * @version 1.0
 * @date 24-07-2023
 *
 * @copyright Copyright (c) 2023
 */

#ifndef PAIRWISE_PARSER
#define PAIRWISE_PARSER

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "logger.hpp"

// Forwar declaration because of circular dependency
class PROBLEM;
class MODEL;

/**
 * @brief This class imports data to the PROBLEM and MODEL class
 */
class PARSER {
public:
  PARSER();
  ~PARSER();

  /**
   * @brief Parses Options from csv file
   *
   * @param p instance of PROBLEM class to parse to
   * @return int status code (see documentation)
   */
  static int parseOptions(PROBLEM *p);

  /**
   * @brief Parses constraints from csv file
   *
   * @param p instance of PROBLEM class to parse to
   * @return int status code (see documentation)
   */
  static int parseConstraints(PROBLEM *p);

  /**
   * @brief Parses Model from csv file
   *
   * @param m instance of MODEL class to parse to
   * @param filename file to parse data from
   * @return int status code (see documentation)
   */
  static int parseModel(MODEL *m);

private:
  /**
   * @brief Helper function to parse a 2-dimensional vector from an input file
   *
   * @param filename Filename of the input file
   * @param parsedData Vector to be filled with parse data
   * @return int
   */
  static int parse(std::string *filename,
                   std::vector<std::vector<std::string>> *parsedData);
};

#endif