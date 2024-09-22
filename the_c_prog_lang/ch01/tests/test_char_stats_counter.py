import pathlib
import subprocess
import unittest


single_inp = '''abcd1234@# '''

multi_lines_inp = '''This is a multiline input. What purpose does it serve?
It just tests the code below. I think this is the 3rd test.
Today is 22/09/2024 and time is 13:56. It is a Sunday.
'''

class TestCharStatsCounter(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.exe = "bin/" + pathlib.Path(__file__).stem[len("test_"):]

    def test_simple(self):
        output = subprocess.run([self.exe], capture_output=True, text=True, input=single_inp).stdout
        self.assertEqual(output.splitlines(), ['Number of whitespaces = 1',
                                               'Number of 0 = 0',
                                               'Number of 1 = 1',
                                               'Number of 2 = 1',
                                               'Number of 3 = 1',
                                               'Number of 4 = 1',
                                               'Number of 5 = 0',
                                               'Number of 6 = 0',
                                               'Number of 7 = 0',
                                               'Number of 8 = 0',
                                               'Number of 9 = 0',
                                               'Number of other = 6'])
    
    def test_empty(self):
        output = subprocess.run([self.exe], capture_output=True, text=True, input="").stdout
        self.assertEqual(output.splitlines(), ['Number of whitespaces = 0',
                                               'Number of 0 = 0',
                                               'Number of 1 = 0',
                                               'Number of 2 = 0',
                                               'Number of 3 = 0',
                                               'Number of 4 = 0',
                                               'Number of 5 = 0',
                                               'Number of 6 = 0',
                                               'Number of 7 = 0',
                                               'Number of 8 = 0',
                                               'Number of 9 = 0',
                                               'Number of other = 0'])
    
    def test_multi_line(self):
        output = subprocess.run([self.exe],
                                capture_output=True,
                                text=True,
                                input=multi_lines_inp).stdout
        self.assertEqual(output.splitlines(), ['Number of whitespaces = 34',
                                               'Number of 0 = 2',
                                               'Number of 1 = 1',
                                               'Number of 2 = 4',
                                               'Number of 3 = 2',
                                               'Number of 4 = 1',
                                               'Number of 5 = 1',
                                               'Number of 6 = 1',
                                               'Number of 7 = 0',
                                               'Number of 8 = 0',
                                               'Number of 9 = 1',
                                               'Number of other = 123'])


if __name__ == '__main__':
    unittest.main()
