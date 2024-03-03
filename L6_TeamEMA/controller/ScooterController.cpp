#include "ScooterController.h"
#include "ScooterRepo.h"
#include <string>


controller::Controller::Controller(shared_ptr<CrudRepository<domain::Scooter>> scooter_repository){
    this->scooter_repository_= scooter_repository;
}

bool controller::Controller::add_Scooter(string id_, string model_, date reg_date, int kilometer_count_,
                                         string address_, State initial_state) {
    auto scooter_ptr = make_shared<domain::Scooter>(id_, model_, reg_date, kilometer_count_,
                                                    address_, initial_state);
    return scooter_repository_->create(scooter_ptr);

}

bool controller::Controller::delete_Scooter(shared_ptr<domain::Scooter> scooter) {
    return scooter_repository_->remove(scooter);
}

bool controller::Controller::update(shared_ptr<domain::Scooter> scooter) {
    return scooter_repository_->update(scooter);
}

vector<shared_ptr<domain::Scooter>> controller::Controller::filter_by_age(int query) {
    vector<shared_ptr<domain::Scooter>> filtered_scooters;
    auto all_scooters = scooter_repository_->read();
    for (auto scooter: all_scooters) {
        if (scooter->getRegistration().year == query)
            filtered_scooters.push_back(scooter);
    }
    return filtered_scooters;

}

vector<shared_ptr<domain::Scooter>> controller::Controller::filter_by_location(string query) {
    vector<shared_ptr<domain::Scooter>> filtered_scooters;
    auto all_scooters = scooter_repository_->read();
    for (auto scooter: all_scooters) {
        if (scooter->get_Last_Address() == query)
            filtered_scooters.push_back(scooter);
    }
    return filtered_scooters;
}

vector<shared_ptr<domain::Scooter>> controller::Controller::filter_by_kilometer_count(int query) {
    vector<shared_ptr<domain::Scooter>> filtered_scooters;
    auto all_scooters = scooter_repository_->read();
    for (auto scooter: all_scooters) {
        if (scooter->get_Kilometer_Count() >= query)
            filtered_scooters.push_back(scooter);
    }
    return filtered_scooters;

}

vector<shared_ptr<domain::Scooter>> controller::Controller::show_by_ascending_age_order() {
    auto all_scooters = scooter_repository_->read();
    sort(all_scooters.begin(), all_scooters.end(), [](const shared_ptr<domain::Scooter> &a,
                                                      const shared_ptr<domain::Scooter> &b) {
        return a->getRegistration().year < b->getRegistration().year;
    });
    return all_scooters;
}

bool controller::Controller::reserve_Scooter(shared_ptr<domain::Scooter> scooter) {
    if (scooter->get_actual_state() == State::Parked) {
        scooter->set_State(State::Reserved);
        return true;
    }
    return false;
}

vector<shared_ptr<domain::Scooter>> controller::Controller::get_all() {
    return scooter_repository_->read();
}

controller::Controller::~Controller() = default;