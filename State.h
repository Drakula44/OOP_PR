#ifndef state_h
#define state_h

#include <cstddef>
#include <memory>
#include <string>
#include <vector>

#include "Strategy.h"

using std::string;
using std::unique_ptr;
using std::vector;

class PublicTransportSystem;

class State {
protected:
    string description;
    string text;
    string output;
    vector<State*> options;
    vector<State*> fails;
    static State* quitOption;
    static PublicTransportSystem& system;

public:
    virtual State* execute() = 0;
    virtual ~State() = default;
    void print();
    void printOptions();
    string getDesc() { return description; }
    static State* getQuitOption() { return quitOption; }
};

class StartUp : public State {
public:
    StartUp();
    ~StartUp() { delete options[0]; }
    State* execute() override;
};
class EndProgram : public State {
public:
    EndProgram();
    State* execute() override;
};
class LoadNetwork : public State {
public:
    LoadNetwork();
    ~LoadNetwork() { delete options[0]; }
    State* execute() override;
};
class LoadStation : public State {
public:
    LoadStation();
    ~LoadStation() { delete options[0]; }
    State* execute() override;
};
class LoadBuses : public State {
public:
    LoadBuses();
    ~LoadBuses() { delete options[0]; }
    State* execute() override;
};
class LoadSuccess : public State {
public:
    LoadSuccess();
    ~LoadSuccess() { delete options[0]; }
    State* execute() override;
};
class MainMenu : public State {
public:
    MainMenu();
    ~MainMenu() {
        for (size_t i = 0; i < options.size(); i++)
            delete options[0];
    }
    State* execute() override;
};
class GetBusInfo : public State {
public:
    GetBusInfo(State* prev);
    ~GetBusInfo() = default;
    State* execute() override;
};
class GetStationInfo : public State {
public:
    GetStationInfo(State* prev);
    ~GetStationInfo() = default;
    State* execute() override;
};
class GetRouteInfo : public State {
public:
    GetRouteInfo(State* prev);
    ~GetRouteInfo() = default;
    State* execute() override;
};
class ChooseRouteStrategy : public State {
private:
    vector<Strategy*> strategies;

public:
    ChooseRouteStrategy(State* prev);
    ~ChooseRouteStrategy();
    State* execute() override;
};

#endif