#ifndef bus_station_h
#define bus_station_h

#include "Abstractions.h"
#include <ostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using std::ostream;
using std::string;
using std::unordered_map;
using std::unordered_set;

class FileHandler;
class Bus;

class IterateBuses {
    unordered_set<string>& buses;

public:
    IterateBuses(unordered_set<string>& buses) : buses(buses) {}

    auto begin() const { return buses.begin(); }
    auto end() const { return buses.end(); }
};

class BusStation {
private:
    const int stationId;
    string stationName;
    bool importantStation;

    mutable unordered_set<string> buses;
    mutable unordered_set<int> neighbors;

public:
    BusStation(int stationId, string stationName, bool importantStation)
        : stationId(stationId), stationName(stationName),
          importantStation(importantStation){};
    BusStation() : stationId(-1){};

    void addBus(const string& bus) const { buses.insert(bus); }
    void addNeighbour(int neighbour) const { neighbors.insert(neighbour); }

    unordered_set<int> directImportant() const;

    auto begin() const { return neighbors.begin(); };
    auto end() const { return neighbors.end(); };

    const IterateBuses iterateBuses() const { return IterateBuses(buses); }

    IterateBuses iterateBuses() { return IterateBuses(buses); }

    int getStationId() const { return stationId; }
    string getStationName() const { return stationName; }
    bool isImportant() const { return importantStation; }

    friend ostream& operator<<(ostream& os, const BusStation& busStation);
    friend Route createRoute(int startStation, int endStation,
                             std::unordered_map<int, int>& path);
};

class BusStations : public unordered_map<int, BusStation> {
private:
    BusStations() = default;
    BusStations(const BusStations&) = delete;
    BusStations& operator=(const BusStations&) = delete;

public:
    static BusStations& instance() {
        static BusStations INSTANCE;
        return INSTANCE;
    }
    const unordered_map<int, BusStation>::mapped_type&
    operator[](const unordered_map<int, BusStation>::key_type& key) const {
        return find(key)->second;
    }
};

#endif