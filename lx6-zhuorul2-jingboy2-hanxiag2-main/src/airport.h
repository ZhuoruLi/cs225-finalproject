#pragma once

#include <string>
#include <vector>
#include <iostream>

using std::string;

class Airport {
    public:
        /**
         * @brief Default constructor.
         * 
         */
        Airport();

        /**
         * @brief Destroy the Airport object
         * 
         */
        ~Airport();

        /**
         * @brief Parameterized constructor.
         * 
         * @note Set up class members just according to
         * the sequence on the website.
         * 
         * @param attributes Vector of attributes in order.
         */
        Airport(std::vector<string> attributes);

        /**
         *we use airportId as the key because it is unique
         */
        Airport(string airportId);

        /**
         * @brief Copy constructor.
         * 
         * @param rhs Airport object to copy from.
         */
        Airport(const Airport & other);

        string getID() const;

        string getCity() const;

        double getLatitude() const;

        double getLongitude() const;

        /**
         * @brief Equality operator.
         * 
         * @param other Airport object to compare with.
         * 
         * @return true 
         * @return false 
         */
        bool operator==(Airport const &other) const {
            return _airportId == other._airportId;
        }

        /**
         * @brief Assignment operator.
         * 
         * @param other Airport object to assign from.
         * 
         * @return Assigned Airport object.
         */
        Airport & operator=(const Airport & rhs);
        
    private:
        string _airportId;
        string _city;
        double _latitude;
        double _longitude;
    
    private:
        void _copy(const Airport & rhs);
        void _clear();
};

// Inject std::hash<Airport> to allow Airport to be used as a key to std::unordered_map;
namespace std {

template<> 
struct hash<Airport> {
    std::size_t operator()(const Airport & v) const noexcept {
        return std::hash<string>()(v.getID());
    }
};

}