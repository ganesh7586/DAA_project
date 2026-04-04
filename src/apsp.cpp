#include "apsp.hpp"

std::vector<std::vector<long long>> floydWarshall(
    std::vector<std::vector<long long>> dist,
    long long INF
) {
    const int n = static_cast<int>(dist.size());

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            if (dist[i][k] == INF) continue;

            for (int j = 0; j < n; ++j) {
                if (dist[k][j] == INF) continue;

                long long through_k = dist[i][k] + dist[k][j];
                if (through_k < dist[i][j]) {
                    dist[i][j] = through_k;
                }
            }
        }
    }

    return dist;
}