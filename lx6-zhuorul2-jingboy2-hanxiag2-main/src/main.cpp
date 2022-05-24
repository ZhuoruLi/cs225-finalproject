/**
 * @file main.cpp
 * @date 11.05.2021
 */

#include "main.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::flush;
using cs225::PNG;

/// Functions for debugging.
#ifdef DEBUG
inline void printCwdInfo() {
    char *cwd = get_current_dir_name();
    cout << "Current working directory: " << cwd << endl;
    free(cwd);
}
void traverseGraph(Graph &g, const char* start) {
    cout << "Traversing through graph starting from " << start << "..." << endl;
    BFSTraversal traversal(g, start);
    for (auto it = traversal.begin(); it != traversal.end(); ++it) {
        cout << "Airport(ID=" << (*it).getID();
        cout << ", City=" << (*it).getCity();
        cout << ", Lat=" << (*it).getLatitude();
        cout << ", Long=" << (*it).getLongitude() << ")" << endl;
    }
}
void printRoutes(vector<Route> &routes) {
    for (Route route : routes) {
        cout << "Route(Start=";
        cout << route.getStart();
        cout << ", Dest=";
        cout << route.getDestination();
        cout << ")" << endl;
    }
}
#endif

/************************************* T O O L S ************************************/

/**
 * @brief Parse the arguments of main.
 * 
 * @param argc Argument count
 * @param argv Argument values, in char*
 * @param[out] dir Directory parameter to parse. Will be altered.
 */
void parseArgs(int argc, char* argv[],
        string &dir_to_data,
        string &out,
        bool &interactive,
        bool &printAllAprts,
        string &s_c,
        string &d_c
    )
{
    vector<char*> unpaired_args;
    bool hasArg = false;
    for (int i = 1; i < argc; i++) {
        hasArg = true;
        if ((std::strcmp(argv[i], "-d") == 0)
            || (std::strcmp(argv[i], "--dir") == 0))
        {
            if (i != argc - 1) {
                dir_to_data = argv[i + 1];
                i++;
            }
        }
        else if ((std::strcmp(argv[i], "-o") == 0)
            || (std::strcmp(argv[i], "--out") == 0))
        {
            if (i != argc - 1) {
                out = argv[i + 1];
                i++;
            }
        }
        else if ((std::strcmp(argv[i], "--interactive") == 0))
        {
            interactive = true;
        }
        else if ((std::strcmp(argv[i], "-p") == 0)
            || (std::strcmp(argv[i], "--print-all-airports") == 0))
        {
            printAllAprts = true;
        }
        else 
            unpaired_args.push_back(argv[i]);
    }

    if (!interactive && unpaired_args.size() == 2) {
        s_c = unpaired_args[0];
        d_c = unpaired_args[1];
        unpaired_args.clear();
    }
    else if (interactive) {
        return;
    }
    else if (printAllAprts) {
        return;
    }
    else {
        cout << USAGE << endl;
        exit(1);
    }

    if (!unpaired_args.empty() || !hasArg) {
        cout << USAGE << endl;
        exit(1);
    }
}


void parseCSV(vector<Airport> &airports, vector<Route> &routes, string &dir) {
    /// Directory format correction.
    if (dir.back() != '/')
        dir.push_back('/');

    const string airportCSVFileName = "airports.csv";
    const string routeCSVFileName = "routes.csv";

    // Deserialization.
    try {
        deserialize(airports, dir + airportCSVFileName);
        deserialize(routes, dir + routeCSVFileName);
    }
    // Such exception shall halt the process.
    catch(const __fatal_error& fe) {
        cerr << RED << "Fatal error caught whilst deserializing." << '\n';
        cerr << fe.what() << RESET << endl;
        exit(-1);
    }
    // Unknown exception shall halt the progress as well.
    catch(const std::exception& e) {
        cerr << RED << "Unknown exception caught whilst deserializing..." << '\n';
        cerr << e.what() << RESET << endl;
        exit(-1);
    }
}


bool userChoice(const char* msg) {
    string answer;
    for (;;) {
        cout << msg;
        cout << "\n\t (y\\n) -> " << flush;
        cin >> answer;
        if (answer == "y") {
            return true;
        }
        else if (answer == "n") {
            return false;
        }
        else {
            cout << "Please enter either y or n." << endl;
            continue;
        }
    }
}


/**
 * @brief Parse the CSV files in dir provided, building
 * the graph w/ data parsed.
 * 
 * @param[out] graph Graph to be initiated.
 * @param[in] dir Directory that contains the source CSV files.
 */
void initGraph(Graph &graph, string &dir) {
    vector<Airport> airports;   vector<Route> routes;
    parseCSV(airports, routes, dir);
    graph = createGraphFromVector(airports, routes);
    graph.setDir(dir);
}

inline void initWorldMap(PNG &map, string dir) {
    /// Directory format correction.
    if (dir.back() != '/')
        dir.push_back('/');

    const string worldMapName = "map.png";
    if (!map.readFromFile(dir + worldMapName)) {
        cerr << RED << "Cannot open " << dir << worldMapName << RESET << endl;
        exit(-1);
    }
}


/**
 * @brief 
 * 
 * @param worldMap World map PNG object
 * @param g The Graph
 * @param path The shortest path linked list.
 * @return true if nothing went wrong.
 * @return false if something went wrong.
 */
