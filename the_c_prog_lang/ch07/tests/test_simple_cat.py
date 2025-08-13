import pathlib
import subprocess
import unittest
import textwrap


class TestSimpleCat(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        p = pathlib.Path(__file__)
        cls.exe = pathlib.Path(p.parents[1] / 'bin' / p.stem[len("test_"):])

    def test_single_file(self):
        output = subprocess.run([self.exe, "tests/data/text1.txt"],
                                capture_output=True,
                                text=True).stdout
        self.assertEqual(output.splitlines(), ['This is a small text from a file.', 'Thank you!'])
    
    def test_two_files(self):
        output = subprocess.run([self.exe, "tests/data/text1.txt", "tests/data/text2.txt"],
                                capture_output=True,
                                text=True).stdout
        self.assertEqual(output.splitlines(),
                         ['This is a small text from a file.',
                          'Thank you!',
                          'Hello world!',
                          'Now it is a another file.',
                          'But with 3 lines.'])
    
    def test_no_files(self):
        arr_inp = textwrap.dedent('''\
            Hello world
            Now this is a newline
        ''')
        output = subprocess.run([self.exe],
                                capture_output=True,
                                text=True,
                                input=arr_inp).stdout
        self.assertEqual(output.splitlines(), ['Hello world', 'Now this is a newline', ''])


if __name__ == '__main__':
    unittest.main()
