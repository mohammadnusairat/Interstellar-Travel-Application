/// @file satellite.cpp

// TODO Header

/// Original project documents by Adam T Koehler, PhD
/// UIC CS211 Spring 2024
/// @brief Satellite derived class from Celestial base class.
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

/// @brief Create a Satellite object specifying values for all private
///     data members of the class. Invoked within initalization lists
///     of constructors for derived classes.
/// @param n the value to set the private data member name to
/// @param nat the value to set the private data member natural to
/// @param r the value to set the private data member radius to
/// note: used an initializer list because base class does not have a default constructor.
/// note: follow order of initialization of variables in base class first, then derived class.
Satellite::Satellite(const string& n, double r, bool nat) 
    : Celestial(n), natural(nat), radius(r)
{
    this->name = n; // update priv member var of inherited celestial class
    this->natural = nat; // update priv member var of Satellite class
    this->radius = r; // update priv member var of Satellite class
}

/// @brief Empty destructor required for polymorphic pointers
Satellite::~Satellite() {} // classes that use simple data types or smart pointers can have empty destructors.

/// @brief obtain the boolean natural of this Satellite object
/// @return true if is natural, false otherwise
bool Satellite::isNatural() const {
    return this->natural;
}

/// @brief obtain the radius of this Satellite object
/// @return the double priv data member radius
double Satellite::getRadius() const {
    return this->radius;
}

/// @brief set the private data member boolean natural of this Satellite object
void Satellite::setNatural(bool nat) {
    this->natural = nat;
}

/// @brief set the private data member double radius of this Satellite object
void Satellite::setRadius(double r) {
    this->radius = r;
}

/// @brief converts the details of the object to a string. not newline terminated.
/// @return string of data members
/// note: must override the function, because base class function is a pure virtual function
string Satellite::toString() const {
    string details = "Satellite " + this->name;
    if (this->natural) {
        details += " is natural ";
    } else {
        details += " is human made ";
    }
    details += "with radius of " + to_string(this->radius);
    
    return details; 
}