#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <climits>
using namespace std;

// ===================== Pre-Thoughts for Q2 =======================

//question confusing question but we will use graph from part 1 meaning that create/load graph file function/code in here and find longest chain

//but trying to do if want specifc nodes etc so seeing that...



const int MAX_VERTICES = 40000;

// Struct to represent a node
struct ListNode {
    int vertex;
    int weight;
    ListNode* next;
};

ListNode* adj_list[MAX_VERTICES]; 
string labels[MAX_VERTICES];      
int influence[MAX_VERTICES];    
int dp[MAX_VERTICES];             // DP array
int parent[MAX_VERTICES];         // Parent array


//initlize that 
void initilize_graph()
{
    for (int i = 0; i < MAX_VERTICES; i++)
    {
        adj_list[i] = nullptr;  //could say sort of empty or no neighbours
    }
}



void add_edge(int u1, int u2, int weight) 
{
    ListNode* new_node = new ListNode{u1, weight, adj_list[u2]};
    adj_list[u2] = new_node;

    new_node = new ListNode{u2, weight, adj_list[u1]};
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

//load influences from influences.txt file
void load_influences_from_file(const string& filename) 
{
    ifstream influence_file(filename);
    if (!influence_file) {
        cout << "Cannot open file: " << filename << endl;
        return;
    }

    string line;
    while (getline(influence_file, line)) {
        istringstream iss(line);
        int user, score;
        if (iss >> user >> score) {
            influence[user] = score;
        }
    }
    influence_file.close();
}

void merge(int nodes[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* Left = new int[n1];
    int* Right = new int[n2];

    // Copy data to temporary arrays
    for (int i = 0; i < n1; i++) 
    {
        Left[i] = nodes[left + i];
    }
    for (int i = 0; i < n2; i++) 
    {
        Right[i] = nodes[mid + 1 + i];
    }

    // Merge the temporary arrays back into nodes[]
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) 
    {
        if (influence[Left[i]] <= influence[Right[j]]) 
        {
            nodes[k] = Left[i];
            i++;
        } 
        else 
        {
            nodes[k] = Right[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if any
    while (i < n1) 
    {
        nodes[k] = Left[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if any
    while (j < n2) 
    {
        nodes[k] = Right[j];
        j++;
        k++;
    }

    delete[] Left;
    delete[] Right;
}

void merge_sort(int nodes[], int left, int right) {
    if (left < right) 
    {
        int mid = left + (right - left) / 2;

        merge_sort(nodes, left, mid);
        merge_sort(nodes, mid + 1, right);

        merge(nodes, left, mid, right);
    }
}

void sort_influences(int nodes[], int n) {
    merge_sort(nodes, 0, n - 1);
}

/*
//sorting influences make it easier to find longets chain (?)
void sort_influences(int nodes[], int n) 
{
    for (int i = 0; i < n - 1; i++) 
    {
        for (int j = 0; j < n - i - 1; j++) 
        {
            if (influence[nodes[j]] > influence[nodes[j + 1]]) 
            {
                int temp = nodes[j];
                nodes[j] = nodes[j + 1];
                nodes[j + 1] = temp;
            }
        }
    }
}
*/

void find_longest_chain(int n) {
    int nodes[MAX_VERTICES];
    for (int i = 0; i < n; i++) {
        nodes[i] = i;
    }

    sort_influences(nodes, n);

    for (int i = 0; i < n; i++) {
        dp[i] = 1;
        parent[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        int current = nodes[i];
        ListNode* neighbor = adj_list[current];
        while (neighbor != nullptr) {
            int next = neighbor->vertex;
            if (influence[current] < influence[next] && dp[current] + 1 > dp[next]) {
                dp[next] = dp[current] + 1;
                parent[next] = current;
            }
            neighbor = neighbor->next;
        }
    }

    int max_length = 0, last_node = -1;
    for (int i = 0; i < n; i++) {
        if (dp[i] > max_length) {
            max_length = dp[i];
            last_node = i;
        }
    }

    int chain[MAX_VERTICES], chain_length = 0;
    while (last_node != -1) {
        chain[chain_length++] = last_node;
        last_node = parent[last_node];
    }

    cout << "Longest chain length: " << max_length << endl;
    cout << "Chain: ";
    for (int i = chain_length - 1; i >= 0; i--) {
        cout << chain[i];
        if (i > 0) cout << " -> ";
    }
    cout << endl;
}

int main() {
    const string graph_file = "social-network-proj-graph.txt";
    const string influence_file = "social-network-proj-Influences.txt";

   initilize_graph();

    load_graph_from_file(graph_file);
    load_influences_from_file(influence_file);

    find_longest_chain(MAX_VERTICES);

    return 0;
}
