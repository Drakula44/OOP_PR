#include "State.h"
#include "Exceptions.h"
#include "Localization.h"
#include "PublicTransportSystem.h"
#include "Strategy.h"
#include <cstddef>
#include <format>
#include <iostream>
#include <limits>
using std::cin;
using std::cout;
using std::endl;
using std::string;

void State::print() {
    if (!text.empty())
        cout << endl << text << endl;
}

void State::printOptions() {
    for (size_t i = 0; i < options.size(); i++) {
        cout << i + 1 << ". " << options[i]->getDesc() << endl;
    }
    cout << "0. " << Localization::local_str[Localization::END_OF_PROGRAM]
         << endl;
}

State* State::quitOption = new EndProgram();
PublicTransportSystem& State::system = PublicTransportSystem::GSP();

StartUp::StartUp() {
    text = Localization::local_str[Localization::WELCOME_MESSAGE];
    options.push_back(new LoadNetwork());
}

EndProgram::EndProgram() {
    description = Localization::local_str[Localization::END_OF_PROGRAM];
}

LoadNetwork::LoadNetwork() {
    description = Localization::local_str[Localization::LOADING_DATA];
    options.push_back(new LoadStation());
}

LoadStation::LoadStation() {
    text = Localization::local_str[Localization::LOADING_STATIONS];
    options.push_back(new LoadBuses());
}

LoadBuses::LoadBuses() {
    text = Localization::local_str[Localization::LOADING_BUSES];
    options.push_back(new LoadSuccess());
}

LoadSuccess::LoadSuccess() {
    text = Localization::local_str[Localization::NETWORK_LOADED_SUCCESS];
    options.push_back(new MainMenu());
}

MainMenu::MainMenu() {
    text = Localization::local_str[Localization::MAIN_MENU];
    options.push_back(new GetBusInfo(this));
    options.push_back(new GetStationInfo(this));
    options.push_back(new GetRouteInfo(this));
    options.push_back(new ChooseRouteStrategy(this));
}

GetBusInfo::GetBusInfo(State* prev) {
    description = Localization::local_str[Localization::GET_BUS_INFO];
    text = Localization::local_str[Localization::SHOW_BUS_INFO];
    options.push_back(prev);
}

GetStationInfo::GetStationInfo(State* prev) {
    description = Localization::local_str[Localization::GET_STATION_INFO];
    text = Localization::local_str[Localization::SHOW_STATION_INFO];
    options.push_back(prev);
}

GetRouteInfo::GetRouteInfo(State* prev) {
    description = Localization::local_str[Localization::GET_PATH];
    text = Localization::local_str[Localization::GET_ROUTE_INFO];
    options.push_back(prev);
}

ChooseRouteStrategy::ChooseRouteStrategy(State* prev) {
    description = Localization::local_str[Localization::GET_PATH];
    text = Localization::local_str[Localization::GET_ROUTE_INFO];
    options.push_back(prev);
    strategies.push_back(new LeastBusChanges());
    strategies.push_back(new LeastStations());
    strategies.push_back(new ThroughImportant());
}

State* StartUp::execute() {
    print();
    printOptions();
    std::size_t choice;
    while (true) {
        cin >> choice;
        if (choice == 0) {
            return quitOption;
        }
        else if (choice - 1 < options.size() && choice - 1 >= 0) {
            return options[choice - 1];
        }
        else {
            cout << Localization::local_str[Localization::INVALID_INPUT]
                 << endl;
        }
    }
}

State* EndProgram::execute() { return quitOption; }

State* LoadNetwork::execute() { return options.front(); }

State* LoadStation::execute() {
    print();
    string fileName;
    while (true) {
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        getline(cin, fileName);
        try {
            system.loadStations(fileName);
            return options.front();
        } catch (const InvalidFile& e) {
            cout << std::vformat(
                        Localization::local_str[Localization::FILE_CANT_LOAD],
                        std::make_format_args(e.what()))
                 << endl;
        }
    }
}

State* LoadBuses::execute() {
    print();
    string fileName;
    while (true) {
        getline(cin, fileName);
        try {
            system.loadBuses(fileName);
            return options.front();
        } catch (const std::exception& e) {
            cout << e.what() << endl;
        }
    }
}

State* LoadSuccess::execute() {
    print();
    return options.front();
}

State* MainMenu::execute() {
    print();
    printOptions();
    int choice;
    while (true) {
        cin >> choice;
        if (choice == 0) {
            return quitOption;
        }
        else if (choice - 1 < options.size() && choice - 1 >= 0) {
            return options[choice - 1];
        }
        else {
            cout << Localization::local_str[Localization::INVALID_INPUT]
                 << endl;
        }
    }
}

State* GetBusInfo::execute() {
    print();
    string busName;
    cin >> busName;
    try {
        system.busInformation(busName);
    } catch (const std::exception& e) {
        cout << e.what() << endl;
    }
    return options.front();
}

State* GetStationInfo::execute() {
    print();
    int stationName;
    cin >> stationName;
    try {
        system.stationInformation(stationName);
    } catch (const std::exception& e) {
        cout << e.what() << endl;
    }
    return options.front();
}

State* GetRouteInfo::execute() {
    print();
    int start, end;
    cin >> start >> end;
    try {
        system.getRoute(start, end);
    } catch (const std::exception& e) {
        cout << e.what() << endl;
    }
    return options.front();
}

State* ChooseRouteStrategy::execute() {
    cout << text << endl;
    for (size_t i = 0; i < strategies.size(); i++) {
        cout << i + 1 << ". " << strategies[i]->getDesc() << endl;
    }
    int choice;
    cin >> choice;
    system.setStrategy(strategies[choice - 1]);
    return options.front();
}

ChooseRouteStrategy::~ChooseRouteStrategy() {
    for (auto& strategy : strategies) {
        delete strategy;
    }
    system.setStrategy(nullptr);
}