import pathlib
import unittest
import textwrap

from . import valgrind

class TestTryWrapper(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        p = pathlib.Path(__file__)
        cls.exe = pathlib.Path(p.parents[1] / 'bin' / p.stem[len("test_"):])

    def test_run(self):
        arr_inp = textwrap.dedent('''\
            This is a line.
            Another line of input.
        ''')
        self.assertTrue(valgrind.check_valgrind_installed(), "Valgrind not installed")
        stdout, stderr, _ = valgrind.run(self.exe, input=arr_inp)
        print("STDERR: ", stderr.splitlines())
        print("STDOUT: ", stdout.splitlines())
        # self.assertEqual(valgrind.parse_valgrind_output(stderr), 0)
        # self.assertEqual(stdout.splitlines(),
        #                  ['Running tests for io_wrapper', 'All tests passed', 'Done'])


if __name__ == '__main__':
    unittest.main()
