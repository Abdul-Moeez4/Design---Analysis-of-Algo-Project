#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib> //for memeory/malloc
#include <climits> // For INT_MAX

using namespace std;


                            //============ PRE-THOUGHTS FOR Q1 ==============================//

//part 1 -> most likely use graph.txt, 1st and 2nd col -> users, 3rd -> weights

//create an undirected graph (goes both ways), can use the help of an adjancy matrix (Check Updated comment on line 18)

//since labels.txt has 0 to 39999 so max vertices is 40000 (?)

//UPDATE!!!!!
//we will use adjancy list as it has a better time (and space) complexity than matrix's time (as well as space) complexity -> Space complexity = List -> O(V + E), matrix -> O(N^2)
//                                                                                                                            Time complexity = List -> O(                                                                                                                  


//Part 1(b) -> now we gotta implement either djisktra or A* to find shortest path from graph in part 1(a)



//total vertices/users/nodes contained in file:
const int MAX_VERTICES = 40000;



//DOWN HERE IS  USING ADJANCY MATRIX
//int undirected_graph[MAX_VERTICES][MAX_VERTICES];

/*
//INitilize graph first (i guess)
void init_graph(int n)  //n being nodes/vertices
{
    for (int i = 0; i < n ; i++)
    {
        for (int j = 0; j < n; j++)
        {
            undirected_graph[i][j] = 0;
            if (i == j)
            {
                undirected_graph[i][j] = 1;
            }
        }
    }
}


//add edge

void add_edge(int u, int v, int weight)
{
    undirected_graph[u][v] = weight;
    undirected_graph[v][u] = weight;
}

*/




//ADJANCY LIST METHOD/PATH STARTS HERE!!!

//make a struct that represnts a node
struct ListNode{
     int vertex;
     int weight;
     ListNode* next;
};

//array to store adj list/nodes(?)
ListNode* adj_list[MAX_VERTICES];

//array to store the labels (names) for each node
string labels[MAX_VERTICES];

//array to store heurstic vlaues
int heuristic[MAX_VERTICES];

//initlize that 
void intilize_graph()
{
    for (int i = 0; i < MAX_VERTICES; i++)
    {
        adj_list[i] = nullptr;  //could say sort of empty or no neighbours
    }
}


//now add a function to insert edges lol
void add_edge(int u1, int u2, int weight)  // u1 -> user1, u2-> user2, wight-> distance between them (i guess)
{
    ListNode* new_node = (ListNode*)malloc(sizeof(ListNode));

    // Add (u1, weight) to the adjacency list of u2 (undirected graph)
    new_node->vertex = u1;
    new_node->weight = weight;
    new_node->next = adj_list[u2];
    adj_list[u2] = new_node;


    // Add (u2, weight) to the adjacency list of u1 (undirected graph)
    new_node = (ListNode*)malloc(sizeof(ListNode));
    new_node->vertex = u2;
    new_node->weight = weight;
    new_node->next = adj_list[u1];
    adj_list[u1] = new_node;
}


//Since we will be using the S.N.P.G.txt and Labels.txt (most likely), load detaisl from files and apply in/to graph
void load_graph_from_file(const string& filename)
{
    ifstream SNPG_file(filename);  //ifstream reads input (bascially file open)

    if (!SNPG_file)
    {
        cout<<"Cannot open file "<<filename<<endl;
    }
    else
    {
        string line; //stores each line of text from file
        while (getline(SNPG_file, line))
        {
            istringstream iss(line);
            int user1, user2, weight;
            if (iss >> user1 >> user2 >> weight)
            {
                add_edge(user1, user2, weight);
            }
        }
    }

    SNPG_file.close();  //Close the file
}


//using S.N.P.G_label.txt
void load_label_file(string& filename)
{
    ifstream label_file(filename); ///opens file

    if (!label_file)
    {
        cout<<"Cannot open file "<< filename <<endl;
    }
    else
    {
        string line;
        while (getline(label_file, line))
        {
            istringstream iss(line);
            int id;
            string name;
            if (iss >> id)
            {
                getline(iss, name); 
                labels[id] = name.substr(1);  // Remove the leading space
            }
        }
    }

    label_file.close();  //close the file
}


//part b start

