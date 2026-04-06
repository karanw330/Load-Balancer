#include "utils/Balancer.h"
#include "utils/Server.h"
#include "utils/Request.h"
#include "utils/RoundRobin.h"
#include "utils/PortHashing.h"
#include "utils/LeastConnections.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <windows.h>
#include <numeric>

// ANSI Color Definitions
#define RESET     "\033[0m"
#define BOLD      "\033[1m"
#define RED       "\033[31m"
#define GREEN     "\033[32m"
#define YELLOW    "\033[33m"
#define CYAN      "\033[36m"
#define BOLDRED   "\033[1m\033[31m"
#define BOLDGREEN "\033[1m\033[32m"

using namespace std;

void renderDashboard(const Balancer& balancer, const string& lastLog, const string& strategyName) {
    system("cls");
    const auto& servers = balancer.GetServers();

    const int TOTAL_WIDTH = 87;
    auto printBorder = [&](const string& left, const string& mid, const string& right, const vector<int>& colWidths = {}) {
        cout << CYAN << left;
        if (colWidths.empty()) {
            for (int i = 0; i < TOTAL_WIDTH - 2; ++i) cout << "─";
        } else {
            for (size_t i = 0; i < colWidths.size(); ++i) {
                for (int j = 0; j < colWidths[i] + 2; ++j) cout << "─";
                if (i < colWidths.size() - 1) cout << mid;
            }
        }
        cout << right << RESET << endl;
    };

    long long totalRequests = 0;
    long long totalDropped = 0;
    for(const auto& s : servers) {
        totalRequests += s->GetTotalRequests();
        totalDropped += s->GetFailedRequests();
    }

    // 1. Top Border
    printBorder("┌", "─", "┐");
    
    // 2. Title Line
    string title = "LOAD BALANCER LIVE DASHBOARD";
    int titlePadding = (TOTAL_WIDTH - 2 - title.length()) / 2;
    cout << CYAN << "│" << RESET << BOLD << string(titlePadding, ' ') << title << string(TOTAL_WIDTH - 2 - titlePadding - title.length(), ' ') << RESET << CYAN << "│" << endl;
    
    // 3. Strategy Line
    string strategyLine = "  Active Strategy: " + strategyName;
    cout << CYAN << "│" << RESET << left << setw(TOTAL_WIDTH - 2) << strategyLine << CYAN << "│" << endl;
    
    // 4. Header Border
    vector<int> cols = {16, 20, 8, 8, 8, 8};
    printBorder("├", "┬", "┤", cols);

    // 5. Column Headers
    cout << CYAN << "│ " << RESET << BOLD << left << setw(16) << "NAME" 
         << CYAN << " │ " << RESET << BOLD << left << setw(20) << "ADDRESS" 
         << CYAN << " │ " << RESET << BOLD << left << setw(8) << "LOAD" 
         << CYAN << " │ " << RESET << BOLD << left << setw(8) << "REQS" 
         << CYAN << " │ " << RESET << BOLD << left << setw(8) << "DROP" 
         << CYAN << " │ " << RESET << BOLD << left << setw(8) << "STATUS" 
         << CYAN << " │" << RESET << endl;
    
    // 6. Content Border
    printBorder("├", "┼", "┤", cols);

    // 7. Server Rows
    if (servers.empty()) {
        string msg = " ( No active servers in the pool ) ";
        int padding = (TOTAL_WIDTH - 2 - msg.length()) / 2;
        cout << CYAN << "│" << RESET << string(padding, ' ') << msg << string(TOTAL_WIDTH - 2 - padding - msg.length(), ' ') << CYAN << "│" << endl;
    } else {
        for (const auto& s : servers) {
            string loadStr = to_string(s->GetCurrentConnections()) + "/" + to_string(s->GetMaxConnections());
            string addr = s->GetIP() + ":" + to_string(s->port);
            string statusColor = (s->GetHealthStatus() == "Healthy") ? GREEN : RED;
            string dropColor = (s->GetFailedRequests() > 0) ? RED : RESET;
            
            cout << CYAN << "│ " << RESET << left << setw(16) << (s->GetName().length() > 16 ? s->GetName().substr(0, 13) + "..." : s->GetName())
                 << CYAN << " │ " << RESET << left << setw(20) << (addr.length() > 20 ? addr.substr(0, 17) + "..." : addr)
                 << CYAN << " │ " << YELLOW << left << setw(8) << loadStr << RESET
                 << CYAN << " │ " << GREEN << left << setw(8) << s->GetTotalRequests() << RESET
                 << CYAN << " │ " << dropColor << left << setw(8) << s->GetFailedRequests() << RESET
                 << CYAN << " │ " << statusColor << left << setw(8) << s->GetHealthStatus().substr(0, 8) << RESET << CYAN << " │" << endl;
        }
    }

    // 8. Footer Border
    printBorder("├", "┴", "┤");

    // 9. Stats Line
    string statsLeft = "  GLOBAL POOL STATS: ";
    string statsRight = "Handled: " + to_string(totalRequests) + " | Dropped: " + to_string(totalDropped) + "  ";
    int midPadding = TOTAL_WIDTH - 2 - statsLeft.length() - statsRight.length();
    cout << CYAN << "│" << RESET << BOLD << statsLeft << RESET << string(max(0, midPadding), ' ') << BOLD << statsRight << RESET << CYAN << "│" << endl;

    // 10. Bottom Border
    printBorder("└", "─", "┘");
    
    cout << " [Legend] " << YELLOW << "[Enter: Route]" << RESET << " | " << CYAN << "add <ip> <port> <name>" << RESET << " | strategy <rr/hash/lc>" << endl;
    cout << "          " << CYAN << "route <key> <payload>" << RESET << " | remove <port> | exit" << endl;
    cout << CYAN << "───────────────────────────────────────────────────────────────────────────────────────" << RESET << endl;
    
    if (!lastLog.empty()) {
        cout << lastLog << endl;
    }
    cout << "> ";
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
#endif
    RoundRobin roundRobinStrategy;
    PortHashing portHashingStrategy;
    LeastConnections leastConnectionsStrategy;
    
    Balancer balancer;
    balancer.SetStrategy(&roundRobinStrategy);
    string currentStrategyName = "Round Robin";

    string lastLog = string(BOLDGREEN) + "[LOG] System initialized. Dashboard updated for metrics." + RESET;
    string input;

    while (true) {
        renderDashboard(balancer, lastLog, currentStrategyName);
        
        if (!getline(cin, input)) break;

        if (input.empty()) {
            Server* routedSrv = balancer.RouteRequest("127.0.0.1", "Auto-Trigger", 0);
            if (routedSrv) {
                lastLog = string(BOLDGREEN) + "[LOG] Routed to Server: " + routedSrv->GetName() + RESET;
            } else {
                lastLog = string(BOLDRED) + "[LOG] DROPPED: No capacity or invalid routing." + RESET;
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
                lastLog = string(BOLDGREEN) + "[LOG] Added server: " + name + " at " + ip + ":" + to_string(port) + RESET;
            } else {
                lastLog = string(BOLDRED) + "[LOG] Usage Error: add <ip> <port> <name>" + RESET;
            }
        } else if (command == "remove") {
            int port;
            if (ss >> port) {
                balancer.RemoveServer(port);
                lastLog = string(BOLDGREEN) + "[LOG] Attempted to remove server on port: " + to_string(port) + RESET;
            } else {
                lastLog = string(BOLDRED) + "[LOG] Usage Error: remove <port>" + RESET;
            }
        } else if (command == "route") {
            string clientKey, payload;
            if (ss >> clientKey >> payload) {
                Server* routedSrv = balancer.RouteRequest(clientKey, payload, 0);
                if (routedSrv) {
                    lastLog = string(BOLDGREEN) + "[LOG] Manually routed (Key: " + clientKey + ") to Server: " + routedSrv->GetName() + RESET;
                } else {
                    lastLog = string(BOLDRED) + "[LOG] DROPPED: Capacity exceeded for key " + clientKey + RESET;
                }
            } else {
                lastLog = string(BOLDRED) + "[LOG] Usage Error: route <clientKey> <payload>" + RESET;
            }
        } else if (command == "strategy") {
            string strategyType;
            if (ss >> strategyType) {
                if (strategyType == "roundrobin" || strategyType == "rr" || strategyType == "1") {
                    balancer.SetStrategy(&roundRobinStrategy);
                    currentStrategyName = "Round Robin";
                    lastLog = string(BOLDGREEN) + "[LOG] Strategy switched to Round Robin." + RESET;
                } else if (strategyType == "hashing" || strategyType == "hash" || strategyType == "2") {
                    balancer.SetStrategy(&portHashingStrategy);
                    currentStrategyName = "Port Hashing";
                    lastLog = string(BOLDGREEN) + "[LOG] Strategy switched to Port Hashing." + RESET;
                } else if (strategyType == "leastconn" || strategyType == "lc" || strategyType == "3") {
                    balancer.SetStrategy(&leastConnectionsStrategy);
                    currentStrategyName = "Least Connections";
                    lastLog = string(BOLDGREEN) + "[LOG] Strategy switched to Least Connections." + RESET;
                } else {
                    lastLog = string(BOLDRED) + "[LOG] Unknown strategy: " + strategyType + ". Use: rr, hash, lc." + RESET;
                }
            } else {
                lastLog = string(BOLDRED) + "[LOG] Usage Error: strategy <rr|hash|lc>" + RESET;
            }
        } else if (command == "status") {
            lastLog = string(BOLDGREEN) + "[LOG] Dashboard refreshed." + RESET;
        } else {
            lastLog = string(BOLDRED) + "[LOG] Unknown command: " + command + RESET;
        }
    }

    cout << "Exiting Load Balancer Simulation. Goodbye!" << endl;
    return 0;
}