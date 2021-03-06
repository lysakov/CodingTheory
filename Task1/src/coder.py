import srcdesc as desc

from itertools import product
from math import prod, log, ceil

class Coder(object):

    def __init__(self, source, R, eps, q):
        self._source = source
        self._R = R
        self._eps = eps
        self._q = q
        self.__check_params()

    def get_code(self):
        most_likely_set = self.__create_most_likely_set()
        symbols = [str(i) for i in range(self._q)]
        code_words = list(product(symbols, repeat=ceil(log(len(most_likely_set), self._q))))
        code_iterator = zip(most_likely_set, code_words[:len(most_likely_set)])

        return dict(code_iterator)

    def __check_params(self):
        desc = self._source.get_description()
        if len(desc.switches) != 1:
            raise ValueError("Discrete source is not stationary")

        self._h = self._source.get_entropy(self._eps, self.__get_alphabet_len())
        if self._h > self._R:
            raise ValueError("Impossible to create code with coding speed less then entropy")

    def __get_alphabet_len(self):
        symb_dict = desc.create_symbol_dictionary_for_switch(self._source.get_description().switches[0])

        return len(symb_dict)

    def __create_most_likely_set(self):
        symb_dict = desc.create_symbol_dictionary_for_switch(self._source.get_description().switches[0])
        symb_list = list(symb_dict.keys())
        eps = self._R - self._h
        set_prob = 0
        n = 1
        most_likely_set = []

        while 1 - set_prob > self._eps:
            most_likely_set.clear()
            n += 1
            sequences = product(symb_list, repeat=n)
            set_prob = 0

            for word in sequences:
                word_prob = prod([symb_dict[i] for i in word])
                if abs(-log(word_prob, 2)/n - self._h) < eps:
                    most_likely_set.append(word) 
                    set_prob += word_prob

        return most_likely_set
