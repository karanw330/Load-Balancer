#include "../utils/Request.h"
#include <string>

using namespace std;

int Request::GetRequestId() {
    return requestId;
}
string Request::GetPayload() {
    return payload;
}
int Request::GetAssignedServer() {
    return assignedServer;
}
void Request::SetAssignedServer(int serverIndex) {
    assignedServer = serverIndex;
}
void Request::SetCreationTime(int time) {
    creationTime = time;
}

int Request::GetCreationTime() {
    return creationTime;
}
