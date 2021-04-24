import os
import sys
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), '../src')))

import unittest
from utils import *
from codegen import CodeGenerator

class Test(unittest.TestCase):

    def setUp(self):
        pass

    def test_code(self):
        code_gen = CodeGenerator(8, 0.2, 0.1)
        print(code_gen.get_matrix())
        print(code_gen.get_error_bound())
        print(code_gen.get_error_prob())
        #code_dict = code_gen.get_code()
        #print(code_dict)

if __name__ == "__main__":
    unittest.main()