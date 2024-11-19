import numpy as np
import time

n = 1000
matriz1 = np.random.uniform(0.0, 10.0, size=(n, n))
matriz2 = np.random.uniform(0.0, 10.0, size=(n, n))

inicio = time.time()
resultado = np.dot(matriz1, matriz2)
fim = time.time()

print(f"Tempo para multiplicar matrizes {n}x{n}: {fim - inicio:.6f} segundos")