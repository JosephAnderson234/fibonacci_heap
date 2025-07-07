#include "Graph.h"
#include "Router.h"
#include <fstream>
#include <sstream>
#include <iostream>

void load_graph(Graph& g, const string& filename) {
	ifstream in(filename);
	if (!in) {
		cerr << "Error al abrir el archivo: " << filename << endl;
		return;
	}
	int u, v, w;
	while (in >> u >> v >> w) {
		g.addEdge(u, v, w);
	}
}

void simulate_scenarios(Graph& g, Router& router) {
	ofstream log("output/routes_log.txt");

	// Escenario 1: Ruta base
	auto res1 = router.dijkstra(1, 6);
	log << "Ruta base 1 -> 6 | Tiempo: " << res1.total_cost << " | Ruta: ";
	for (int v : res1.path) log << v << " ";
	log << "\n";

	// Escenario 2: Congestión en la ruta 2-3
	g.updateEdgeWeight(2, 3, 10);
	auto res2 = router.dijkstra(1, 6);
	log << "Tras congestión 2-3 | Tiempo: " << res2.total_cost << " | Ruta: ";
	for (int v : res2.path) log << v << " ";
	log << "\n";

	// Escenario 3: Emergencia en la ruta 5-6
	g.updateEdgeWeight(5, 6, 1);
	auto res3 = router.dijkstra(1, 6);
	log << "Emergencia 5-6 | Tiempo: " << res3.total_cost << " | Ruta: ";
	for (int v : res3.path) log << v << " ";
	log << "\n";
	log.close();
}
