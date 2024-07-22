/// @file flightpath.cpp

// TODO Header

/// Original project documents by Adam T Koehler, PhD
/// UIC CS211 Spring 2024
/// @brief Flight path class implementations.
///        Utilized by the Interstellar Travel App.

// Copyright Notice
// This document is protected by U.S. copyright law. Reproduction and 
// distribution of this work, including posting or sharing through any medium, 
// is explicitly prohibited by law, and also violates UIC's Student 
// Disciplinary Policy (A2-c. Unauthorized Collaboration; and A2-e3. 
// Participation in Academically Dishonest Activities: Material Distribution).

// All the headers you need!
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "solarsystem.h"
#include "flightpath.h"

using namespace std;


// Local Helper Functions
// If you were allowed to change the the .h files many, if not all,
// of these would go into a private section of the class declaration.





// Class Implementations
// Defining all functions from the header that are not already
// fully defined within the header and class declaration.


/// @brief Create a path through user input. Once complete, the path
/// data member contains the valid Solar Systems entered.
/// Contains console output and input via getline.
/// Invalid Solar Systems are not added to the path, for this function
/// invalid systems are those that do not exist in the data set.
/// @param systems is the vector with the valid systems in it
void FlightPath::createPath(const vector<shared_ptr<SolarSystem>> &systems) {
    this->clear();
    cout << "Name of a Solar System to add to plan: ";
    string userInput; int i = 0;
    while (getline(cin, userInput)) {
        if (i != 0) {
            cout << "Name of a Solar System to add to plan: ";
        }
        cout << endl;
        // whitespace only means break the loop and end the function
        if (userInput == "" || userInput == "DONE") {
            break;
        }

        // check if the name inputted by the user is in the systems vector
        bool userInputInside = false;
        for (const auto& system : systems) {
            if (system->getName() == userInput) {
                userInputInside = true;
                this->path.push_back(system); // add to the path vector
                break;
            }
        }

        // notify user if failed/succeeded
        if (userInputInside) {
            cout << userInput << " added to path." << endl;
        } else {
            cout << "Invalid system: Nothing added to path." << endl;
        }
        i++;
    }
}

/// @brief Utilizes the Solar System connections to determine whether
/// we can successfully navigate along the stored path from the
/// first system to the last system to determine whether our
/// path is a valid pathway through the stars.
bool FlightPath::isValid(const vector<shared_ptr<SolarSystem>> &systems) const {
    for (long unsigned int i = 0; i < this->path.size(); i++) {
        shared_ptr<SolarSystem> currentStep = this->path.at(i);
        if (i + 1 < this->path.size()) {
            const string nextStep = this->path.at(i + 1)->getName();
            if (!currentStep->connectionExists(nextStep)) {
                return false;
            }
        }
    }
    return true;
}

/// @brief return the private data member
vector<shared_ptr<SolarSystem>> FlightPath::getPath() const {
    return this->path;
}

/// @brief Convert to string containing names of systems
/// e.g. A path with A, B, and C the string is A -> B -> C
string FlightPath::toString() const {
    string details = ""; int ind = 0;
    for (const auto& step : this->path) {
        if (ind == 0) {
            details += step->getName();
            ind++;
            continue;
        }
        details += " -> " + step->getName();
    }
    return details;
}

/// @brief Creates a human readable string of everything we see on our journey.
/// The returned string has all Celestial objects on path using
/// the various object's member functions with a newline
/// between each system but none at the end.
string FlightPath::toStringAll() const {
    string details = ""; int ind = 0;
    for (const auto& step : this->path) {
        if (ind != 0) {
            details += "\n";
        }
        details += step->toString();
        ind++;
    }
    return details;
}

/// @brief Convert path's Solar System connections to a string
/// One example with path A, B, C could produce a string:
/// A -> {}
/// B -> {A, C}
/// C -> {B}
/// The last line does not contain a newline.
string FlightPath::connectionsString() const {
    string details = ""; long unsigned int ind = 0;
    for (const auto& step : this->path) {
        if (ind == this->path.size() - 1) {
            details += step->getName() + " -> " + step->connectionsToString();
            break;
        }
        details += step->getName() + " -> " + step->connectionsToString() + "\n";
        ind++;
    }
    return details;
}

/// @brief Output various generated strings to console followed by newline
/// Outputs "(empty path)" when the path data member is empty
void FlightPath::printPath() const {
    cout << "Planned Path:\n";
    if (this->path.empty()) {
        cout << "(empty path)" << endl;
        return;
    }

    long unsigned int ind = 0;
    for (const auto& step : this->path) {
        if (ind == this->path.size() - 1) {
            cout << step->getName() + "\n";
            break;
        }
        cout << step->getName() + " -> ";
        ind++;
    }
}

/// @brief Output various generated strings to console followed by newline
/// Outputs "(empty path)" when the path data member is empty
void FlightPath::printPathCelestials() const {
    cout << "Celestials on Path:\n";
    if (this->path.empty()) {
        cout << "(empty path)" << endl;
        return;
    }

    for (const auto& step : this->path) {
        long unsigned int ind = 0;
        cout << step->getName() << "\n  ";
        vector<shared_ptr<Celestial>> celestialBodiesInStep = step->getCelestialBodies();
        for (const auto& celestialBody : celestialBodiesInStep) {
            if (ind == celestialBodiesInStep.size() - 1) {
                cout << celestialBody->toString() + "\n";
                break;
            }
            cout << celestialBody->toString() + "\n  ";
            ind++;
        }
    }
}

/// @brief Output various generated strings to console followed by newline
/// Outputs "(empty path)" when the path data member is empty
void FlightPath::printConnections() const {
    cout << "Path Connections:\n";
    if (this->path.empty()) {
        cout << "(empty path)" << endl;
        return;
    }

    for (const auto& step : this->path) {
        cout << step->getName() << " -> ";
        cout << step->connectionsToString() << endl;
    }
}

/// @brief clear the path and reset to empty
void FlightPath::clear() {
    this->path.clear();
}




/// @brief Acquire a starting system and an ending system.
///        Then automatically generate a path from start to end.
/// @param systems The data vector of Solar Systems
/// @return true when a path was generated, otherwise false
bool FlightPath::generatePath(const vector<shared_ptr<SolarSystem>> &systems)
{
    // TODO: Extra Credit
    return {};
}