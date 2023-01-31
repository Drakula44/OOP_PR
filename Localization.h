#ifndef localization_h
#define localization_h

#include <array>
#include <string>
#include <unordered_map>

using std::string;
using std::unordered_map;

// clang-format off
/* cSpell:disable */
struct Localization{
    // clang-format on
    enum local_enum {
        WELCOME_MESSAGE,
        LOADING_DATA,
        END_OF_PROGRAM,
        LOADING_STATIONS,
        FILE_LOADED_STATIONS_DEFAULT,
        FILE_LOADED_STATIONS_CUSTOM,
        LOADING_BUSES,
        FILE_LOADED_BUSES_DEFAULT,
        FILE_LOADED_BUSES_CUSTOM,
        NETWORK_LOADED_SUCCESS,
        MAIN_MENU,
        SHOW_BUS_INFO,
        SHOW_STATION_INFO,
        GET_PATH,
        GET_STRATEGY,
        GET_BUS_INFO,
        BUS_INFO_GENERATED,
        GET_STATION_INFO,
        BUS_STATION_GENERATED,
        GET_ROUTE_INFO,
        ROUTE_INFO_GENERATED,
        GET_STRATEGY_INFO,
        STRATEGY_INFO_SELECTED,
        FILE_CANT_LOAD,
        INVALID_INPUT,
        BUS_NOT_FOUND,
        STATION_NOT_FOUND,
        ROUTE_NOT_FOUND,

    };
    static unordered_map<enum local_enum, string> local_str;
};

#endif