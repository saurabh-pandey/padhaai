import pathlib
import subprocess
import unittest


single_inp = '''a'''

two_lines_inp = '''abc
def
'''

single_line_inp = '''
'''

class TestLineCounter(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.exe = "bin/" + pathlib.Path(__file__).stem[len("test_"):]

    def test_simple(self):
        output = subprocess.run([self.exe], capture_output=True, text=True, input=single_inp).stdout
        self.assertEqual(output.splitlines(), ['Total number of Lines = 0'])
    
    def test_empty(self):
        output = subprocess.run([self.exe], capture_output=True, text=True, input='').stdout
        self.assertEqual(output.splitlines(), ['Total number of Lines = 0'])
    
    def test_two_lines(self):
        output = subprocess.run([self.exe],
                                capture_output=True,
                                text=True,
                                input=two_lines_inp).stdout
        self.assertEqual(output.splitlines(), ['Total number of Lines = 2'])
    
    def test_single_line(self):
        output = subprocess.run([self.exe],
                                capture_output=True,
                                text=True,
                                input=single_line_inp).stdout
        self.assertEqual(output.splitlines(), ['Total number of Lines = 1'])


if __name__ == '__main__':
    unittest.main()
