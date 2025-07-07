#include "Graph.h"
#include "Router.h"
#include "SimulationScenario.h"
#include <iostream>


int main() {
	Graph city(100); // 100 nodos por defecto
	load_graph(city, "data/city_graph_large.txt");

	Router router(city);
	simulate_scenarios(city, router);
	simulate_many_dijkstra(city);
	cout << "Simulación completada. Revisa output/routes_log.txt\n";
	return 0;
}
