/// @file interstellar.cpp
/// @date 4/24/2024

// TODO Header

/// Original project documents by Adam T Koehler, PhD
/// UIC CS211 Spring 2024
/// @brief An object oriented terminal program that allows reading of
///        Celestial data files to plan flights between the Solar Systems.

// Copyright Notice
// This document is protected by U.S. copyright law. Reproduction and 
// distribution of this work, including posting or sharing through any medium, 
// is explicitly prohibited by law, and also violates UIC's Student 
// Disciplinary Policy (A2-c. Unauthorized Collaboration; and A2-e3. 
// Participation in Academically Dishonest Activities: Material Distribution).

// These are all the libraries you need!
#include <algorithm>
#include <cstring>
#include <exception>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

// CS 211 Spring 2024 Project Specific Header Files
#include "celestial.h"
#include "solarsystem.h"
#include "fileexception.h"
#include "flightpath.h"

using namespace std;

// Externally define welcome message function
extern void welcomeSplash(bool);

// Local Function Prototypes
string acquireOption();
void printMenu();
bool validChoice(const string &);
void readCelestialObjectsDataFile(vector<shared_ptr<SolarSystem>> &systems);
void readSolarSystemConnectionFile(vector<shared_ptr<SolarSystem>> &systems);
void printSystemsCelestialDetails(vector<shared_ptr<SolarSystem>> &systems);
void printSystemsConnectionDetails(vector<shared_ptr<SolarSystem>> &systems);
void printLoadedCelestialStats(vector<shared_ptr<SolarSystem>> &systems);
void planFlightPath(FlightPath &flightPath, vector<shared_ptr<SolarSystem>> &systems);
void validateFlightPath(FlightPath &flightPath, vector<shared_ptr<SolarSystem>> &systems);
void clearSystems(vector<shared_ptr<SolarSystem>> &systems);

int main(int argc, char* argv[])
{ 
    // Command line argument flags   
    bool showSplash = false;
    bool hideMenu = false;

    // Vector of shared pointers to Solar Systems
    vector<shared_ptr<SolarSystem>> systems;

    // Flight path through the Solar Systems
    FlightPath path;

    // TODO: Determine whether -splash or -hidemenu command line argument exists.
    for (int i = 1; i < argc; i++) {
        string arg = argv[i];
        if (arg == "-splash") {
            showSplash = true;
        } else if (arg == "-hidemenu") {
            hideMenu = true;
        }
    }
    
    // Display the welcome splash or the simple one depending on settings
    welcomeSplash(showSplash);

    // Acquire user option from menu
    string option;
    if (!hideMenu)
    {
        printMenu();    
    }
    option = acquireOption(); 

    while (option != "15")
    {
        if (validChoice(option))
        {                
            switch (stoi(option))
            {
                case 1:
                    readCelestialObjectsDataFile(systems);
                    break;           
                case 2:
                    readSolarSystemConnectionFile(systems);
                    break;
                case 3:
                    printSystemsCelestialDetails(systems);
                    break;
                case 4:
                    printSystemsConnectionDetails(systems);
                    break;
                case 5:
                    printLoadedCelestialStats(systems);
                    break;
                case 6:
                    planFlightPath(path, systems);
                    break;
                case 7:
                    validateFlightPath(path, systems);
                    break;
                case 8:
                    path.printPath();
                    break;
                case 9:
                    path.printConnections();
                    break;
                case 10:
                    path.printPathCelestials();
                    break;
                case 11:
                    path.clear();
                    break;
                case 12:
                    clearSystems(systems);
                    break;
                case 13:
                    // clear system's data
                    systems.clear();
                    break;
                case 14:
                    // ignore this case
                    cout << "***ERROR: NOT IMPLEMENTED***" << endl;
                    break;
                case 15: 
                    // exit the application
                    return 0;
                default:
                    // invalid choice, do nothing
                    break;    
            }
        }

        cout << endl;
        if (!hideMenu)
        {
            printMenu();
        }
        option = acquireOption();        
    }

    cout << endl << "Thank you for using the Interstellar Travel App." 
        << endl << endl;

    return 0;
}

