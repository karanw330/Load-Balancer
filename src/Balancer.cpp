#include "../utils/Balancer.h"
#include <iostream>

using namespace std;

int LoadBalancingStrategy::totalServers = 0;

Balancer::Balancer() : strategy(nullptr), totalServers(0) {}

void Balancer::AddServer(Server* server) {   
    servers.push_back(server);
    totalServers++;
    LoadBalancingStrategy::totalServers = totalServers;
}

void Balancer::RemoveServer(int port) {
    for (auto it = servers.begin(); it != servers.end(); ++it) {
        if ((*it)->port == port) {
            servers.erase(it);
            totalServers--;
            LoadBalancingStrategy::totalServers = totalServers;
            break;
        }
    }
}

Server* Balancer::RouteRequest(string clientIP, string payload, int currentTime) {
    if (!strategy) {
        cout << "Error: No load balancing strategy set." << endl;
        return nullptr;
    }

    if (servers.empty()) {
        cout << "Error: No servers available to route the request." << endl;
        return nullptr;
    }

    int serverIndex = strategy->GetNextServerIndex();
    if (serverIndex >= 0 && serverIndex < servers.size()) {
        servers[serverIndex]->Connect();
        return servers[serverIndex];
    } else {
        cout << "Error: Strategy returned an invalid server index." << endl;
        return nullptr;
    }
}

void Balancer::SetStrategy(LoadBalancingStrategy* newStrategy) {
    strategy = newStrategy;
}