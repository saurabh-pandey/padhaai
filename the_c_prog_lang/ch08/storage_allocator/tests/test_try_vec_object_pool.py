import pathlib
import subprocess
import unittest


class TestTryVecObjectPool(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        p = pathlib.Path(__file__)
        cls.const_exe = pathlib.Path(p.parents[1] / 'bin' / "try_vec_linear_pool_constant")
        cls.linear_exe = pathlib.Path(p.parents[1] / 'bin' / "try_vec_linear_pool_linear")
        cls.freelist_exe = pathlib.Path(p.parents[1] / 'bin' / "try_vec_freelist_pool")

    def test_run(self):
        const_output = subprocess.run([self.const_exe], capture_output=True, text=True).stdout
        linear_output = subprocess.run([self.linear_exe], capture_output=True, text=True).stdout
        freelist_output = subprocess.run([self.freelist_exe], capture_output=True, text=True).stdout
        const_result = self._parse_output(const_output)
        linear_result = self._parse_output(linear_output)
        freelist_result = self._parse_output(freelist_output)
        self.assertEqual(len(const_result),
                         len(linear_result),
                         "Constant and linear results size mismatch")
        self.assertEqual(len(const_result),
                         len(freelist_result),
                         "Constant and Freelist results size mismatch")
        for key in const_result:
            self.assertTrue(key in linear_result, f"{key} not found in linear output result")
            self.assertTrue(key in freelist_result, f"{key} not found in freelist output result")
            self.assertGreaterEqual(linear_result[key],
                                    const_result[key],
                                    f"Constant {key} result is slower")
            self.assertGreaterEqual(const_result[key],
                                    freelist_result[key],
                                    f"Freelist {key} result is slower")
    
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
