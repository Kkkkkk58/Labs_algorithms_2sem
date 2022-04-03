from operator import attrgetter

class DSU:
    def __init__(self):
        self.represent_ = [i for i in range(n)]
        self.size_ = [1 for _ in range(n)]
    def find_set(self, key):
        if key == self.represent_[key]:
            return key
        self.represent_[key] = self.find_set(self.represent_[key])
        return self.represent_[key]
    def unite(self, a, b):
        a = self.find_set(a)
        b = self.find_set(b)
        if a != b:
            if self.size_[a] < self.size_[b]:
                a, b = b, a
            self.represent_[b] = a
            self.size_[a] += self.size_[b]

class Edge:
    def __init__(self, begin, end, weight):
        self.begin_ = begin
        self.end_ = end
        self.weight_ = weight


def kruskal_mst(edges):
    dsu = DSU()
    edges = sorted(edges, key=attrgetter("weight_"))
    edges_count = 0
    total_weight = 0
    for edge in edges:
        if dsu.find_set(edge.begin_) != dsu.find_set(edge.end_):
            dsu.unite(edge.begin_, edge.end_)
            total_weight += edge.weight_
            edges_count += 1
        if edges_count == n - 1:
            break
    return total_weight



fin = open("spantree3.in")
fout = open("spantree3.out", "w")

n, m = map(int, fin.readline().split())
edges = []

for i in range(m):
    first_vertex, second_vertex, weight = map(int, fin.readline().split())
    edges.append(Edge(first_vertex - 1, second_vertex - 1, weight))

total_weight = kruskal_mst(edges)
print(total_weight, file=fout)

fin.close()
fout.close()