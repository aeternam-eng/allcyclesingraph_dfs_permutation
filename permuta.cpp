// Grafos - Verifica se um grafo direcionado tem ciclo

#include <iostream>
#include <algorithm>
#include <list>
#include <stack> // pilha para usar na DFS
#include <vector>
#include <chrono>

using namespace std;

bool increase(std::vector<bool>& bs) {
    for (std::size_t i = 0; i != bs.size(); ++i) {
        bs[i] = !bs[i];
        if (bs[i] == true) {
            return true;
        }
    }
    return false; // overflow
}
template <typename T, typename F>
void getSubconjuntos(const std::vector<T>& v, F f) {
    std::vector<bool> bitset(v.size());

    do {
        f(v, bitset);
    } while (increase(bitset));
}
template <typename T, typename F>
void getArranjos(const std::vector<T>& v, F f) {
    getSubconjuntos(v, [f](const std::vector<T>& v, const std::vector<bool>& bitset){
        std::vector<T> toPermute;
        for (std::size_t i = 0; i != v.size(); ++i) {
            if (bitset[i]) {
                toPermute.push_back(v[i]);
            }
        }
        do {
            f(toPermute);
        } while (std::next_permutation(toPermute.begin(), toPermute.end()));
    });
}

class Grafo
{
	int V; // número de vertices
	list<int> *adj;

	vector<vector<int>> auxpermut;
	vector<vector<int>> permutacoes;

public:
	Grafo(int V);
	void adicionarAresta(int v1, int v2);

	void permutaGrafo() {
		vector<int> itens;

		for(int i = 0; i < V; i++) {
			itens.push_back(i);
		}

		getArranjos(itens, [this](const auto& v) {
			//v contem o arranjo atual
			if(v.size() > 2) {
				for(auto it = v.begin(); it != v.end(); it++) {
					list<int> vizinhos_vertice_atual = this->adj[*it];

					//se for o último elemento do vetor da permutacao
					if(std::next(it, 1) == v.end()){
						//se o primeiro elemento da permutacao estiver na lista de adjacencia do último elemento da permutacao
						if(!(std::find(vizinhos_vertice_atual.begin(), vizinhos_vertice_atual.end(), v[0]) != vizinhos_vertice_atual.end())) {
							return;
						}
					} else if(!(std::find(vizinhos_vertice_atual.begin(), vizinhos_vertice_atual.end(), *(std::next(it, 1))) != vizinhos_vertice_atual.end())) { 
						return; 
					}
				}

				//Ordena a permutacao atual para não ter os mesmos ciclos
				vector<int> aux = v;
				std::sort(aux.begin(), aux.end());

				//Caso a permutacao atual já exista na lista de permutacoes
				if(!(std::find(this->auxpermut.begin(), this->auxpermut.end(), aux) != (this->auxpermut.end()))) {
					this->auxpermut.push_back(aux);
					this->permutacoes.push_back(v);
					for(auto elemento : v) {
						cout << elemento << " ";
					}
					cout << endl;
				}
			}
		});
	}

	const vector<vector<int>>& getCiclos() {
		return this->permutacoes;
	}
};

Grafo::Grafo(int V)
{
	this->V = V;
	adj = new list<int>[V];
}

void Grafo::adicionarAresta(int v1, int v2)
{
	adj[v1].push_back(v2);
	adj[v2].push_back(v1);
}

int main(int argc, char *argv[])
{
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

	Grafo grafo(5);

	grafo.adicionarAresta(0, 1);
	grafo.adicionarAresta(0, 2);
	grafo.adicionarAresta(0, 3);
	grafo.adicionarAresta(1, 2);
	grafo.adicionarAresta(2, 3);
	grafo.adicionarAresta(2, 4);
	grafo.adicionarAresta(3, 4);

	grafo.permutaGrafo();

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

	cout << "Tempo: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << endl;

	return 0;
}