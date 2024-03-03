#pragma once

#include "CRUDRepository.h"

using namespace std;
namespace repository {
    class InMemoryRepository : public CrudRepository<domain::Scooter> {
    private:
        vector<shared_ptr<domain::Scooter>> elements;
    public:
        InMemoryRepository();

        bool create(shared_ptr<domain::Scooter> new_entity) override;

        std::vector<shared_ptr<domain::Scooter>> read() override;

        bool update(shared_ptr<domain::Scooter> new_entity) override;

        bool remove(shared_ptr<domain::Scooter> new_entity) override;

        ~InMemoryRepository();
    };

    shared_ptr<domain::Scooter> parseLine(const string& line);

    class CSVFileRepository : public CrudRepository<domain::Scooter> {
        std::string file;
    public:
        CSVFileRepository(const string& filename);

        bool create(shared_ptr<domain::Scooter> new_entity) override;

        std::vector<shared_ptr<domain::Scooter>> read() override;

        bool update(shared_ptr<domain::Scooter> entity) override;

        bool remove(shared_ptr<domain::Scooter> entity) override;

        ~CSVFileRepository();
    };
}