/*
// djikstra algo
void dijkstra(int start, int end)
{
    int dist[MAX_VERTICES];  // Distance from start to each node
    bool visited[MAX_VERTICES] = {false}; // Keep track of visited nodes
    int previous[MAX_VERTICES];  // Array to track the previous node in the path

    // Initialize distances with a large value (infinity)
    for (int i = 0; i < MAX_VERTICES; i++) 
    {
        dist[i] = INT_MAX;
        previous[i] = -1;  // -1 means no previous node
    }

    dist[start] = 0;

    // Iterate until all nodes are processed
    for (int i = 0; i < MAX_VERTICES; i++) 
    {
        // Find the unvisited node with the smallest distance
        int min_dist = INT_MAX;
        int u = -1;
        for (int j = 0; j < MAX_VERTICES; j++) {
            if (!visited[j] && dist[j] < min_dist) {
                min_dist = dist[j];
                u = j;
            }
        }

        if (u == -1) break;  // No unvisited nodes left

        visited[u] = true;

        // Update the distances to the neighbors of u
        ListNode* temp = adj_list[u];
        while (temp != nullptr) {
            int v = temp->vertex;
            int weight = temp->weight;
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                previous[v] = u;  // Track the previous node
            }
            temp = temp->next;
        }
    }

    // Output the shortest path distance
    if (dist[end] == MAX_VERTICES) {
        cout << "No path found from " << labels[start] << " to " << labels[end] << endl;
    } else {
        cout << "Shortest distance from " << labels[start] << " to " << labels[end] << ": " << dist[end] << endl;
        
     cout << "Path: ";

    int path[MAX_VERTICES];  // Array to store the path
    int path_length = 0;     // Counter for the number of nodes in the path

    int current = end;
    while (current != -1) 
    {
        path[path_length++] = current;  // Store the current node in the path array
        current = previous[current];   // Move to the previous node
    }

    // Print the path in the correct order (reverse of the stored array)
    for (int i = path_length - 1; i >= 0; i--) 
    {
        cout << labels[path[i]] << "(" << path[i] << ")";  // Print the label of the node

        if (i > 0) cout << " -> ";  // Add an arrow if not the last node
    }
        cout << endl;
    }
}
*/

//A* ALgorithm FOLLOWS EQUATION -> G(n) + h(n), where G(n) is the actual cost from start node to n (end node, i think)

//calclate heursitc value of nodes -> For a node n, h(n) equals the total number of neighbours connected to n.
void calculate_heuristic()
{
    for (int i = 0; i < MAX_VERTICES; i++)
    {
        heuristic[i] = 0; //default
        ListNode* temp = adj_list[i];
        while (temp != nullptr)
        {
            heuristic[i]++;
            temp = temp->next;
        }
    }
}


void A_star_algo(int start, int end)
{
    int dist[MAX_VERTICES];  // g(n): Distance from start to each node
    int f_cost[MAX_VERTICES]; // f(n): Combined cost
    int previous[MAX_VERTICES];  // To reconstruct the path
    bool visited[MAX_VERTICES] = {false};  // Track visited nodes

    // Initialize distances and costs
    for (int i = 0; i < MAX_VERTICES; i++) {
        dist[i] = INT_MAX;
        f_cost[i] = INT_MAX;
        previous[i] = -1;
    }

    dist[start] = 0;  // Cost to reach the start node is 0
    f_cost[start] = heuristic[start];  // f(n) = g(n) + h(n)

    for (int i = 0; i < MAX_VERTICES; i++) {
        // Select the unvisited node with the smallest f_cost
        int u = -1;
        int min_cost = MAX_VERTICES;

        for (int j = 0; j < MAX_VERTICES; j++) {
            if (!visited[j] && f_cost[j] < min_cost) {
                min_cost = f_cost[j];
                u = j;
            }
        }

        if (u == -1 || u == end)   // No more nodes or reached the target
        {
            break;
        }  
        
        visited[u] = true;

        // Update costs for neighbors of u
        ListNode* temp = adj_list[u];
        while (temp != nullptr) {
            int v = temp->vertex;
            int weight = temp->weight;

            if (!visited[v] && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;  // Update g(n)
                f_cost[v] = dist[v] + heuristic[v];  // Update f(n)
                previous[v] = u;  // Track the path
            }
            temp = temp->next;
        }
    }

    // Output the shortest path distance and reconstruct the path
    if (dist[end] == MAX_VERTICES) {
        cout << "No path found from " << labels[start] << " to " << labels[end] << endl;
    } else {
        cout << "A* shortest distance from " << labels[start] << " to " << labels[end] << ": " << dist[end] <<"\n" << endl;

        // Reconstruct the path
        cout << "Path: ";
        int path[MAX_VERTICES];
        int path_length = 0;

        int current = end;
        while (current != -1) {
            path[path_length++] = current;
            current = previous[current];
        }

        // Print the path in the correct order
        for (int i = path_length - 1; i >= 0; i--) 
        {
            cout << labels[path[i]] << "(" << path[i] << ")";  // Print the label of the node
           
            if (i > 0) cout << " -> ";
        }
        cout << endl;
    }
}















