#include "../utils/LeastConnections.h"
#include <climits>

int LeastConnections::GetNextServerIndex(const std::string& clientKey, const std::vector<Server*>& servers) {
    if (servers.empty()) return -1;

    int minConnections = INT_MAX;
    int bestServerIndex = -1;

    for (int i = 0; i < servers.size(); ++i) {
        // Find the server with the minimum current connections
        int currentConnections = servers[i]->GetCurrentConnections();
        if (currentConnections < minConnections) {
            minConnections = currentConnections;
            bestServerIndex = i;
        }
    }

    return bestServerIndex;
}
