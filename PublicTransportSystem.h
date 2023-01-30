#ifndef public_transport_system_h
#define public_transport_system_h

#include <format>
#include <iostream>
#include <optional>
#include <string>
#include <unordered_map>
#include <unordered_set>

using std::string;

#include "Abstractions.h"
#include "Bus.h"
#include "BusStation.h"
#include "Exceptions.h"
#include "FileHandler.h"
#include "Strategy.h"
#include "UserInterface.h"

using std::cout;
using std::endl;

class PublicTransportSystem {
private:
    FileHandler fileHandler;
    Strategy* currentStrategy;
    BusStations& busStations;
    Buses& buses;
    unordered_set<int> importantStations;

    void updateBusStations();

    PublicTransportSystem();

public:
    static PublicTransportSystem& GSP() {
        static PublicTransportSystem singleton;
        return singleton;
    }

    const Bus& getBus(const string& busId) const { return buses.at(busId); }
    const BusStation& getStation(const int stationId) const {
        return busStations.at(stationId);
    }

    const unordered_set<int>& getImportantStations() const {
        return importantStations;
    }

    int getStationsNumber() const { return busStations.size(); }

    void busInformation(const string& busId) const {
        if (!buses.contains(busId))
            throw InvalidBus(busId);
        string filePath = std::format("linija_{}.txt", busId);
        fileHandler.writeBus(getBus(busId), filePath);
    }
    void stationInformation(const int& stationId) const {
        if (!busStations.contains(stationId))
            throw InvalidBusStation(std::to_string(stationId));
        string filePath = std::format("stajaliste_{}.txt", stationId);
        fileHandler.writeBusStation(getStation(stationId), filePath);
    }

    void getRoute(const int startStation, const int endStation) const;
    void loadStations(const string& fileName) {
        fileHandler.parseBusStations(fileName);
        updateBusStations();
    }
    void loadBuses(const string& fileName) {
        fileHandler.parseBuses(fileName);
        updateBusStations();
    }
    void setStrategy(Strategy* strategy) { currentStrategy = strategy; }
};

#endif