class Balancer {
    vector<Server *> servers;
    LoadBalancingStrategy* strategy;
    public:
        int totalServers = 0;
        Balancer() = default;
        void AddServer(Server* server);
        void RemoveServer(int port);
        void RouteRequest(string clientIP, int currentTime);
};