import os
import sys
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), '../src')))

import unittest
import mocks

from source import *
from interactors import ProbabilityComputer, SequenceGenerator
from controllers import JsonController

class Test(unittest.TestCase):

    def setUp(self):
        self.description = mocks.get_stationary_src_desc()
        self.src = DiscreteSource(self.description)

    def test_probability(self):
        prob_comp = ProbabilityComputer(self.src)
        self.assertAlmostEqual(0.001, prob_comp.compute(10000, "111"), delta=0.001)

    def test_generator(self):
        generator = SequenceGenerator(self.src)
        #generator.generate_infinite_seq(sys.stdout)

    def test_controller(self):
        with open("test/resources/test.json") as inp:
            controller = JsonController(inp)
            print(controller.get_description())

if __name__ == "__main__":
    unittest.main()