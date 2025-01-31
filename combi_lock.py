
import time
import random

def combi(N, S_int, E_int):
    total_steps = 0
    for i in range(N):
        S = (S_int // 10**(i)) % 10
        E = (E_int // 10**(i)) % 10
        min_val = min(S, E)
        max_val = max(S, E)
        step_a = max_val - min_val
        step_b = (min_val+10) - max_val
        total_steps += min(step_a, step_b)

#check runtime for same length
total_runtime = 0
for i in range(1000):
    N = 50
    S = random.randint(10**(N-1), 10**N - 1)
    E = random.randint(10**(N-1), 10**N - 1)
    start_time = time.time()
    combi(N,S,E)
    end_time = time.time()
    runtime = end_time - start_time
    total_runtime += runtime
print("Runtime for same length: {:.6f} seconds".format(total_runtime))

#check runtime for different length
total_runtime = 0
for i in range(1000):
    N = random.randint(2, 100)
    S = random.randint(10**(N-1), 10**N - 1)
    E = random.randint(10**(N-1), 10**N - 1)
    start_time = time.time()
    combi(N,S,E)
    end_time = time.time()
    runtime = end_time - start_time
    total_runtime += runtime
print("Runtime for different length: {:.6f} seconds".format(total_runtime))
