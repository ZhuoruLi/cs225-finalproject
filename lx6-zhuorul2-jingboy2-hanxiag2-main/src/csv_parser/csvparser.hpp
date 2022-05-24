/**
 * @file csvparser.cpp
 * @brief Implementation of csvparser.
 * @date 2021-11-09
 * 
 * @see https://stackoverflow.com/questions/1120140/how-can-i-read-and-parse-csv-files-in-c
 * 
 */

#include <fstream>
#include <iostream>

#include "../airport.h"

using std::string;
using std::vector;
using std::unordered_map;
using std::cerr;
using std::endl;

using ID = string;
using city = string;


enum class CSVState {
    UnquotedField,
    QuotedField,
    QuotedQuote
};

vector<string> util::readCSVRow(const string& row) {
    CSVState state = CSVState::UnquotedField;
    vector<string> fields {""};
    /// Index of the current field.
    size_t i = 0;
    for (char c : row) {
        switch (state) {
            case CSVState::UnquotedField:
                switch (c) {
                    case ',': // end of field
                              fields.push_back(""); i++;
                              break;
                    case '"': state = CSVState::QuotedField;
                              break;
                    default:  fields[i].push_back(c);
                              break; }
                break;
            case CSVState::QuotedField:
                switch (c) {
                    case '"': state = CSVState::QuotedQuote;
                              break;
                    default:  fields[i].push_back(c);
                              break; }
                break;
            case CSVState::QuotedQuote:
                switch (c) {
                    case ',': // , after closing quote
                              fields.push_back(""); i++;
                              state = CSVState::UnquotedField;
                              break;
                    case '"': // "" -> "
                              fields[i].push_back('"');
                              state = CSVState::QuotedField;
                              break;
                    default:  // end of quote
                              state = CSVState::UnquotedField;
                              break; }
                break;
        }
    }
    return fields;
}

/// Read CSV file, Excel dialect. Accept "quoted fields ""with quotes"""
vector<string> util::readCSV(std::istream& in) {
    string row;
    std::getline(in, row);
    if (in.bad() || in.fail()) {
        throw __unexpected_behavior("Unable to read the current line.");
    }
    return readCSVRow(row);
}

template <class T>
void deserialize(vector<T>& container, string pathToFile) {
#ifdef DEBUG
    clog << "Deserializating...";
#endif
    std::filebuf filebuffer;
    if (!filebuffer.open(pathToFile, std::ios::in)) {
        throw __fail_to_open_file(pathToFile);
    }

    std::istream in(&filebuffer);
    while (!in.eof()) {
        try {
            vector<string> aRow = util::readCSV(in);
            if (aRow.size() < 2) {
#           ifdef DEBUG
                clog << "Done." << endl;
#           endif
                return;
            }
            T result(aRow);
            container.push_back(result);
        }
        // Such exception shall continue.
        catch(const __unexpected_behavior& ub) {
#       ifdef DEBUG
            cerr << ub.what() << '\n';
#       endif
            continue;
        }
    }
#ifdef DEBUG
    clog << "Done." << endl;
#endif
}

unordered_map<ID, Airport> createAirportHashmap(string pathToFile) {
    unordered_map<city, Airport> ret;
    vector<Airport> airports;
    deserialize(airports, pathToFile);

    for (Airport airport : airports)
        ret[airport.getCity()] = airport;
    
    return ret;
}

Graph createGraphFromVector(vector<Airport> airports, vector<Route> routes) {
    Graph ret;
    for (Airport airport : airports)
        ret.insertVertex(airport);
    for (Route route : routes)
        try {
            ret.insertEdge(route);
        }
        catch (const __unexpected_behavior &ub) {
#       ifdef DEBUG
            cerr << ub.what() << endl;
#       endif
            continue;
        }
    return ret;
}
