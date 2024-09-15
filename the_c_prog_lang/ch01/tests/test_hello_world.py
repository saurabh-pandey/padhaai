import pathlib
import subprocess
import unittest


class TestHelloWorld(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.exe = "bin/" + pathlib.Path(__file__).stem[len("test_"):]

    def test_run(self):
        output = subprocess.run([self.exe], capture_output=True, text=True).stdout
        self.assertEqual(output.splitlines(), ['hello, world'])

if __name__ == '__main__':
    unittest.main()
