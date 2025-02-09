import pathlib
import subprocess
import unittest


single_inp = '''hello
a
bc
def ghi
Hello
hellO
heLLo
Welcome hello!
End of line hello
hello start of line
Mid of line hello is this
'''

empty_inp = '''
'''

space_in_pattern = '''hello
he ll o
h e l l o
 h e l l o
h ello
he llo
hel lo
hell o
hello 
 hello
'''

class TestSimplePatternSearch(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        p = pathlib.Path(__file__)
        cls.exe = pathlib.Path(p.parents[1] / 'bin' / p.stem[len("test_"):])

    def test_simple(self):
        output = subprocess.run([self.exe, "hello"],
                                capture_output=True,
                                text=True,
                                input=single_inp).stdout
        print(output.splitlines())
        self.assertEqual(output.splitlines(), ['hello',
                                               'Welcome hello!',
                                               'End of line hello',
                                               'hello start of line',
                                               'Mid of line hello is this'])
    
    def test_empty(self):
        output = subprocess.run([self.exe, "hello"], capture_output=True, text=True, input=empty_inp).stdout
        print(output.splitlines())
        self.assertEqual(output.splitlines(), [])
    
    def test_usage(self):
        output = subprocess.run([self.exe], capture_output=True, text=True, input=empty_inp).stdout
        print(output.splitlines())
        self.assertEqual(output.splitlines(),
                         ['','Usage:', '   ./bin/simple_pattern_search <pattern>', ''])
    
    def test_space_in_pattern(self):
        output = subprocess.run([self.exe, "hello"],
                                capture_output=True,
                                text=True,
                                input=space_in_pattern).stdout
        print(output.splitlines())


if __name__ == '__main__':
    unittest.main()
