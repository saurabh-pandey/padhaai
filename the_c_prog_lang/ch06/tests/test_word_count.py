import collections
import pathlib
import subprocess
import textwrap
import unittest


class TestWordCount(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        p = pathlib.Path(__file__)
        cls.exe = pathlib.Path(p.parents[1] / 'bin' / p.stem[len("test_"):])
    
    def check_word_count(self, input, output):
        expected_word_count = collections.Counter(input.split())
        lines = output.splitlines()
        self.assertEqual(lines[0], 'Count all words')
        word_count_mismatch = {}
        for line in lines[1:]:
            if line == "Done":
                break
            word_count_pair = line.split(" => ")
            actual_count = int(word_count_pair[1])
            if (word_count_pair[0] in expected_word_count):
                expected_count = expected_word_count[word_count_pair[0]]
                if expected_count != actual_count:
                    word_count_mismatch[word_count_pair[0]] = (expected_count, actual_count)
            else:
                word_count_mismatch[word_count_pair[0]] = (0, actual_count)
        self.assertEqual(len(word_count_mismatch), 0, word_count_mismatch)
    
    def test_simple(self):
        input = textwrap.dedent('''\
            now is the time for all good men to come to the aid of their party
        ''')
        output = subprocess.run([self.exe], capture_output=True, text=True, input=input).stdout
        self.check_word_count(input, output)
    
    def test_multiple_line(self):
        input = textwrap.dedent('''\
            this is a multiple line example and this is the first line
            another sentence that makes it two line
            this is the third line now what next
            now i have added a fourth line to see if it works
            finally a fifth line to finish things
        ''')
        output = subprocess.run([self.exe], capture_output=True, text=True, input=input).stdout
        self.check_word_count(input, output)
    
    def test_empty(self):
        input = textwrap.dedent('''\
        ''')
        output = subprocess.run([self.exe], capture_output=True, text=True, input=input).stdout
        self.check_word_count(input, output)
    
    def test_char_case(self):
        input = textwrap.dedent('''\
            Now we will try to test an example with lower and upper case
            Best is to mix the cases and see if they match
            How about this This THIS tHis tHIS thiS
            Since we have tested above line we test now what
            Let us try another line that will test best as well
        ''')
        output = subprocess.run([self.exe], capture_output=True, text=True, input=input).stdout
        self.check_word_count(input, output)


if __name__ == '__main__':
    unittest.main()
