import pathlib
import subprocess
import unittest
import os


class TestSysCp(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        p = pathlib.Path(__file__)
        cls.exe = pathlib.Path(p.parents[1] / 'bin' / p.stem[len("test_"):])
    
    def test_copy(self):
        subprocess.run([self.exe, "tests/data/input.txt", "tests/data/output.txt"],
                       capture_output=True,
                       text=True)
        self.assertTrue(os.path.exists("tests/data/output.txt"),
                        "The file 'tests/data/output.txt' should exist.")
        if os.path.exists("tests/data/output.txt"):
            os.remove("tests/data/output.txt")
    
    def test_bad_input(self):
        result = subprocess.run([self.exe, "tests/data/input1.txt", "tests/data/output.txt"],
                                capture_output=True,
                                text=True)
        self.assertEqual(result.stderr,
                         "Error while opening tests/data/input1.txt: No such file or directory\n")
        self.assertFalse(os.path.exists("tests/data/output.txt"),
                        "The file 'tests/data/output.txt' should not exist.")
    
    def test_bad_output(self):
        result = subprocess.run([self.exe, "tests/data/input.txt", "tests/data1/output.txt"],
                                capture_output=True,
                                text=True)
        self.assertEqual(result.stderr,
                         "Error while creating tests/data1/output.txt: No such file or directory\n")
        self.assertFalse(os.path.exists("tests/data/output.txt"),
                        "The file 'tests/data/output.txt' should not exist.")
    
    def test_bad_arg(self):
        result = subprocess.run([self.exe], capture_output=True, text=True)
        self.assertEqual(result.stderr,
                         "Usage: /home/saurabh/kaam/github/padhaai/the_c_prog_lang/ch08/bin/"
                         "sys_cp source_file copied_file\n")
        self.assertFalse(os.path.exists("tests/data/output.txt"),
                        "The file 'tests/data/output.txt' should not exist.")


if __name__ == '__main__':
    unittest.main()