//(Try) print the undirected graph alltogether now
void print_graph(int nodes)           //IMPORTANT -> output will show which node is connected to which other node and its weight
{
    for (int i = 0; i < nodes; i++)
    {
        cout << "Node " << labels[i] << " (" << i << ") : "<<endl;
        ListNode* temp = adj_list[i];

        bool isFirst = true;  //handles comma formatting

        while (temp != nullptr)
        {
            if (isFirst)
            {
                cout << "(" << labels[temp->vertex] << "(" <<temp->vertex << ")" << ", " << temp->weight << ") "<<endl;
                isFirst = false;
            }
            else
            {
                cout << "(" << labels[temp->vertex] << "(" <<temp->vertex << ")" << ", " << temp->weight << ")"<<endl;
            }
            
            temp = temp->next;
        }

        cout<<"\n";
    }
}


//free memory as we are allocating so must also destry when done

void free_graph(int nodes) 
{
    for (int i = 0; i < nodes; ++i) 
    {
        ListNode* current = adj_list[i];
        while (current != nullptr) 
        {
            ListNode* next = current->next;
            free(current);
            current = next;
        }
    }
}


//main function
int main()
{
    intilize_graph();

    string graph_file = "social-network-proj-graph.txt";
    load_graph_from_file(graph_file);

    string labels_file = "social-network-proj-LABELS.txt";
    load_label_file(labels_file);

    //calculate heiristic function
    calculate_heuristic();


    //can give user choices if want to check a specifc node or as many as they input etc//
        cout << "\n =================== NODE SELECTION ======================\n";
        cout << "1. Print connections for your choice number of nodes (limited to first N nodes)\n"<<endl;
        cout << "2. Print connections for a specific node\n"<<endl;
        cout<<  "3. Head to Part B of Q1\n"<<endl;
        cout << "4. Exit\n"<<endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        

        //user choice number of nodes
        if (choice == 1)
        {
             int specific_node;

            do {
                 cout << "Enter the number of nodes to display: ";
                 cin >> specific_node;

                 if (specific_node < 0 || specific_node >= MAX_VERTICES) 
                 {
                    cout << "Invalid number of nodes! Please select a valid number!" << endl;
                    exit(1);
                 }

                } while (specific_node < 0);

            print_graph(specific_node);
            cout<<"\n\n";
            
        }

        //specific node connections
        else if(choice == 2)
        {
            int chosen_node;
            do {
                 cout<<"Enter specific node: "<<endl;
                 cin>>chosen_node;
                 cout<<endl;

                 if ( chosen_node < 0 || chosen_node >= MAX_VERTICES) 
                {
                    cout<<"Please select a valid number of nodes!" << endl;
                    exit(1);
                }
            } while (chosen_node < 0);

            cout << "Node: " << labels[chosen_node] << " (" << chosen_node << ") connections:\n";

            //similar to print_graph() function
             ListNode* temp = adj_list[chosen_node];
            
             bool isFirst = true;  //handles comma formatting

            while (temp != nullptr)
            {
                if (isFirst)
                {
                    cout << "(" << labels[temp->vertex] << "(" <<temp->vertex << ")" << ", " << temp->weight << ") "<<endl;
                    isFirst = false;
                }

                else
                {
                    cout << "(" << labels[temp->vertex] << "(" <<temp->vertex << ")" << ", " << temp->weight << ")"<<endl;
                }

                temp = temp->next;
            }

             if (isFirst) 
             {
                cout << "  No connections found.\n";  // If no neighbors exist
             }
             cout<<"\n";
        }

        //head into part b of quesstion 1
        else if (choice == 3)
        {
            int start_node, end_node;

            cout<<"Enter Start Node: ";
            cin>>start_node;

            if (start_node < 0 || start_node > MAX_VERTICES)
            {
                cout<<"Please select a valid number of nodes!" << endl;
                exit(1);
            }
            
            cout<<"Enter End Node: ";
            cin>>end_node;
            
            if (end_node < 0 || end_node > MAX_VERTICES)
            {
                cout<<"Please select a valid number of nodes!" << endl;
                exit(1);
            }

            cout<<"\n";

            /*
            cout<<"Running Djikstra algorithm\n"<<endl;
            dijkstra(start_node, end_node);

            cout<<endl;
            */

            cout<<"\nRunning A* Algorithm\n"<<endl;
            A_star_algo(start_node, end_node);
        }

        //exit choices
        else if (choice == 4)
        {
            cout<<"Thank you, Come Again!"<<endl;
        }

        //if none of choice picked, print error message
        else
        {
            cout<<"Please enter a valid choice!"<<endl;
        }

    return 0;
}