#include "utils/Balancer.h"
#include "utils/Server.h"
#include "utils/Request.h"
#include "utils/RoundRobin.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

void ShowHelp() {
    cout << "\n--- Load Balancer CLI Commands ---\n";
    cout << "add <ip> <port> <name>       : Add a new server\n";
    cout << "remove <port>                : Remove a server by port\n";
    cout << "route <clientIP> <payload>   : Route a simulated request\n";
    cout << "status                       : Show health and load of all servers\n";
    cout << "help                         : Show this help message\n";
    cout << "exit                         : Quit the simulation\n";
    cout << "----------------------------------\n";
}

int main() {
    RoundRobin roundRobinStrategy;
    Balancer balancer;
    balancer.SetStrategy(&roundRobinStrategy);

    string input;
    cout << "Welcome to the Load Balancer Simulation CLI!" << endl;
    ShowHelp();

    while (true) {
        cout << "> ";
        if (!getline(cin, input)) break;
        if (input.empty()) continue;

        stringstream ss(input);
        string command;
        ss >> command;

        if (command == "exit") {
            break;
        } else if (command == "help") {
            ShowHelp();
        } else if (command == "add") {
            string ip, name;
            int port;
            if (ss >> ip >> port >> name) {
                // Using dynamic allocation for simplified storage in this simulation
                // In a real system, we'd manage this memory more carefully.
                Server* newServer = new Server(ip, port, name);
                balancer.AddServer(newServer);
                cout << "Added server " << name << " at " << ip << ":" << port << endl;
            } else {
                cout << "Usage: add <ip> <port> <name>" << endl;
            }
        } else if (command == "remove") {
            int port;
            if (ss >> port) {
                balancer.RemoveServer(port);
                cout << "Removed server on port " << port << " (if it existed)" << endl;
            } else {
                cout << "Usage: remove <port>" << endl;
            }
        } else if (command == "route") {
            string clientIP, payload;
            if (ss >> clientIP >> payload) {
                balancer.RouteRequest(clientIP, payload, 0);
            } else {
                cout << "Usage: route <clientIP> <payload>" << endl;
            }
        } else if (command == "status") {
            const auto& servers = balancer.GetServers();
            if (servers.empty()) {
                cout << "No active servers." << endl;
            } else {
                cout << "\n--- Server Status ---\n";
                for (const auto& s : servers) {
                    cout << "[" << s->GetName() << "] " << s->GetIP() << ":" << s->port 
                         << " | Connections: " << s->GetCurrentConnections() << "/" << s->GetMaxConnections()
                         << " | Status: " << s->GetHealthStatus() << endl;
                }
                cout << "----------------------\n";
            }
        } else {
            cout << "Unknown command: " << command << ". Type 'help' for available commands." << endl;
        }
    }

    cout << "Exiting Load Balancer Simulation. Goodbye!" << endl;
    return 0;
}