#include "../utils/Server.h"
#include <iostream>

using namespace std;

bool Server::Connect() {
    if (currentConnections < maxConnections) {
        currentConnections++;
        totalRequestsHandled++;
        return true;
    } else {
        failedRequests++;
        return false;
    }
}

void Server::UpdateHealthStatus(string newStatus) {
    healthStatus = newStatus;
    cout << "Updated health status of server " << serverName << " to: " << healthStatus << endl;
}

void Server::DisplayActiveConnections() {
    cout << "Server " << serverName << " has " << currentConnections << " active connections." << endl;
}

void Server::DecrementLoad() {
    if (currentConnections > 0) {
        currentConnections--;
        cout << "Request completed on server " << serverName << ". Remaining connections: " << currentConnections << endl;
    } else {
        cout << "Server " << serverName << " has no active connections to decrement." << endl;
    }
}

void Server::AddLoad(int count) {
    if (currentConnections + count <= maxConnections) {
        currentConnections += count;
    } else {
        currentConnections = maxConnections;
    }
}

void Server::RemoveLoad(int count) {
    if (currentConnections - count >= 0) {
        currentConnections -= count;
    } else {
        currentConnections = 0;
    }
}
