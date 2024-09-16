import pathlib
import subprocess
import unittest


single_inp = '''a'''

two_lines_inp = '''abc
def
'''

single_line_inp = '''
'''

class TestSimpleCopy(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.exe = "bin/" + pathlib.Path(__file__).stem[len("test_"):]

    def test_simple(self):
        output = subprocess.run([self.exe],
                                capture_output=True,
                                text=True,
                                input=single_inp).stdout
        self.assertEqual(output, single_inp)
    
    def test_empty(self):
        output = subprocess.run([self.exe], capture_output=True, text=True, input='').stdout
        self.assertEqual(output, '')
    
    def test_two_lines(self):
        output = subprocess.run([self.exe],
                                capture_output=True,
                                text=True,
                                input=two_lines_inp).stdout
        self.assertEqual(output, two_lines_inp)
    
    def test_single_line(self):
        output = subprocess.run([self.exe],
                                capture_output=True,
                                text=True,
                                input=single_line_inp).stdout
        self.assertEqual(output, single_line_inp)


if __name__ == '__main__':
    unittest.main()