void readCelestialObjectsDataFile(vector<shared_ptr<SolarSystem>> &systems) {
    // get the filename
    string inputFileLocationAndName;
    cout << "Enter the file location and name:"; // structure is 'data/alldata.csv'
    getline(cin, inputFileLocationAndName);
    cout << endl << endl;

    ifstream inFile;
    try {
        // open the file
        inFile.open(inputFileLocationAndName);

        // check if file opened correctly
        if (!inFile.is_open()) {
            // throw FileException if the file couldn't be opened
            throw FileException("Exception Caught: File Not Found - " + inputFileLocationAndName);
        } 
        else {
            // get data from the file
            string line; int lineNumber = 0;
            while (getline(inFile, line)) {
                lineNumber++;

                // skip blank lines
                if (line.empty()) {
                    continue;
                }

                // skip lines starting with a #
                if (line.at(0) == '#' || line == "#") {
                    continue;
                }

                // find the position of the comma delimiter
                size_t commaPos = line.find(',');

                // no comma 
                if (commaPos == string::npos) {
                    throw FileException("Exception Caught: Bad Data Line - No Comma Found: " + line);
                    continue;
                }

                // extract the keyword and keyword name from the line
                string keyword = line.substr(0, commaPos);
                string keywordName = line.substr(commaPos + 1);
                
                if (keyword == "System") {
                    // if already exists dont create
                    bool duplicate = false;
                    for (const auto& system : systems) {
                        if (keywordName == system->getName()) {
                            duplicate = true;
                            break;
                        }
                    }
                    if (duplicate) {
                        continue;
                    }

                    // create solar system object
                    shared_ptr<SolarSystem> solarSystem = make_shared<SolarSystem>(keywordName);
                    
                    // add to systems vector
                    systems.push_back(solarSystem);
                } else if (keyword == "Star") {
                    // get the name of the star, solarSystem, spectralType, temperature, and solarMass
                    size_t pos = keywordName.find(',');
                    if (pos == string::npos) {
                        throw FileException("Exception Caught: Bad Data Line - Mismatched Data Amount: " + line);
                        continue;
                    }
                    string starName = keywordName.substr(0, pos);
                    keywordName.erase(0, pos + 1);
                    
                    pos = keywordName.find(',');
                    if (pos == string::npos) {
                        throw FileException("Exception Caught: Bad Data Line - Mismatched Data Amount: " + line);
                        continue;
                    }
                    string solarSystemName = keywordName.substr(0, pos);
                    keywordName.erase(0, pos + 1);
                    
                    pos = keywordName.find(',');
                    if (pos == string::npos) {
                        throw FileException("Exception Caught: Bad Data Line - Mismatched Data Amount: " + line);
                        continue;
                    }
                    string spectralType = keywordName.substr(0, pos);
                    keywordName.erase(0, pos + 1);

                    pos = keywordName.find(',');
                    if (pos == string::npos) {
                        throw FileException("Exception Caught: Bad Data Line - Mismatched Data Amount: " + line);
                        continue;
                    }
                    string temperatureStr = keywordName.substr(0, pos);
                    double temperature = 0.0;
                    if (temperatureStr != "") {
                        temperature = stod(temperatureStr);
                    }
                    keywordName.erase(0, pos + 1);
                    
                    double solarMass = 0.0;
                    if (keywordName != "") {
                        solarMass = stod(keywordName);
                    }

                    // create star object
                    shared_ptr<Celestial> star = make_shared<Star>(starName, spectralType, temperature, solarMass);

                    // if already exists dont create
                    bool duplicate = false;
                    for (const auto& sys : systems) {
                        if (sys->getName() == solarSystemName) {
                            Star tempStar(starName, spectralType, temperature, solarMass);
                            if (sys->celestialsSearch(tempStar, starName) != -1) {
                                duplicate = true;
                                break;
                            }
                        }
                    }
                    if (duplicate) {
                        continue;
                    }

                    // add star to its solar system if it exists, if not create the solar system and add it
                    bool added = false;
                    for (const auto& solarsystem : systems) {
                        if (solarsystem->getName() == solarSystemName) {
                            solarsystem->insertCelestial(star);
                            added = true;
                        }
                    }
                    if (!added) {
                        shared_ptr<SolarSystem> solarSystem = make_shared<SolarSystem>(solarSystemName);
                        solarSystem->insertCelestial(star);
                        systems.push_back(solarSystem);
                    }
                } else if (keyword == "Planet") {
                    // get the name of the planet, starName, solarSystem, orbitalPeriod, and radius
                    size_t pos = keywordName.find(',');
                    if (pos == string::npos) {
                        throw FileException("Exception Caught: Bad Data Line - Mismatched Data Amount: " + line);
                        continue;
                    }
                    string planetName = keywordName.substr(0, pos);
                    keywordName.erase(0, pos + 1);
                    
                    pos = keywordName.find(',');
                    if (pos == string::npos) {
                        throw FileException("Exception Caught: Bad Data Line - Mismatched Data Amount: " + line);
                        continue;
                    }
                    string starName = keywordName.substr(0, pos);
                    keywordName.erase(0, pos + 1);
                    
                    pos = keywordName.find(',');
                    if (pos == string::npos) {
                        throw FileException("Exception Caught: Bad Data Line - Mismatched Data Amount: " + line);
                        continue;
                    }
                    string solarSystemName = keywordName.substr(0, pos);
                    keywordName.erase(0, pos + 1);
                    
                    pos = keywordName.find(',');
                    if (pos == string::npos) {
                        throw FileException("Exception Caught: Bad Data Line - Mismatched Data Amount: " + line);
                        continue;
                    }
                    string orbitalPeriodStr = keywordName.substr(0, pos);
                    double orbitalPeriod = 0.0;
                    if (orbitalPeriodStr != "") {
                        orbitalPeriod = stod(orbitalPeriodStr);
                    }
                    keywordName.erase(0, pos + 1);
                    
                    double radius = 0.0;
                    if (keywordName != "") {
                        radius = stod(keywordName);
                    }
                    // create planet object
                    shared_ptr<Celestial> planet = make_shared<Planet>(planetName, orbitalPeriod, radius);

                    // find the solar system
                    shared_ptr<SolarSystem> solarSystem;
                    for (const auto& sys : systems) {
                        if (sys->getName() == solarSystemName) {
                            solarSystem = sys;
                            break;
                        }
                    }

                    // if the solar system doesn't exist, create it
                    if (solarSystem == nullptr) {
                        solarSystem = make_shared<SolarSystem>(solarSystemName);
                        systems.push_back(solarSystem);
                    }

                    // find the star
                    shared_ptr<Celestial> star;
                    for (const auto& celestial : solarSystem->getCelestialBodies()) {
                        if (celestial->getName() == starName) {
                            star = celestial;
                            break;
                        }
                    }

                    // if the star doesn't exist, create it
                    if (star == nullptr) {
                        star = make_shared<Star>(starName, "unknown", 0.0, 0.0); // Spectral type, temperature, and solar mass are not specified in the data
                        solarSystem->insertCelestial(star);
                    }

                    // add planet to the solar system
                    solarSystem->insertCelestial(planet);
                } else if (keyword == "Satellite") {
                    // get the name of the satellite, planetName, solarSystemName, radius, and the isNaturalStr
                    size_t pos = keywordName.find(',');
                    if (pos == string::npos) {
                        throw FileException("Exception Caught: Bad Data Line - Mismatched Data Amount: " + line);
                        continue;
                    }
                    string satelliteName = keywordName.substr(0, pos);
                    keywordName.erase(0, pos + 1);
                    
                    pos = keywordName.find(',');
                    if (pos == string::npos) {
                        throw FileException("Exception Caught: Bad Data Line - Mismatched Data Amount: " + line);
                        continue;
                    }
                    string planetName = keywordName.substr(0, pos);
                    keywordName.erase(0, pos + 1);
                    
                    pos = keywordName.find(',');
                    if (pos == string::npos) {
                        throw FileException("Exception Caught: Bad Data Line - Mismatched Data Amount: " + line);
                        continue;
                    }
                    string solarSystemName = keywordName.substr(0, pos);
                    keywordName.erase(0, pos + 1);
                    
                    pos = keywordName.find(',');
                    if (pos == string::npos) {
                        throw FileException("Exception Caught: Bad Data Line - Mismatched Data Amount: " + line);
                        continue;
                    }
                    string radiusStr = keywordName.substr(0, pos);
                    double radius = 0.0;
                    if (radiusStr != "") {
                        radius = stod(radiusStr);
                    }
                    keywordName.erase(0, pos + 1);
                    
                    string isNaturalStr = keywordName;
                    
                    // get whether the satellite is natural or not
                    bool isNatural = false;
                    if (isNaturalStr == "Yes") {
                        isNatural = true;
                    }

                    // find the solar system
                    shared_ptr<SolarSystem> solarSystem;
                    for (const auto& sys : systems) {
                        if (sys->getName() == solarSystemName) {
                            solarSystem = sys;
                            break;
                        }
                    }

                    // if the solar system doesn't exist, create it
                    if (solarSystem == nullptr) {
                        solarSystem = make_shared<SolarSystem>(solarSystemName);
                        systems.push_back(solarSystem);
                        isNatural = false;
                    }

                    // create satellite object
                    shared_ptr<Celestial> satellite = make_shared<Satellite>(satelliteName, radius, isNatural);

                    // find the planet
                    shared_ptr<Celestial> planet;
                    for (const auto& celestial : solarSystem->getCelestialBodies()) {
                        if (celestial->getName() == planetName) {
                            planet = celestial;
                            break;
                        }
                    }

                    // if the planet doesn't exist, create it
                    if (planet == nullptr) {
                        planet = make_shared<Planet>(planetName, 0.0, 0.0); // Orbital period and radius are not specified in the data
                        solarSystem->insertCelestial(planet);
                    }

                    // add satellite to the planet
                    shared_ptr<Planet> planetPtr = dynamic_pointer_cast<Planet>(planet);
                    if (planetPtr != nullptr) {
                        planetPtr->addSat(satellite);
                    }
                } else {
                    // throw exception if the type of Celestial object is invalid
                    throw FileException("Exception Caught: Bad Data Line - Invalid Celestial Type: " + line);
                }
                
            }

            // close the file
            inFile.close();
        }
    } catch(const FileException& e) {
        // catch any FileException that occurred during file reading
        cout << e.what() << endl << endl;
    } catch(const exception& e) {
        // catch any other standard exceptions
        cout << e.what() << endl << endl;
    }
    
}

