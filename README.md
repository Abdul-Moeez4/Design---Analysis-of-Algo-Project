# README

## Project Overview
This project is for the **Design and Analysis of Algorithm** course. It focuses on analyzing a dataset representing a social network. The dataset contains information about connections between users, with weights representing the distance (or strength) of their connection. The project is divided into two parts: **Graph-Based Algorithms** and **Dynamic Programming on Graphs.**

## Dataset
The dataset for this project is available at the following link: [Social Network Dataset](https://drive.google.com/file/d/1SAcWvOR4cTwOrE_JHto3jHLfeJE3fkV2/view?usp=sharing).

### Dataset Structure
The dataset consists of the following:
- **Connections File**: Contains 3 columns:
  - Column 1: User A
  - Column 2: User B
  - Column 3: Weight of the connection between User A and User B

- **Influences File**: Contains 2 columns:
  - Column 1: User
  - Column 2: Influence score of the user

---

## Part 1: Graph-Based Analysis
### Objective
Analyze the social network graph and find the most significant connections using algorithms such as Dijkstra or A*.

### Tasks
1. **Create an Undirected Graph**
   - Construct a graph where:
     - Nodes represent users.
     - Edges represent connections between users.
     - Weights on edges indicate the strength of the connection (shorter weight implies stronger connection).

2. **Shortest Path Algorithm**
   - Implement **Dijkstra Algorithm** or **A* Algorithm** to find the shortest path between nodes.
   - For **A* Algorithm**, use the following heuristic function:
     - Combine actual cost \( g(n) \) and heuristic \( h(n) \) to find the optimal path.

---

## Implementation Details for Part 1

### Environment Setup
1. Ensure you have a C++ compiler installed.
2. Place the file `Part1.cpp` in your working directory.
3. Ensure all dataset files (`social-network-proj-graph.txt` and `social-network-proj-LABELS.txt`) are in the same directory as the source code.

### Files
- **Part1.cpp**: Contains the implementation for graph creation and shortest path algorithms.
- **social-network-proj-graph.txt**: Contains the social network connections.
- **social-network-proj-LABELS.txt**: Contains the labels for each user.

### Code Structure
1. **Graph Construction**:
   - Load the `social-network-proj-graph.txt` file to build an undirected graph.
2. **Shortest Path**:
   - Implement Dijkstra or A* algorithms (or both).
3. **Heuristic Function**:
   - Calculate heuristic values based on the number of neighbors for each node.

### How to Run
1. Compile the code using a C++ compiler:
   ```bash
   g++ Part1.cpp -o Part1
   ```
2. Run the compiled program:
   ```bash
   ./Part1
   ```
3. Follow the prompts to:
   - Print connections for a specified number of nodes.
   - Print connections for a specific node.
   - Find the shortest path using either Dijkstra or A* algorithm.

---

## Results for Part 1
1. **Graph Representation**:
   - Output the adjacency list for nodes or specific nodes.
2. **Shortest Path**:
   - Display the shortest path and its total weight using the selected algorithm.

---

## Part 2: Dynamic Programming on Graphs
### Objective
Analyze the level of influence among users and find the longest increasing chain of influence scores in the network.

### Tasks
1. **Longest Increasing Path**
   - Use dynamic programming to find the longest chain of influence where:
     - The influence score of each user in the chain is strictly greater than the previous user.

2. **Return Results**
   - Output the **maximum length** of the chain.
   - Provide the **sequence of users** in the chain.

---

## Implementation Details for Part 2

### Environment Setup
1. Ensure you have a C++ compiler installed.
2. Place the file `Part2.cpp` in your working directory.
3. Ensure all dataset files (`social-network-proj-graph.txt` and `social-network-proj-Influences.txt`) are in the same directory as the source code.

### Files
- **Part2.cpp**: Contains the implementation for dynamic programming algorithms.
- **social-network-proj-graph.txt**: Contains the social network connections.
- **social-network-proj-Influences.txt**: Contains the influence scores for each user.

### Code Structure
1. **Graph Construction**:
   - Load the `social-network-proj-graph.txt` file to build an undirected graph.
2. **Load Influences**:
   - Parse the `social-network-proj-Influences.txt` file to load user influence scores.
3. **Dynamic Programming**:
   - Implement a dynamic programming algorithm to compute the longest increasing chain based on influence scores.

### How to Run
1. Compile the code using a C++ compiler:
   ```bash
   g++ Part2.cpp -o Part2
   ```
2. Run the compiled program:
   ```bash
   ./Part2
   ```
3. The program will output the longest chain of influence scores and the corresponding sequence of users.

---

## Results
1. **Shortest Path (Part 1)**:
   - Output the shortest path between selected users.
   - Display the path and its total weight.

2. **Longest Chain of Influence (Part 2)**:
   - Output the maximum length of the chain.
   - Display the sequence of users in the chain.


