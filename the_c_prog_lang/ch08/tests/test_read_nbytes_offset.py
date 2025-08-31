import pathlib
import subprocess
import unittest


class TestReadNbytesOffset(unittest.TestCase):
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
    
    def test_help(self):
        result = subprocess.run([self.exe, "-h"], capture_output=True, text=True)
        self.assertEqual(result.stdout.splitlines(),
                         ['Usage: /home/saurabh/kaam/github/padhaai/the_c_prog_lang/ch08/bin/'
                          'read_nbytes_offset [-h] [-v] [-f file] [-n nbytes] [-o offset]',
                          '  -h  Help',
                          '  -v  Enable SEEK_DATA version (Default SEEK_SET)',
                          '  -f  File to seek',
                          '  -n  Maximum number of bytes to be read. Must be positive number',
                          '  -o  Offset from where to start reading. Must be non-negative',
                          '',
                          'Example: /home/saurabh/kaam/github/padhaai/the_c_prog_lang/ch08/bin/'
                          'read_nbytes_offset -v -f some_file.txt -n 16 -o 10',
                          ''])

    # def test_run(self):
        # result = subprocess.run([self.exe, "tests/data/text.txt"],
        #                         capture_output=True,
        #                         text=True)
        # output_rows = TestLseekTrials._parse_rows(result.stdout.splitlines())
        # # Test if output is not empty
        # self.assertTrue(output_rows)
        
        # # Fetch expected output
        # parent_path = pathlib.Path(__file__).parent
        # data_file_path = parent_path / "data" / "expected.txt"
        # expected_rows = []
        # with open(data_file_path) as expected_f:
        #     expected_rows = TestLseekTrials._parse_rows(expected_f.readlines())
        # self.assertEqual(output_rows, expected_rows)
    

    # def test_bad_input(self):
    #     result = subprocess.run([self.exe, "tests/data/input1.txt"],
    #                             capture_output=True,
    #                             text=True)
    #     self.assertEqual(result.stderr,
    #                      "Error while opening tests/data/input1.txt: No such file or directory\n")
    
    
    def test_no_arg(self):
        result = subprocess.run([self.exe], capture_output=True, text=True)
        self.assertEqual(result.stderr.splitlines(),
                         ['',
                          'ERROR: Please provide an input file using "-f some_file" option',
                          '',
                          'Usage: /home/saurabh/kaam/github/padhaai/the_c_prog_lang/ch08/bin/'
                          'read_nbytes_offset [-h] [-v] [-f file] [-n nbytes] [-o offset]',
                          '  -h  Help',
                          '  -v  Enable SEEK_DATA version (Default SEEK_SET)',
                          '  -f  File to seek',
                          '  -n  Maximum number of bytes to be read. Must be positive number',
                          '  -o  Offset from where to start reading. Must be non-negative',
                          '',
                          'Example: /home/saurabh/kaam/github/padhaai/the_c_prog_lang/ch08/bin/'
                          'read_nbytes_offset -v -f some_file.txt -n 16 -o 10',
                          ''])
    
    def test_no_nbytes_arg(self):
        result = subprocess.run([self.exe, "-f some_file"], capture_output=True, text=True)
        self.assertEqual(result.stderr.splitlines(),
                         ['',
                          'ERROR: nbytes is a compulsory parameter',
                          '',
                          'Usage: /home/saurabh/kaam/github/padhaai/the_c_prog_lang/ch08/bin/'
                          'read_nbytes_offset [-h] [-v] [-f file] [-n nbytes] [-o offset]',
                          '  -h  Help',
                          '  -v  Enable SEEK_DATA version (Default SEEK_SET)',
                          '  -f  File to seek',
                          '  -n  Maximum number of bytes to be read. Must be positive number',
                          '  -o  Offset from where to start reading. Must be non-negative',
                          '',
                          'Example: /home/saurabh/kaam/github/padhaai/the_c_prog_lang/ch08/bin/'
                          'read_nbytes_offset -v -f some_file.txt -n 16 -o 10',
                          ''])
    
    def test_zero_nbytes_arg(self):
        result = subprocess.run([self.exe, "-f some_file", "-n 0"], capture_output=True, text=True)
        self.assertEqual(result.stderr.splitlines(),
                         ['',
                          'ERROR: nbytes has to be a positive number',
                          '',
                          'Usage: /home/saurabh/kaam/github/padhaai/the_c_prog_lang/ch08/bin/'
                          'read_nbytes_offset [-h] [-v] [-f file] [-n nbytes] [-o offset]',
                          '  -h  Help',
                          '  -v  Enable SEEK_DATA version (Default SEEK_SET)',
                          '  -f  File to seek',
                          '  -n  Maximum number of bytes to be read. Must be positive number',
                          '  -o  Offset from where to start reading. Must be non-negative',
                          '',
                          'Example: /home/saurabh/kaam/github/padhaai/the_c_prog_lang/ch08/bin/'
                          'read_nbytes_offset -v -f some_file.txt -n 16 -o 10',
                          ''])
    
    def test_no_offset_arg(self):
        result = subprocess.run([self.exe, "-f some_file", "-n 10"], capture_output=True, text=True)
        self.assertEqual(result.stderr.splitlines(),
                         ['',
                          'ERROR: Offset must be non-negative',
                          '',
                          'Usage: /home/saurabh/kaam/github/padhaai/the_c_prog_lang/ch08/bin/'
                          'read_nbytes_offset [-h] [-v] [-f file] [-n nbytes] [-o offset]',
                          '  -h  Help',
                          '  -v  Enable SEEK_DATA version (Default SEEK_SET)',
                          '  -f  File to seek',
                          '  -n  Maximum number of bytes to be read. Must be positive number',
                          '  -o  Offset from where to start reading. Must be non-negative',
                          '',
                          'Example: /home/saurabh/kaam/github/padhaai/the_c_prog_lang/ch08/bin/'
                          'read_nbytes_offset -v -f some_file.txt -n 16 -o 10',
                          ''])


if __name__ == '__main__':
    unittest.main()
