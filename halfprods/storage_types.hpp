//
// Created by macie on 14.01.2023.
//

#ifndef NETSIM_STORAGE_TYPES_HPP
#define NETSIM_STORAGE_TYPES_HPP

#include "package.hpp"
#include "types.hpp"
#include <list>
#include <utility>
#include <stack>
#include <stdlib.h>
#include <memory>
#include <map>
#include <optional>

class IPackageStockpile{
public:
    using const_iterator = std::list<Package>::const_iterator;
    virtual void push(Package&&) = 0;
    virtual bool empty() const = 0;
    virtual std::size_t size() const = 0;
    virtual ~IPackageStockpile() = default;
    virtual const_iterator begin() const = 0;
    virtual const_iterator cbegin() const = 0;
    virtual const_iterator end() const = 0;
    virtual const_iterator cend() const = 0;
};

enum class PackageQueueType{
    FIFO,
    LIFO
};

class IPackageQueue: public IPackageStockpile{
public:
    virtual Package pop() = 0;
    virtual PackageQueueType get_queue_type() const = 0;
    ~IPackageQueue() override = default;
};

class PackageQueue: public IPackageQueue{
    std::list<Package> packages_;
    PackageQueueType queueType_;
public:
    PackageQueue(PackageQueueType queueType): queueType_(queueType) {}

    void push(Package&& p) override {
        packages_.emplace_back(std::move(p));
    }
    bool empty() const override{
        return packages_.empty();
    }
    std::size_t size() const override{
        return packages_.size();
    }
    const_iterator begin() const override{
        return packages_.cbegin();
    }
    const_iterator end() const override{
        return packages_.end();
    }
    const_iterator cbegin() const override{
        return packages_.cbegin();
    }
    const_iterator cend() const override{
        return packages_.cend();
    }
    Package pop() override;
};
#endif //NETSIM_STORAGE_TYPES_HPP
