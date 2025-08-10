import pathlib
import subprocess
import unittest
import textwrap


class TestMinscanf(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        p = pathlib.Path(__file__)
        cls.exe = pathlib.Path(p.parents[1] / 'bin' / p.stem[len("test_"):])
    
    def test_simple(self):
        arr_inp = textwrap.dedent('''\
            412
            3.141
            helloworld
            1, 3.2
            2, monkey
            21.04, donkey
            (17, 5, 403)
            03/01/2021
        ''')
        output = subprocess.run([self.exe],
                                capture_output=True,
                                text=True,
                                input=arr_inp).stdout
        self.assertEqual(output.splitlines(),
                         ['Running tests for minscanf',
                          'Enter an int: int = 412',
                          'Enter a float: float = 3.141000',
                          'Enter a str: Str = helloworld',
                          'Enter an int(i) and a float(f) like i, f: Num = 1, float = 3.200000',
                          'Enter an int(i) and a str(s) like i, s: Num = 2, str = monkey',
                          'Enter an real(f) and a str(s) like f, s: Float = 21.040001, str = '
                          'donkey',
                          'Enter three numbers like (n1, n2, n3): Three numbers are (17, 5, 403)',
                          'Enter date in dd/mm/yyyy format (e.g. 02/03/1978): Entered date is 3/1/'
                          '2021',
                          'Done'])
    
    def test_negative(self):
        arr_inp = textwrap.dedent('''\
            -412
            -3.141
            good
            -1, -3.2
            -2, shark
            -21.04, -whale
            (-17, -5, -403)
            03/01/2021
        ''')
        output = subprocess.run([self.exe],
                                capture_output=True,
                                text=True,
                                input=arr_inp).stdout
        self.assertEqual(output.splitlines(),
                         ['Running tests for minscanf',
                          'Enter an int: int = -412',
                          'Enter a float: float = -3.141000',
                          'Enter a str: Str = good',
                          'Enter an int(i) and a float(f) like i, f: Num = -1, float = -3.200000',
                          'Enter an int(i) and a str(s) like i, s: Num = -2, str = shark',
                          'Enter an real(f) and a str(s) like f, s: Float = -21.040001, str = '
                          '-whale',
                          'Enter three numbers like (n1, n2, n3): Three numbers are (-17, -5, -403)'
                          '',
                          'Enter date in dd/mm/yyyy format (e.g. 02/03/1978): Entered date is 3/1/'
                          '2021',
                          'Done'])

if __name__ == '__main__':
    unittest.main()
