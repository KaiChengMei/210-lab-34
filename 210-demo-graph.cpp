#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int SIZE = 11;

struct Edge {
    int src, dest, weight;
};

typedef pair<int, int> Pair;  // Creates alias 'Pair' for the pair<int,int> data type

class Graph {
public:
    // a vector of vectors of Pairs to represent an adjacency list
    vector<vector<Pair>> adjList;
    vector<Edge> edges;

    // Graph Constructor
    Graph(vector<Edge> const &edges) {
        // resize the vector to hold SIZE elements of type vector<Edge>
        adjList.resize(SIZE);
        this->edges = edges;

        // add edges to the directed graph
        for (auto &edge: edges) {
            int src = edge.src;
            int dest = edge.dest;
            int weight = edge.weight;

            // insert at the end
            adjList[src].push_back(make_pair(dest, weight));
            // for an undirected graph, add an edge from dest to src also
            adjList[dest].push_back(make_pair(src, weight));
        }
    }

    // Print the graph's adjacency list
    void printGraph() {
        for (int i = 0; i < adjList.size(); i++) {
            cout << "City " << i << " drive to ....." << endl;
            for (Pair v : adjList[i])
                cout << "    City [" << v.first << "] is {" << v.second << "} minutes " << endl;
            cout << endl;
        }
    }


    // DFS
    void DFS(int s) {
        vector<bool> visit(SIZE, false);
        DFSrec(visit, s);

    }
    
    //  DFS recursive function 
    void DFSrec( vector<bool> &visit, int n) {
        visit[n] = true;
        cout << "Inspecting City " << n << endl;

        for ( auto &neighbor : adjList[n]) {
            if (!visit[neighbor.first] ) {
                cout << "    Possibly drive to City " << neighbor.first << " and cost {" << neighbor.second << "} minutes" << endl;
                DFSrec(visit, neighbor.first);
            }
        }
    }

    void BFS(int s) {
        queue<int> l;
        vector<bool> visit(SIZE, false);

        visit[s] = true;
        l.push(s);

        while (!l.empty()) {

            cout << "Checking City " << l.front() <<endl;
            int temp = l.front();
            l.pop();

            
            for ( auto &neighbor : adjList[temp]) {
                if (visit[neighbor.first] == false) {
                    visit[neighbor.first] = true;
                    cout << "    travel to nex City " << neighbor.first << " and use " << neighbor.second << " minutes." << endl;
                    l.push(neighbor.first);
                }
            }
        }

    }


    // find short path
    void shortpath(int s) {
        priority_queue<Pair, vector<Pair>, greater<Pair>> pq;
        vector<int> dist(SIZE, INT_MAX);
        pq.push(make_pair(0,s));
        dist[s] = 0; 

        while (!pq.empty()) {
            int distance = pq.top().first;
            int current = pq.top().second;
            pq.pop();

            for (auto &neighbor : adjList[current]) {
                int next = neighbor.first;
                int weight = neighbor.second;

                if (dist[current] + weight  < dist[next]) {
                    dist[next] = dist[current] + weight;
                    pq.push(make_pair(dist[next], next));
                }
            }
        }

        for (int i = 0; i < SIZE; i++) { 
            cout << s << " -> " << i << " : " << dist[i] << endl;
        }
    }

    // fastest way to get to city?
    void mintime() {
        // sort first
        sort(edges.begin(), edges.end(), [](Edge a, Edge b) {return a.weight < b.weight;});
        vector<int> parent(SIZE, -1);

        auto unite = [&](int x, int y) {
            int s1 = find(parent,x); 
            int s2 = find(parent,y);
            if (s1 != s2) {
                parent[s1] = s2;
            }
        };

        int tempmins = 0;
        for (auto &edge : edges) {
            int a = edge.src;
            int b = edge.dest;
            int c = edge.weight;

            if (find(parent,a) != find(parent,b)) { 
                unite(a, b); 
                tempmins += c; 
                cout << "City " << a << " to City " << b << " shortest distance is " << c << " minutes" << endl; 
            } 
        }
    }
    
    // seperate find cuz always show
    // 210-demo-graph.cpp:135:32: error: use of 'find' before deduction of 'auto'
    // 135 |             return parent[x] = find(parent[x]);
    int find(vector<int>& parent, int x) {
        if (parent[x] == -1) {
            return x;
        }
        return parent[x] = find(parent, parent[x]);
    }

};

int main() {
    // Creates a vector of graph edges/weights
    vector<Edge> edges = {
        // (x, y, w) —> edge from x to y having weight w
        // delete {2,6,2},{5,6,6},{4,5,9},{2,5,5}
        {0,1,12},{0,2,8},{0,3,21},{2,3,6},{2,4,4},
        {4,5,10},{4,6,5},{6,7,7},{6,8,12},{7,8,9},{8,9,14},{8,10,3}

    };

    // Creates graph
    Graph graph(edges);

    int choice;
    do {
        cout << "City traffic Menu " << endl;
        cout << "[1] City Traffic Network" << endl;
        cout << "[2] Network Trace (DFS) from City 0" << endl;
        cout << "[3] Layer-by-Layer Network Inspection (BFS) from City 0" << endl;
        cout << "[4] Shortest path from node " << endl;
        cout << "[5] Minimum Spanning Tree:" << endl;
        cout << "[0] Exit" << endl;
        cin >> choice;
        
    switch (choice) {
        case 1:
            cout << "City Traffic Network:" << endl;
            graph.printGraph();
            break;
        case 2:
            cout << "Network Trace (DFS) from City 0:" << endl;
            graph.DFS(0);
            cout << endl;
            break;
        case 3:
            cout << "Layer-by-Layer Network Inspection (BFS) from City 0:" << endl;
            graph.BFS(0);
            cout << endl;
            break;
        case 4:
            cout << "Shortest path from node 0: " << endl;
            graph.shortpath(0);
            cout << endl;
            break;
        case 5:
            cout << "Minimum Spanning Tree:" << endl;
            graph.mintime();
            cout << endl;
            break;
        case 0:
            cout << "Exiting...";
            break;
        default:
            cout << "Enter 0~5 " << endl;
        }
    } while (choice != 0) ;

    return 0;
}
