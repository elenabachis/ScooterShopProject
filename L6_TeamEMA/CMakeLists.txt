cmake_minimum_required(VERSION 3.24)
project(Labor5)

set(CMAKE_CXX_STANDARD 20)

include_directories(controller domain repository ui)

add_executable(Labor5 main.cpp repository/ScooterRepo.h domain/Electroscooter.h
        controller/ScooterController.h ui/ScooterUi.h domain/Electroscooter.cpp repository/ScooterRepo.cpp
        controller/ScooterController.cpp
        ui/ScooterUI.cpp repository/CRUDRepository.h
        tests.cpp tests.h)
