#ifndef user_interface_h
#define user_interface_h

#include "Localization.h"
#include "State.h"

class State;

class UserInterface {
    State* startUp;

public:
    UserInterface() { startUp = new StartUp(); }
    void run() {
        State* currentState = startUp;
        while (currentState != State::getQuitOption()) {
            currentState = currentState->execute();
        }
    }
    ~UserInterface() { delete startUp; }
};

#endif