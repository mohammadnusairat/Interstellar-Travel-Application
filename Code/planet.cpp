/// @file planet.cpp

// TODO Header

/// Original project documents by Adam T Koehler, PhD
/// UIC CS211 Spring 2024
/// @brief Planet derived class from Celestial base class.
///        Utilized by the Interstellar Travel App.

// Copyright Notice
// This document is protected by U.S. copyright law. Reproduction and 
// distribution of this work, including posting or sharing through any medium, 
// is explicitly prohibited by law, and also violates UIC's Student 
// Disciplinary Policy (A2-c. Unauthorized Collaboration; and A2-e3. 
// Participation in Academically Dishonest Activities: Material Distribution).

// All the headers you need!
#include <iostream>
#include <string>
#include <vector>
#include "celestial.h"

using namespace std;

// Local Helper Functions
// If you were allowed to change the the .h files many, if not all,
// of these would go into a private section of the class declaration.





// Class Implementations
// Defining all functions from the header that are not already
// fully defined within the header and class declaration.

/// @brief Create a Planet object specifying values for all private
///     data members of the class. Invoked within initalization lists
///     of constructors for derived classes.
/// @param name the value to set the private data member name to
/// @param orbitP the value to set the private data member orbitalPeriod to
/// @param radius the value to set the private data member radius to
/// note: used an initializer list because base class does not have a default constructor.
/// note: follow order of initialization of variables in base class first, then derived class.
Planet::Planet(const string& n, double orbitP, double r) 
    : Celestial(n), orbitalPeriod(orbitP), radius(r)
{
    this->name = name; // update priv member var of inherited celestial class
    this->orbitalPeriod = orbitP; // update priv member var of planet class
    this->radius = radius; // update priv member var of planet class
}

/// @brief Empty destructor required for polymorphic pointers
Planet::~Planet() {} // classes that use simple data types or smart pointers can have empty destructors.

/// @brief obtain the orbitalPeriod of this Planet object
/// @return the private data member double containing the orbitalPeriod
double Planet::getOrbitalPeriod() const {
    return this->orbitalPeriod;
}

/// @brief obtain the radius of this Planet object
/// @return the private data member double containing the radius
double Planet::getRadius() const {
    return this->radius;
}

/// @brief obtain the number of sats of this Planet object
/// @return the size of the private data member sats
int Planet::numSats() const {
    return this->sats.size();
}

/// @brief set the private data member double orbitalPeriod of this Planet object
void Planet::setOrbitalPeriod(double oP) {
    this->orbitalPeriod = oP;
}

/// @brief set the private data member double radius of this Planet object
void Planet::setRadius(double r) {
    this->radius = r;
}

/// @brief add a ptr to a celestial object to the orbit of this Planet
/// @param celestialObject ptr to the celestial object to be added to sats vector
void Planet::addSat(shared_ptr<Celestial> &celestialObject) {
    this->sats.push_back(celestialObject);
}

/// @brief search sats to see if an object exists in the collection
/// @param name the name of the object we are searching for
/// @return true if found, false otherwise
bool Planet::satExists(const string &name) const {
    for (const auto& sat : this->sats) {
        if (sat->getName() == name) {
            return true;
        }
    }
    return false; // not found
}

/// @brief output all the 'toString' details of every sat in sats
void Planet::printSats() const {
    for (const auto& sat : this->sats) {
        cout << sat->toString() << endl;
    }
}

/// @brief converts the details of the object to a string. each object in orbit is also added to the string.
/// @brief may have newlines internally, but not newline terminated.
/// @return string of data members
/// note: must override the function, because base class function is a pure virtual function
string Planet::toString() const {
    string details = "Planet " + this->name + " with orbital period " + to_string(this->orbitalPeriod) + " and relative radius of " + to_string(this->radius);
    if (!sats.empty()) {
        for (const auto& sat : this->sats) {
            details += "\n    " + sat->toString();
        }
    }
    
    return details;
}