#pragma once
#include "LoadBalancingStrategy.h"

class RoundRobin : public LoadBalancingStrategy {
    int currentIndex = -1;
public:
    int GetNextServerIndex(const std::string& clientKey, const std::vector<Server*>& servers) override {
        if (totalServers == 0) return -1; // No servers available
        currentIndex = (currentIndex + 1) % totalServers; // Move to the next index
        return currentIndex;
    }
};