#include <iostream>
#include <map>
#include <unordered_set>
#include <list>
#include <vector>
#include <algorithm>
#include <chrono>

class Graph {
private:
    std::map<int, std::list<int>> adjacency_list;
    std::vector<std::vector<int>> auxpermut;
    std::vector<std::vector<int>> permutacoes;

public:
    const std::map<int, std::list<int>>& getAdjacencyList() {
        return this->adjacency_list;
    }

    void addEdge(int u, int v) {
        adjacency_list[u].push_back(v);
        adjacency_list[v].push_back(u);
    }

    void DFS(
        int vertex,
        int parent, 
        std::unordered_set<int> visited,
        std::map<int, std::list<int>> adjacency_list,
        std::vector<int>& path)
    {
        if(visited.find(vertex) != visited.end()) {
            if(vertex == parent) {
                if(path.size() > 2) {
                    std::vector<int> aux = path;
                    std::sort(aux.begin(), aux.end());

                    if(!(std::find(this->auxpermut.begin(), this->auxpermut.end(), aux) != (this->auxpermut.end()))){
                        this->auxpermut.push_back(aux);
					    this->permutacoes.push_back(path);

                        for(auto item : path) {
                            std::cout << item << " ";
                        }
                        std::cout << std::endl;
                    }
                }
                return;
            } else return;
        }

        visited.insert(vertex);

        path.push_back(vertex);

        for(auto adjacent_vertex : adjacency_list[vertex]) {
            DFS(adjacent_vertex, parent, visited, adjacency_list, path);
        }

        visited.erase(vertex);

        path.pop_back();
    }

    bool listCycles() {
        std::unordered_set<int> visited;
        std::vector<int> path;

        for(auto vertex : this->adjacency_list) {
            //caso o vértice esteja na lista de visitados
            if(visited.find(vertex.first) != visited.end()) {
                continue;
            }

            DFS(vertex.first, vertex.first, visited, (this->adjacency_list), path);
        }
        return false;
    }
};  

int main() {
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    Graph g;

    g.addEdge(0,1);
    g.addEdge(0,2);
    g.addEdge(0,3);
    g.addEdge(1,2);
    g.addEdge(2,3);
    g.addEdge(2,4);
    g.addEdge(3,4);

    g.listCycles();

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << "Time to end: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << std::endl;

    return 0;
}