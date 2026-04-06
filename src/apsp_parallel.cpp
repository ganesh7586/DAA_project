#include "apsp_parallel.hpp"

#include <omp.h>

std::vector<std::vector<long long>> floydWarshallParallel(
    std::vector<std::vector<long long>> dist,
    long long INF
) {
    const int n = static_cast<int>(dist.size());

    for (int k = 0; k < n; ++k) {
        #pragma omp parallel for schedule(static)
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