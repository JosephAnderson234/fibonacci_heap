#include "Graph.h"
#include "Router.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <random>

using namespace std;
using namespace chrono;

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

void log_result(ofstream& log, const string& title, const PathResult& res, long long duration_fibo, long long duration_binary) {
	log << title << "\n";
	log << "  Tiempo FiboHeap: " << duration_fibo << "us | Tiempo BinaryHeap: " << duration_binary << "us\n";
	log << "  Ruta: ";
	for (int v : res.path) log << v << " ";
	log << "| Costo: " << res.total_cost << "\n\n";
}

void simulate_scenarios(Graph& g) {
	ofstream log("output/routes_log.txt");

	auto simulate = [&](const string& title) {
		auto g_fibo = g;
		auto g_bin = g;

		Router routerFibo(g_fibo);
		Router routerBin(g_bin);

		auto start1 = high_resolution_clock::now();
		auto res_fibo = routerFibo.dijkstraWithFibonacciHeap(1, 6);
		auto end1 = high_resolution_clock::now();

		auto start2 = high_resolution_clock::now();
		auto res_bin = routerBin.dijkstraWithBinaryHeap(1, 6);
		auto end2 = high_resolution_clock::now();

		auto dur_fibo = duration_cast<microseconds>(end1 - start1).count();
		auto dur_bin = duration_cast<microseconds>(end2 - start2).count();

		log_result(log, title, res_fibo, dur_fibo, dur_bin);
	};


	simulate("Escenario 1: Ruta base");


	g.updateEdgeWeight(2, 3, 10);
	simulate("Escenario 2: Congestión en la ruta 2-3");


	g.updateEdgeWeight(5, 6, 1);
	simulate("Escenario 3: Emergencia en la ruta 5-6");


	g.updateEdgeWeight(1, 2, 7);
	g.updateEdgeWeight(4, 5, 10);
	simulate("Escenario 4: Congestión combinada 1-2 y 4-5");

	log.close();
}

void simulate_many_dijkstra(Graph& g) {
	ofstream log("output/performance_comparison.txt");

	vector<int> nodes;
	for (auto& p : g.adj) {
		nodes.push_back(p.first);
	}


	vector<pair<int, int>> test_cases;
	mt19937 rng(time(nullptr));
	uniform_int_distribution<int> dist(0, nodes.size() - 1);

	for (int i = 0; i < 100; ++i) {
		int src_idx = dist(rng);
		int dst_idx = dist(rng);
		while (dst_idx == src_idx) dst_idx = dist(rng);
		test_cases.emplace_back(nodes[src_idx], nodes[dst_idx]);
	}

	for (int i = 0; i < test_cases.size(); ++i) {
		auto [src, dst] = test_cases[i];


		Router routerFibo(g);
		Router routerBin(g);

		auto start1 = high_resolution_clock::now();
		auto res_fibo = routerFibo.dijkstraWithFibonacciHeap(src, dst);
		auto end1 = high_resolution_clock::now();

		auto start2 = high_resolution_clock::now();
		auto res_bin = routerBin.dijkstraWithBinaryHeap(src, dst);
		auto end2 = high_resolution_clock::now();

		auto dur_fibo = duration_cast<microseconds>(end1 - start1).count();
		auto dur_bin = duration_cast<microseconds>(end2 - start2).count();

		string title = "Ruta Aleatoria " + to_string(i + 1) + ": " + to_string(src) + " → " + to_string(dst);
		log_result(log, title, res_fibo, dur_fibo, dur_bin);
	}

	log.close();
}
