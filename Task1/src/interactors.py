from pynput.keyboard import Listener, KeyCode

class ProbabilityComputer(object):

    def __init__(self, src):
        self._src = src

    def compute(self, N, seq):
        if N < len(seq):
            raise ValueError("Sample size can't be smaller then length of sequence")

        buffer = [self._src.get_symb() for i in range(len(seq))]
        ngram_dict = {tuple(buffer) : 1}
        cnt = N - len(seq)

        for i in range(cnt):
            buffer.pop(0)
            buffer.append(self._src.get_symb())
            next_seq = tuple(buffer)

            if next_seq in ngram_dict:
                ngram_dict[next_seq] += 1
            else:
                ngram_dict[next_seq] = 1

        if tuple(seq) in ngram_dict:
            return ngram_dict[tuple(seq)] / (N - len(seq) + 1)
        else:
            return 0.0

class SequenceGenerator(object):

    def __init__(self, src):
        self._src = src
        self._end_flag = False

    def generate_finite_seq(self, N, output):
        for i in range(N):
            output.write(self._src.get_symb())

    def generate_infinite_seq(self, output):
        with Listener(on_press=self.__on_press) as listener:
            while not self._end_flag:
                output.write(self._src.get_symb())

            listener.stop()
            listener.join()

    def __on_press(self, key):
        if key == KeyCode.from_char("q"):
            self._end_flag = True

class FirstTaskInteractor(object):

    def __init__(self, seq_generator, prob_computer):
        self._seq_generator = seq_generator
        self._prob_computer = prob_computer

    def generate_seq(self, N, output):
        if N is None:
            self._seq_generator.generate_infinite_seq(output)
        else:
            self._seq_generator.generate_finite_seq(N, output)

    def compute_probability(self, N, seq):
        return self._prob_computer.compute(N, seq)