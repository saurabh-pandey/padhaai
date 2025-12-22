import pathlib
import subprocess
import unittest

# from . import valgrind

class TestTryVecObjectPool(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        p = pathlib.Path(__file__)
        cls.exe = pathlib.Path(p.parents[1] / 'bin' / p.stem[len("test_"):])

    def test_run(self):
        output = subprocess.run([self.exe],
                                capture_output=True,
                                text=True).stdout
        print()
        result = {}
        for line in output.splitlines():
            if ':' in line:
                key, value_unit = line.split(':', 1)
                value = value_unit.strip().split()[0]
                result[key.strip()] = float(value)
        print(result)


if __name__ == '__main__':
    unittest.main()
