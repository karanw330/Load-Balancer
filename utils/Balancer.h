class Balancer {
    vector<Server *> servers;
    LoadBalancingStrategy* strategy;
    public:
        Balancer() = default;
        ~Balancer() = default;

        void AddServer(Server* server);
        void RemoveServer(string serverName);
        void RouteRequest(string clientIP);
        void RoundRobin();
        void LeastConnections();
        void IPHashing();

};