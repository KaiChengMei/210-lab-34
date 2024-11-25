#include <iostream>
#include <vector>
#include <queue>
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

    // Graph Constructor
    Graph(vector<Edge> const &edges) {
        // resize the vector to hold SIZE elements of type vector<Edge>
        adjList.resize(SIZE);

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
        cout << "Graph's adjacency list:" << endl;
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
            cout << "    Possibly drive to City " << neighbor.first << " and cost {" << neighbor.second << "} minutes" << endl;
            if (visit[neighbor.first] == false) {
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

            cout << l.front() << " ";
            int temp = l.front();
            l.pop();

            
            for ( auto &neighbor : adjList[temp]) {
                if (visit[neighbor.first] == false) {
                    visit[neighbor.first] = true;
                    l.push(neighbor.first);
                }
            }
        }

    }

};

int main() {
    // Creates a vector of graph edges/weights
    vector<Edge> edges = {
        // (x, y, w) —> edge from x to y having weight w
        // delete {2,6,2},{5,6,6},{4,5,9},{2,5,5}
        {0,1,12},{0,2,8},{0,3,21},{2,3,6},{2,4,4},
        {3,6,10},{4,6,8},
        {0,5,7},{1,5,9},
        {1,7,14},{7,4,15},
        {7,8,10},{4,8,6},
        {9,3,3},
        {0,10,9},{9,10,7}

    };

    // Creates graph
    Graph graph(edges);

    cout << "City Traffic Network:" << endl << "===========================================" << endl ;

    // Prints adjacency list representation of graph
    graph.printGraph();

    cout << "Network Trace (DFS) from City 0:" << endl;
    graph.DFS(0);
    cout << endl;

    cout << "Layer-by-Layer Network Inspection (BFS) from City 0:" << endl;
    graph.BFS(0);

    return 0;
}
