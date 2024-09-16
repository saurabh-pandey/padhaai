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
        cls.exe = "bin/" + pathlib.Path(__file__).stem[len("test_"):]

    def test_simple(self):
        output = subprocess.run([self.exe], capture_output=True, text=True, input=repeat_inp).stdout
        print("### = ", output.splitlines())
        # self.assertEqual(output.splitlines(), ['Total number of Lines = 0'])
    
    # def test_empty(self):
    #     output = subprocess.run([self.exe], capture_output=True, text=True, input='').stdout
    #     self.assertEqual(output.splitlines(), ['Total number of Lines = 0'])
    
    # def test_two_lines(self):
    #     output = subprocess.run([self.exe],
    #                             capture_output=True,
    #                             text=True,
    #                             input=two_lines_inp).stdout
    #     self.assertEqual(output.splitlines(), ['Total number of Lines = 2'])
    
    # def test_single_line(self):
    #     output = subprocess.run([self.exe],
    #                             capture_output=True,
    #                             text=True,
    #                             input=single_line_inp).stdout
    #     self.assertEqual(output.splitlines(), ['Total number of Lines = 1'])


if __name__ == '__main__':
    unittest.main()
