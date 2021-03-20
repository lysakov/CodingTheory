import os
import sys
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), '../src')))

import unittest
import srcdesc
import source
import mocks
import coder

from math import log2

class Test(unittest.TestCase):

    def setUp(self):
        self.description = mocks.get_src_desc()

    def test_source(self):
        src = source.DiscreteSource(self.description)
        for i in range(100):
            print(src.get_symb(), end='')
        print("\n" + 100*"=")

    def test_stationary_src(self):
        print("Entropy for binary stationary source")
        src = source.DiscreteSource(mocks.get_stationary_src_desc())
        delta = 0.01
        h = src.get_entropy(delta, 2)
        print("H =", h)

        bin_entropy = lambda p: -p*log2(p) - (1 - p)*log2(1 - p)
        self.assertAlmostEqual(h, bin_entropy(0.1), delta=delta)
        print(100 * "=")

    def test_most_likely_set(self):
        print("Most likely set test")
        src = source.DiscreteSource(mocks.get_stationary_src_desc())
        coder_ = coder.Coder(src, 1, 0.01, 4)
        most_likely_set = coder_._Coder__create_most_likely_set()
        print("|T| =", len(most_likely_set))
        print("n =", len(most_likely_set[0]))
        print(100 * "=")

    def test_coder(self):
        print("Coder test")
        src = source.DiscreteSource(mocks.get_stationary_src_desc())
        coder_ = coder.Coder(src, 1, 0.01, 4)
        code = coder_.get_code()

        for word, word_code in code.items():
            print(word, word_code)
        print(100 * "=")

if __name__ == "__main__":
    unittest.main()