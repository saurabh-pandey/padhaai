import pathlib
import subprocess
import unittest
import textwrap


class TestSysCat(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        p = pathlib.Path(__file__)
        cls.exe = pathlib.Path(p.parents[1] / 'bin' / p.stem[len("test_"):])

    def test_single_file(self):
        output = subprocess.run([self.exe, "tests/data/text.txt"],
                                capture_output=True,
                                text=True).stdout
        self.assertEqual(output.splitlines(), ['This is a small text from a file.', 'Thank you!'])
    
    def test_two_files(self):
        output = subprocess.run([self.exe, "tests/data/input.txt", "tests/data/text.txt"],
                                capture_output=True,
                                text=True).stdout
        self.assertEqual(output.splitlines(),
                         ['This is file supposed to be copied to output.txt in this same folder.',
                          'It is copied using simple_cp exe.',
                          "Let's see if this work!!!",
                          'Get set go!!!',
                          'This is a small text from a file.',
                          'Thank you!'])
    
    def test_stdin(self):
        arr_inp = textwrap.dedent('''\
            Hello world
            Now this is a newline
        ''')
        output = subprocess.run([self.exe],
                                capture_output=True,
                                text=True,
                                input=arr_inp).stdout
        self.assertEqual(output.splitlines(), ['Hello world', 'Now this is a newline'])
    
    def test_stderr(self):
        result = subprocess.run([self.exe, "tests/data/no_file.txt"],
                                capture_output=True,
                                text=True)
        self.assertEqual(result.stdout, "")
        self.assertEqual(result.stderr,
                         "Error while opening tests/data/no_file.txt: No such file or directory\n")


if __name__ == '__main__':
    unittest.main()
