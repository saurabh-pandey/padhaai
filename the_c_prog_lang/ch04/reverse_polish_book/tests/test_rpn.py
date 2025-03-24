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
        # print(output.splitlines())
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
        # print(output.splitlines())
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
        # print(output.splitlines())
        self.assertEqual(output.splitlines(), ['expr> Result = -9.000000', 'expr> DONE ', ''])

if __name__ == '__main__':
    unittest.main()
