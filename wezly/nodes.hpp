//
// Created by macie on 17.01.2023.
//

#ifndef NETSIM_NODES_HPP
#define NETSIM_NODES_HPP
#include "types.hpp"
#include "helpers.hpp"
#include "storage_types.hpp"



#include <iostream>
#include <memory>
#include <optional>
#include <map>
#include <functional>
enum ReceiverType {
    WORKER,STOREHOUSE
};
class IPackageReceiver {
public:
    using const_iterator = IPackageStockpile::const_iterator;
    virtual void receive_package(Package&& package) = 0;
#if (EXERCISE_ID > EXERCISE_ID_NODES)
    virtual ReceiverType get_receiver_type () const = 0;
#endif
    virtual ElementId get_id() const = 0;
    virtual const_iterator begin() const = 0;
    virtual const_iterator end() const = 0;
    virtual const_iterator cbegin() const = 0;
    virtual const_iterator cend() const = 0;
};

class ReceiverPreferences{
public:
    using preferences_t = std::map<IPackageReceiver*, double>;
    using const_iterator = preferences_t::const_iterator;

    ReceiverPreferences(ProbabilityGenerator pg = probability_generator) : pg_(std::move(pg)) {};
    void add_receiver (IPackageReceiver* r);
    void remove_receiver (IPackageReceiver* r);
    IPackageReceiver* choose_receiver();
    const preferences_t &get_preferences() const {return preferences;};
    const_iterator begin() {return preferences.begin();}
    const_iterator end() {return preferences.end();}
    const_iterator cbegin() const {return preferences.cbegin();}
    const_iterator cend() const {return preferences.cend();}

private:
    ProbabilityGenerator pg_;
    preferences_t preferences;
};

class PackageSender {
public:
    ReceiverPreferences receiver_preferences_;

    PackageSender()(PackageSender&&) = default;
    void send_package();

    const std::optional<Package>& get_sending_buffer() const {return sending_buffer_;}

    virtual ~PackageSender() = default;

protected:
    void push_package(Package&& p) { sending_buffer_ = std::move(p);}

private:
    std::optional<Package> sending_buffer_;
};

class Ramp: public PackageSender{
public:
    Ramp(ElementId id, TimeOffset delivery_interval): id_(id), delivery_interval_(delivery_interval) {}
    void deliver_goods(Time current_time);
    TimeOffset get_delivery_interval() const {return delivery_interval_;}
    ElementId get_id() const {return id_;}

private:
    ElementId id_;
    TimeOffset delivery_interval_;
};

class Storehouse : public IPackageReceiver{
public:
    Storehouse(ElementId id, std::unique_ptr<IPackageStockpile> d = std::make_unique<PackageQueue>(PackageQueueType::LIFO)) : id_(id), package_stockpile_(std::move(d)) {}
#if (EXERCISE_ID > EXERCISE_ID_NODES)
    ReceiverType get_receiver_type() const {return ReceiverType::STOREHOUSE;};
#endif
    ElementId get_id() const { return id_; }
    void receive_package(Package &&package) override {package_stockpile_->push(std::move(package))}
    virtual const_iterator cbegin() const override {return package_stockpile_->cbegin();};
    virtual const_iterator begin() const override { return package_stockpile_->begin(); };
    virtual const_iterator cend() const override {return package_stockpile_->cend();};
    virtual const_iterator end() const override {return package_stockpile_->end();};
private:
    ElementId id_;
    std::unique_ptr<IPackageStockpile> package_stockpile_;
};

class Worker: public PackageSender, public IPackageReceiver{
public:
    Worker(ElementId id, TimeOffset pd, std::unique_ptr<IPackageQueue> q) : id_(id), pd_(pd), q_(std::move(q)) {}
    void do_work(Time t);
    TimeOffset get_processing_duration() const {return pd_;}
    Time get_package_processing_start_time() const {return t_;}
#if (EXERCISE_ID > EXERCISE_ID_NODES)
    ReceiverType get_receiver_type() const override {return ReceiverType::WORKER;}
#endif

    void receive_package(Package&& p) override {q_->push(std::move(p));}
    ElementID get_id() const override { return id_; }

    // Iteratory
    IPackageStockpile::const_iterator begin() const override {return q_->begin();}
    IPackageStockpile::const_iterator end() const override {return q_->end();}
    IPackageStockpile::const_iterator cbegin() const override {return q_->cbegin();}
    IPackageStockpile::const_iterator cend() const override {return q_->cend();}
private:
    ElementID id_;
    TimeOffset pd_;
    std::unique_ptr<IPackageQueue> q_;
    Time t_ = 0;
    std::optional<Package> processing_buffer_;
};


#endif //NETSIM_NODES_HPP
