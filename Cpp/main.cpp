#include <list>
#include <set>
#include <queue>
#include <format>
#include <iostream>

using NodeId = unsigned;

struct Edge {
    NodeId from;
    NodeId to;

    Edge& operator=(const Edge&) = default;

    bool operator==(const Edge& other) const {
        return from == other.from && to == other.to;
    }

    bool operator<(const Edge& other) const {
        return std::make_tuple(from, to) < std::make_tuple(other.from, other.to);
    }

    Edge reverse() const {
        return { to, from };
    }
};

using Path = std::list<Edge>;

class Graph {
public:
    Graph(Path paths) 
    : _paths { std::move(paths) }
    {}

    std::string toGraphvizFormat(const Path& path) const {
        std::string graphviz_string;

        const auto is_in_path = [&path](const Edge edge) {
            return std::find(path.begin(), path.end(), edge) != path.end();
        };

        for (const auto edge : _paths) {
            std::format_to(
                std::back_inserter(graphviz_string),
                R"({} -> {} [{}];)",
                edge.from,
                edge.to,
                (is_in_path(edge) ? "color=red" : "")
            );
        }

        return std::format(
            R"(
                digraph G {{
                    rankdir = "LR"
                    {}
                }}
            )",
            graphviz_string
        );
    }

    Path dfs(const NodeId from, const NodeId to) const {
        Path current_path;
        Path best_path;

        std::set<Edge> visited;
        NodeId current = from;
        while (true) {
            const auto next_edge_opt = findNextEdgeFrom(current, visited);

            if (next_edge_opt) {
                current_path.push_back(*next_edge_opt);
                visited.insert(current_path.back());
                current = current_path.back().to;

                continue;
            }

            if (current == to) {
                if (best_path.empty() || best_path.size() > current_path.size()) {
                    best_path = current_path;
                }
            }

            if (current_path.empty()) {
                break;
            }

            for (auto it = visited.begin(); it != visited.end(); ++it) {
                if (it->from == current) {
                    it = visited.erase(it);
                }
            }

            // Revert to previous node
            current = current_path.back().from;
            current_path.pop_back();
        }

        return best_path;
    }

    Path bfs(const NodeId from, const NodeId to) {
        Path path;

        std::queue<Edge> queue = findAllEdgesFrom(from);
        while(not queue.empty()) {
            const auto next_edge = queue.front();
            queue.pop();

            auto edges = findAllEdgesFrom(next_edge.from);
            while (not edges.empty()) {
                queue.push(edges.front());
                queue.pop();
            }
        }

        return path;
    }

private:
    std::optional<Edge> findNextEdgeFrom(NodeId node, const std::set<Edge>& visited) const {
        const auto it = std::find_if(
            _paths.begin(), 
            _paths.end(),
            [node, &visited](const Edge edge) -> bool {
                if (visited.find(edge) != visited.end()) {
                    return false;
                }

                if (visited.find(edge.reverse()) != visited.end()) {
                    return false;
                }

                if (node != edge.from) {
                    return false;
                }

                return true;
            }
        );

        if (it != _paths.end()) {
            return *it;
        }

        return  std::nullopt;
    }

    std::queue<Edge> findAllEdgesFrom(NodeId node) {
        std::queue<Edge> edges;

        for (const auto edge : _paths) {
            if (edge.from == node) {
                edges.push(edge);
            }
        }

        return edges;
    }

private:
    Path _paths;
};

void graphviz(const Graph& graph, const Path& path, std::string name)
{
    std::system(std::format(R"(echo '{}' | dot -Tsvg > {}.svg && open -a "Google Chrome" ./{}.svg)", graph.toGraphvizFormat(path), name, name).data());
}

int main() {
    Graph graph {
        {
            {0, 1},
            {1, 2},
            {2, 3},
            {2, 5},
            {3, 4},
            {4, 5},
            {5, 0}
        }
    };

    graphviz(graph, graph.dfs(2, 1), "Lab1");
}