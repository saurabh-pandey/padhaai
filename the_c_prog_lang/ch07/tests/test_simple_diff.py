import pathlib
import subprocess
import unittest
import textwrap


class TestSimpleDiff(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        p = pathlib.Path(__file__)
        cls.exe = pathlib.Path(p.parents[1] / 'bin' / p.stem[len("test_"):])

    def test_matching_file(self):
        output = subprocess.run([self.exe, "tests/data/match1.txt", "tests/data/match2.txt"],
                                capture_output=True,
                                text=True).stdout
        self.assertEqual(output.splitlines(),
                         ['Overall diff statistics:',
                          'No. of lines matching      = 14',
                          'No. of lines with diff     = 0',
                          'No. of lines only one file = 0',
                          'No. of lines file1         = 14',
                          'No. of lines file2         = 14'])
    
    def test_mismatching_file(self):
        output = subprocess.run([self.exe, "tests/data/mismatch1.txt", "tests/data/mismatch2.txt"],
                                capture_output=True,
                                text=True).stdout
        self.assertEqual(output.splitlines(),
                         ['Overall diff statistics:',
                          'No. of lines matching      = 11',
                          'No. of lines with diff     = 4',
                          'No. of lines only one file = 0',
                          'No. of lines file1         = 15',
                          'No. of lines file2         = 15'])
    
    def test_eof_diff_file(self):
        output = subprocess.run([self.exe, "tests/data/text1.txt", "tests/data/text2.txt"],
                                capture_output=True,
                                text=True).stdout
        self.assertEqual(output.splitlines(),
                         ['Overall diff statistics:',
                          'No. of lines matching      = 0',
                          'No. of lines with diff     = 2',
                          'No. of lines only one file = 1',
                          'No. of lines file1         = 2',
                          'No. of lines file2         = 3'])
    
    def test_another_diff_file(self):
        output = subprocess.run([self.exe,
                                 "tests/data/simple_diff_test1.txt",
                                 "tests/data/simple_diff_test2.txt"],
                                capture_output=True,
                                text=True).stdout
        self.assertEqual(output.splitlines(),
                         ['Overall diff statistics:',
                          'No. of lines matching      = 3',
                          'No. of lines with diff     = 6',
                          'No. of lines only one file = 6',
                          'No. of lines file1         = 15',
                          'No. of lines file2         = 9'])
    
    def test_no_args(self):
        result = subprocess.run([self.exe],
                                capture_output=True,
                                text=True)
        self.assertEqual(result.stdout, "")
        self.assertEqual(result.stderr,
                         "ERROR: /home/saurabh/kaam/github/padhaai/the_c_prog_lang/ch07/bin/"
                         "simple_diff need 2 files for diff\n")
    
    def test_one_args(self):
        result = subprocess.run([self.exe, "tests/data/text1.txt"],
                                capture_output=True,
                                text=True)
        self.assertEqual(result.stdout, "")
        self.assertEqual(result.stderr,
                         "ERROR: /home/saurabh/kaam/github/padhaai/the_c_prog_lang/ch07/bin/"
                         "simple_diff need 2 files for diff\n")
    
    def test_three_args(self):
        result = subprocess.run([self.exe, "tests/data/text1.txt", "tests/data/text1.txt", "abc"],
                                capture_output=True,
                                text=True)
        self.assertEqual(result.stdout, "")
        self.assertEqual(result.stderr,
                         "ERROR: /home/saurabh/kaam/github/padhaai/the_c_prog_lang/ch07/bin/"
                         "simple_diff need 2 files for diff\n")
    
    def test_bad_path(self):
        result = subprocess.run([self.exe, "tests/data/text1.txt", "tests/data/text3.txt"],
                                capture_output=True,
                                text=True)
        self.assertEqual(result.stdout, "")
        self.assertEqual(result.stderr,
                         "ERROR: /home/saurabh/kaam/github/padhaai/the_c_prog_lang/ch07/bin/"
                         "simple_diff Can't open file tests/data/text3.txt\n")


if __name__ == '__main__':
    unittest.main()
