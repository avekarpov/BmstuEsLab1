from edge import Edge


class GraphDfs:
    def __init__(self, edges):
        self.edges = edges

        self.opened = []
        self.closed = []

    def dfs(self, start, goal):
        self.opened.append(start)

        has_found_child = True
        while has_found_child:
            print(f'stak: {self.opened}')

            (has_found_child, has_found_path) = self.child_search(goal)
            
            if has_found_path:
                return self.opened

            if not has_found_child and len(self.opened) > 1:
                self.closed.append(self.opened.pop())
                has_found_child = True

        return []

    def child_search(self, goal):
        has_found_child = False

        for edge in self.edges:
            current_node = self.opened[-1]

            if edge.start_node != current_node:
                continue

            if edge.used:
                continue

            if edge.end_node in self.opened or edge.end_node in self.closed:
                continue

            edge.used = True

            has_found_child = True

            self.opened.append(edge.end_node)

            return (has_found_child, edge.end_node == goal)
        
        return (has_found_child, False)