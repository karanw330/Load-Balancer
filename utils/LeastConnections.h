#pragma once
#include "LoadBalancingStrategy.h"
#include <string>
#include <vector>

class LeastConnections : public LoadBalancingStrategy {
public:
    int GetNextServerIndex(const std::string& clientKey, const std::vector<Server*>& servers) override;
};
