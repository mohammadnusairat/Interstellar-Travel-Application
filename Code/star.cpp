/// @file star.cpp

// TODO Header

/// Original project documents by Adam T Koehler, PhD
/// UIC CS211 Spring 2024
/// @brief Star derived class from Celestial base class.
///        Utilized by the Interstellar Travel App.

// Copyright Notice
// This document is protected by U.S. copyright law. Reproduction and 
// distribution of this work, including posting or sharing through any medium, 
// is explicitly prohibited by law, and also violates UIC's Student 
// Disciplinary Policy (A2-c. Unauthorized Collaboration; and A2-e3. 
// Participation in Academically Dishonest Activities: Material Distribution).

// All the headers you need!
#include <string>
#include "celestial.h"

using namespace std;

// Local Helper Functions
// If you were allowed to change the the .h files many, if not all,
// of these would go into a private section of the class declaration.





// Class Implementations
// Defining all functions from the header that are not already
// fully defined within the header and class declaration.


/// @brief Create a Star object specifying values for all private
///     data members of the class. Invoked within initalization lists
///     of constructors for derived classes.
/// @param name the value to set the private data member name to
/// @param spectralType the value to set the private data member spectralType to
/// @param temperature the value to set the private data member temperature to
/// @param mass the value to set the private data member mass to
/// note: used an initializer list because base class does not have a default constructor.
/// note: follow order of initialization of variables in base class first, then derived class.
Star::Star(const string& n, const string &sT, double t, double m) 
    : Celestial(n), mass(m), temperature(t), spectralType(sT)
{
    this->name = name; // update priv member var of inherited celestial class
    this->spectralType = spectralType; // update priv member var of star class
    this->temperature = temperature; // update priv member var of star class
    this->mass = mass; // update priv member var of star class
}

/// @brief Empty destructor required for polymorphic pointers
Star::~Star() {} // classes that use simple data types or smart pointers can have empty destructors.

/// @brief obtain the mass of this Star object
/// @return the private data member double containing the mass
double Star::getMass() const {
    return this->mass;
}

/// @brief obtain the temperature of this Star object
/// @return the private data member double containing the temperature
double Star::getTemperature() const {
    return this->temperature;
}

/// @brief obtain the spectralType of this Star object
/// @return the private data member string containing the spectralType
string Star::getSpectralType() const {
    return this->spectralType;
}

/// @brief set the private data member double mass of this Star object
void Star::setMass(double m) {
    this->mass = m;
}

/// @brief set the private data member double temperature of this Star object
void Star::setTemperature(double t) {
    this->temperature = t;
}

/// @brief set the private data member string spectralType of this Star object
void Star::setSpectralType(const string& s) {
    this->spectralType = s;
}

/// @brief converts the details of the object to a string. not newline terminated.
/// @return string of data members
/// note: must override the function, because base class function is a pure virtual function
string Star::toString() const {
    return "Star " + this->name + " of type " + this->spectralType + " with temperature " + to_string(this->temperature) + " and mass " + to_string(this->mass); 
}