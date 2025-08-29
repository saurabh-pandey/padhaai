import pathlib
import subprocess
import unittest


class TestLseekTrials(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        p = pathlib.Path(__file__)
        cls.exe = pathlib.Path(p.parents[1] / 'bin' / p.stem[len("test_"):])
    

    @staticmethod
    def _parse_rows(lines):
        rows = []
        for line in lines:
            line.strip()
            if not line or line.startswith("=") or line.startswith("index"):
                continue
            parts = line.split()
            if len(parts) == 4:
                idx, offset, bytes_, nread = map(int, parts)
                rows.append((idx, offset, bytes_, nread))
        return rows
    

    def test_run(self):
        result = subprocess.run([self.exe, "tests/data/text.txt"],
                                capture_output=True,
                                text=True)
        output_rows = TestLseekTrials._parse_rows(result.stdout.splitlines())
        # Test if output is not empty
        self.assertTrue(output_rows)
        
        # Fetch expected output
        parent_path = pathlib.Path(__file__).parent
        data_file_path = parent_path / "data" / "expected.txt"
        expected_rows = []
        with open(data_file_path) as expected_f:
            expected_rows = TestLseekTrials._parse_rows(expected_f.readlines())
        self.assertEqual(output_rows, expected_rows)
    

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
