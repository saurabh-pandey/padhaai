import pathlib
import subprocess
import unittest


class TestHelloWorld(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        p = pathlib.Path(__file__)
        cls.exe = pathlib.Path(p.parents[1] / 'bin' / p.stem[len("test_"):])

    def test_run(self):
        output = subprocess.run([self.exe], capture_output=True, text=True).stdout
        self.assertEqual(output.splitlines(), ['hello, world'])

if __name__ == '__main__':
    unittest.main()
