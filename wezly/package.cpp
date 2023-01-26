//
// Created by macie on 17.01.2023.
//

#include "package.hpp"
#include <stdexcept>

Package::Package() {
    ElementId newId = -1;
    if (!freed_IDs.empty()) {
        newId = *(freed_IDs.begin());
    }
    else {
        newId = *assigned_IDs.rbegin() + 1;
        freed_IDs.erase(newId);
    }
    assigned_IDs.insert(newId);
    id_ = newId;

}

Package::Package(ElementId id) {
    if (assigned_IDs.find(id) != assigned_IDs.end())
        throw std::invalid_argument("ID is already assigned");
    assigned_IDs.insert(id);
    id_ = id;
    if (freed_IDs.find(id) != freed_IDs.end()) freed_IDs.erase(id);
}

Package::Package(Package &&package) noexcept {
    id_ = package.id_;
    package.id_ = -1;
}

Package &Package::operator=(Package && package) noexcept {
    if (id_ != -1){
        assigned_IDs.erase(id_);
        freed_IDs.insert(id_);
    }

    id_ = package.id_;
    package.id_ = -1;

    return *this;
}

Package::~Package() {
    if (id_ != -1){
        // if not exist - insert
        if (freed_IDs.find(id_) == freed_IDs.end()) freed_IDs.insert(id_);

        // Erase if exist
        if (assigned_IDs.find(id_) != assigned_IDs.end()) assigned_IDs.erase(id_);
    }
}