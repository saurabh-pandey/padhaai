import pathlib
import subprocess
import textwrap
import unittest


class TestCountKeywords(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        p = pathlib.Path(__file__)
        cls.exe = pathlib.Path(p.parents[1] / 'bin' / p.stem[len("test_"):])
    
    def check_keywords_count(self, expected, output):
        lines = output.splitlines()
        self.assertEqual(lines[0], 'Count all keyword occurrences')
        self.assertEqual(lines[1], 'Word       Count')
        keyword_mismatch = {}
        for line in lines[2:]:
            words = line.split()
            actual = int(words[1])
            if (words[0] in expected):
                if expected[words[0]] != actual:
                    keyword_mismatch[words[0]] = (expected[words[0]], actual)
            elif actual != 0:
                keyword_mismatch[words[0]] = (0, actual)
        self.assertEqual(len(keyword_mismatch), 0, keyword_mismatch)
    
    def test_simple(self):
        arr_inp = textwrap.dedent('''\
            Hello World
            auto
        ''')
        output = subprocess.run([self.exe], capture_output=True, text=True, input=arr_inp).stdout
        self.check_keywords_count({'auto': 1}, output)
    
    def test_all(self):
        arr_inp = textwrap.dedent('''\
            This a simple sentence
            It has auto and break in it
            It has case char const and we continue
            By default we can never double the float to an int
            There is long return to struct
            Finally unsigned void is also volatile
        ''')
        output = subprocess.run([self.exe], capture_output=True, text=True, input=arr_inp).stdout
        self.check_keywords_count({'auto' : 1, 'break' : 1, 'case' : 1, 'char' : 1, 'const' : 1,
                                   'continue' : 1, 'default' : 1, 'double' : 1, 'float' : 1,
                                   'int' : 1, 'long' : 1, 'return' : 1, 'struct' : 1,
                                   'unsigned' : 1, 'void' : 1, 'volatile' : 1}, output)
    
    def test_empty(self):
        arr_inp = textwrap.dedent('''\
        ''')
        output = subprocess.run([self.exe], capture_output=True, text=True, input=arr_inp).stdout
        self.check_keywords_count({}, output)
    
    def test_case_sensitive(self):
        arr_inp = textwrap.dedent('''\
            INT iNT InT inT INt iNt Int int
        ''')
        output = subprocess.run([self.exe], capture_output=True, text=True, input=arr_inp).stdout
        self.check_keywords_count({'int' : 1}, output)


if __name__ == '__main__':
    unittest.main()
