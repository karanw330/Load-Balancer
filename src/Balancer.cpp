#include "../utils/Balancer.h"

void Balancer::AddServer(Server* server) {   
    servers.push_back(server);
    totalServers++;
}

void Balancer::RemoveServer(int port) {
    for (auto it = servers.begin(); it != servers.end(); ++it) {
        if ((*it)->port == port) {
            servers.erase(it);
            totalServers--;
            break;
        }
    }
}

void Balancer::RouteRequest(string clientIP, int currentTime) {
    // Implement routing logic based on the selected strategy
    
    
}