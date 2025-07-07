#ifndef GRAPGH_H
#define GRAPGH_H
#include <vector>
#include <unordered_map>
#include <list>

using namespace std;

class Graph {
public:
	int num_vertices;
	unordered_map<int, list<pair<int, int>>> adj; // nodo -> lista de (vecino, peso)

	Graph(int V) : num_vertices(V) {}

	void addEdge(int u, int v, int w) {
		adj[u].push_back({v, w});
		adj[v].push_back({u, w}); // si es bidireccional
	}

	void updateEdgeWeight(int u, int v, int new_weight) {
		for (auto& p : adj[u]) {
			if (p.first == v) { p.second = new_weight; break; }
		}
		for (auto& p : adj[v]) {
			if (p.first == u) { p.second = new_weight; break; }
		}
	}
};

#endif //GRAPGH_H
