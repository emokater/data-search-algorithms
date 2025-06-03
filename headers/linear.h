/// \file  linear.h
/// \brief Contains functions for performing linear search on an array.
/// 
/// This file provides two templated functions:
/// - linearSearch: Finds the first occurrence of a given element in an array.
/// - searchAll: Finds all occurrences of a given element and returns their indices.

#ifndef LINEAR_H
#define LINEAR_H

#include <vector>
using namespace std;

/**
 * \brief Perform a linear search to find the first occurrence of an element in an array.
 *
 * \param a     Pointer to the array of elements of type T.
 * \param start Index in the array from which to begin the search.
 * \param size  Total number of elements in the array (one past the last valid index).
 * \param b     The value to search for in the array.
 * \return      The index of the first matching element, or -1 if the element is not found.
 */
template<class T>
int linearSearch(T a[], long start, long size, T b) {
    for (long i = start; i < size; ++i) {
        if (a[i] == b) {
            return i;
        }
    }
    return -1;
}

/**
 * \brief Find all occurrences of a given element in an array.
 *
 * This function uses linearSearch to locate each instance of the target value
 * in the array. It stores each found index in a std::vector and returns the vector.
 *
 * \param a    Pointer to the array of elements of type T.
 * \param size Total number of elements in the array.
 * \param b    The value to search for in the array.
 * \return     A std::vector<int> containing the indices where the element b was found.
 *             If the element is not found, the vector will be empty.
 */
template<class T>
vector<int> searchAll(T a[], long size, T b) {
    vector<int> res;

    int i = linearSearch(a, 0, size, b);
    while (i != -1) {
        res.push_back(i);
        i = linearSearch(a, i+1, size, b);
    }

    return res;
}

#endif