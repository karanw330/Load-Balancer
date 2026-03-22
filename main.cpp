#include "utils/Balancer.h"
#include "utils/Server.h"
#include "utils/Request.h"
#include "utils/RoundRobin.h"
#include "utils/LoadBalancingStrategy.h"
#include <iostream>
#include <vector>

using namespace std;

RoundRobin roundRobinStrategy;
Balancer balancer;

int main() {
    
    // Add some servers to the balancer
    Server server1("192.168.1.101", 8080, "Server1");
    Server server2("192.168.1.102", 8081, "Server2");


    balancer.AddServer(&server1);

    balancer.AddServer(&server2);
    int LoadBalancingStrategy::totalServers = balancer.totalServers;
    LoadBalancingStrategy* strategy = &roundRobinStrategy; // Set the load balancing strategy
    
}