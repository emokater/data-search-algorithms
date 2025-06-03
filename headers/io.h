/**
 * \file  io.h
 * \brief Interface for input/output functions:
 *        parsing CSV files and save result to files.
 */

#ifndef IO_H
#define IO_H

#include "flower.h"
#include <string>
#include <vector>

using namespace std;

/// \brief          Reads a CSV file and returns a vector of Flower objects.
/// \param filename Path to the input CSV file.
/// \throws         runtime_error if the file cannot be opened.
/// \return         Vector of Flower objects loaded from the file.
///
/// \details
/// The function opens the given CSV file and discards the first line (assumed to be a header).  
/// Each subsequent line must contain exactly four comma-separated fields:
/// 1. name  
/// 2. color  
/// 3. smell  
/// 4. regions — a list of one or more region names enclosed in square brackets, e.g. `[Region1,Region2,…]`  
///
/// Internally, the parser locates the first three commas to extract the name, color and smell fields.  
/// It then strips the surrounding brackets from the remaining substring and splits it on commas to obtain each region.  
/// A `Flower` is constructed with these values and appended to the result vector.  
/// If the file contains no data lines (only a header or is empty), an empty vector is returned.
vector<Flower> parserCSV(string filename);

/**
 * \brief Run multiple search algorithms on a dataset of Flower objects and save results to files.
 *
 * This function performs the following steps:
 *  1. Measures and records execution time for linear search, binary search tree search,
 *     red-black tree search, hash table search, and multimap search.
 *  2. Writes matching records for each algorithm into separate output files named:
 *     "<size>_linear.txt", "<size>_binary.txt", "<size>_rb.txt", "<size>_hash.txt", "<size>_multimap.txt".
 *  3. Appends timing information (and collision count for hash) into "info_time.txt".
 *
 * \param source Reference to a vector of Flower objects to be searched.
 * \param size   Number of elements in the source vector (expected to match source.size()).
 * \param target The Flower object to search for.
 *
 * \throws std::runtime_error If any output file cannot be opened for writing.
 */
void saveRes(vector<Flower>& source, long size, Flower target);

#endif