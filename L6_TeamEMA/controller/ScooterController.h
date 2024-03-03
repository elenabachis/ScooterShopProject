#pragma once

#include "ScooterRepo.h"

namespace controller{
    class Controller{
        shared_ptr<CrudRepository<domain::Scooter>> scooter_repository_;
    public:
        ///
        /// \param scooter_repository
        explicit Controller(shared_ptr<CrudRepository<domain::Scooter>> scooter_repository);
//        Controller(shared_ptr<repository::Repository> repo);
        ~Controller();
        ///
        /// \param id_
        /// \param model_
        /// \param reg_date
        /// \param kilometer_count_
        /// \param address_
        /// \param initial_state
        /// \return true if the scooter was added
        bool add_Scooter(string id_, string model_, date reg_date, int kilometer_count_, string address_, State initial_state);
        ///
        /// \param scooter
        /// \return true if the scooter was deleted
        bool delete_Scooter(shared_ptr<domain::Scooter> scooter);
        ///
        /// \param scooter
        /// \return true if the scooter was updated
        bool update(shared_ptr<domain::Scooter> scooter);
        ///
        /// \param query
        /// \return a vector of shared pointers to a Scooter Class
        vector<shared_ptr<domain::Scooter>> filter_by_age(int query);
        ///
        /// \param query
        /// \return a vector of shared pointers to a Scooter Class
        vector<shared_ptr<domain::Scooter>> filter_by_location(string query);
        ///
        /// \param query
        /// \return a vector of shared pointers to a Scooter Class
        vector<shared_ptr<domain::Scooter>> filter_by_kilometer_count(int query);
        ///
        /// \return a vector of shared pointers to a Scooter Class
        vector<shared_ptr<domain::Scooter>> show_by_ascending_age_order();
        ///
        /// \param scooter
        /// \return true if the client can reserve the scooter
        bool reserve_Scooter(shared_ptr<domain::Scooter> scooter);

        vector<shared_ptr<domain::Scooter>> get_all();
    };
}