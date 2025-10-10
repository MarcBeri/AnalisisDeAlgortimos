import time
import statistics

def search_all(lst, v):
    list=[]
    for i in range(len(lst)):
        if lst[i] == v:
            list.append(i)
    return list

def time_measure(f, dataprep, Nlst, Nrep=1000, Nstat=100):
    results = []
    for n in Nlst:
        times = []
        for _ in range(Nstat):
            data = dataprep(n)
            start = time.perf_counter()
            for _ in range(Nrep):
                f(data)
            end = time.perf_counter()
            elapsed = (end - start) / Nrep
            times.append(elapsed)
        mean_time = statistics.mean(times)
        variance_time = statistics.pvariance(times)
        results.append((mean_time, variance_time))
    return results


def heap_insert(h, key):
    h.append(key)
    i = len(h) -1
    while i > 0 and h[(i - 1) // 2] < h[i]:
        parent = (i - 1) // 2
        h[i], h[parent] = h[parent], h[i]
        i = parent

    return h

def heap_extract(h):
    e = h[0]             
    h[0] = h[-1]          
    h.pop()              

    i = 0
    n = len(h)
    while True:
        left = 2 * i + 1
        right = 2 * i + 2
        largest = i
        if left < n and h[left] > h[largest]:
            largest = left
        if right < n and h[right] > h[largest]:
            largest = right
        if largest != i:
            h[i], h[largest] = h[largest], h[i]
            i = largest
        else:
            break
    return (h, e)

def pq_ini():
    return []


def pq_insert(h, key):
    return heap_insert(h, key)


def pq_extract(h):
    return heap_extract(h)
