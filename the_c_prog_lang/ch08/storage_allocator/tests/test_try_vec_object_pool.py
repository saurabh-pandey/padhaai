import pathlib
import subprocess
import unittest


class TestTryVecObjectPool(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        p = pathlib.Path(__file__)
        cls.const_exe = pathlib.Path(p.parents[1] / 'bin' / (p.stem[len("test_"):] + "_constant"))
        cls.linear_exe = pathlib.Path(p.parents[1] / 'bin' / (p.stem[len("test_"):] + "_linear"))

    def test_run(self):
        const_output = subprocess.run([self.const_exe], capture_output=True, text=True).stdout
        linear_output = subprocess.run([self.linear_exe], capture_output=True, text=True).stdout
        print()
        print(self._parse_output(const_output))
        print()
        print(self._parse_output(linear_output))
    

    def _parse_output(self, output):
        result = {}
        for line in output.splitlines():
            if ':' in line:
                key, value_unit = line.split(':', 1)
                value = value_unit.strip().split()[0]
                result[key.strip()] = float(value)
        return result
        

if __name__ == '__main__':
    unittest.main()
