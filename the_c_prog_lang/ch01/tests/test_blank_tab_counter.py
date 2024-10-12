import pathlib
import subprocess
import unittest


single_inp = '''a b c\td\te'''

trail_lead_space_inp = ''' a b c\td\te '''
trail_lead_tab_inp = '''\ta b c\td\te\t'''

two_lines_inp = '''a b c
d e f
'''

blank_tab_inp = ''' \t \t
\t \t 
'''

single_line_inp = '''
'''

repeat_inp = '''a   b\t\t\tc'''

class TestBlankTabCounter(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        p = pathlib.Path(__file__)
        cls.exe = pathlib.Path(p.parents[1] / 'bin' / p.stem[len("test_"):])

    def test_simple(self):
        output = subprocess.run([self.exe], capture_output=True, text=True, input=single_inp).stdout
        self.assertEqual(output.splitlines(), ['Number of tabs = 2 and blank = 2'])
    
    def test_empty(self):
        output = subprocess.run([self.exe], capture_output=True, text=True, input="").stdout
        self.assertEqual(output.splitlines(), ['Number of tabs = 0 and blank = 0'])
    
    def test_trail_lead_space(self):
        output = subprocess.run([self.exe],
                                capture_output=True,
                                text=True,
                                input=trail_lead_space_inp).stdout
        self.assertEqual(output.splitlines(), ['Number of tabs = 2 and blank = 4'])
    
    def test_trail_lead_tab(self):
        output = subprocess.run([self.exe],
                                capture_output=True,
                                text=True,
                                input=trail_lead_tab_inp).stdout
        self.assertEqual(output.splitlines(), ['Number of tabs = 4 and blank = 2'])
    
    def test_two_lines(self):
        output = subprocess.run([self.exe],
                                capture_output=True,
                                text=True,
                                input=two_lines_inp).stdout
        self.assertEqual(output.splitlines(), ['Number of tabs = 0 and blank = 4'])
    
    def test_blank_tab(self):
        output = subprocess.run([self.exe],
                                capture_output=True,
                                text=True,
                                input=blank_tab_inp).stdout
        self.assertEqual(output.splitlines(), ['Number of tabs = 4 and blank = 4'])
    
    def test_single_line(self):
        output = subprocess.run([self.exe],
                                capture_output=True,
                                text=True,
                                input=single_line_inp).stdout
        self.assertEqual(output.splitlines(), ['Number of tabs = 0 and blank = 0'])
    
    def test_repeat(self):
        output = subprocess.run([self.exe],
                                capture_output=True,
                                text=True,
                                input=repeat_inp).stdout
        self.assertEqual(output.splitlines(), ['Number of tabs = 3 and blank = 3'])


if __name__ == '__main__':
    unittest.main()
