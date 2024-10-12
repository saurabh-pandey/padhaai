import pathlib
import subprocess
import unittest


single_inp = '''a
bc
def
ghij
klmnop
'''

empty_inp = '''
'''

multi_lines_inp = '''This is a multiline input. What purpose does it serve?
It just tests the code below. I think this is the 3rd test.
Today is 22/09/2024 and time is 13:56. It is a Sunday.
'''

class TestLongestLine(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.exe = "bin/" + pathlib.Path(__file__).stem[len("test_"):]

    def test_simple(self):
        output = subprocess.run([self.exe], capture_output=True, text=True, input=single_inp).stdout
        self.assertEqual(output.splitlines(), ['Line = a', 'length = 2',
                                               'Line = bc', 'length = 3',
                                               'Line = def', 'length = 4',
                                               'Line = ghij', 'length = 5',
                                               'Line = klmnop', 'length = 7',
                                               'Max line = klmnop', 'length = 7'])
    
    def test_empty(self):
        output = subprocess.run([self.exe], capture_output=True, text=True, input=empty_inp).stdout
        self.assertEqual(output.splitlines(), ['Line = ',
                                               'length = 1',
                                               'Max line = ',
                                               'length = 1'])
    
    def test_multi_lines(self):
        output = subprocess.run([self.exe],
                                capture_output=True,
                                text=True,
                                input=multi_lines_inp).stdout
        self.assertEqual(output.splitlines(),
                         ['Line = This is a multiline input. What purpose does it serve?',
                          'length = 55',
                          'Line = It just tests the code below. I think this is the 3rd test.',
                          'length = 60',
                          'Line = Today is 22/09/2024 and time is 13:56. It is a Sunday.',
                          'length = 55',
                          'Max line = It just tests the code below. I think this is the 3rd test.',
                          'length = 60'])


if __name__ == '__main__':
    unittest.main()
