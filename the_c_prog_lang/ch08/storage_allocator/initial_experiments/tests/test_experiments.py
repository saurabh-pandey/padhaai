import pathlib
import unittest

from . import valgrind

expected_output = """============================================================
 Running sizeof, alignment and memory location experiments
============================================================


  First sizeof
==================
Size of (bytes):
  char        : 1
  int         : 4
  long        : 8
  double      : 8
  max_align_t : 32
  example     : 16
  example1    : 48
  example2    : 32 // This has smaller size than example1!!




  Next alignment and offset
===============================
Alignment requirements (bytes):
  char        : 1
  int         : 4
  long        : 8
  double      : 8
  max_align_t : 16
  example     : 8
  example1    : 8
  example2    : 8


Offset of example struct:
example struct member offset (bytes):
  offsetof(c) : 0 // It starts here
  offsetof(i) : 4 // There is a padding of 3 bytes after char
  offsetof(d) : 8 // No padding needed here

address of struct members:
  &example.c : 0x1ffefffdc0
  &example.i : 0x1ffefffdc4 // Note the padding!
  &example.d : 0x1ffefffdc8

calculated offset of struct members:
  &offset.c : 0
  &offset.i : 4
  &offset.d : 8


Stack Variable addresses:
  &c       = 0x1ffefffdab
  &i       = 0x1ffefffdac
  &l       = 0x1ffefffdb0
  &d       = 0x1ffefffdb8
  &s       = 0x1ffefffdc0

Stack vars alignment check (addr % align == 0):
  char     : 1
  int      : 1
  long     : 1
  double   : 1
  example  : 1


Heap pointer addresses:
  char*    = 0x4a8e080
  int*     = 0x4a8e0d0
  long*    = 0x4a8e120
  double*  = 0x4a8e170 // Note all are 16 byte aligned and 32 bytes apart

Heap vars alignment check:
  char     : 1
  int      : 1
  long     : 1
  double   : 1



  Finally memory addresses
===============================
function        0x109b5a   →  /home/saurabh/kaam/github/padhaai/the_c_prog_lang/ch08/storage_allocator/bin/experiments
global          0x10c010   →  /home/saurabh/kaam/github/padhaai/the_c_prog_lang/ch08/storage_allocator/bin/experiments
static global   0x10c014   →  /home/saurabh/kaam/github/padhaai/the_c_prog_lang/ch08/storage_allocator/bin/experiments
static local    0x10c018   →  /home/saurabh/kaam/github/padhaai/the_c_prog_lang/ch08/storage_allocator/bin/experiments
heap            0x4a8e1c0   →  anonymous
stack           0x1ffefffdcc   →  anonymous

Before malloc Program break        : 0x403c000
After malloc Program break         : 0x403c000
After free Program break           : 0x403c000
After sbrk(1024*100) Program break : 0x4055000 // It changes here!!!
"""

class TestExperiments(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        p = pathlib.Path(__file__)
        cls.exe = pathlib.Path(p.parents[1] / 'bin' / p.stem[len("test_"):])

    def test_run(self):
        self.assertTrue(valgrind.check_valgrind_installed(), "Valgrind not installed")
        stdout, stderr, _ = valgrind.run(self.exe)
        self.assertEqual(valgrind.parse_valgrind_output(stderr), 0)
        print("Len example output = ", len(expected_output.splitlines()))
        print("Len std output = ", len(stdout.splitlines()))
        example_lines = expected_output.splitlines()
        stdout_lines = stdout.splitlines()
        for example_line, stdout_line in zip(example_lines, stdout_lines):
            print("Example line : ", example_line)
            print("stdout line  : ", stdout_line)
            
        # self.assertEqual(expected_output, stdout)
        # for i range(len(ex))


if __name__ == '__main__':
    unittest.main()
