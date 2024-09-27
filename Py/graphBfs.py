class GraphBfs:
    def __init__(self, edges):
        self.edges = edges

    def bfs(self, start, goal):
        self.opened = []
        self.closed = []

        self.result_path = {}

        self.opened.append(start)

        has_found_child = True
        while has_found_child:
            print(f'queue: {self.opened}')
            (has_found_child, has_found_path) = self.chileMethod(goal)

            if has_found_path:
                return self.getresultPath(start, goal)

            if len(self.opened) != 0:
                self.closed.append(self.opened.pop(0))

            if len(self.opened) != 0:
                has_found_child = True

        return []

    def chileMethod(self, goal):
        has_found_child = False

        current_node = self.opened[0]
        for edge in self.edges:
            if edge.start_node != current_node:
                continue

            if edge.used:
                continue

            if edge.end_node in self.opened or edge.end_node in self.closed:
                continue

            edge.used = True

            has_found_child = True

            self.opened.append(edge.end_node)
            self.result_path[edge.end_node] = edge.start_node

            if edge.end_node == goal:
                return (has_found_child, True)

        return (has_found_child, False)

    def getresultPath(self, start, goal):
        current = goal

        result = [current]
        while current != start:
            current = self.result_path[current]
            result.append(current)

        result.reverse()

        return result

