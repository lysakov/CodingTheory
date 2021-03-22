import sys

from controllers import JsonController
from interactors import SecondTaskInteractor
from source import DiscreteSource
from coder import Coder

if __name__ == "__main__":
    controller = None
    with open(sys.argv[1], "r") as inp:
        controller = JsonController(inp)

    src_desc = controller.get_description()
    src = DiscreteSource(src_desc)
    print("Discrete source was successfuly created.")
    interactor = SecondTaskInteractor(src)
    n = None

    while n != "1" and n != "2":
        print("1. Compute entropy for discrete source source.")
        print("2. Create code for discrete source.")

        n = input()
        if n == "1":
            print("Enter precision of computation:")
            eps = input()
            interactor.compute_entropy(eps)
        elif n == "2":
            print("Enter right bound for coding speed:")
            R = float(input())
            print("Enter error probability:")
            eps = float(input())
            print("Enter number of symbols in code's alphabet:")
            q = int(input())
            coder = Coder(src, R, eps, q)
            print("Coder was successfuly created.")
            with open("src/resources/code.txt", "w") as output:
                code_r, most_likely_set_length = interactor.create_code(coder, output)
                print(f"Code with speed {code_r} and {most_likely_set_length} code words was created.")
                print("Code was written in src/resources/code.txt")
        else:
            print("Enter 1 or 2.")