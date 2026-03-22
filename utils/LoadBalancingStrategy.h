class LoadBalancingStrategy {
    public:
        static int totalServers;
        virtual int GetNextServerIndex() = 0; // Pure virtual function
        virtual ~LoadBalancingStrategy() = default; // Virtual destructor for proper cleanup
};