void readSolarSystemConnectionFile(vector<shared_ptr<SolarSystem>> &systems) {
    // get the filename
    string inputFileLocationAndName;
    cout << "Enter the file location and name:"; // structure is 'data/alldata_allconnections.csv'
    getline(cin, inputFileLocationAndName);
    cout << endl << endl;

    try {
        // open the file
        ifstream inFile;
        inFile.open(inputFileLocationAndName);

        // check if file opened correctly
        if (!inFile.is_open()) {
            // throw FileException if the file couldn't be opened
            throw FileException("Exception Caught: File Not Found - " + inputFileLocationAndName);
        } else {
            // get data from the file
            string line; int lineNumber = 0;
            while (getline(inFile, line)) {
                lineNumber++;

                // skip blank lines
                if (line.empty()) {
                    continue;
                }

                // skip lines starting with a #
                if (line.at(0) == '#' || line == "#") {
                    continue;
                }

                // get the first word of the line (every character before the comma)
                size_t pos = line.find(',');
                if (pos == string::npos) {
                    // skip line without a comma
                    continue;
                }
                string sourceSolarSystemName = line.substr(0, pos);
                line.erase(0, pos + 1);

                // create the source solar system object
                shared_ptr<SolarSystem> sourceSolarSystem = make_shared<SolarSystem>(sourceSolarSystemName);

                // check the source solar system exists in the systems vector
                int ind = 0; bool found = false;
                for (const auto& system : systems) {
                    if (system->getName() == sourceSolarSystemName) {
                        found = true;
                        break;
                    }
                    ind++;
                }

                // if search failed skipped line
                if (!found) {
                    continue;
                }

                // add the connections to the collection of the current solar system
                while (line.find(',') != string::npos) { // a comma exists
                    //cout << "***Line: " << line << endl;
                    // loop through line and build connection name
                    int i = 0; string connection = "";
                    for (const auto& c : line) {
                        if (c != ',') {
                            connection += line.at(i);
                        } else {
                            break;
                        }
                        i++;
                    }
                    //cout << "***Connection: " << connection << endl;

                    // no data there
                    if (connection == "") {
                        continue;
                    }
                    
                    // erase that part of the string
                    line.erase(0, line.find(',') + 1);
                    if (line == ",") {
                        line = "";
                    }

                    // check if connection is in systems vector
                    int index = 0;
                    for (const auto& system : systems) {
                        if (system->getName() == connection) {
                            // add the connection
                            systems.at(ind)->addConnection(system);
                            //cout << "added: " << system->getName() << endl;
                            break;
                        }
                        index++;
                    }
                }

                // check if last word (or if line only had two words) is in the systems vector
                int index = 0;
                for (const auto& system : systems) {
                    if (system->getName() == line) {
                        // add the connection
                        systems.at(ind)->addConnection(system);
                        break;
                    }
                    index++;
                }
            }
            // close the file
            inFile.close();
        }
    } catch(const FileException& e) {
        // catch any FileException that occurred during file reading
        cout << e.what() << endl << endl;
    } catch(const exception& e) {
        // catch any other standard exceptions
        cout << e.what() << endl << endl;
    }
}

