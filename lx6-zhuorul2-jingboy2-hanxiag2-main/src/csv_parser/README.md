# **CSV Parser Module**  
## Functionality:
Accepts a reference of _empty_ `vector` of any class `T` and a `string` that indicates the path to the csv file to be parsed, fills the passed `vector` with parsed data _(aka `T` objects)_.

## Usage:
1. Create an empty `vector<T>` object (e.g. `vector<Airport> airports`).
2. Create a `string` and initialize with the expected path to csv file. (e.g. `string pathToFile("data/airports.csv")`).
3. Call `deserialize(airports, pathToFile)`.  

## Note:
- Functions with namespace `util` are not intended for external calls.
- Class `T` must implement a constructor with parameter `vector<string>` which contains properties needed by such class.


The core functionality is adapted from an answer of parsing csv files on stackoverflow _(see https://stackoverflow.com/questions/1120140/how-can-i-read-and-parse-csv-files-in-c)_.