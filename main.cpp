#include <filesystem>
#include <iostream>
using namespace std;

#include "PublicTransportSystem.h"
#include "UserInterface.h"

#include "Bus.h"
#include "BusStation.h"

int main() {
    // auto& gsp = PublicTransportSystem::GSP();
    UserInterface ui;
    ui.run();
}