void printSystemsCelestialDetails(vector<shared_ptr<SolarSystem>> &systems) {
    if (systems.empty()) {
        cout << "No data loaded." << endl;
    }
    // iterate through systems vector
    for (const auto& solarsystem : systems) {
        cout << solarsystem->toString() << endl;
    }
}

void printSystemsConnectionDetails(vector<shared_ptr<SolarSystem>> &systems) {
    if (systems.empty()) {
        cout << "No connections loaded." << endl;
    }
    // iterate through systems vector
    for (const auto& solarsystem : systems) {
        cout << solarsystem->getName() << " -> " << solarsystem->connectionsToString() << endl;
    }
}

void printLoadedCelestialStats(vector<shared_ptr<SolarSystem>> &systems) {
    // Stats for Loaded Data
    // =====================
    // Number of Solar Systems: 3
    // Number of Stars: 4
    // Number of Planets: 4
    // Number of Satellites: 1
    // Minimum Number of Connections: 0
    // Maximum Number of Connections: 0
    // Average Number of Connections: 0
    // Median Number of Connections: 0

    int numSolarSystems = 0, totalNumStars = 0, totalNumPlanets = 0, totalNumSatellites = 0, minNumConnections = 0, maxNumConnections = 0; double avgNumConnections = 0.0, medNumConnections = 0.0;
    vector<int> cons; int consSize = 0;
    for (const auto& system : systems) {
        numSolarSystems++;
        totalNumStars += system->numStars();
        totalNumPlanets += system->numPlanets();
        totalNumSatellites += system->numSatellites();
        avgNumConnections += system->numConnections();
        cons.push_back(system->numConnections());
        consSize++;
    }

    if (!cons.empty()) {
        // calculate minimum and maximum number of connections
        minNumConnections = *min_element(cons.begin(), cons.end());
        maxNumConnections = *max_element(cons.begin(), cons.end());

        // calculate average number of connections
        avgNumConnections = avgNumConnections / consSize;

        // calculate median number of connections
        sort(cons.begin(), cons.end());
        if (consSize % 2 == 0) {
            // even number of elements
            medNumConnections = cons[consSize / 2 - 1] + cons[consSize / 2] / 2.0;
        } else {
            // odd number of elements
            medNumConnections = cons[consSize / 2.0];
        }
    } else {
        // no connections found
        minNumConnections = 0;
        maxNumConnections = 0;
        avgNumConnections = 0;
        medNumConnections = 0;
    }



    cout << "Stats for Loaded Data" << endl;
    cout << "=====================" << endl;
    cout << "Number of Solar Systems: " << numSolarSystems << endl;
    cout << "Number of Stars: " << totalNumStars << endl;
    cout << "Number of Planets: " << totalNumPlanets << endl;
    cout << "Number of Satellites: " << totalNumSatellites << endl;
    cout << "Minimum Number of Connections: " << minNumConnections << endl;
    cout << "Maximum Number of Connections: " << maxNumConnections << endl;
    cout << "Average Number of Connections: " << avgNumConnections << endl;
    cout << "Median Number of Connections: " << medNumConnections << endl;
}

