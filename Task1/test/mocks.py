import os
import sys
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), '../src')))

import srcdesc

def get_src_desc():
    model1 = srcdesc.ModelDescription("Coin1", ["0", "1"], [1/2, 1/2])
    model2 = srcdesc.ModelDescription("Coin2", ["0", "1"], [1/3, 2/3])
    model3 = srcdesc.ModelDescription("Coin3", ["0", "1"], [2/5, 3/5])
    switch1 = srcdesc.SwitchDescription("Switch1", [model1, model2], [1/2, 1/2])
    switch2 = srcdesc.SwitchDescription("Switch2", [model2, model3], [1/4, 3/4])
    source = srcdesc.DiscreteSourceDescription([switch1, switch2])

    return source

def get_stationary_src_desc():
    model = srcdesc.ModelDescription("Coin", ["0", "1"], [0.9, 0.1])
    switch = srcdesc.SwitchDescription("Switch", [model], [1.0])
    source = srcdesc.DiscreteSourceDescription([switch])

    return source
