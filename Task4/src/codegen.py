from random import randint
from itertools import product, combinations

from utils import *
from math import ceil

class CodeGenerator(object):
    
    def __init__(self, n, R, p):
        self._n = n
        self._k = ceil(R * n)
        self._p = p
        self._matrix = self.__generate_matrix()
        self._encode_dict, self._decode_dict, self._t, self._error_prob = self.__generate_code(self._matrix)

    def get_decode_dict(self) -> dict:
        return self._decode_dict

    def get_encode_dict(self) -> dict:
        return self._encode_dict

    def get_matrix(self) -> list:
        return self._matrix

    def get_error_bound(self) -> int:
        return self._t

    def get_error_prob(self) -> float:
        return self._error_prob

    def __generate_matrix(self):
        matrix = []

        for i in range(self._k):
            matrix.append([])
            for j in range(self._n):
                if j < self._k:
                    matrix[i].append(1 if i == j else 0)
                else:
                    matrix[i].append(randint(0, 1))
            
        return matrix

    def __generate_code(self, matrix):
        decode_dict = {}
        encode_dict = {}
        code = []
        t = 0
        error_prob = 1

        for block in product([0, 1], repeat=self._k):
            code_word = binary_vec_matrix_mul(block, matrix)
            decode_dict[tuple(code_word)] = block
            encode_dict[tuple(block)] = code_word
            code.append(code_word)

        error_prob -= (1 - self._p)**(self._n)

        for w in range(1, self._n + 1):
            a, a_max = self.__fill_standart_location_level(w, decode_dict, code)
            error_prob -= a * self._p**w * (1 - self._p)**(self._n - w) 
            if a == a_max:
                t += 1

        return encode_dict, decode_dict, t, error_prob

    def __fill_standart_location_level(self, weight, code_dict, code):
        cnt = [0, 0]

        for indices in combinations(range(self._n), weight):
            cnt[1] += 1
            vec = [0]*self._n
            for i in indices:
                vec[i] = 1
            if tuple(vec) in code_dict:
                continue
            else:
                cnt[0] += 1
                for code_word in code:
                    code_dict[tuple(binary_vec_add(vec, code_word))] = tuple(code_word[:self._k])

        return cnt