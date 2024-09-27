class Edge:
    def __init__(self, start_node, end_node):
        self.start_node = start_node
        self.end_node = end_node
        
        self.label = f'{self.start_node} - {self.end_node}'

        self.used = False
