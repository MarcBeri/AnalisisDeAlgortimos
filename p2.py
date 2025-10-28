import numpy as np
import queue
from queue import PriorityQueue
import random
import time
import statistics
from typing import List, Tuple
import matplotlib.pyplot as plt

# I. TAD CONJUNTO DISJUNTO

def init_cd(n: int) -> np.ndarray:
    """Inicializa un conjunto disjunto con n elementos, todos como raíces."""
    return np.full(n, -1, dtype=int)

def find(ind: int, p_cd: np.ndarray) -> int:
    """Devuelve el representante del índice 'ind' con compresión de caminos."""
    if p_cd[ind] < 0:
        return ind
    p_cd[ind] = find(p_cd[ind], p_cd)
    return p_cd[ind]

def union(rep_1: int, rep_2: int, p_cd: np.ndarray) -> int:
    """Une dos conjuntos por rango y devuelve el representante resultante."""
    if rep_1 == rep_2:
        return rep_1
    if p_cd[rep_1] < p_cd[rep_2]:  # rep_1 tiene mayor rango
        p_cd[rep_2] = rep_1
        return rep_1
    elif p_cd[rep_2] < p_cd[rep_1]:  # rep_2 tiene mayor rango
        p_cd[rep_1] = rep_2
        return rep_2
    else:  # mismos rangos
        p_cd[rep_2] = rep_1
        p_cd[rep_1] -= 1
        return rep_1

# II. ÁRBOLES ABARCADORES

def create_pq(n: int, l_g: List) -> PriorityQueue:
    """Inserta las ramas del grafo (n, l_g) en una cola de prioridad."""
    pq = PriorityQueue()
    for u, v, w in l_g:
        pq.put((w, (u, v)))
    return pq

def kruskal(n: int, l_g: List) -> Tuple[int, List]:
    """Devuelve un árbol abarcador mínimo (peso total, lista de aristas) o None si no es conexo."""
    cd = init_cd(n)
    pq = create_pq(n, l_g)
    l_t = []
    total_weight = 0
    num_edges = 0
    while not pq.empty() and num_edges < n - 1:
        w, (u, v) = pq.get()
        ru, rv = find(u, cd), find(v, cd)
        if ru != rv:
            union(ru, rv, cd)
            l_t.append((u, v, w))
            total_weight += w
            num_edges += 1
    return (total_weight, l_t) if num_edges == n - 1 else None

def complete_graph(n_nodes: int, max_weight=50) -> Tuple[int, List]:
    """Genera un grafo completo con pesos aleatorios entre 1 y max_weight."""
    l_g = [(u, v, random.randint(1, max_weight))
           for u in range(n_nodes) for v in range(u+1, n_nodes)]
    return n_nodes, l_g

def time_kruskal(n_graphs: int, n_nodes_ini: int, n_nodes_fin: int, step: int) -> List[float]:
    """Devuelve lista con tiempos medios de ejecución de Kruskal para varios tamaños de grafo."""
    import time, statistics
    mean_times = []
    for n in range(n_nodes_ini, n_nodes_fin+1, step):
        times = []
        for _ in range(n_graphs):
            nn, lg = complete_graph(n)
            start = time.perf_counter()
            kruskal(nn, lg)
            times.append(time.perf_counter()-start)
        mean_times.append(statistics.mean(times))
    return mean_times

# II-C. LABERINTO PERFECTO

Coord = Tuple[int,int]
Wall = Tuple[Coord,Coord]

def create_maze(num_rows: int, num_cols: int) -> List[Wall]:
    """Genera un laberinto perfecto como lista de paredes restantes."""
    walls = []
    for r in range(num_rows):
        for c in range(num_cols):
            if r < num_rows-1: walls.append(((r,c),(r+1,c)))
            if c < num_cols-1: walls.append(((r,c),(r,c+1)))
    random.shuffle(walls)
    p_cd = init_cd(num_rows*num_cols)
    def idx(r,c): return r*num_cols + c
    remaining = []
    for a,b in walls:
        ra,ca = a; rb,cb = b
        ida, idb = idx(ra,ca), idx(rb,cb)
        if find(ida,p_cd) != find(idb,p_cd):
            union(find(ida,p_cd), find(idb,p_cd), p_cd)
        else:
            remaining.append((a,b))
    return remaining

# III. PROBLEMA DEL VIAJANTE (TSP)

def dist_matrix(n_nodes: int, w_max=10) -> np.ndarray:
    """Genera matriz simétrica de distancias con valores enteros entre 1 y w_max, diagonal 0."""
    m = np.random.randint(1,w_max+1,(n_nodes,n_nodes))
    m = (m + m.T)//2
    np.fill_diagonal(m,0)
    return m

def greedy_tsp(dist_m: np.ndarray, node_ini=0) -> List[int]:
    """Devuelve un circuito basado en el vecino más cercano desde node_ini."""
    n = dist_m.shape[0]
    visited = [False]*n
    circuit = [node_ini]; visited[node_ini]=True
    for _ in range(n-1):
        last = circuit[-1]
        next_node = np.argmin([dist_m[last][j] if not visited[j] else np.inf for j in range(n)])
        circuit.append(next_node)
        visited[next_node] = True
    circuit.append(node_ini)
    return circuit

def len_circuit(circuit: List[int], dist_m: np.ndarray) -> int:
    """Calcula la longitud de un circuito dado su matriz de distancias."""
    return sum(dist_m[circuit[i], circuit[i+1]] for i in range(len(circuit)-1))

def repeated_greedy_tsp(dist_m: np.ndarray) -> List[int]:
    """Aplica greedy_tsp desde todos los nodos y devuelve el circuito más corto."""
    n = dist_m.shape[0]
    best_circuit, best_len = None, float('inf')
    for start in range(n):
        circuit = greedy_tsp(dist_m, start)
        l = len_circuit(circuit, dist_m)
        if l < best_len: best_circuit, best_len = circuit, l
    return best_circuit

def exhaustive_tsp(dist_m: np.ndarray) -> List[int]:
    """Resuelve el TSP examinando todas las permutaciones posibles (solo para grafos pequeños)."""
    from itertools import permutations
    n = dist_m.shape[0]
    best_circuit, best_len = None, float('inf')
    for perm in permutations(range(1,n)):
        circuit = [0]+list(perm)+[0]
        l = len_circuit(circuit, dist_m)
        if l < best_len: best_circuit, best_len = circuit, l
    return best_circuit
