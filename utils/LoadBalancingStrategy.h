#pragma once
#include <string>
#include <vector>
#include "Server.h"

class LoadBalancingStrategy {
public:
    static int totalServers;
    virtual int GetNextServerIndex(const std::string& clientKey, const std::vector<Server*>& servers) = 0; // Pure virtual function
    virtual ~LoadBalancingStrategy() = default; // Virtual destructor for proper cleanup
};