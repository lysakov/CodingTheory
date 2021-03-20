import sys

from controllers import JsonController
from interactors import SequenceGenerator, ProbabilityComputer, FirstTaskInteractor
from source import DiscreteSource

def generate(interactor):
    print("Enter length of generated sequence of None to create infinite one:")
    n = input()
    n = None if n == "None" else int(n)

    interactor.generate_seq(n, sys.stdout)

def compute(interactor):
    print("Enter sequence:")
    seq = input()

    print("Enter length of generated sample:")
    n = int(input())

    p = interactor.compute_probability(n, seq)
    print("p = {:.10f}".format(p))


if __name__ == "__main__":
    controller = None
    with open(sys.argv[1], "r") as inp:
        controller = JsonController(inp)

    src_desc = controller.get_description()
    src = DiscreteSource(src_desc)
    print("Discrete source was successfuly created.")
    interactor = FirstTaskInteractor(SequenceGenerator(src), ProbabilityComputer(src))
    n = None

    while n != "1" and n != "2":
        print("1. Generate sequence of symbol generate by discrete source.")
        print("2. Compute probability of sequence.")

        n = input()
        if n == "1":
            generate(interactor)
        elif n == "2":
            compute(interactor)
        else:
            print("Enter 1 or 2.")