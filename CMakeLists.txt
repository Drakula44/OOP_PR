# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required(VERSION 3.8)

# set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_EXTENSIONS on)
set(CMAKE_EXPORT_COMPILE_COMMANDS on)

if(MSVC)
  # warninglevel 4 and all warnings as errors
  add_compile_options(/W4)
else()
  add_compile_options(-std=c++20 -stdlib=libc++ -fexperimental-library -g -O0 -fsanitize=address)
  add_link_options(-stdlib=libc++ -fexperimental-library -fsanitize=address -fno-omit-frame-pointer)

  # add_compile_options(-std=c++20 -stdlib=libc++ -fexperimental-library -g -O0 -Wall -Wextra -Wpedantic)
  # add_link_options(-stdlib=libc++ -fexperimental-library)

  # add_compile_options(-std=c++20 -Wall -Wextra -Wpedantic)
endif()

project("OOP_PR")

# file(GLOB Project_src
# "include/*.h"
# "src/*.cpp"
# )
add_executable(
  BusNetwork "main.cpp"
  "Bus.h" "Bus.cpp"
  "BusStation.h" "BusStation.cpp"
  "Exceptions.h"
  "FileHandler.h" "FileHandler.cpp"
  "Formating.h" "Formating.cpp"
  "Localization.h" "Localization.cpp"
  "PublicTransportSystem.h" "PublicTransportSystem.cpp"
  "State.h" "State.cpp"
  "Strategy.h" "Strategy.cpp"
  "UserInterface.h"
)

add_custom_command(
  OUTPUT test.lic
  COMMAND BusNetwork
  DEPENDS BusNetwork
  COMMENT "Testing"
  VERBATIM
)

add_custom_target(
  Testing ALL
  DEPENDS test.lic
)