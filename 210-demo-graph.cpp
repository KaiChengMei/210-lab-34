#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int SIZE = 7;

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
            cout << i << " --> ";
            for (Pair v : adjList[i])
                cout << "(" << v.first << ", " << v.second << ") ";
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
        cout << n << " ";

        for ( auto &neighbor : adjList[n]) {
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
        {0,1,12},{0,2,8},{0,3,21},{2,3,6},{2,6,2},{5,6,6},{4,5,9},{2,4,4},{2,5,5}
    };

    // Creates graph
    Graph graph(edges);

    // Prints adjacency list representation of graph
    graph.printGraph();

    cout << "DFS starting from vertex 0:" << endl;
    graph.DFS(0);
    cout << endl;
    cout << "BFS starting from vertex 0:" << endl;
    graph.BFS(0);

    return 0;
}
