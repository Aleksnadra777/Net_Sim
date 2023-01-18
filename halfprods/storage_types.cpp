//
// Created by macie on 18.01.2023.
//

#include "../include/storage_types.hpp"

Package PackageQueue::pop() {
    switch (queueType_) {
        case PackageQueueType::FIFO: {
            auto p = std::move(packages_.front());
            packages_.pop_front();
            return p;
        }
        case PackageQueueType::LIFO: {
            auto p = std::move(packages_.back());
            packages_.pop_back();
            return p;
        }
    }
}