#include "BusStation.h"
#include "Bus.h"
#include <cstddef>
#include <unordered_set>
#include <vector>

ostream& operator<<(ostream& os, const BusStation& busStation) {
    os << busStation.stationId << " " << busStation.stationName << " ";
    os << "[";
    bool i = false;
    for (const auto& bus : busStation.buses) {
        os << (i == 0 ? "" : " ") << bus;
        i = true;
    }
    os << "] ";
    os << "{!";
    for (const auto& importantStations : busStation.directImportant())
        os << " " << importantStations;
    os << " !}";
    return os;
}

unordered_set<int> BusStation::directImportant() const {
    unordered_set<int> importantStops;
    const auto& global_buses = Buses::instance();
    for (const auto& bus : buses) {
        auto tmp = global_buses[bus].checkImportant(stationId);
        importantStops.insert(tmp.begin(), tmp.end());
    }

    return importantStops;
}

ostream& operator<<(ostream& os, const BusStations& busStations) {
    for (const auto& busStation : busStations) {
        os << busStation.second;
        os << std::endl << std::endl;
    }
    return os;
}
