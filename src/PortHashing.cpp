#include "../utils/PortHashing.h"
#include <functional>

int PortHashing::GetNextServerIndex(const std::string& clientKey, const std::vector<Server*>& servers) {
    if (servers.empty()) return -1;
    
    // Hash the client key 
    std::hash<std::string> hasher;
    size_t hashValue = hasher(clientKey);
    
    // Map the hash value to a server index
    return static_cast<int>(hashValue % servers.size());
}
