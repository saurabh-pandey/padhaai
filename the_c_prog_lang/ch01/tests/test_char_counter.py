import pathlib
import subprocess
import unittest


single_inp = '''a'''

two_lines_inp = '''abc
def
'''

single_line_inp = '''
'''

class TestCharCounter(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        p = pathlib.Path(__file__)
        cls.exe = pathlib.Path(p.parents[1] / 'bin' / p.stem[len("test_"):])

    def test_simple(self):
        output = subprocess.run([self.exe], capture_output=True, text=True, input=single_inp).stdout
        self.assertEqual(output.splitlines(), ['Total number of characters = 1'])
    
    def test_empty(self):
        output = subprocess.run([self.exe], capture_output=True, text=True, input='').stdout
        self.assertEqual(output.splitlines(), ['Total number of characters = 0'])
    
    def test_two_lines(self):
        output = subprocess.run([self.exe],
                                capture_output=True,
                                text=True,
                                input=two_lines_inp).stdout
        self.assertEqual(output.splitlines(), ['Total number of characters = 8'])
    
    def test_single_line(self):
        output = subprocess.run([self.exe],
                                capture_output=True,
                                text=True,
                                input=single_line_inp).stdout
        self.assertEqual(output.splitlines(), ['Total number of characters = 1'])


if __name__ == '__main__':
    unittest.main()
