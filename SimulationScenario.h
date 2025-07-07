#pragma once

#include "Graph.h"
#include "Router.h"

void load_graph(Graph& g, const std::string& filename);
void simulate_scenarios(Graph& g, Router& router);
void simulate_many_dijkstra(Graph& g);