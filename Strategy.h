#ifndef strategy_h
#define strategy_h

#include "Abstractions.h"
#include "Localization.h"

#include <optional>
#include <string>
#include <vector>

class Strategy {
protected:
    string description;

public:
    virtual ~Strategy() = default;
    virtual std::optional<Route> getRoute(int startStation, int endStation) = 0;
    string getDesc() { return description; }
};

class LeastStations : public Strategy {
public:
    ~LeastStations() = default;
    LeastStations() { description = "Least stations"; }
    virtual std::optional<Route> getRoute(int startStation,
                                          int endStation) override;
};

class LeastBusChanges : public Strategy {
public:
    ~LeastBusChanges() = default;
    LeastBusChanges() { description = "Least bus changes"; }
    virtual std::optional<Route> getRoute(int startStation,
                                          int endStation) override;
};

class ThroughImportant : public Strategy {
public:
    ~ThroughImportant() = default;
    ThroughImportant() { description = "Through important"; }
    virtual std::optional<Route> getRoute(int startStation,
                                          int endStation) override;
};

#endif