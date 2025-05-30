import pathlib
import subprocess
import unittest


class TestSimpleStrend(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        p = pathlib.Path(__file__)
        cls.exe = pathlib.Path(p.parents[1] / 'bin' / p.stem[len("test_"):])

    def test_run(self):
        output = subprocess.run([self.exe],
                                capture_output=True,
                                text=True).stdout
        self.assertEqual(output.splitlines(),
                         ['Running tests for simple_strend', 'All tests passed', 'Done'])


if __name__ == '__main__':
    unittest.main()
