from random import choices

class Coder(object):

    def __init__(self, block_size, encode_dict):
        self._k = block_size
        self._dict = encode_dict

    def encode(self, data : str) -> str:
        res = ""
        for i in range(len(data)//self._k):
            block = data[self._k*i:self._k*i + self._k]
            if block in self._dict:
                res += self.generate_error(self._dict[block])
            else:
                raise ValueError(f"{block}: Unexepected symbol or unfilled block")

        return res

    def generate_error(self, word : str) -> str:
        return word

class Encoder(Coder):

    def __init__(self, p, block_size, encode_dict):
        super().__init__(block_size, encode_dict)
        self._error = ""
        self._error_val = [False, True]
        self._error_probs = [1 - p, p]

    def generate_error(self, word):
        res = ""
        for i in word:
            error = choices(self._error_val, self._error_probs)[0]
            bit = ""

            if error:
                bit = "1" if i == "0" else "0"
                self._error += "1"
            else:
                bit = i
                self._error += "0"

            res += bit

        return res

    def get_error(self) -> str:
        return self._error

class Decoder(Coder):

    def __init__(self, block_size, decode_dict):
        super().__init__(block_size, decode_dict)

    def decode(self, data : str) -> str:
        return self.encode(data)