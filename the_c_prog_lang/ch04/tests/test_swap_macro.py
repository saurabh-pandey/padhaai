import pathlib
import subprocess
import unittest


class TestSimpleAtof(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        p = pathlib.Path(__file__)
        cls.exe = pathlib.Path(p.parents[1] / 'bin' / p.stem[len("test_"):])

    def test_run(self):
        output = subprocess.run([self.exe],
                                capture_output=True,
                                text=True).stdout
        self.assertEqual(output.splitlines(),
                         ['Before swap = (2, 3)',
                          'After  swap = (3, 2)',
                          'Before swap = (2.100000, 3.200000)',
                          'After swap = (3.200000, 2.100000)'])


if __name__ == '__main__':
    unittest.main()
