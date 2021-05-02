import os
import sys
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), '../src')))

import unittest
from utils import *
from converters import *
from codegen import CodeGenerator
from coder import *

class Test(unittest.TestCase):

    def setUp(self):
        self.msg = "10001100"*10
        self.coded_msg = None

        code_gen = CodeGenerator(8, 0.2, 0.01)
        with open("tests/resources/code.json", "w") as outp:
            presenter = JsonPresenter()
            presenter.write(outp, code_gen)

    def test_coder(self):
        desc = None
        with open("tests/resources/code.json", "r") as inp:
            desc = JsonController(inp)

        encoder = Encoder(float(desc.get_attribute("channel_error_prob")),
                      int(desc.get_attribute("k")),
                      desc.get_attribute("encode_dict"))
        self.coded_msg = encoder.encode(self.msg)

        decoder = Decoder(int(desc.get_attribute("n")), desc.get_attribute("decode_dict"))
        self.assertEqual(self.msg, decoder.decode(self.coded_msg))


if __name__ == "__main__":
    unittest.main()