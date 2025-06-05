import pathlib
import subprocess
import textwrap
import unittest


class TestSimpleSort(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        p = pathlib.Path(__file__)
        cls.exe = pathlib.Path(p.parents[1] / 'bin' / p.stem[len("test_"):])
    
    def test_simple(self):
        arr_inp = textwrap.dedent('''\
            hello
            world
            zoo
            like
            rat
            abc
            vote
            done
        ''')
        output = subprocess.run([self.exe],
                                capture_output=True,
                                text=True,
                                input=arr_inp).stdout
        print(output.splitlines())
        # self.assertEqual(output.splitlines(), ['arr = [1, 2, 3, 4, 5, 0, 0, 0, 0, 0]'])

if __name__ == '__main__':
    unittest.main()
