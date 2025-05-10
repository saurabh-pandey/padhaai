import pathlib
import subprocess
import unittest


simple_input = '''2 3 +
2 3 -
2 3 *
2 3 /
'''

floating_input = '''2.1 3.1 +
5.2 3.1 -
3.3 1.7 *
2.1 3.7 /
'''

bigger_input = '''1 2 - 4 5 + *
'''

incorrect_input = '''1 2 - 4
'''

fault_tolerance_inp = '''2 3 *
2 + 3
2 3 +
'''

new_lines_inp = '''


2 3 +
'''

empty_inp = '''
'''

div_zero_inp = '''3 4 *
2 3 +
5 0 /
5 2 -
'''


class TestRpnCalc(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        p = pathlib.Path(__file__)
        cls.exe = pathlib.Path(p.parents[1] / 'bin' / p.stem[len("test_"):])
    
    def test_simple(self):
        output = subprocess.run([self.exe],
                                capture_output=True,
                                text=True,
                                input=simple_input).stdout
        self.assertEqual(output.splitlines(), ['expr> Result = 5.000000',
                                               'expr> Result = -1.000000',
                                               'expr> Result = 6.000000',
                                               'expr> Result = 0.666667',
                                               'expr> DONE ', ''])
    
    def test_floating(self):
        output = subprocess.run([self.exe],
                                capture_output=True,
                                text=True,
                                input=floating_input).stdout
        self.assertEqual(output.splitlines(), ['expr> Result = 5.200000',
                                               'expr> Result = 2.100000',
                                               'expr> Result = 5.610000',
                                               'expr> Result = 0.567568',
                                               'expr> DONE ', ''])
    
    def test_bigger(self):
        output = subprocess.run([self.exe],
                                capture_output=True,
                                text=True,
                                input=bigger_input).stdout
        self.assertEqual(output.splitlines(), ['expr> Result = -9.000000', 'expr> DONE ', ''])
    
    def test_incorrect(self):
        output = subprocess.run([self.exe],
                                capture_output=True,
                                text=True,
                                input=incorrect_input).stdout
        self.assertEqual(output.splitlines(),
                         ['expr> WARNING: Expected the stack to contain only one element here. Stack status:',
                          'Stack size = 2',
                          'Stack content = [-1.000000, 4.000000]',
                          'Clearing the stack',
                          'expr> DONE ', ''])
    
    def test_fault_tolerance(self):
        output = subprocess.run([self.exe],
                                capture_output=True,
                                text=True,
                                input=fault_tolerance_inp).stdout
        self.assertEqual(output.splitlines(),
                         ['expr> Result = 6.000000', 'expr> WARNING: Min stack size = 2. Stack status:',
                         'Stack size = 1',
                         'Stack content = [2.000000]',
                         'Clearing the stack',
                         'Result = 3.000000',
                         'expr> Result = 5.000000',
                         'expr> DONE ', ''])
    
    def test_new_lines(self):
        output = subprocess.run([self.exe],
                                capture_output=True,
                                text=True,
                                input=new_lines_inp).stdout
        self.assertEqual(output.splitlines(),
                         ['expr> WARNING: Expected the stack to contain only one element here. Stack status:',
                          'Stack size = 0',
                          'Stack content = []',
                          'Clearing the stack',
                          'expr> WARNING: Expected the stack to contain only one element here. Stack status:',
                          'Stack size = 0',
                          'Stack content = []',
                          'Clearing the stack',
                          'expr> WARNING: Expected the stack to contain only one element here. Stack status:',
                          'Stack size = 0',
                          'Stack content = []',
                          'Clearing the stack',
                          'expr> Result = 5.000000',
                          'expr> DONE ',
                          ''])
    
    def test_empty(self):
        output = subprocess.run([self.exe],
                                capture_output=True,
                                text=True,
                                input=empty_inp).stdout
        self.assertEqual(output.splitlines(),
                         ['expr> WARNING: Expected the stack to contain only one element here. Stack status:',
                          'Stack size = 0',
                          'Stack content = []',
                          'Clearing the stack',
                          'expr> DONE ', ''])
    
    def test_div_zero(self):
        output = subprocess.run([self.exe],
                                capture_output=True,
                                text=True,
                                input=div_zero_inp).stdout
        self.assertEqual(output.splitlines(),
                         ['expr> Result = 12.000000',
                          'expr> Result = 5.000000',
                          'expr> ERROR: Division by zero is not allowed', 'Result = 5.000000',
                          'expr> Result = 3.000000',
                          'expr> DONE ', ''])

if __name__ == '__main__':
    unittest.main()
