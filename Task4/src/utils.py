def binary_vec_matrix_mul(x, a):
    res = [0]*len(a[0])

    for i in range(len(x)):
        if x[i] != 0:
            for j in range(len(a[0])):
                res[j] ^= a[i][j]

    return res

def binary_vec_add(x, y):
    return [x[i]^y[i] for i in range(len(x))]