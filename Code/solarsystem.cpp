/// @file satellite.cpp

// TODO Header

/// Original project documents by Adam T Koehler, PhD
/// UIC CS211 Spring 2024
/// @brief Implementations for the Solar System class that allows 
///        collection of and interaction with Celestial objects.
///        Utilized as part of the Interstellar Travel App.

// Copyright Notice
// This document is protected by U.S. copyright law. Reproduction and 
// distribution of this work, including posting or sharing through any medium, 
// is explicitly prohibited by law, and also violates UIC's Student 
// Disciplinary Policy (A2-c. Unauthorized Collaboration; and A2-e3. 
// Participation in Academically Dishonest Activities: Material Distribution).

#include "solarsystem.h"
#include "celestial.h"

// Local Helper Functions
// If you were allowed to change the the .h files many, if not all,
// of these would go into a private section of the class declaration.





// Class Implementations
// Defining all functions from the header that are not already
// fully defined within the header and class declaration.

/// @brief Create a SolarSystem object specifying values for all private
///     data members of the class.
/// @param n the value to set the private data member name to
SolarSystem::SolarSystem(const string &n) {
    this->name = n;
}

/// @brief return name of SolarSystem
string SolarSystem::getName() const {
    return this->name;
}

/// @brief return the celestial bodies of the SolarSystem
vector<shared_ptr<Celestial>> SolarSystem::getCelestialBodies() const {
    return this->celestialBodies;
}

/// @brief Acquire a pointer to a Celestial object at a specific
/// index in the private data member celestialBodies
/// @param ind the index of the requested celestial object
shared_ptr<Celestial> SolarSystem::getCelestialAt(int ind) {
    if (ind >= 0 && ind < static_cast<int>(this->celestialBodies.size())) {
        return this->celestialBodies.at(ind);
    }
    return nullptr;  // return nullptr if the index is out of bounds
}

/// @brief set the name of the SolarSystem
/// @param n is the name to set it to
void SolarSystem::setName(const string &n) {
    this->name = n;
}

/// @brief clear the vector of connections to other SolarSystems
void SolarSystem::clearConnections() {
    this->connections.clear();
}

/// @brief Add a Celestial pointer to the back of private data member celestialBodies.
/// @param newC is the celestial ptr to add
void SolarSystem::insertCelestial(shared_ptr<Celestial> &newC) {
    this->celestialBodies.push_back(newC);
}

/// @brief Add a Solar System pointer to the back of private data member connections.
/// @param con is the SolarSystem ptr to add
void SolarSystem::addConnection(const shared_ptr<SolarSystem> &con) {
    // make sure con is not nullptr
    if (con == nullptr) {
        return;
    }
    
    // make sure connection (or a SolarSystem with a similiar name) doesnt already exist
    for (const auto& connection : this->connections) {
        if (connection == con || connection->getName() == con->getName()) {
            return;
        }
    }

    this->connections.push_back(con);
}

/// @brief return number of celestial bodies in the priv data member celestialBodies
int SolarSystem::numCelestialBodies() const {
    return this->celestialBodies.size();
}

/// @brief return number of celestial bodies in the priv data member connections
int SolarSystem::numConnections() const {
    return this->connections.size();
}

/// @brief count the number of planets in the celestialBodies private vector
int SolarSystem::numPlanets() const {
    int ct = 0;
    for (const auto& celestialBody : celestialBodies) {
        if (dynamic_pointer_cast<Planet>(celestialBody) != nullptr) {
            // dynamic pointer cast to Planet pointer successful
            ct++;
        }
    }
    return ct;
}

/// @brief count the number of stars in the celestialBodies private vector
int SolarSystem::numStars() const {
    int ct = 0;
    for (const auto& celestialBody : celestialBodies) {
        if (dynamic_pointer_cast<Star>(celestialBody) != nullptr) {
            // dynamic pointer cast to Star pointer successful
            ct++;
        }
    }
    return ct;
}

/// @brief count the number of satellites orbiting planets in the celestialBodies private vector
int SolarSystem::numSatellites() const {
    int ct = 0;
    for (const auto& celestialBody : celestialBodies) {
        shared_ptr<Planet> planet = dynamic_pointer_cast<Planet>(celestialBody); 
        if (planet != nullptr) {
            // dynamic pointer cast to Planet pointer successful
            ct += planet->numSats();
        }
    }
    return ct;
}

/// @brief Dermine whether specified connection with provided name exists
/// e.g. A->B is only connection, calling with "B" will result in true
///      A->B is only connection, calling with "C" will result in false
/// @param name the name we are checking for in the connections vector
bool SolarSystem::connectionExists(const string &name) const {
    for (const auto& connection : connections) {
        string connectionName = connection->getName();
        if (connectionName == name) {
            return true;
        }
    }
    return false;
}

/// @brief convert Solar System to a readable multi-line string
/// containing all of its Celestial bodies contained
/// directly or indirectly in the private data member
string SolarSystem::toString() const {
    // get the SolarSystem name
    string details = this->getName();
    
    // get the celestial bodies' in this solar system names
    for (const auto& celestialBody : this->celestialBodies) {
        details += "\n  " + celestialBody->toString();
    }

    return details;
}

/// @brief convert Solar Systems connections to string
/// {con1_name, con2_name, ...}
string SolarSystem::connectionsToString() const {
    string details = "{"; int ind = 0;
    for (const auto& connection : connections) {
        if (ind > 0) { details += ", "; }
        details += connection->getName();
        ind++;
    }
    details += "}";

    return details;
}