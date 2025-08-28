import pathlib
import subprocess
import unittest


class TestLseekTrials(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        p = pathlib.Path(__file__)
        cls.exe = pathlib.Path(p.parents[1] / 'bin' / p.stem[len("test_"):])
    
    def test_run(self):
        result = subprocess.run([self.exe, "tests/data/text.txt"],
                                capture_output=True,
                                text=True)
        print(result.stdout)
        # self.assertEqual(result.stdout,
        #                  "Error while opening tests/data/input1.txt: No such file or directory\n")
    
    def test_bad_input(self):
        result = subprocess.run([self.exe, "tests/data/input1.txt"],
                                capture_output=True,
                                text=True)
        self.assertEqual(result.stderr,
                         "Error while opening tests/data/input1.txt: No such file or directory\n")
    
    def test_bad_arg(self):
        result = subprocess.run([self.exe], capture_output=True, text=True)
        self.assertEqual(result.stderr,
                         "Usage: /home/saurabh/kaam/github/padhaai/the_c_prog_lang/ch08/bin/"
                         "lseek_trials input_file\n")


if __name__ == '__main__':
    unittest.main()
