#include "Bus.h"
#include "Abstractions.h"
#include "BusStation.h"
#include <cstddef>
#include <iostream>
#include <iterator>
#include <optional>
#include <vector>

ostream& operator<<(ostream& os, const Bus& bus) {
    const auto& stations = BusStations::instance();
    os << bus.busNumber << " ";
    os << stations[bus.travelPath.front()].getStationName() << " -> "
       << stations[bus.travelPath.back()].getStationName();
    for (const auto& stationId : bus.travelPath)
        os << '\n' << stationId << " " << stations[stationId].getStationName();
    return os;
}

ostream& operator<<(ostream& os, const Buses& buses) {
    for (const auto& bus : buses) {
        os << bus.second;
        os << std::endl;
    }
    return os;
}

std::optional<int> Bus::getNext(int stationIndex) const {
    auto it = busStations.find(stationIndex);
    if (it == busStations.end())
        return std::nullopt;
    std::size_t travelPathIndex = it->second;
    if (travelPathIndex >= travelPath.size() - 1)
        return std::nullopt;
    return travelPath[travelPathIndex + 1];
}

std::optional<int> Bus::getPrevious(int stationIndex) const {
    auto it = busStations.find(stationIndex);
    if (it == busStations.end())
        return std::nullopt;
    std::size_t travelPathIndex = it->second;
    if (travelPathIndex <= 0)
        return std::nullopt;
    return travelPath[travelPathIndex - 1];
}

vector<int> Bus::checkImportant(const int stationId) const {
    const auto& stations = BusStations::instance();
    std::size_t stationIndex = busStations.find(stationId)->second;
    vector<int> importantStations;
    if (stationIndex != 0 &&
        stations[travelPath[stationIndex - 1]].isImportant())
        importantStations.push_back(travelPath[stationIndex - 1]);
    if (stationIndex != travelPath.size() - 1 &&
        stations[travelPath[stationIndex + 1]].isImportant())
        importantStations.push_back(travelPath[stationIndex + 1]);
    return importantStations;
}

string Bus::getBusNumber() const { return busNumber; }