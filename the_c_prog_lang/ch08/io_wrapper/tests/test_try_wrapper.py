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
        self.assertEqual(valgrind.parse_valgrind_output(stderr), 0)
        self.assertIn("This is an error message", stderr)
        self.assertEqual(stdout.splitlines(),
                         ['This is a line.',
                          'Another line of input.',
                          'This is a simple output message'])


if __name__ == '__main__':
    unittest.main()
