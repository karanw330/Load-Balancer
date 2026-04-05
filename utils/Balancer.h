#pragma once
#include <vector>
#include <string>
#include "Server.h"
#include "LoadBalancingStrategy.h"

class Balancer {
    std::vector<Server *> servers;
    LoadBalancingStrategy* strategy;
    
public:
    int totalServers;
    Balancer();
    void AddServer(Server* server);
    void RemoveServer(int port);
    Server* RouteRequest(std::string clientIP, std::string payload, int currentTime);
    void SetStrategy(LoadBalancingStrategy* newStrategy);
    const std::vector<Server*>& GetServers() const { return servers; }
};