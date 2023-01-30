#ifndef bus_h
#define bus_h

#include "Abstractions.h"
#include "State.h"

#include <cstddef>
#include <optional>
#include <ostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <variant>
#include <vector>

using std::ostream;
using std::pair;
using std::string;
using std::unordered_map;
using std::vector;

class FileHandler;
class BusStation;

using iter = std::variant<vector<int>::const_iterator,
                          vector<int>::const_reverse_iterator>;

class StatIter {
private:
    iter it;

public:
    StatIter() {}
    StatIter(iter it) : it{it} {}

    StatIter(iter& it) : it{it} {}
    StatIter(vector<int>::const_iterator it) : it(it) {}
    StatIter(vector<int>::const_reverse_iterator it) : it(it) {}

    void operator++() {
        if (std::holds_alternative<vector<int>::const_iterator>(it))
            it = std::get<vector<int>::const_iterator>(it) + 1;
        else
            it = std::get<vector<int>::const_reverse_iterator>(it) + 1;
    }

    bool operator!=(const StatIter& other) const { return other.it != it; }

    int operator*() const {
        if (std::holds_alternative<vector<int>::const_iterator>(it))
            return *std::get<vector<int>::const_iterator>(it);
        else {
            return *std::get<vector<int>::const_reverse_iterator>(it);
        }
    }
};

class StationIterator {
private:
    const vector<int>& travelPath;
    std::size_t from;
    std::size_t to;

public:
    StationIterator(const vector<int>& travelPath)
        : travelPath(travelPath), from(0), to(travelPath.size() - 1) {}
    StationIterator(const vector<int>& travelPath, int from, int to)
        : travelPath(travelPath), from(from), to(to) {}

    StatIter begin() const {
        if (to > from)
            return StatIter(travelPath.begin() + from);
        return StatIter(make_reverse_iterator(travelPath.begin() + (from + 1)));
    }
    StatIter end() const {
        if (to > from)
            return StatIter(travelPath.begin() + to + 1);
        return StatIter(make_reverse_iterator(travelPath.begin() + to));
    }
};
class BusFormatter;
class Bus {
private:
    using BusStationId = int;

private:
    unordered_map<BusStationId, int> busStations;
    vector<BusStationId> travelPath;

    const string busNumber;

public:
    Bus(string busNumber, vector<BusStationId> travelPath)
        : travelPath(travelPath), busNumber(busNumber) {
        for (std::size_t i = 0; i < travelPath.size(); i++) {
            busStations.insert({travelPath[i], i});
        }
    }
    Bus() : busNumber("-1"){};

    // getNextBusStation(const BusStationId& currentBusStation);
    string getBusNumber() const;
    bool isBusStationInTravelPath(const BusStation& busStation);

    vector<int> checkImportant(const int stationId) const;

    std::optional<int> getNext(int stationIndex) const;
    std::optional<int> getPrevious(int stationIndex) const;

    auto begin() const { return travelPath.begin(); }
    auto end() const { return travelPath.end(); }
	auto front() const { return travelPath.front(); }
	auto back() const { return travelPath.back(); }

    auto stationIterator() const { return StationIterator(travelPath); }
    auto stationIterator(pair<int, int> fromToStation) const {
        int fromIndex = busStations.find(fromToStation.first)->second;
        int toIndex = busStations.find(fromToStation.second)->second;
        return StationIterator(travelPath, fromIndex, toIndex);
    }
    friend BusFormatter;
    friend ostream& operator<<(ostream& os, const Bus& bus);
};

class Buses : public unordered_map<string, Bus> {
private:
    Buses() = default;
    Buses(const Buses&) = delete;
    Buses& operator=(const Buses&) = delete;

public:
    static Buses& instance() {
        static Buses INSTANCE;
        return INSTANCE;
    }
    const unordered_map<string, Bus>::mapped_type&
    operator[](const unordered_map<string, Bus>::key_type& key) const {
        return find(key)->second;
    }
};

#endif