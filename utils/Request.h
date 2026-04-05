#pragma once
#include <string>

class Request {
    int requestId;
    std::string payload;
    int assignedServer; // Optional: To track which server is handling the request
    int creationTime; // Optional: To track when the request was created
    int connectedTime; // Optional: To track when the request was connected to a server
    
public:
    Request(int reqId, std::string load, int create_time) {
        requestId = reqId;
        payload = load;
        assignedServer = -1; // Initialize to an invalid server index
        creationTime = create_time;
    }
    int GetRequestId();
    std::string GetPayload();
    int GetAssignedServer();
    void SetAssignedServer(int serverIndex);
    void SetCreationTime(int time);
    int GetCreationTime();
};