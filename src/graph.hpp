#pragma once

#include <string>
#include <vector>

struct Edge {
    int u;
    int v;
    long long w;
};

class Graph {
public:
    explicit Graph(int n = 0, bool directed = true);

    bool loadFromFile(const std::string& path);

    int vertexCount() const;
    bool directed() const;
    const std::vector<Edge>& edges() const;

    std::vector<std::vector<long long>> toAdjMatrix(long long INF) const;

private:
    int n_;
    bool directed_;
    std::vector<Edge> edges_;
};