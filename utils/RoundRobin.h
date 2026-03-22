class RoundRobin: public LoadBalancingStrategy {
    int currentIndex=-1;
    public:
        int GetNextServerIndex() {
            if (totalServers == 0) return -1; // No servers available
            currentIndex = (currentIndex + 1) % totalServers; // Move to the next index
            return currentIndex;
        }
};