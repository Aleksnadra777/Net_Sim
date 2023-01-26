//
// Created by macie on 14.01.2023.
//

#ifndef NETSIM_PACKAGE_HPP
#define NETSIM_PACKAGE_HPP

#include "types.hpp"
#include <set>
class Package {
public:
    Package();
    explicit Package(ElementId);
    Package(Package&&) noexcept;
    Package(Package&) = delete;
    Package& operator = (Package&&) noexcept;
    Package& operator = (Package&) = delete;
    ElementId get_id() {return id_;}
    ~Package();

private:
    ElementId id_ = 0;

    inline static std::set<ElementId> assigned_IDs{0};
    inline static std::set<ElementId> freed_IDs;
};

#endif //NETSIM_PACKAGE_HPP
