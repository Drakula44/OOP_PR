#include "PublicTransportSystem.h"
#include <iostream>
#include <ostream>

using std::cout;
using std::endl;

ostream& operator<<(ostream& os, const Route& route) {
    for (auto& busTravel : route) {
        cout << busTravel.first << endl;
        for (auto& station : busTravel.second)
            os << station << " ";
    }
    return os;
}

PublicTransportSystem::PublicTransportSystem()
    : currentStrategy(nullptr), busStations(BusStations::instance()),
      buses(Buses::instance()) {
    // busStations = fileHandler.parseBusStations();
    // buses = fileHandler.parseBuses();
    // updateBusStations();
}

void PublicTransportSystem::updateBusStations() {
    for (const auto& bus : buses) {
        for (const auto& station : bus.second) {
            if (busStations.find(station) == busStations.end())
                cout << station << "Not found ";
            busStations[station].addBus(bus.first);
        }
    }

    for (const auto& bus : buses) {
        int last = -1;
        for (const auto& station : bus.second) {
            if (last == -1) {
                last = station;
                continue;
            }
            if (busStations.find(station) == busStations.end())
                cout << station << "Not found ";
            busStations[station].addNeighbour(last);
            busStations[last].addNeighbour(station);
            last = station;
        }
    }

    for (const auto& station : busStations)
        if (station.second.isImportant())
            importantStations.insert(station.first);
}

void PublicTransportSystem::getRoute(const int startStation,
                                     const int endStation) const {
    if (!busStations.contains(startStation))
        throw InvalidBusStation(std::to_string(startStation));
    if (!busStations.contains(endStation))
        throw InvalidBusStation(std::to_string(endStation));

    auto route_o = currentStrategy->getRoute(startStation, endStation);
    if (route_o == std::nullopt) {
        throw InvalidRoute(std::to_string(startStation) + " " +
                           std::to_string(endStation));
    }
    Route route = *route_o;
    string filePath =
        std::format("putanja_{}_{}.txt", startStation, endStation);
    fileHandler.writeRoute(route, filePath);
}