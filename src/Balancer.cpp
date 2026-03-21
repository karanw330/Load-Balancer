#include "Balancer.h"

void Balancer::AddServer(Server* server) {
    servers.push_back(&server);
}

void Balancer::RemoveServer(string serverName) {
    for (auto it = servers.begin(); it != servers.end(); ++it) {
        if ((*it)->serverName == serverName) {
            servers.erase(it);
            break;
        }
    }
}

void Balancer::RouteRequest(string clientIP) {
    // Implement routing logic based on the selected strategy
    // For example, you can call RoundRobin(), LeastConnections(), or IPHashing() here
    
}