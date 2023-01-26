//
// Created by macie on 14.01.2023.
//

#ifndef NETSIM_STORAGE_TYPES_HPP
#define NETSIM_STORAGE_TYPES_HPP

#include "package.hpp"
#include "types.hpp"
#include <list>


class IPackageStockpile{
public:
    using const_iterator = std::list<Package>::const_iterator;
    virtual void push(Package&&) = 0;
    virtual bool empty() const = 0;
    virtual size_type size() const = 0;
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
    virtual PackageQueueType get_queue_type() = 0;
    ~IPackageQueue() override = default;
};

class PackageQueue: public IPackageQueue{
public:
    std::list<Package> packages_;
    PackageQueueType queueType_;

    explicit PackageQueue(PackageQueueType type) { queueType_ = type;};
    void push(Package&& p) override {
        packages_.emplace_back(std::move(p));
    }
    bool empty() const override{
        return packages_.empty();
    }
    size_type size() const override{
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
    PackageQueueType get_queue_type() override { return queueType_;};
};
#endif //NETSIM_STORAGE_TYPES_HPP
