from graphBfs import GraphBfs
from graphDfs import GraphDfs
from edge import Edge

graph = [
    Edge(0, 1),
    Edge(0, 2),
    Edge(0, 3),
    Edge(3, 4),
    Edge(1, 4),
    Edge(2, 4),
    Edge(2, 5),
    Edge(3, 5),
    Edge(3, 6),
    Edge(5, 4),
    Edge(5, 7),
    Edge(5, 9),
    Edge(6, 7),
]

if __name__ == "__main__":
    print("Depth First Search")
    print(*GraphDfs(graph).dfs(0, 7), sep=' -> ')

    print("Breadth First Search")
    print(*GraphBfs(graph).bfs(0, 7), sep=' -> ')
