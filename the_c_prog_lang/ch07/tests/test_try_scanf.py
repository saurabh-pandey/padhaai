import pathlib
import subprocess
import unittest
import textwrap


class TestTryScanf(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        p = pathlib.Path(__file__)
        cls.exe = pathlib.Path(p.parents[1] / 'bin' / p.stem[len("test_"):])
    
    def test_simple(self):
        arr_inp = textwrap.dedent('''\
            412
            3.141
            helloworld
            (-17, 5, 43)
            03-Nov-1897
            03/01/2021
        ''')
        output = subprocess.run([self.exe],
                                capture_output=True,
                                text=True,
                                input=arr_inp).stdout
        self.assertEqual(output.splitlines(),
                         ['Running tests for try_scanf',
                          'Enter an int: int entered is = 412',
                          'Enter a double: double entered is = 3.141000',
                          'Enter a string: String entered is = helloworld',
                          'Enter three numbers like (n1, n2, n3): Three numbers are (-17, 5, 43)', 
                          'Enter date in dd-month_name_yy format (e.g. 02-March-1978): Entered date'
                          ' is 3-Nov-1897',
                          'Enter date in dd/mm/yyyy format (e.g. 02/03/1978): Entered date is'
                          ' 3/1/2021',
                          'Done'])
    
    def test_another(self):
        arr_inp = textwrap.dedent('''\
            -412
            -3.141
            def
            (3, -9, -101)
            13-October-2023
            23/12/2001
        ''')
        output = subprocess.run([self.exe],
                                capture_output=True,
                                text=True,
                                input=arr_inp).stdout
        self.assertEqual(output.splitlines(),
                         ['Running tests for try_scanf',
                          'Enter an int: int entered is = -412',
                          'Enter a double: double entered is = -3.141000',
                          'Enter a string: String entered is = def',
                          'Enter three numbers like (n1, n2, n3): Three numbers are (3, -9, -101)', 
                          'Enter date in dd-month_name_yy format (e.g. 02-March-1978): Entered date'
                          ' is 13-October-2023',
                          'Enter date in dd/mm/yyyy format (e.g. 02/03/1978): Entered date is'
                          ' 23/12/2001',
                          'Done'])

if __name__ == '__main__':
    unittest.main()
