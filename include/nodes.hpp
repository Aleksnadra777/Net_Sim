//
// Created by macie on 17.01.2023.
//
#include <memory>
#include <map>
#include <optional>
#include "types.hpp"
#include "storage_types.hpp"
#include "helpers.hpp"
#ifndef NETSIM_NODES_HPP
#define NETSIM_NODES_HPP
class IPackageReceiver {
public:
    using const_iterator = IPackageStockpile::const_iterator;
    virtual void receive_package(Package&& package) = 0;
    virtual ElementId get_id() const = 0;
    virtual const_iterator begin() const = 0;
    virtual const_iterator end() const = 0;
    virtual const_iterator cbegin() const = 0;
    virtual const_iterator cend() const = 0;
};

class StoreHouse : public IPackageReceiver{
public:
    virtual const_iterator cbegin() const override {return package_stockpile_->cbegin();};

    virtual const_iterator begin() const override { return cbegin(); };

    virtual const_iterator cend() const override = {return package_stockpile_->cend();};;

    virtual const_iterator end() const override {return cend();};

private:

};
#endif //NETSIM_NODES_HPP
