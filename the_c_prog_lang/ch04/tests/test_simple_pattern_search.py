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
End of file hello
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

part_word = '''hehello
hehehellohe
hellhellhellohell
hhhhhello
helhello
hellhello
hhello
'''

edge_case = '''babababbaabaabbbbb'''

simpler_edge_case = '''aaab'''

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
        self.assertEqual(output.splitlines(), ['hello',
                                               'Welcome hello!',
                                               'End of line hello',
                                               'hello start of line',
                                               'Mid of line hello is this',
                                               'End of file hello'])
    
    def test_empty(self):
        output = subprocess.run([self.exe, "hello"], capture_output=True, text=True, input=empty_inp).stdout
        self.assertEqual(output.splitlines(), [])
    
    def test_usage(self):
        output = subprocess.run([self.exe], capture_output=True, text=True, input=empty_inp).stdout
        self.assertEqual(output.splitlines(),
                         ['','Usage:', '   ./bin/simple_pattern_search <pattern>', ''])
    
    def test_space_in_pattern(self):
        output = subprocess.run([self.exe, "hello"],
                                capture_output=True,
                                text=True,
                                input=space_in_pattern).stdout
        self.assertEqual(output.splitlines(), ['hello', 'hello ', ' hello'])
    
    def test_part_word(self):
        output = subprocess.run([self.exe, "hello"],
                                capture_output=True,
                                text=True,
                                input=part_word).stdout
        self.assertEqual(output.splitlines(),  ['hehello',
                                                'hehehellohe',
                                                'hellhellhellohell',
                                                'hhhhhello',
                                                'helhello',
                                                'hellhello',
                                                'hhello'])
    
    def test_edge_case(self):
        output = subprocess.run([self.exe, "baabb"],
                                capture_output=True,
                                text=True,
                                input=edge_case).stdout
        self.assertEqual(output.splitlines(), ['babababbaabaabbbbb'])
    
    def test_simpler_edge_case(self):
        output = subprocess.run([self.exe, "aab"],
                                capture_output=True,
                                text=True,
                                input=simpler_edge_case).stdout
        self.assertEqual(output.splitlines(), ['aaab'])


if __name__ == '__main__':
    unittest.main()
