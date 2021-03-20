import json

from srcdesc import *
from fractions import Fraction

class JsonController(object):
    
    def __init__(self, input):
        self._obj = json.load(input)

    def get_description(self):
        models = self.__parse_models(self._obj)
        switches = self.__parse_switches(self._obj, models)
        switches_order = self._obj["source"]

        return DiscreteSourceDescription(list(map(lambda x: switches[x], switches_order)))
        
    def __parse_models(self, obj):
        models = {}
        
        for model in list(obj["models"].items()):
            name = model[0]
            symb_prob = model[1]
            models[name] = ModelDescription(
                name, 
                list(symb_prob.keys()), 
                list(map(self.__convert_str_to_prob, symb_prob.values()))
            )

        return models

    def __parse_switches(self, obj, models):
        switches = {}

        for switch in list(obj["switches"].items()):
            name = switch[0]
            models_name = list(switch[1].keys())
            models_prob = list(map(self.__convert_str_to_prob, switch[1].values()))
            switches[name] = SwitchDescription(
                name, 
                list(map(lambda x: models[x], models_name)), 
                models_prob
            )

        return switches

    def __convert_str_to_prob(self, str):
        try:
            return float(str)
        except ValueError:
            return float(Fraction(str))