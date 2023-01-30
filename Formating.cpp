#include "Formating.h"
#include <iostream>
#include "Bus.h"
#include "BusStation.h"
#include "PublicTransportSystem.h"

using std::endl;

void SimpleBusStationFormatter::format(ostream& os, const BusStation& station) const
{
	auto& gps = PublicTransportSystem::GSP();
	auto& buses = Buses::instance();
    os << station.getStationId() << " " << station.getStationName() << " ";
    os << "[";
    bool i = false;
    for (const auto& bus : station.iterateBuses()) {
        os << (i == 0 ? "" : " ") << bus;
        i = true;
    }
    os << "] ";
    os << "{!";
    for (const auto& bus : station.iterateBuses())
        for (const auto& station: buses[bus])
		    if (gps.getImportantStations().find(station) != gps.getImportantStations().end())
			os << " " << station;
    os << " !}";
}

//for (auto& busTravel : route) {
//    routesFile << busTravel.first << endl;
//    for (auto& station : busTravel.second)
//        routesFile << station << " ";
//    routesFile << endl;
//}

void SimpleRouteFormatter::format(ostream& os, const Route& route) const
{
    string lastBus = "";
    for (auto& busTravel : route) {
     os << lastBus << "->" << busTravel.first << endl;
     for (auto& station : busTravel.second)
         os << station << " ";
     os << endl;
     lastBus = busTravel.first;
 }
}

void SimpleBusFormatter::format(ostream& os, const Bus& bus) const
{
    const auto& stations = BusStations::instance();
    os << bus.getBusNumber() << " ";
    os << stations[bus.front()].getStationName() << " -> "
        << stations[bus.back()].getStationName();
    for (const auto& stationId : bus)
        os << '\n' << stationId << " " << stations[stationId].getStationName();
}
