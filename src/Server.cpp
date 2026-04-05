#include "../utils/Server.h"
#include <iostream>

using namespace std;

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

void Server::DecrementLoad() {
    if (currentConnections > 0) {
        currentConnections--;
        cout << "Request completed on server " << serverName << ". Remaining connections: " << currentConnections << endl;
    } else {
        cout << "Server " << serverName << " has no active connections to decrement." << endl;
    }
}
