import pathlib
import subprocess
import unittest


class TestFsize(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        p = pathlib.Path(__file__)
        cls.exe = pathlib.Path(p.parents[1] / 'bin' / p.stem[len("test_"):])

    def test_wo_arg(self):
        output = subprocess.run([self.exe],
                                capture_output=True,
                                text=True).stdout
        # print(output.splitlines())
        for line in output.splitlines():
            print(line)
        # self.assertEqual(output.splitlines(), ['Hello world', 'Now this is a newline'])
    
    def test_wi_arg(self):
        output = subprocess.run([self.exe, "dir_test"],
                                capture_output=True,
                                text=True).stdout
        # print(output.splitlines())
        for line in output.splitlines():
            print(line)
        # self.assertEqual(output.splitlines(), ['Hello world', 'Now this is a newline'])


if __name__ == '__main__':
    unittest.main()
