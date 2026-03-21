class Server {
    string ip;
    int port;
    int currentConnections;
    int maxConnections;
    string serverName;
    string healthStatus;
    public:
        Server(string ip, int port, string serverName, int maxConnections, string healthStatus) {
            this->ip = ip;
            this->port = port;
            this->currentConnections = 0;
            this->maxConnections = maxConnections;
            this->serverName = serverName;
            this->healthStatus = "Healthy";
        };

        void Connect();
        void Disconnect();
        void UpdateHealthStatus(string newStatus);
        void DisplayActiveConnections();
        void DecrementLoad();
};