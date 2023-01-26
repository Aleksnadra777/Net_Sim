//
// Created by macie on 18.01.2023.
//

#include "../include/storage_types.hpp"

Package PackageQueue::pop() {
    Package package;
    switch(queueType_) {
        case PackageQueueType::FIFO: {
            auto p = std::move(packages_.front());
            packages_.pop_front();
            break;
        }
        case PackageQueueType::LIFO: {
            auto p = std::move(packages_.back());
            packages_.pop_back();
            break;
        }
    }
}