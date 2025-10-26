import pathlib
import subprocess
import unittest

import os

def expected_file_size_map(path):
    expected_map = {}
    for root, _, files in os.walk(path):
        for name in files:
            filepath = os.path.join(root, name)
            if os.path.isfile(filepath):  # avoid broken links, etc.
                sz = os.path.getsize(filepath)
                expected_map[filepath] = sz
    return expected_map

def actual_file_size_map(output: str):
    actual_map = {}
    lines = output.splitlines()
    for line in lines[1:]:
        split_lines = line.split()
        actual_map[split_lines[0]] = int(split_lines[-1])
    return actual_map

class TestFsize(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        p = pathlib.Path(__file__)
        cls.exe = pathlib.Path(p.parents[1] / 'bin' / p.stem[len("test_"):])

    def test_wo_arg(self):
        output = subprocess.run([self.exe],
                                capture_output=True,
                                text=True).stdout
        expected = expected_file_size_map(".")
        actual = actual_file_size_map(output)
        self.assertDictEqual(expected, actual, "File size don't match for the no args test")
    
    def test_wi_arg(self):
        output = subprocess.run([self.exe, "dir_test"],
                                capture_output=True,
                                text=True).stdout
        expected = expected_file_size_map("dir_test")
        actual = actual_file_size_map(output)
        self.assertDictEqual(expected, actual, "File size don't match for the args test")


if __name__ == '__main__':
    unittest.main()
