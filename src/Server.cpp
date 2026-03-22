#include "../utils/Server.h"

void Server::Connect() {
    if (currentConnections < maxConnections) {
        currentConnections++;
        cout << "Connected to server: " << serverName << " (" << ip << ":" << port << ")" << endl;
    } else {
        cout << "Server " << serverName << " is at maximum capacity. Cannot connect." << endl;
    }
}

void Server::UpdateHealthStatus(string newStatus) {
    healthStatus = newStatus;
    cout << "Updated health status of server " << serverName << " to: " << healthStatus << endl;
}

void Server::DisplayActiveConnections() {
    cout << "Server " << serverName << " has " << currentConnections << " active connections." << endl;
}

