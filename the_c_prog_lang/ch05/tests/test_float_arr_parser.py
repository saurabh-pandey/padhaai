import pathlib
import subprocess
import unittest


class TestFloatArrParser(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        p = pathlib.Path(__file__)
        cls.exe = pathlib.Path(p.parents[1] / 'bin' / p.stem[len("test_"):])
    
    def test_simple(self):
        arr_inp = "1.2 2.3 3.4 4.5 5.6"
        output = subprocess.run([self.exe],
                                capture_output=True,
                                text=True,
                                input=arr_inp).stdout
        # print(output.splitlines())
        self.assertEqual(output.splitlines(),
                         ['arr = [1.20, 2.30, 3.40, 4.50, 5.60, 0.00, 0.00, 0.00, 0.00, 0.00]'])
    
    def test_empty(self):
        arr_inp = ""
        output = subprocess.run([self.exe],
                                capture_output=True,
                                text=True,
                                input=arr_inp).stdout
        self.assertEqual(output.splitlines(),
                         ['arr = [0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00]'])
    
    def test_comma(self):
        arr_inp = "1.2, 2.3, 3.4, 4.5, 5.6"
        output = subprocess.run([self.exe],
                                capture_output=True,
                                text=True,
                                input=arr_inp).stdout
        self.assertEqual(output.splitlines(),
                         ['arr = [1.20, 2.30, 3.40, 4.50, 5.60, 0.00, 0.00, 0.00, 0.00, 0.00]'])
    
    def test_negative(self):
        arr_inp = "-1.2 -2.3 -3.4 -4.5 -5.6"
        output = subprocess.run([self.exe],
                                capture_output=True,
                                text=True,
                                input=arr_inp).stdout
        self.assertEqual(output.splitlines(),
                         ['arr = [-1.20, -2.30, -3.40, -4.50, -5.60, 0.00, 0.00, 0.00, 0.00, 0.00]'])
    
    def test_mixed_sign(self):
        arr_inp = "-1.2, +2.3, -3.4, +4.5, -5.6"
        output = subprocess.run([self.exe],
                                capture_output=True,
                                text=True,
                                input=arr_inp).stdout
        self.assertEqual(output.splitlines(),
                         ['arr = [-1.20, 2.30, -3.40, 4.50, -5.60, 0.00, 0.00, 0.00, 0.00, 0.00]'])
    
    def test_no_num(self):
        arr_inp = "+ - ++-- === ++++ ---- +-+-+- abcdlk%$#@"
        output = subprocess.run([self.exe],
                                capture_output=True,
                                text=True,
                                input=arr_inp).stdout
        self.assertEqual(output.splitlines(),
                         ['arr = [0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00]'])
    
    def test_mixed_sep(self):
        arr_inp = "0.1a0.02b-.03c-0.42#05.1&-6.02"
        output = subprocess.run([self.exe],
                                capture_output=True,
                                text=True,
                                input=arr_inp).stdout
        self.assertEqual(output.splitlines(),
                         ['arr = [0.10, 0.02, -0.03, -0.42, 5.10, -6.02, 0.00, 0.00, 0.00, 0.00]'])
    
    def test_big_nums(self):
        arr_inp = "12.34 -345.23 6789.54"
        output = subprocess.run([self.exe],
                                capture_output=True,
                                text=True,
                                input=arr_inp).stdout
        self.assertEqual(output.splitlines(),
                         ['arr = [12.34, -345.23, 6789.54, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00]'])
    
    def test_spaced_sign(self):
        arr_inp = "- 1.01 + 2.02 -3.03 --4.04 +-5.05 -   6.06 --- 7.07"
        output = subprocess.run([self.exe],
                                capture_output=True,
                                text=True,
                                input=arr_inp).stdout
        self.assertEqual(output.splitlines(),
                         ['arr = [1.01, 2.02, -3.03, -4.04, -5.05, 6.06, 7.07, 0.00, 0.00, 0.00]'])
    
    def test_zero_prefix(self):
        arr_inp = "-01.01 +002.02 -0003.03 -0014.04 +00105.05 -0 07"
        output = subprocess.run([self.exe],
                                capture_output=True,
                                text=True,
                                input=arr_inp).stdout
        self.assertEqual(output.splitlines(),
                         ['arr = [-1.01, 2.02, -3.03, -14.04, 105.05, -0.00, 7.00, 0.00, 0.00, 0.00]'])
    
    def test_max_size(self):
        arr_inp = "1.11 2.22 3.33 4.44 5.55 6.66 7.77 8.88 9.99 10.10 11.11 12.12"
        output = subprocess.run([self.exe],
                                capture_output=True,
                                text=True,
                                input=arr_inp).stdout
        self.assertEqual(output.splitlines(),
                         ['Array has reached max size = 10',
                          'Exiting.',
                          'arr = [1.11, 2.22, 3.33, 4.44, 5.55, 6.66, 7.77, 8.88, 9.99, 10.10]'])
    
    def test_dot_sign(self):
        arr_inp = "+. --.+ ..-+ -+0014.04 --.+00105.05 .-0 .+07"
        output = subprocess.run([self.exe],
                                capture_output=True,
                                text=True,
                                input=arr_inp).stdout
        self.assertEqual(output.splitlines(),
                         ['arr = [14.04, 105.05, -0.00, 7.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00]'])


if __name__ == '__main__':
    unittest.main()
