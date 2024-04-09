/**
 * @file problem.hpp
 * @author Max Heinekamp
 * @brief Contains declarations for PROBLEM class
 * @version 1.0
 * @date 24-07-2023
 *
 * @copyright Copyright (c) 2023
 */

#ifndef PAIRWISE_PROBLEM
#define PAIRWISE_PROBLEM

#include "prettyPrint.hpp"
#include <stdio.h>
#include <string>
#include <vector>

// Forward declaration because of circular dependency
class PARSER;

/**
 * @brief This class stores the inported information about the problem
 */
class PROBLEM {
public:
  PROBLEM();

  /**
   * @brief Construct a new PROBLEM object
   *
   * @param optionsI String containing filename for options file, default =
   * in.options
   * @param constraintsI String containing filename for consstrains file,
   * default = in.constraints
   * @param optionsO String containing filename for options output file,
   * default = out.options
   * @param constraintsO String containing filename for consstrains output file,
   * default = out.constraints
   */
  PROBLEM(std::string optionsI = "in.options",
          std::string constraintsI = "in.constraints",
          std::string optionsO = "out.options",
          std::string constraintsO = "out.constraints");
  ~PROBLEM();

  /**
   * @brief parses the data from the given csv files (#m_optionFileIn,
   * #m_constrainFileIn)
   *
   * @return Staus code (see documentation)
   */
  int parse();

  /**
   * @brief prints the data to the desired csv files (#m_optionFileOut,
   * #m_constrainFileOut)
   *
   * @return Staus code (see documentation)
   */
  int print();

  /**
   * @brief Getter function for #m_options vector
   *
   * @return Parsed options as std::vector<std::vector<std::string>>
   */
  std::vector<std::vector<std::string>> getOptions() const;

  /**
   * @brief Getter function for #m_constraints vector
   *
   * @return Parsed constraints as std::vector<std::vector<std::string>>
   */
  std::vector<std::vector<std::string>> getConstraints() const;

  /**
   * @brief Set the #m_options vector
   *
   * @param options Vector to be written to #m_options
   */
  void setOptions(std::vector<std::vector<std::string>> options);
  /**
   * @brief Set the #m_constraints vector
   *
   * @param constraints Vector to be written to #m_constraints
   */
  void setConstraints(std::vector<std::vector<std::string>> constraints);

  /**
   * @brief Returns the #m_optionFileIn filename
   *
   * @return std::string Filename for Options file
   */
  std::string getOptionsFileIn() const;

  /**
   * @brief Returns the #m_constrainFileIn filename
   *
   * @return std::string Filename for Constraints file
   */
  std::string getConstraintsFileIn() const;

  /**
   * @brief Returns the #m_optionFileOut filename
   *
   * @return std::string Filename for new Options file
   */
  std::string getOptionsFileOut() const;

  /**
   * @brief Returns the #m_constrainFileOut filename
   *
   * @return std::string Filename for new constraints file
   */
  std::string getConstraintsFileOut() const;

private:
  /**
   * @brief Stores the imported options
   * @note  Each category is stored as a vector, wehre the first element is
   *        the name of the catgeory.
   */
  std::vector<std::vector<std::string>> m_options;

  /**
   * @brief Stores the imported constraints
   * @note  Each group of constraints is stored as a vector.
   */
  std::vector<std::vector<std::string>> m_constraints;

  /**
   * @brief Filename for the csv file containing the options
   */
  std::string m_optionFileIn;

  /**
   * @brief Filename to which the csv file containing the options will be
   *        written
   */
  std::string m_optionFileOut;

  /**
   * @brief Filename for the csv file containing the constraints
   */
  std::string m_constrainFileIn;

  /**
   * @brief Filename to which the csv file containing the constraints will be
   *        written
   */
  std::string m_constrainFileOut;
};

#endif
