import json

def convert_dict(code_dict):
    res = {}
    for entry in code_dict.items():
        key = list(map(lambda x: str(x), entry[0]))
        val = list(map(lambda x: str(x), entry[1]))
        res[''.join(key)] = ''.join(val)

    return res

def convert_matrix(matrix):
    res = []
    for string in matrix:
        res.append(list(map(lambda x: str(x), string)))

    return res

class JsonController(object):
    
    def __init__(self, stream):
        self._json = json.load(stream)

    def get_attribute(self, attribute: str):
        return self._json[attribute]

class JsonPresenter(object):

    def write(self, stream, codegen):
        json_dict = {"error_bound": str(codegen.get_error_bound()),
                     "error_prob": str(codegen.get_error_prob()),
                     "channel_error_prob": str(codegen._p),
                     "n": str(codegen._n),
                     "k": str(codegen._k),
                     "matrix": convert_matrix(codegen.get_matrix()),
                     "encode_dict": convert_dict(codegen.get_encode_dict()),
                     "decode_dict": convert_dict(codegen.get_decode_dict())}

        json.dump(json_dict, stream, indent=4)