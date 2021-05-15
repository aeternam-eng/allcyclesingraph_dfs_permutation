#include <iostream>
#include <map>
#include <unordered_set>
#include <list>
#include <vector>
#include <algorithm>
#include <chrono>

class Grafo {
private:
    std::map<int, std::list<int>> adj;
    std::vector<std::vector<int>> auxpermut;
    std::vector<std::vector<int>> permutacoes;

public:
    void adicionarAresta(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void DFS(
        int vertice,
        int inicio, 
        std::unordered_set<int> visitados,
        std::map<int, std::list<int>> adj,
        std::vector<int>& caminho)
    {
        if(visitados.find(vertice) != visitados.end()) {
            if(vertice == inicio) {
                if(caminho.size() > 2) {
                    std::vector<int> aux = caminho;
                    std::sort(aux.begin(), aux.end());

                    if(!(std::find(this->auxpermut.begin(), this->auxpermut.end(), aux) != (this->auxpermut.end()))){
                        this->auxpermut.push_back(aux);
					    this->permutacoes.push_back(caminho);

                        for(auto item : caminho) {
                            std::cout << item << " ";
                        }
                        std::cout << std::endl;
                    }
                }
                return;
            } else return;
        }

        visitados.insert(vertice);

        caminho.push_back(vertice);

        for(auto adjacent_vertex : adj[vertice]) {
            DFS(adjacent_vertex, inicio, visitados, adj, caminho);
        }

        visitados.erase(vertice);

        caminho.pop_back();
    }

    bool listarCiclos() {
        std::unordered_set<int> visitados;
        std::vector<int> caminho;

        for(auto vertice : this->adj) {
            //caso o vértice esteja na lista de visitados
            if(visitados.find(vertice.first) != visitados.end()) {
                continue;
            }

            DFS(vertice.first, vertice.first, visitados, (this->adj), caminho);
        }
        return false;
    }
};  

int main() {
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    Grafo g;

    g.adicionarAresta(0,1);
    g.adicionarAresta(0,2);
    g.adicionarAresta(0,3);
    g.adicionarAresta(1,2);
    g.adicionarAresta(2,3);
    g.adicionarAresta(2,4);
    g.adicionarAresta(3,4);

    g.listarCiclos();

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << "Tempo: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << std::endl;

    return 0;
}