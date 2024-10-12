import pathlib
import subprocess
import unittest


single_inp = '''a
bc
def
ghij
klmnop
'''

empty_line_inp = '''
'''

multi_lines_inp = '''This is a multiline input. What purpose does it serve?
It just tests the code below. I think this is the 3rd test.
Today is 22/09/2024 and time is 13:56. It is a Sunday.
'''

class TestLongestLine(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        p = pathlib.Path(__file__)
        # exe = p.stem[len("test_"):]
        # print("### exe = ", exe)
        # print("### path = ", pathlib.Path(p.parents[1] / 'bin'))
        cls.exe = pathlib.Path(p.parents[1] / 'bin' / p.stem[len("test_"):])
        print("### cls.exe = ", cls.exe)

    def test_simple(self):
        output = subprocess.run([self.exe], capture_output=True, text=True, input=single_inp).stdout
        self.assertEqual(output.splitlines(),
                         ['Number of characters = 21, words = 5 and lines = 5'])
    
    def test_empty(self):
        output = subprocess.run([self.exe], capture_output=True, text=True, input="").stdout
        self.assertEqual(output.splitlines(),
                         ['Number of characters = 0, words = 0 and lines = 0'])
    
    def test_empty_line(self):
        output = subprocess.run([self.exe],
                                capture_output=True,
                                text=True,
                                input=empty_line_inp).stdout
        self.assertEqual(output.splitlines(),
                         ['Number of characters = 1, words = 0 and lines = 1'])
    
    def test_multi_lines(self):
        output = subprocess.run([self.exe],
                                capture_output=True,
                                text=True,
                                input=multi_lines_inp).stdout
        self.assertEqual(output.splitlines(),
                         ['Number of characters = 170, words = 34 and lines = 3'])


if __name__ == '__main__':
    unittest.main()
