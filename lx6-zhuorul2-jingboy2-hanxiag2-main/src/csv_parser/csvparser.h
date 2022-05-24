/**
 * @file csvparser.h
 * @author Unidentity (jingboy2@illinois.edu)
 * @brief Parsers for OpenFlight source data.
 * @date 2021-11-09
 * 
 */

#pragma once

#include <istream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

#include "../exceptions.h"
#include "../graph.h"

using std::string;
using ID = string;

namespace util {
    /**
     * @brief Healper function of readCSV.
     * Read one row of csv source file, 
     * storing each value into a vector.
     * 
     * @param row The particular row to parse.
     * @return A vector of parsed values in `string`.
     */
    std::vector<string> readCSVRow(const string& row);

    /**
     * 
     * @brief CSV parser according to the given stream.
     * 
     * @param in Input stream.
     * @return A 2D vector of string values.
     */
    std::vector<string> readCSV(std::istream &in);
}

/**
 * @brief Transform parsed data into objects.
 * 
 * @param[out] container Vector of objects (airport, route) to deserialize into.
 * The sequence strictly follows the order indicated 
 * by https://openflights.org/data.html (top-down).
 * 
 * @return Whether deserialization succeeded.
 * @throw __fatal_error Deserialization encountered unresolveable problem.
 */
template <class T>
void deserialize(std::vector<T>& container, std::string pathToFile);

/**
 * @brief Transform parsed data into objects, indexed by unique identifier of string.
 * 
 * @param container Hashmap that maps a unique identifier of string to the speficied object.
 * @param pathToFile Path to source CSV file, in string.
 */
std::unordered_map<ID, Airport> createAirportHashmap(string pathToFile);

/**
 * @brief Create a graph from parsed data.
 * 
 * @return Graph generated.
 */
Graph createGraphFromVector(std::vector<Airport>, std::vector<Route>);

#include "csvparser.hpp"