import pathlib
import subprocess
import unittest


class TestReversePolishCalc(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        p = pathlib.Path(__file__)
        cls.exe = pathlib.Path(p.parents[1] / 'bin' / p.stem[len("test_"):])
    
    def eval(self, expression: str) -> str:
        return subprocess.run([self.exe, *expression.split()],
                              capture_output=True,
                              text=True).stdout
    
    def test_usage(self):
        output = self.eval("")
        self.assertEqual(output.splitlines(),
                         ['', 'Usage:', '   ./bin/reverse_polish_calc <some_calculation>',
                          '   Some examples are:', '     ./bin/reverse_polish_calc 1 2 +',
                          '     ./bin/reverse_polish_calc 1 2 - 4 5 + \'*\'', ''])
    
    def test_simple_int(self):
        output = self.eval("1 2 +")
        self.assertEqual(output.splitlines(), ['Result = 3.000000'])
        output = self.eval("1 2 -")
        self.assertEqual(output.splitlines(), ['Result = -1.000000'])
        output = self.eval("3 2 *")
        self.assertEqual(output.splitlines(), ['Result = 6.000000'])
        output = self.eval("6 2 /")
        self.assertEqual(output.splitlines(), ['Result = 3.000000'])
    
    def test_simple_double(self):
        output = self.eval("1.1 2.2 +")
        self.assertEqual(output.splitlines(), ['Result = 3.300000'])
        output = self.eval("1.4 2.2 -")
        self.assertEqual(output.splitlines(), ['Result = -0.800000'])
        output = self.eval("3.1 2.7 *")
        self.assertEqual(output.splitlines(), ['Result = 8.370000'])
        output = self.eval("6.5 1.3 /")
        self.assertEqual(output.splitlines(), ['Result = 5.000000'])
    
    def test_bigger(self):
        output = self.eval("1 2 - 4 5 + *")
        self.assertEqual(output.splitlines(), ['Result = -9.000000'])
    
    def test_incorrect_rpn(self):
        output = self.eval("1 2 - 4")
        self.assertEqual(output.splitlines(),
                         ['WARNING: Stack is not empty (size is 1) at the end of RPN expression evaluation', 'Result = 4.000000'])
    
    def test_empty(self):
        output = self.eval("+")
        self.assertEqual(output.splitlines(),
                         ["ERROR: Stack is empty so can't pop", 'Result = 0.000000'])
    
    def test_single(self):
        output = self.eval("1")
        self.assertEqual(output.splitlines(), ['Result = 1.000000'])
    
    def test_negative(self):
        output = self.eval("-42")
        self.assertEqual(output.splitlines(), ['Result = -42.000000'])


if __name__ == '__main__':
    unittest.main()
