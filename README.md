# Load Balancer Simulation ⚡

A high-performance C++ simulation of a Layer 4/7 Load Balancer, demonstrating core networking concepts, request routing strategies, and server health management through a command-line interface.

## 🚀 Features

- **Dynamic Server Management**: Add or remove backend servers in real-time.
- **Round-Robin Strategy**: Balanced request distribution across active servers.
- **Health Monitoring**: Track server status, active connections, and capacity limits.
- **Request Simulation**: Route simulated client requests with custom payloads and IPs.
- **Modern C++ Architecture**: Utilizes Strategy Pattern for extensible load balancing algorithms.

## 📂 Project Structure

```text
Load Balancer/
├── src/                # Implementation files
│   ├── Balancer.cpp    # Core logic for request routing
│   ├── Request.cpp     # Request object lifecycle
│   └── Server.cpp      # Backend server simulation
├── utils/              # Header files and strategies
│   ├── Balancer.h      # Balancer class definition
│   ├── Server.h        # Server class definition
│   ├── Request.h       # Request data structure
│   ├── RoundRobin.h    # Round Robin strategy implementation
│   └── LoadBalancingStrategy.h # Strategy Interface
├── main.cpp            # CLI Entry point
└── CMakeLists.txt       # Build configuration
```

## 🛠️ Build and Run

### Prerequisites
- **C++ Compiler** (supporting C++17)
- **CMake** (v3.10 or higher)

### Using CMake

1. Create a build directory:
   ```powershell
   mkdir build
   cd build
   ```
2. Configure and build:
   ```powershell
   cmake ..
   cmake --build .
   ```
3. Run the executable:
   ```powershell
   .\LoadBalancer.exe
   ```

### Manual Compilation (Alternative)
If you have `g++` installed, you can compile directly:
```powershell
g++ main.cpp src/Balancer.cpp src/Request.cpp src/Server.cpp -I utils -o LoadBalancer.exe
```

## 🎮 CLI Usage

Once the simulation starts, you can interact with it using the following commands:

| Command | Usage | Description |
| :--- | :--- | :--- |
| `add` | `add <ip> <port> <name>` | Registers a new backend server. |
| `route` | `route <clientIP> <payload>` | Simulates an incoming request. |
| `status` | `status` | Displays active servers, health, and current load. |
| `remove` | `remove <port>` | Removes a server from the rotation by its port. |
| `help` | `help` | Shows available commands. |
| `exit` | `exit` | Closes the simulation. |

## 🧠 Key Concepts

### Load Balancing Strategy
The project implements the **Strategy Pattern**. Currently, it uses **Round Robin**, but the architecture allows for easy integration of new strategies (e.g., Least Connections, IP Hash) by implementing the `LoadBalancingStrategy` interface.

### Server Lifecycle
Each `Server` object maintains a queue of `activeRequests` and tracks `currentConnections` vs `maxConnections`. Servers can be marked with different health statuses, affecting how the balancer interacts with them.

---
*Developed with modern C++ for low-latency simulation.*
