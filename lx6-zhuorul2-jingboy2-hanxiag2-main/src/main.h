/**
 * @file main.h
 * @author Unidentity (jingboy2@illinois.edu)
 * @date 2021-12-11
 * 
 */

// #define DEBUG

#pragma once

#include <iostream>
#include <fstream>
#include <cstring>

#include "graph.h"
#include "csv_parser/csvparser.h"

#ifdef DEBUG
#   include <unistd.h>
#   include "bfs/bfs.h"
#endif

#define USAGE \
"   A Simple program that extracts flight data and computes the shortest path between airports.\n" \
"   Usage:\n" \
"   ./release [-d|--dir DIR] [-o|--out FILENAME] [--interactive] start_code dest_code\n" \
"       --dir -d    The path to the source CSV file.\n" \
"       --out -o    File name of output.\n" \
"       --interactive   Enable interactive mode." \
"       --print-all-airports -p     Print all airports available."

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */
