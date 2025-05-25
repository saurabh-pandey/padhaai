import pathlib
import subprocess
import unittest


class TestIntArrParser(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        p = pathlib.Path(__file__)
        cls.exe = pathlib.Path(p.parents[1] / 'bin' / p.stem[len("test_"):])
    
    def test_simple(self):
        arr_inp = "1 2 3 4 5"
        output = subprocess.run([self.exe],
                                capture_output=True,
                                text=True,
                                input=arr_inp).stdout
        self.assertEqual(output.splitlines(), ['arr = [1, 2, 3, 4, 5, 0, 0, 0, 0, 0]'])
    
    def test_empty(self):
        arr_inp = ""
        output = subprocess.run([self.exe],
                                capture_output=True,
                                text=True,
                                input=arr_inp).stdout
        self.assertEqual(output.splitlines(), ['arr = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]'])
    
    def test_comma(self):
        arr_inp = "1, 2, 3, 4, 5"
        output = subprocess.run([self.exe],
                                capture_output=True,
                                text=True,
                                input=arr_inp).stdout
        self.assertEqual(output.splitlines(), ['arr = [1, 2, 3, 4, 5, 0, 0, 0, 0, 0]'])
    
    def test_negative(self):
        arr_inp = "-1 -2 -3 -4 -5"
        output = subprocess.run([self.exe],
                                capture_output=True,
                                text=True,
                                input=arr_inp).stdout
        self.assertEqual(output.splitlines(), ['arr = [-1, -2, -3, -4, -5, 0, 0, 0, 0, 0]'])
    
    def test_mixed_sign(self):
        arr_inp = "-1, +2, -3, +4, -5"
        output = subprocess.run([self.exe],
                                capture_output=True,
                                text=True,
                                input=arr_inp).stdout
        self.assertEqual(output.splitlines(), ['arr = [-1, 2, -3, 4, -5, 0, 0, 0, 0, 0]'])
    
    def test_no_num(self):
        arr_inp = "+ - ++-- === ++++ ---- +-+-+- abcdlk%$#@"
        output = subprocess.run([self.exe],
                                capture_output=True,
                                text=True,
                                input=arr_inp).stdout
        self.assertEqual(output.splitlines(), ['arr = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]'])
    
    def test_mixed_sep(self):
        arr_inp = "1a2b-3c-4#5&-6"
        output = subprocess.run([self.exe],
                                capture_output=True,
                                text=True,
                                input=arr_inp).stdout
        self.assertEqual(output.splitlines(), ['arr = [1, 2, -3, -4, 5, -6, 0, 0, 0, 0]'])
    
    def test_big_nums(self):
        arr_inp = "12 -345 6789"
        output = subprocess.run([self.exe],
                                capture_output=True,
                                text=True,
                                input=arr_inp).stdout
        self.assertEqual(output.splitlines(), ['arr = [12, -345, 6789, 0, 0, 0, 0, 0, 0, 0]'])
    
    def test_spaced_sign(self):
        arr_inp = "- 1 + 2 -3 --4 +-5 -   6 --- 7"
        output = subprocess.run([self.exe],
                                capture_output=True,
                                text=True,
                                input=arr_inp).stdout
        self.assertEqual(output.splitlines(), ['arr = [1, 2, -3, -4, -5, 6, 7, 0, 0, 0]'])
    
    def test_zero_prefix(self):
        arr_inp = "-01 +002 -0003 -0014 +00105 -0 07"
        output = subprocess.run([self.exe],
                                capture_output=True,
                                text=True,
                                input=arr_inp).stdout
        self.assertEqual(output.splitlines(), ['arr = [-1, 2, -3, -14, 105, 0, 7, 0, 0, 0]'])
    
    def test_max_size(self):
        arr_inp = "1 2 3 4 5 6 7 8 9 10 11 12"
        output = subprocess.run([self.exe],
                                capture_output=True,
                                text=True,
                                input=arr_inp).stdout
        self.assertEqual(output.splitlines(), ['Array has reached max size = 10',
                                               'Exiting.',
                                               'arr = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]'])


if __name__ == '__main__':
    unittest.main()
