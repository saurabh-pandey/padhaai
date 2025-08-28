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
        # print(result.stdout)
        rows = []
        for line in result.stdout.splitlines():
            line.strip()
            if not line or line.startswith("=") or line.startswith("index"):
                continue
            # print(line)
            parts = line.split()
            if len(parts) == 4:
                idx, offset, bytes_, nread = map(int, parts)
                rows.append((idx, offset, bytes_, nread))
        # print()
        # print(rows)
        here = pathlib.Path(__file__).parent
        data_file = here / "data" / "expected.txt"
        file_rows = []
        with open(data_file) as expected_f:
            # print(expected_f.readlines())
            for line in expected_f.readlines():
                line.strip()
                if not line or line.startswith("=") or line.startswith("index"):
                    continue
                # print(line)
                parts = line.split()
                if len(parts) == 4:
                    idx, offset, bytes_, nread = map(int, parts)
                    file_rows.append((idx, offset, bytes_, nread))
        # print(file_rows)
        self.assertEqual(rows, file_rows)
    
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
