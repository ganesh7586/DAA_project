#include "graph.hpp"
#include "apsp.hpp"

#include <iostream>
#include <iomanip>
#include <limits>
#include <string>

static void printMatrix(const std::vector<std::vector<long long>>& dist, long long INF) {
    const int n = static_cast<int>(dist.size());

    std::cout << "\nShortest Path Matrix:\n\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (dist[i][j] == INF) {
                std::cout << std::setw(8) << "INF";
            } else {
                std::cout << std::setw(8) << dist[i][j];
            }
        }
        std::cout << '\n';
    }
}

static bool hasNegativeCycle(const std::vector<std::vector<long long>>& dist) {
    for (int i = 0; i < static_cast<int>(dist.size()); ++i) {
        if (dist[i][i] < 0) {
            return true;
        }
    }
    return false;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage:\n";
        std::cout << "  " << argv[0] << " <graph_file> [directed|undirected]\n";
        return 1;
    }

    std::string filePath = argv[1];
    bool directed = true;

    if (argc >= 3) {
        std::string mode = argv[2];
        if (mode == "undirected") {
            directed = false;
        }
    }

    Graph g(0, directed);

    if (!g.loadFromFile(filePath)) {
        return 1;
    }

    const long long INF = std::numeric_limits<long long>::max() / 4;

    auto matrix = g.toAdjMatrix(INF);
    auto dist = floydWarshall(matrix, INF);

    if (hasNegativeCycle(dist)) {
        std::cout << "Warning: graph contains a negative cycle.\n";
    }

    printMatrix(dist, INF);

    return 0;
}