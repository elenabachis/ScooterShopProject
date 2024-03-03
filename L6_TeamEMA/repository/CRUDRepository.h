#pragma once


#include "Electroscooter.h"
#include <memory>
#include <vector>

template<class T>
class CrudRepository {
public:

    virtual bool create(std::shared_ptr<T> new_entity) = 0;

    virtual std::vector<std::shared_ptr<T>> read() = 0;

    virtual bool update(std::shared_ptr<T> entity) = 0;

    virtual bool remove(std::shared_ptr<T> entity) = 0;
};


