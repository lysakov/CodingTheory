from converters import *
from coder import Encoder, Decoder
from codegen import CodeGenerator
from random import randint

if __name__ == "__main__":
    print("1. Generate new code")
    print("2. Encode binary string")
    print("3. Decode binary string")

    n = ""
    while n not in ("1", "2", "3"):
        n = input()

        if n == "1":
            print("Enter code block length:")
            N = int(input())
            print("Enter coding speed:")
            R = float(input())
            print("Enter channel error probability:")
            p = float(input())
            codegen = CodeGenerator(N, R, p)
            json_presenter = JsonPresenter()

            path = f"output/code{randint(2**31, 2**32 - 1)}.json"
            with open(path, "w") as output:
                json_presenter.write(output, codegen)
            print(f"Code description can be found in {path}")
            print(f"Code improves {codegen.get_error_bound} mistakes.")
            print(f"Probability of having mistake is {codegen.get_error_prob}.")

        elif n == "2":
            print("Enter path to code description:")
            path = input()
            encoder = None

            with open(path, "r") as inp:
                json_controller = JsonController(inp)
                encoder = Encoder(float(json_controller.get_attribute("channel_error_prob")),
                                  int(json_controller.get_attribute("k")),
                                  json_controller.get_attribute("encode_dict"))

            print("Enter message to encode:")
            msg = input()
            enc_msg = encoder.encode(msg)
            print("Encoded message:   ", enc_msg)
            print("Error vector:      ", encoder.get_error())

        elif n == "3":
            print("Enter path to code description:")
            path = input()
            decoder = None

            with open(path, "r") as inp:
                json_controller = JsonController(inp)
                decoder = Decoder(int(json_controller.get_attribute("n")), 
                                  json_controller.get_attribute("decode_dict"))
                
            print("Enter message to decode:")
            enc_msg = input()
            msg = decoder.decode(enc_msg)
            print("Decoded message:   ", msg)