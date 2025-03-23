import pathlib
import subprocess
import unittest


simple_input = '''2 3 +
2 3 -
2 3 *
2 3 /
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
        print(output.splitlines())

if __name__ == '__main__':
    unittest.main()
