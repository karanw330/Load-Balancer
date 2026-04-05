#include "utils/Balancer.h"
#include "utils/Server.h"
#include "utils/Request.h"
#include "utils/RoundRobin.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <windows.h>

using namespace std;

void renderDashboard(const Balancer& balancer, const string& lastLog) {
    system("cls");
    const auto& servers = balancer.GetServers();

    cout << "┌────────────────────────────────────────────────────────────────────────────┐" << endl;
    cout << "│                         LOAD BALANCER LIVE DASHBOARD                       │" << endl;
    cout << "├──────────────────┬──────────────────────┬────────────┬─────────────────────┤" << endl;
    cout << "│ NAME             │ ADDRESS              │ LOAD       │ STATUS              │" << endl;
    cout << "├──────────────────┼──────────────────────┼────────────┼─────────────────────┤" << endl;

    if (servers.empty()) {
        cout << "│                  ( No active servers in the pool )                         │" << endl;
    } else {
        for (const auto& s : servers) {
            string loadStr = to_string(s->GetCurrentConnections()) + "/" + to_string(s->GetMaxConnections());
            string addr = s->GetIP() + ":" + to_string(s->port);
            
            cout << "│ " << left << setw(16) << s->GetName().substr(0, 16)
                 << " │ " << left << setw(20) << addr.substr(0, 20)
                 << " │ " << left << setw(10) << loadStr
                 << " │ " << left << setw(19) << s->GetHealthStatus().substr(0, 19) << " │" << endl;
        }
    }

    cout << "└──────────────────┴──────────────────────┴────────────┴─────────────────────┘" << endl;
    cout << " [Legend] [Enter: Quick Route | add <ip> <port> <name> | remove <port> | exit] " << endl;
    cout << "──────────────────────────────────────────────────────────────────────────────" << endl;
    
    if (!lastLog.empty()) {
        cout << lastLog << endl;
    }
    cout << "> ";
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    RoundRobin roundRobinStrategy;
    Balancer balancer;
    balancer.SetStrategy(&roundRobinStrategy);

    string lastLog = "[LOG] System initialized. Ready for requests.";
    string input;

    while (true) {
        renderDashboard(balancer, lastLog);
        
        if (!getline(cin, input)) break;

        if (input.empty()) {
            Server* routedSrv = balancer.RouteRequest("127.0.0.1", "Auto-Trigger", 0);
            if (routedSrv) {
                lastLog = "[LOG] Successfully routed to Server: " + routedSrv->GetName();
            } else {
                lastLog = "[LOG] Error: Routing failed (Check server pool).";
            }
            continue;
        }

        stringstream ss(input);
        string command;
        ss >> command;

        if (command == "exit") {
            break;
        } else if (command == "add") {
            string ip, name;
            int port;
            if (ss >> ip >> port >> name) {
                Server* newServer = new Server(ip, port, name);
                balancer.AddServer(newServer);
                lastLog = "[LOG] Added server: " + name + " at " + ip + ":" + to_string(port);
            } else {
                lastLog = "[LOG] Usage Error: add <ip> <port> <name>";
            }
        } else if (command == "remove") {
            int port;
            if (ss >> port) {
                balancer.RemoveServer(port);
                lastLog = "[LOG] Attempted to remove server on port: " + to_string(port);
            } else {
                lastLog = "[LOG] Usage Error: remove <port>";
            }
        } else if (command == "route") {
            string clientIP, payload;
            if (ss >> clientIP >> payload) {
                Server* routedSrv = balancer.RouteRequest(clientIP, payload, 0);
                if (routedSrv) {
                    lastLog = "[LOG] Manually routed to Server: " + routedSrv->GetName();
                } else {
                    lastLog = "[LOG] Error: Manual routing failed.";
                }
            } else {
                lastLog = "[LOG] Usage Error: route <clientIP> <payload>";
            }
        } else if (command == "status") {
            // Dashboard already shows status, so we just acknowledge
            lastLog = "[LOG] Dashboard refreshed.";
        } else {
            lastLog = "[LOG] Unknown command: " + command;
        }
    }

    cout << "Exiting Load Balancer Simulation. Goodbye!" << endl;
    return 0;
}