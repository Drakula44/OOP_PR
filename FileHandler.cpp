#include "FileHandler.h"
#include "Bus.h"
#include "BusStation.h"
#include "Exceptions.h"
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::stringstream;


void FileHandler::parseBusStations(const string& busStationsFilePath) {
    string filePath = (busStationsFilePath.empty() ? busStationDefaultFp
                                                   : busStationsFilePath);

    auto& busStations = BusStations::instance();

    ifstream busStationsFile(filePath); // handle error
    // check if file exists
	if (!busStationsFile.is_open()) {
		throw InvalidFile(filePath);
	}

    string line;
    while (getline(busStationsFile, line)) {
        stringstream ss(line);

        int stationId;
        string stationName;
        ss >> stationId;
        bool isImportant = false;
        std::getline(ss, stationName);
        stationName = stationName.substr(1);
        if (stationName.find("[!]") != string::npos) {
            stationName = stationName.erase(stationName.size() - 4);
            isImportant = true;
        }
        busStations.insert({stationId, {stationId, stationName, isImportant}});
    }
}

void FileHandler::parseBuses(const string& busesFilePath) {
    string filePath = (busesFilePath.empty() ? busesDefaultFp : busesFilePath);

    auto& buses = Buses::instance();

    ifstream busesFile(filePath); // handle error
    
	// check if file exists
	if (!busesFile.is_open()) {
		throw InvalidFile(filePath);
	}

    string line;
    while (getline(busesFile, line)) {
        stringstream ss(line);
        string busNumber;
        vector<int> travelPath;
        ss >> busNumber;
        int last = -1;
        int tmp = 0;
        while (tmp != last) {
            last = tmp;
            ss >> tmp;
            if (tmp == last)
                break;
            travelPath.push_back(tmp);
        }
        buses.insert({busNumber, {busNumber, travelPath}});
    }
}


void FileHandler::writeBusStation(const BusStation& busStation,
                                  const string& busStationsFilePath) const {

    ofstream busStationsFile(busStationsFilePath);
	busStationFormatter->format(busStationsFile, busStation);
}

void FileHandler::writeBus(const Bus& bus, const string& busesFilePath) const {
    ofstream busesFile(busesFilePath);
	busFormatter->format(busesFile, bus);
    
}

void FileHandler::writeRoute(const Route& route, const string& routesFilePath) const {
    ofstream routesFile(routesFilePath);
	routeFormatter->format(routesFile, route);
}
