//
// Created by macie on 17.01.2023.
//

#include "nodes.hpp"
#include "helpers.hpp"


void Ramp::deliver_goods(Time t)
{
    if (t % delivery_interval_ == 1)
    {
        Package pack;
        push_package(std::move(pack));
    }
}


void Worker::do_work(Time t) {
    if (!processing_buffer_)
    {
        if (!q_->empty())
        {
            processing_buffer_.emplace(q_->pop());
            t_ = t;
        }
    }

    if (processing_buffer_)
    {
        if ((t - t_) == pd_ - 1)
        {
            push_package(std::move(processing_buffer_.value()));
            processing_buffer_.reset();
        }
    }
}


void PackageSender::send_package()
{
    if (sending_buffer_)
    {
        IPackageReceiver* receiver = receiver_preferences_.choose_receiver();
        receiver->receive_package(std::move(*sending_buffer_));
        sending_buffer_.reset();
    }
}


void ReceiverPreferences::add_receiver(IPackageReceiver* r)
{
    double preference = 1;
    preferences[r] = preference;
    for(auto &i : preferences) {i.second = 1;}
    for(auto &i : preferences){ i.second /= static_cast<double>(preferences.size());}
}


IPackageReceiver *ReceiverPreferences::choose_receiver ()
{
    double p = pg_();
    double distributor_value = 0.0;
    for (auto& item: preferences) {
        distributor_value = distributor_value + item.second;
        if (p<=distributor_value) {
            return item.first;
        }
    }
    throw std::runtime_error("Error has occurred in ReceiverPreferences::choose_receiver()");
}


void ReceiverPreferences::remove_receiver(IPackageReceiver* r){
    if(preferences.find(r) != preferences.end())
    {
        preferences.erase(r);
        if (preferences.empty()) return;
        for(auto &i : preferences) {i.second = 1;}
        for(auto &i : preferences){ i.second /= static_cast<double>(preferences.size());}
    }
}
