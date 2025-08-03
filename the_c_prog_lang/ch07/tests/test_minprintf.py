import pathlib
import subprocess
import unittest


class TestMinPrintf(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        p = pathlib.Path(__file__)
        cls.exe = pathlib.Path(p.parents[1] / 'bin' / p.stem[len("test_"):])

    def test_run(self):
        output = subprocess.run([self.exe],
                                capture_output=True,
                                text=True).stdout
        self.assertEqual(output.splitlines(),
                         ['Running tests for minprintf',
                          'input int 42 input double 3.140000 input str Hello, World',
                          'Another test with negative int -10',
                          'Another test with negative double -2.710000',
                          'Another test with empty string ""',
                          'ABC1233.210000',
                          'Done'])


if __name__ == '__main__':
    unittest.main()
