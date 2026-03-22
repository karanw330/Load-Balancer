class Server {
    string ip;
    int currentConnections=0;
    int maxConnections=0;
    string serverName;
    string healthStatus;
    public:
        int port;
        Server(string ip, int port, string serverName, int maxConnections=30, string healthStatus="Healthy") {
            this->ip = ip;
            this->port = port;
            this->currentConnections = 0;
            this->maxConnections = maxConnections;
            this->serverName = serverName;
            this->healthStatus = "Healthy";
        };
        queue<Request> activeRequests;
        void Connect();
        void UpdateHealthStatus(string newStatus);
        void DisplayActiveConnections();
        void DecrementLoad();
};