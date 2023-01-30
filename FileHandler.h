#ifndef file_handler_h
#define file_handler_h
#include <string>
using std::string;

#include "Abstractions.h"
#include "Bus.h"
#include "BusStation.h"
#include "Formating.h"

class FileHandler {
private:
    string busStationDefaultFp = "test/ulazi/stajalista.txt";
    string busesDefaultFp = "test/ulazi/linije.txt";
	BusFormatter* busFormatter;
	BusStationFormatter* busStationFormatter;
	RouteFormatter* routeFormatter;

public:
	FileHandler():busFormatter(new SimpleBusFormatter),
    busStationFormatter(new SimpleBusStationFormatter),
    routeFormatter(new SimpleRouteFormatter){}
    
    void parseBusStations(const string& busStationsFilePath = "");
    void parseBuses(const string& busesFilePath = "");

    void writeBusStation(const BusStation& busStation,
                         const string& busStationsFilePath = "") const;
    void writeBus(const Bus& bus, const string& busesFilePath = "") const;
    void writeRoute(const Route& route,
                    const string& routesFilePath = "") const;
};

#endif