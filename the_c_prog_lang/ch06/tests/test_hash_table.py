import pathlib
import unittest

from . import valgrind

class TestHashTable(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        p = pathlib.Path(__file__)
        cls.exe = pathlib.Path(p.parents[1] / 'bin' / p.stem[len("test_"):])

    def test_run(self):
        self.assertTrue(valgrind.check_valgrind_installed(), "Valgrind not installed")
        stdout, stderr, retcode = valgrind.run(self.exe)
        self.assertEqual(valgrind.parse_valgrind_output(stderr), 0)
        self.assertEqual(stdout.splitlines(),
                         ['Running tests for hash_table', 'All tests passed', 'Done'])


if __name__ == '__main__':
    unittest.main()
