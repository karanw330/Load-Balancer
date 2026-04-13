#pragma once
#include <string>
#include <queue>
#include <iostream>
#include "Request.h"

class Server {
    std::string ip;
    int currentConnections;
    int maxConnections;
    std::string serverName;
    std::string healthStatus;
    
public:
    int port;
    Server(std::string ip, int port, std::string serverName, int maxConnections = 30, std::string healthStatus = "Healthy") {
        this->ip = ip;
        this->port = port;
        this->currentConnections = 0;
        this->maxConnections = maxConnections;
        this->serverName = serverName;
        this->healthStatus = healthStatus;
    };

    long long totalRequestsHandled = 0;
    long long failedRequests = 0;

    std::queue<Request> activeRequests;
    bool Connect();
    void UpdateHealthStatus(std::string newStatus);
    void DisplayActiveConnections();
    void DecrementLoad();
    void AddLoad(int count);
    void RemoveLoad(int count);

    // Getters
    std::string GetName() const { return serverName; }
    std::string GetIP() const { return ip; }
    int GetCurrentConnections() const { return currentConnections; }
    int GetMaxConnections() const { return maxConnections; }
    std::string GetHealthStatus() const { return healthStatus; }
    long long GetTotalRequests() const { return totalRequestsHandled; }
    long long GetFailedRequests() const { return failedRequests; }
};