bool resolvedMapWriteToFile(
        Image &worldMap,
        Graph &g,
        list<string> &path,
        string &outfile) 
{
    // Create PNG file.
    std::ofstream resultDotPNG;
    resultDotPNG.open( outfile, ios::out | ios::trunc );
    resultDotPNG.close();

    try {
        PNG ret = g.drawpath(worldMap, path);
        return ret.writeToFile(outfile);
    }
    catch (const std::exception &e) {
#   ifdef DEBUG
        cerr << "Unknown exception caught whilst writing result to file." << '\n';
        cerr << e.what() << endl;
#   endif
        return false;
    }
    return true;
}


inline void printPath(std::list<string> &p, Graph &g) {
    cout << '\n';
    for (auto ID_it = p.begin(); ID_it != p.end(); ) {
        cout << CYAN << g.vertexTable[*ID_it].getCity() << RESET;
        cout << "(code=" << *ID_it << ')';
        if (++ID_it != p.end())
            cout << MAGENTA " ==> " << RESET;
    }
    cout << '\n' << endl;
}

inline void printAirports(string &dir) {
    vector<Airport> airports;   vector<Route> routes_unused;
    parseCSV(airports, routes_unused, dir);
    unsigned count = 0;
    for (auto airport = airports.begin(); airport != airports.end(); ++airport) {
        cout << BOLDYELLOW << "Airport" << CYAN << "(" << RESET;
        cout << "ID=" << BOLDBLUE << airport->getID() << RESET;
        cout << ", City=" << BOLDBLUE << airport->getCity() << RESET;
        cout << ", Lat=" << BOLDBLUE << airport->getLatitude() << RESET;
        cout << ", Long=" << BOLDBLUE << airport->getLongitude() << RESET;
        cout << CYAN << ")" << RESET << endl;
        if (count == 2500) {
            if (userChoice("Do you wish to continue?")) {
                goto CONTINUE;
            }
            else {
                cout << "User requested to quit." << endl;
                return;
            }
        }
        CONTINUE:
        count %= 2500;
        count++;
    }
    cout << endl;
}


/**
 * @brief Validate input code of airport.
 * If is valid, the conversion should not throw an exception.
 * 
 * @param input User inputs
 * @return true 
 * @return false 
 */
inline bool validCode(const string &input) {
    try {
        std::stod(input);
    }
    catch (const std::exception &e) {
        return false;
    }
    return true;
}


/// Commandline mode.
inline void performCmdFunc(
        string &outfile,
        Graph &graph,
        Image &worldMap,
        string &start_code,
        string &destination_code
) {
    // Compute the shortest path.
    cout << "Calculating the best path to " << destination_code << "..." << flush;
    std::list<string> shortestPath = graph.shortestpath(start_code, destination_code);
    cout << "Done." << endl;

    // Restart if there's no path.
    if (shortestPath.size() == 1) {
        cout << YELLOW << "No path from ";
        cout << start_code << " to "; 
        cout << destination_code;
        cout << '.' << RESET << endl;
        return;
    }
    // Show the path.
    printPath(shortestPath, graph);

    // Draw the path to the world map and write to file.
    cout << "Writing result..." << flush;
    bool success = resolvedMapWriteToFile(worldMap, graph, shortestPath, outfile);
    if (!success) {
        cout << '\r' << RED << "Failed writing to " << outfile << RESET << endl;
        return;
    }
    else
        cout << '\r' << GREEN << "Result written to " << outfile << RESET << endl;
}

/// Interactive mode.
inline void performUserInteraction(
        string &outfile,
        Graph &graph,
        Image &worldMap
) {
    for (;;) {
        // Take user's input;
        // Expected input would be the openflight code of requested airport.
        string start_code, destination_code;
        cout << "Enter where you want to take off:\n\t-> " << flush;
        cin >> start_code;
        // Invalid input jumps to quit request part.
        if (!validCode(start_code)) {
            cout << "Invalid airport code. ";
            if (userChoice("Do you wish to quit?")) {
                cout << "User requested to quit." << endl;
                return;
            }
            else {
                continue;
            }
        }

        RE_REQUEST:
        cout << "Enter where you want to land:\n\t-> " << flush;
        cin >> destination_code;
        // Invalid input
        if (!validCode(destination_code)) {
            cout << "Invalid airport code. ";
            goto RE_REQUEST;
        }
        
        // The rest part just resembles to the CMD mode.
        performCmdFunc(
            outfile,
            graph,
            worldMap,
            start_code,
            destination_code
        );

        cout << endl;
    }
}



    /////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////      M    A    I    N       ///////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[]) {
    // Print current working directory when debugging is on.
#ifdef DEBUG
    printCwdInfo();
#endif
    // Parse arguments.
    string data_dir, outfile, start_code, destination_code;
    data_dir = "data/";          // "data/" by default.
    outfile = "result.png";      // "result.png" by default.
    bool interactiveMode = false;
    bool printAllAirports = false;
    parseArgs(argc, argv,
        data_dir,
        outfile,
        interactiveMode,
        printAllAirports,
        start_code,
        destination_code
    );

    cout << YELLOW << "Initiating..."  << '\r' << RESET << flush;
    Graph graph;          initGraph(graph, data_dir);
    Image worldMap;       initWorldMap(worldMap, data_dir);
    cout << GREEN << "Initiated.    " << RESET << endl;

    if (interactiveMode)
        performUserInteraction(outfile, graph, worldMap);
    else if (printAllAirports)
        printAirports(data_dir);
    else
        performCmdFunc(
            outfile,
            graph,
            worldMap,
            start_code,
            destination_code
        );

    return 0;
}
