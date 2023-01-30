#ifndef formating_h
#define formating_h

#include "Abstractions.h"

#include <string>
#include <ostream>
using std::string;
using std::ostream;

class BusStation;
class Bus;

class RouteFormatter {
public:
    virtual void format(ostream& os,const Route& route) const = 0;
};

class SimpleRouteFormatter : public RouteFormatter {
public:
	void format(ostream& os, const Route& route) const override;
};

class BusFormatter {
public:
	virtual void format(ostream& os, const Bus& route) const = 0;
};

class SimpleBusFormatter : public BusFormatter {
public:
	void format(ostream& os, const Bus& route) const override;
};

class BusStationFormatter {
public:
	virtual void format(ostream& os, const BusStation& station) const = 0;
};

class SimpleBusStationFormatter : public BusStationFormatter {
public:
	void format(ostream& os, const BusStation& station) const override;
};
    
#endif