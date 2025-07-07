#ifndef ROUTER_H
#define ROUTER_H

#include "FibonacciHeap.h"
#include "BinaryHeap.h"
#include "Graph.h"
#include <unordered_map>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
#include <chrono>

using namespace std;

struct PathResult {
    int total_cost;
    vector<int> path;
};

class Router {
    Graph& graph;
public:
    Router(Graph& g) : graph(g) {}

    PathResult dijkstraWithFibonacciHeap(int src, int dst) {
        unordered_map<int, Node*> node_ptrs;
        unordered_map<int, int> dist;
        unordered_map<int, int> prev;
        FibonacciHeap heap;

        for (auto& [u, _] : graph.adj) {
            if (u == src) {
                node_ptrs[u] = heap.insert(0);
                dist[u] = 0;
            } else {
                node_ptrs[u] = heap.insert(INT_MAX);
                dist[u] = INT_MAX;
            }
        }

        while (heap.getN() > 0) {
            Node* min_node = heap.extract_min();
            int u = -1;
            for (auto& [key, ptr] : node_ptrs) {
                if (ptr == min_node) {
                    u = key;
                    break;
                }
            }

            if (u == dst) break;

            for (auto& [v, weight] : graph.adj[u]) {
                if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    prev[v] = u;
                    heap.decrease_key(node_ptrs[v], dist[v]);
                }
            }
        }

        vector<int> path;
        int u = dst;
        while (prev.count(u)) {
            path.push_back(u);
            u = prev[u];
        }
        if (u == src) path.push_back(src);
        reverse(path.begin(), path.end());

        return { dist[dst], path };
    }

    PathResult dijkstraWithBinaryHeap(int src, int dst) {
        BinaryHeap bh;
        unordered_map<int, int> dist;
        unordered_map<int, int> prev;

        for (auto& [u, _] : graph.adj) {
            if (u == src) {
                bh.insert(u, 0);
                dist[u] = 0;
            } else {
                bh.insert(u, INT_MAX);
                dist[u] = INT_MAX;
            }
        }

        while (!bh.empty()) {
            int u = bh.extract_min();
            if (u == dst) break;

            for (auto& [v, w] : graph.adj[u]) {
                if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    prev[v] = u;
                    bh.decrease_key(v, dist[v]);
                }
            }
        }

        vector<int> path;
        int u = dst;
        while (prev.count(u)) {
            path.push_back(u);
            u = prev[u];
        }
        if (u == src) path.push_back(src);
        reverse(path.begin(), path.end());

        return { dist[dst], path };
    }

};

#endif // ROUTER_H
