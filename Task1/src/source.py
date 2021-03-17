import srcdesc as desc

from random import choices
from math import log

class DiscreteSource(object):

    def __init__(self, description):
        self._description = description
        self._cur_switch = 0

    def get_description(self):
        return self._description

    def get_symb(self):
        switch = self._description.switches[self._cur_switch]
        self._cur_switch = (self._cur_switch + 1) % len(self._description.switches)
        model = choices(switch.models, switch.probabilities, k=1)[0]

        return choices(model.symbols, model.probabilities, k=1)[0]

    """
    H(X|X^{oo}) = lim 1\n H(X^{n}) as n -> oo
    As source doesn't have memory H(X^{n}) = sum H(X_i) from i = 1 to n
    """ 
    def get_entropy(self, eps, log_base=2):

        buffer = []
        for switch in self._description.switches:
            buffer.append(self.__count_entropy_for_switch(switch, log_base))

        switch_entropy_sum = sum(buffer)
        i = len(buffer)
        old_entropy = eps
        new_entropy = switch_entropy_sum/i

        while abs(new_entropy - old_entropy) > eps:
            old_entropy = new_entropy
            switch_entropy_sum += buffer[i % len(buffer)]
            i += 1
            new_entropy = switch_entropy_sum/i 
        
        return switch_entropy_sum/i

    def __count_entropy_for_switch(self, switch, log_base):

        symb_dict = desc.create_symbol_dictionary_for_switch(switch) 
        tmp_list = [i * log(i, log_base) for i in list(symb_dict.values())]

        return -sum(tmp_list)