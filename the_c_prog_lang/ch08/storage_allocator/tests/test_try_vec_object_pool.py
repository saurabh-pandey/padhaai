import pathlib
import subprocess
import unittest


class TestTryVecObjectPool(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        p = pathlib.Path(__file__)
        cls.const_exe = pathlib.Path(p.parents[1] / 'bin' / "try_vec_linear_pool_constant")
        cls.linear_exe = pathlib.Path(p.parents[1] / 'bin' / "try_vec_linear_pool_linear")
        cls.freelist_exe_v1 = pathlib.Path(p.parents[1] / 'bin' / "try_vec_freelist_pool_v1")
        cls.freelist_exe_v2 = pathlib.Path(p.parents[1] / 'bin' / "try_vec_freelist_pool_v2")

    def test_run(self):
        const_output = subprocess.run([self.const_exe], capture_output=True, text=True).stdout
        linear_output = subprocess.run([self.linear_exe], capture_output=True, text=True).stdout
        freelist_output_v1 = subprocess.run([self.freelist_exe_v1],
                                            capture_output=True,
                                            text=True).stdout
        freelist_output_v2 = subprocess.run([self.freelist_exe_v2],
                                            capture_output=True,
                                            text=True).stdout
        const_result = self._parse_output(const_output)
        linear_result = self._parse_output(linear_output)
        freelist_result_v1 = self._parse_output(freelist_output_v1)
        freelist_result_v2 = self._parse_output(freelist_output_v2)
        self.assertEqual(len(const_result),
                         len(linear_result),
                         "Constant and linear results size mismatch")
        self.assertEqual(len(const_result),
                         len(freelist_result_v1),
                         "Constant and Freelist V1 results size mismatch")
        self.assertEqual(len(const_result),
                         len(freelist_result_v2),
                         "Constant and Freelist V2 results size mismatch")
        for key in const_result:
            self.assertTrue(key in linear_result, f"{key} not found in linear output result")
            self.assertTrue(key in freelist_result_v1,
                            f"{key} not found in freelist v1 output result")
            self.assertTrue(key in freelist_result_v2,
                            f"{key} not found in freelist v2 output result")
            self.assertGreaterEqual(linear_result[key],
                                    const_result[key],
                                    f"Constant {key} result is slower")
            self.assertGreaterEqual(const_result[key],
                                    freelist_result_v1[key],
                                    f"Freelist V1 {key} result is slower")
            self.assertGreaterEqual(const_result[key],
                                    freelist_result_v2[key],
                                    f"Freelist V2 {key} result is slower")
    
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
