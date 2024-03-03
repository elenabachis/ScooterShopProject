#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include "ScooterRepo.h"

using namespace repository;

InMemoryRepository::InMemoryRepository() = default;

InMemoryRepository::~InMemoryRepository() = default;

bool InMemoryRepository::create(shared_ptr<domain::Scooter> new_entity) {
    auto it = find_if(elements.begin(), elements.end(), [&](const shared_ptr<domain::Scooter> &entity) {
        return new_entity->getId() == entity->getId();
    });
    if (it == elements.end()) {
        elements.push_back(new_entity);
        return true;
    }
    return false;
}

vector<shared_ptr<domain::Scooter>> InMemoryRepository::read() {
    return this->elements;
}

bool InMemoryRepository::update(shared_ptr<domain::Scooter> new_entity) {
    auto it = find_if(elements.begin(), elements.end(), [&](const shared_ptr<domain::Scooter> &entity) {
        return new_entity->getId() == entity->getId();
    });
    if (it != elements.end()) {
        (*it)->set_Last_Address(new_entity->get_Last_Address());
        (*it)->set_State(new_entity->get_actual_state());
        (*it)->set_kilometer_count(new_entity->get_Kilometer_Count());
        return true;
    }
    return false;
}

bool InMemoryRepository::remove(shared_ptr<domain::Scooter> new_entity) {
    auto it = find_if(elements.begin(), elements.end(), [&](const shared_ptr<domain::Scooter> &entity) {
        return new_entity->getId() == entity->getId();
    });
    if (it != elements.end()) {
        elements.erase(it);
        return true;
    }
    return false;
}

CSVFileRepository::CSVFileRepository(const string &filename) {
    this->file = filename;
    ofstream f;
    f.open(this->file, ios::in);
    f << "Identifier,Modell,Inbetriebnahmedatum,Kilometer,Standort,Status" << endl;
    f.close();
}

CSVFileRepository::~CSVFileRepository() = default;

bool CSVFileRepository::create(shared_ptr<domain::Scooter> new_entity) {
    ofstream f;
    f.open(this->file, std::ios::app);
    if (!f) {
        std::cerr << "Failed to open file" << endl;
        return false;
    }
    f << new_entity->getId() << ',' << new_entity->getModel() << ',';
    f << new_entity->getRegistration().year << '-' << new_entity->getRegistration().month << '-'
      << new_entity->getRegistration().day << ',';
    f << new_entity->get_Kilometer_Count() << ',' << new_entity->get_Last_Address() << ',';
//    Parked, Reserved, In_Use, In_Service, Out_of_Order
    switch (new_entity->get_actual_state()) {
        case Parked: {
            f << "parked" << endl;
            break;
        }
        case Reserved:
            f << "reserved" << endl;
            break;
        case In_Use:
            f << "in use" << endl;
            break;
        case In_Service:
            f << "in service" << endl;
            break;
        default:
            break;
        case Out_of_Order:
            f << "out of order" << endl;
            break;
    }
    f.close();
    return true;
}

std::vector<shared_ptr<domain::Scooter>> CSVFileRepository::read() {
    ifstream f;
    vector<shared_ptr<domain::Scooter>> elements;
    f.open(this->file, std::ios::in);
    if (!f) {
        std::cerr << "Failed to open file" << endl;
        return elements;
    }
    f.ignore();
    std::string line;
    while (std::getline(f, line)) {
        // Parse the line and create a new Scooter object
        std::shared_ptr<domain::Scooter> scooter = repository::parseLine(line);

        if (scooter) {
            elements.push_back(scooter);
        }
    }
    f.close();
    return elements;
}

bool CSVFileRepository::update(shared_ptr<domain::Scooter> entity) {
    auto elements = read();
    auto it = find_if(elements.begin(), elements.end(), [&](const shared_ptr<domain::Scooter> &scooter) {
        return entity->getId() == scooter->getId();
    });
    if (it != elements.end()) {
        (*it)->set_Last_Address(entity->get_Last_Address());
        (*it)->set_State(entity->get_actual_state());
        (*it)->set_kilometer_count(entity->get_Kilometer_Count());
        ofstream f;
        f.open(this->file, std::ios::trunc);
        if (!f) {
            std::cerr << "Failed to open file" << endl;
            return false;
        }
        f << "Identifier,Modell,Inbetriebnahmedatum,Kilometer,Standort,Status" << endl;
        f.close();

        for (auto element: elements){
            CSVFileRepository::create(element);
        }
        return true;
    }
    return false;
}

bool CSVFileRepository::remove(shared_ptr<domain::Scooter> entity) {
    auto elements = read();
    auto it = find_if(elements.begin(), elements.end(), [&](const shared_ptr<domain::Scooter> &scooter) {
        return scooter->getId() == entity->getId();
    });
    if (it != elements.end()) {
        elements.erase(it);
        ofstream f;
        f.open(this->file, std::ios::trunc);
        if (!f) {
            std::cerr << "Failed to open file" << endl;
            return false;
        }
        f << "Identifier,Modell,Inbetriebnahmedatum,Kilometer,Standort,Status" << endl;
        f.close();

        for (auto element: elements){
            CSVFileRepository::create(element);
        }
        return true;
    }
    return false;
}

shared_ptr<domain::Scooter> repository::parseLine(const string &line) {
    std::stringstream ss(line);
    std::string token;
    std::vector<std::string> tokens;

    while (std::getline(ss, token, ',')) {
        tokens.push_back(token);
    }

    // Extract the necessary data from the tokens and create a Scooter object
    // Modify the code below according to your CSV file structure and Scooter class implementation
    if (tokens.size() != 6) {
        // Invalid line format
        return nullptr;
    }

    std::string id = tokens[0];
    std::string model = tokens[1];
    std::stringstream registration(tokens[2]);
    string registration_token;
    vector<string> registration_tokens;
    while (getline(registration, registration_token, '-')) {
        registration_tokens.push_back(registration_token);
    }
    if (registration_tokens.size() != 3) {
        return nullptr;
    }
    date registration_date;
    registration_date.year = stoi(registration_tokens[0]);
    registration_date.month = stoi(registration_tokens[1]);
    registration_date.day = stoi(registration_tokens[2]);
    int kilometer = stoi(tokens[3]);
    std::string location = tokens[4];
    std::string status = tokens[5];
    if (status == "parked") {
        return std::make_shared<domain::Scooter>(id, model, registration_date, kilometer, location, State::Parked);
    }
    if (status == "reserved") {
        return std::make_shared<domain::Scooter>(id, model, registration_date, kilometer, location, State::Reserved);
    }
    if (status == "in use") {
        return std::make_shared<domain::Scooter>(id, model, registration_date, kilometer, location, State::In_Use);
    }
    if (status == "in service") {
        return std::make_shared<domain::Scooter>(id, model, registration_date, kilometer, location, State::In_Service);
    }
    if (status == "out of order") {
        return std::make_shared<domain::Scooter>(id, model, registration_date, kilometer, location,
                                                 State::Out_of_Order);
    }
}
