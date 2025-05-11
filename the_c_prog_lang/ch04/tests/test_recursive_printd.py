import pathlib
import subprocess
import unittest


class TestRecursivePrintd(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        p = pathlib.Path(__file__)
        cls.exe = pathlib.Path(p.parents[1] / 'bin' / p.stem[len("test_"):])

    def test_run(self):
        output = subprocess.run([self.exe],
                                capture_output=True,
                                text=True).stdout
        output_lines = output.splitlines()
        self.assertEqual(output_lines[0], 'Running tests for recursive_printd')
        self.assertEqual(output_lines[-1], 'Done')
        for i, n in enumerate(range(-100, 101)):
            self.assertEqual(n, int(output_lines[i + 1]))


if __name__ == '__main__':
    unittest.main()
