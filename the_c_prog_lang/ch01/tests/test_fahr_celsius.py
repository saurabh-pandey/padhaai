import pathlib
import subprocess
import unittest

class TestFahrCelsius(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        p = pathlib.Path(__file__)
        cls.exe = pathlib.Path(p.parents[1] / 'bin' / p.stem[len("test_"):])

    def test_run(self):
        output = subprocess.run([self.exe], capture_output=True, text=True).stdout
        expected_output = ['',
                           'Fahrenheit\tCelsius',
                           '       0\t -17.8',
                           '      20\t  -6.7',
                           '      40\t   4.4',
                           '      60\t  15.6',
                           '      80\t  26.7',
                           '     100\t  37.8',
                           '     120\t  48.9',
                           '     140\t  60.0',
                           '     160\t  71.1',
                           '     180\t  82.2',
                           '     200\t  93.3',
                           '     220\t 104.4',
                           '     240\t 115.6',
                           '     260\t 126.7',
                           '     280\t 137.8',
                           '     300\t 148.9']
        self.assertEqual(output.splitlines(), expected_output)


if __name__ == '__main__':
    unittest.main()
