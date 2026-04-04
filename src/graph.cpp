#include "graph.hpp"

#include <fstream>
#include <iostream>
#include <limits>
#include <algorithm>

Graph::Graph(int n, bool directed)
    : n_(n), directed_(directed) {}

bool Graph::loadFromFile(const std::string& path) {
    std::ifstream fin(path);
    if (!fin.is_open()) {
        std::cerr << "Error: could not open file " << path << "\n";
        return false;
    }

    int m;
    if (!(fin >> n_ >> m)) {
        std::cerr << "Error: invalid file format. Expected: n m followed by edges.\n";
        return false;
    }

    std::vector<Edge> tempEdges;
    tempEdges.reserve(m);

    int minId = std::numeric_limits<int>::max();
    int maxId = std::numeric_limits<int>::min();

    for (int i = 0; i < m; ++i) {
        Edge e{};
        if (!(fin >> e.u >> e.v >> e.w)) {
            std::cerr << "Error: invalid edge at line " << (i + 2) << "\n";
            return false;
        }
        tempEdges.push_back(e);
        minId = std::min(minId, std::min(e.u, e.v));
        maxId = std::max(maxId, std::max(e.u, e.v));
    }

    if (minId == 1 && maxId == n_) {
        for (auto& e : tempEdges) {
            e.u--;
            e.v--;
        }
    } else if (minId == 0 && maxId < n_) {
        // already 0-based
    } else {
        std::cerr << "Error: vertex numbering must be either 0-based or 1-based.\n";
        return false;
    }

    edges_ = std::move(tempEdges);
    return true;
}

int Graph::vertexCount() const {
    return n_;
}

bool Graph::directed() const {
    return directed_;
}

const std::vector<Edge>& Graph::edges() const {
    return edges_;
}

std::vector<std::vector<long long>> Graph::toAdjMatrix(long long INF) const {
    std::vector<std::vector<long long>> mat(n_, std::vector<long long>(n_, INF));

    for (int i = 0; i < n_; ++i) {
        mat[i][i] = 0;
    }

    for (const auto& e : edges_) {
        if (e.u < 0 || e.u >= n_ || e.v < 0 || e.v >= n_) {
            continue;
        }

        mat[e.u][e.v] = std::min(mat[e.u][e.v], e.w);

        if (!directed_) {
            mat[e.v][e.u] = std::min(mat[e.v][e.u], e.w);
        }
    }

    return mat;
}