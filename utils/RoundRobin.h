class RoundRobin {
    int currentIndex=-1;
    public:
        int GetNextServerIndex(int totalServers) {
            if (totalServers == 0) return -1; // No servers available
            currentIndex = (currentIndex + 1) % totalServers; // Move to the next index
            return currentIndex;
        }
};