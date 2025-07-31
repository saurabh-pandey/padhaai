import collections
import pathlib
import textwrap
import unittest

from . import valgrind

class TestWordCount(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        p = pathlib.Path(__file__)
        cls.exe = pathlib.Path(p.parents[1] / 'bin' / p.stem[len("test_"):])
    
    # =======================
    # Test functions
    # =======================
    def test_simple(self):
        input = textwrap.dedent('''\
            now is the time for all good men to come to the aid of their party
        ''')
        # output = subprocess.run([self.exe], capture_output=True, text=True, input=input).stdout
        # self._check_word_count(input, output)
        self._run_and_test_tree_view(input)
        self._run_and_test_count_view(input)
    
    def test_multiple_line(self):
        input = textwrap.dedent('''\
            this is a multiple line example and this is the first line
            another sentence that makes it two line
            this is the third line now what next
            now i have added a fourth line to see if it works
            finally a fifth line to finish things
        ''')
        # output = subprocess.run([self.exe], capture_output=True, text=True, input=input).stdout
        # self._check_word_count(input, output)
        self._run_and_test_tree_view(input)
        self._run_and_test_count_view(input)
    
    def test_empty(self):
        input = textwrap.dedent('''\
        ''')
        # output = subprocess.run([self.exe], capture_output=True, text=True, input=input).stdout
        # self._check_word_count(input, output)
        self._run_and_test_tree_view(input)
        self._run_and_test_count_view(input)
    
    def test_char_case(self):
        input = textwrap.dedent('''\
            Now we will try to test an example with lower and upper case
            Best is to mix the cases and see if they match
            How about this This THIS tHis tHIS thiS
            Since we have tested above line we test now what
            Let us try another line that will test best as well
        ''')
        # output = subprocess.run([self.exe], capture_output=True, text=True, input=input).stdout
        # self._check_word_count(input, output)
        self._run_and_test_tree_view(input)
        self._run_and_test_count_view(input)
    
    # ===========================
    # Private helper functions
    # ===========================
    def _run_and_test_tree_view(self, input):
        self.assertTrue(valgrind.check_valgrind_installed(), "Valgrind not installed")
        stdout, stderr, retcode = valgrind.run(self.exe, input)
        self.assertEqual(valgrind.parse_valgrind_output(stderr), 0)
        self._check_tree_view(input, stdout)
    
    def _check_tree_view(self, input, output):
        lines = output.splitlines()
        self.assertEqual(lines[0], 'Count all words')
        self.assertEqual(lines[1], 'Tree based view')
        if len(input) == 0:
            return
        expected_word_count = collections.Counter(input.split())
        word_count_mismatch = {}
        for line in lines[2:]:
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
    
    def _run_and_test_count_view(self, input):
        self.assertTrue(valgrind.check_valgrind_installed(), "Valgrind not installed")
        stdout, stderr, retcode = valgrind.run(self.exe, input, ["--count"])
        self.assertEqual(valgrind.parse_valgrind_output(stderr), 0)
        self._check_count_view(input, stdout)

    def _check_count_view(self, input, output):
        lines = output.splitlines()
        self.assertEqual(lines[0], 'Count all words')
        self.assertEqual(lines[1], 'Count based view')
        if len(input) == 0:
            return
        expected_word_count = collections.Counter(input.split())
        min_count, max_count = min(expected_word_count.values()), max(expected_word_count.values())
        count_ordered_words = {}
        for count in range(max_count, min_count - 1, -1):
            count_ordered_words[count] = []
        
        for key, value in expected_word_count.items():
            count_ordered_words[value].append(key)
        self.assertEqual(lines[2], f'min_count = {min_count}, max_count = {max_count}')
        for line in lines[3:]:
            if line == "Done":
                break
            comma_split_line = [part.strip() for part in line.split(',')]
            # Parse count part of line
            count_line_split = [part.strip() for part in comma_split_line[0].split('=')]
            self.assertEqual(count_line_split[0], 'Count')
            count_num = int(count_line_split[1])
            # Parse nodes part of the line
            nodes_line_split = [part.strip() for part in comma_split_line[1].split('=')]
            self.assertEqual(nodes_line_split[0], 'Nodes')
            
            # Remove the opening square bracket from parsed output
            all_words = [nodes_line_split[1][1:]]
            all_words.extend(comma_split_line[2:])
            # Remove the closing square bracket from parsed output
            all_words[-1] = all_words[-1][:-1]
            self.assertEqual(set(count_ordered_words[count_num]), set(all_words))


if __name__ == '__main__':
    unittest.main()
