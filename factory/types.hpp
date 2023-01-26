//
// Created by macie on 14.01.2023.
//

#ifndef NETSIM_TYPES_HPP
#define NETSIM_TYPES_HPP
#include <functional>
using ElementId = unsigned int;
using size_type = unsigned int;
//Po półproduktach
using TimeOffset = unsigned int;
using Time = unsigned int;
using ProbabilityGenerator = std::function<double()>;

#endif //NETSIM_TYPES_HPP
