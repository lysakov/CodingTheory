class ModelDescription(object):

    def __init__(self, name, symbols, probabilities):
        self.name = name
        self.symbols = symbols
        self.probabilities = probabilities

    def __str__(self):
        result = f"{self.name}:\n" 
        for pair in list(zip(self.symbols, self.probabilities)):
            result += f"{pair[0]}: {pair[1]}\n"

        return result

class SwitchDescription(object):

    def __init__(self, name, models, probabilities):
        self.name = name
        self.models = models
        self.probabilities = probabilities

    def __str__(self):
        result = f"{self.name}:\n" 
        for pair in list(zip(self.models, self.probabilities)):
            result += f"{pair[0].name}: {pair[1]}\n"

        return result

class DiscreteSourceDescription(object):

    def __init__(self, switches):
        self.switches = switches

    def __str__(self):
        result = ""
        for switch in self.switches:
            result += f"{str(switch)}"

        return result
        
def create_symbol_dictionary_for_switch(switch):

    symb_dict = dict()
    for i in range(len(switch.models)):
        for j in range(len(switch.models[i].symbols)):
            symb = switch.models[i].symbols[j]
            if symb in symb_dict:
                symb_dict[symb] += switch.probabilities[i] * switch.models[i].probabilities[j]
            else:
                symb_dict[symb] = switch.probabilities[i] * switch.models[i].probabilities[j]

    return symb_dict