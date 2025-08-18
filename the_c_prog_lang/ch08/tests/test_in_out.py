import pathlib
import subprocess
import unittest
import textwrap


class TestInOut(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        p = pathlib.Path(__file__)
        cls.exe = pathlib.Path(p.parents[1] / 'bin' / p.stem[len("test_"):])
    
    def test_in_out(self):
        arr_inp = textwrap.dedent('''\
            Hello world
            Now this is a newline
        ''')
        output = subprocess.run([self.exe],
                                capture_output=True,
                                text=True,
                                input=arr_inp).stdout
        self.assertEqual(output.splitlines(), ['Hello world', 'Now this is a newline'])


if __name__ == '__main__':
    unittest.main()
