import pathlib
import subprocess
import unittest


class TestReversePolishCalc(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        p = pathlib.Path(__file__)
        cls.exe = pathlib.Path(p.parents[1] / 'bin' / p.stem[len("test_"):])

    def test_simple(self):
        output = subprocess.run([self.exe, "1 2 +"],
                                capture_output=True,
                                text=True).stdout
        print(output.splitlines())
    
    def test_usage(self):
        output = subprocess.run([self.exe], capture_output=True, text=True).stdout
        print(output.splitlines())
        # self.assertEqual(output.splitlines(),
        #                  ['','Usage:', '   ./bin/simple_pattern_search <pattern>', ''])


if __name__ == '__main__':
    unittest.main()