void planFlightPath(FlightPath &flightPath, vector<shared_ptr<SolarSystem>> &systems) {
    cout << "Activating flight plan plotting system..." << endl;
    cout << "Only valid solar systems can be added to the plan." << endl << endl;
    cout << "Type DONE to terminate flight planning." << endl << endl;

    flightPath.createPath(systems);
}

void validateFlightPath(FlightPath &flightPath, vector<shared_ptr<SolarSystem>> &systems) {
    if (flightPath.isValid(systems)) {
        cout << "Path is valid, ready to explore!" << endl;
    } else {
        cout << "Invalid path, route not connected." << endl;
    }
}

void clearSystems(vector<shared_ptr<SolarSystem>> &systems) {
    for (const auto& system : systems) {
        system->clearConnections();
    }
}

/// @brief acquire user menu choice
/// @return acquried string value
string acquireOption()
{
    string option;
    
    cout << endl << "Enter a selection: ";
    getline(cin, option);
    cout << endl;

    return option;
}


/// @brief prints out the contents of menu.txt
void printMenu()
{
    ifstream menuFile("menu.txt");
    if (menuFile.is_open()) {
        string line;
        while (getline(menuFile, line)) {
            cout << line << endl;
        }
        menuFile.close();
    } else {
        cout << "Unable to open menu file." << endl;
    }
}


/// @brief Determines whether a provided string meets the criteria.
///        Valid choices are size 1 or 2 and must be all numeric digits.
/// @param choice the string to validate 
/// @return true when the choice is valid
bool validChoice(const string &choice)
{
    // check if the length if either 1 or 2
    if (choice.size() == 1 || choice.size() == 2) {
        // make sure each char is a digit
        for (const auto& c : choice) {
            if (c < '0' || c > '9') {
                return false; // a char is not a digit
            }
        }
        return true; // length is 1 or 2 and all chars are digits
    }
    return false; // length not 1 or 2
}
