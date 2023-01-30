#include "Strategy.h"
#include "Abstractions.h"
#include "Bus.h"
#include "BusStation.h"
#include "PublicTransportSystem.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <optional>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <variant>

using std::cout;
using std::endl;
using std::queue;

Route createRoute(int startStation, int endStation,
                  std::unordered_map<int, int>& path) {
    Route route;
    auto tmp = endStation;
    auto& stations = BusStations::instance();
    unordered_set<string> buses;

    int lastStation = endStation;
    tmp = path[endStation];
    const auto busIt = stations[tmp].iterateBuses();
    buses.insert(busIt.begin(), busIt.end());
    route.push_back({"", {endStation}});
    while (path.find(tmp) != path.end()) {
        auto& chooseBus = stations[tmp].buses;
        route.back().second.push_back(tmp);
        queue<string> toErase;
        for (const auto& bus : buses) {
            if (chooseBus.count(bus))
                continue;
            if (buses.size() - toErase.size() == 0) {
                route.back().first = bus;
                route.back().second.pop_back();
                route.push_back({"", {lastStation, tmp}});
                const auto busIt = stations[lastStation].iterateBuses();
                buses.insert(busIt.begin(), busIt.end());
            }
            toErase.push(bus);
        }
        while (!toErase.empty()) {
            buses.erase(toErase.front());
            toErase.pop();
        }
        lastStation = tmp;
        tmp = path[tmp];
    }
    route.back().first = *buses.begin();
    route.back().second.push_back(startStation);
    for (auto& el : route)
        std::reverse(el.second.begin(), el.second.end());
    std::reverse(route.begin(), route.end());
    return route;
}

std::optional<Route> LeastStations::getRoute(int startStation, int endStation) {
    const auto& stations = BusStations::instance();
    queue<int> toVisit;
    unordered_set<int> visited;
    unordered_map<int, int> travelPath; // key = to, value = from
    toVisit.push(startStation);
    visited.insert(startStation);
    while (!toVisit.empty()) {
        auto front = toVisit.front();
        toVisit.pop();

        for (auto& neighbour : stations[front]) {
            if (visited.count(neighbour))
                continue;
            travelPath[neighbour] = front;
            if (neighbour == endStation)
                return createRoute(startStation, endStation, travelPath);
            visited.insert(neighbour);
            toVisit.push(neighbour);
        }
    }
    return std::nullopt;
}

Route createRoute(int startStation, int endStation,
                  unordered_map<string, pair<string, int>>& path,
                  const string& endBus) {
    Route route;
    const auto& buses = Buses::instance();

    auto tmp = endStation;
    string currBus = endBus;
    while (path.count(currBus)) {
        route.push_back({currBus, {}});
        for (const auto& station :
             buses[currBus].stationIterator({path[currBus].second, tmp})) {
            route.back().second.push_back(station);
        }
        tmp = path[currBus].second;
        currBus = path[currBus].first;
    }
    route.push_back({currBus, {}});

    for (const auto& station :
         buses[currBus].stationIterator({tmp, startStation})) {
        route.back().second.push_back(station);
    }

    for (auto& el : route)
        std::reverse(el.second.begin(), el.second.end());
    std::reverse(route.begin(), route.end());
    return route;
}

std::optional<Route> LeastBusChanges::getRoute(int startStation,
                                               int endStation) {
    static const auto& stations = BusStations::instance();
    static const auto& buses = Buses::instance();
    using StationLine = pair<int, string>;

    queue<StationLine> possibleTransfers;
    unordered_set<string> usedBuses;
    unordered_map<string, pair<string, int>> travelPath;
    for (const auto& bus : stations[startStation].iterateBuses()) {
        possibleTransfers.push({startStation, bus});
        usedBuses.insert(bus);
    }

    while (!possibleTransfers.empty()) {
        auto [station, currBusId] = possibleTransfers.front();
        possibleTransfers.pop();
        cout << currBusId << endl;
        const auto& currBus = buses[currBusId];
        int nextStation = station;
        while (nextStation != -1) {
            if (nextStation == endStation) {
                cout << endl;
                return createRoute(startStation, endStation, travelPath,
                                   currBusId);
            }
            for (const auto& bus : stations[nextStation].iterateBuses()) {
                if (usedBuses.count(bus))
                    continue;
                possibleTransfers.push({nextStation, bus});
                travelPath.insert({bus, {currBusId, nextStation}});
                usedBuses.insert(bus);
            }
            nextStation = currBus.getNext(nextStation).value_or(-1);
        }
        cout << "__";
        int prevStation = station;
        while (prevStation != -1) {
            if (prevStation == endStation) {
                return createRoute(startStation, endStation, travelPath,
                                   currBusId);
            }
            for (const auto& bus : stations[prevStation].iterateBuses()) {
                if (usedBuses.count(bus))
                    continue;
                possibleTransfers.push({prevStation, bus});
                travelPath.insert({bus, {currBusId, prevStation}});
                usedBuses.insert(bus);
            }
            prevStation = currBus.getPrevious(prevStation).value_or(-1);
        }
        cout << endl;
    }
    return std::nullopt;
}

std::optional<Route> ThroughImportant::getRoute(int startStation,
                                                int endStation) {
    static const auto& stations = BusStations::instance();
    // static const auto& buses = Buses::instance();
    static const auto& importantStations =
        PublicTransportSystem::GSP().getImportantStations();

    queue<int> toVisit;
    unordered_set<int> visited;
    unordered_map<int, int> travelPath; // key = to, value = from
    toVisit.push(startStation);
    visited.insert(startStation);

    unordered_set<int> visitedImportant;
    Route route;

    while (!toVisit.empty()) {
        auto front = toVisit.front();
        toVisit.pop();

        for (auto& neighbour : stations[front]) {
            if (visited.count(neighbour))
                continue;
            travelPath[neighbour] = front;
            if (importantStations.count(neighbour) &&
                !visitedImportant.count(neighbour)) {
                auto tmp_route =
                    createRoute(startStation, neighbour, travelPath);
                route.insert(route.end(), tmp_route.begin(), tmp_route.end());
                startStation = neighbour;
                visitedImportant.insert(neighbour);
                toVisit = queue<int>();
                visited = unordered_set<int>();
                travelPath = unordered_map<int, int>();
                toVisit.push(startStation);
                visited.insert(startStation);
                break;
            }
            if (importantStations.size() == visitedImportant.size() &&
                neighbour == endStation) {
                auto tmp_route =
                    createRoute(startStation, endStation, travelPath);
                route.insert(route.end(), tmp_route.begin(), tmp_route.end());
                return route;
            }
            visited.insert(neighbour);
            toVisit.push(neighbour);
        }
    }
    return std::nullopt;
}