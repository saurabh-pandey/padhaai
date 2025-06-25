import pathlib
import subprocess
import textwrap
import unittest


class TestCountKeywords(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        p = pathlib.Path(__file__)
        cls.exe = pathlib.Path(p.parents[1] / 'bin' / p.stem[len("test_"):])
    
    def check_keywords_count(self, expected, output):
        lines = output.splitlines()
        self.assertEqual(lines[0], 'Count all keyword occurrences')
        self.assertEqual(lines[1], 'Word       Count')
        for line in lines[2:]:
            words = line.split()
            print(words)
            if (words[0] in expected):
                # print("Found keyword", words[0])
                if expected[words[0]] != int(words[1]):
                    print("Found mismatch 1")
            elif len(words) == 2 and int(words[1]) != 0:
                print("Found mismatch 0")
                
    
    def test_simple(self):
        arr_inp = textwrap.dedent('''\
            Hello World
            auto
        ''')
        output = subprocess.run([self.exe], capture_output=True, text=True, input=arr_inp).stdout
        self.check_keywords_count({'auto': 1}, output)
        # self.assertEqual(output.splitlines(), ['This is a cat.', 'This also has cat.'])
    
    # def test_simple_except(self):
    #     arr_inp = textwrap.dedent('''\
    #         Hi!
    #         This is a cat.
    #         What about this line?
    #         Cat is here but.
    #         This also has cat.
    #         CAT is an exam.
    #         Not in this line.
    #     ''')
    #     output = subprocess.run([self.exe, "-x", "cat"],
    #                             capture_output=True,
    #                             text=True,
    #                             input=arr_inp).stdout
    #     self.assertEqual(output.splitlines(),
    #                      ['Hi!', 'What about this line?', 'Cat is here but.', 'CAT is an exam.', 
    #                       'Not in this line.'])
    
    # def test_simple_line_num(self):
    #     arr_inp = textwrap.dedent('''\
    #         Hi!
    #         This is a cat.
    #         What about this line?
    #         Cat is here but.
    #         This also has cat.
    #         CAT is an exam.
    #         Not in this line.
    #     ''')
    #     output = subprocess.run([self.exe, "-n", "cat"],
    #                             capture_output=True,
    #                             text=True,
    #                             input=arr_inp).stdout
    #     self.assertEqual(output.splitlines(), ['2: This is a cat.', '5: This also has cat.'])
    
    # def test_simple_except_line_num(self):
    #     arr_inp = textwrap.dedent('''\
    #         Hi!
    #         This is a cat.
    #         What about this line?
    #         Cat is here but.
    #         This also has cat.
    #         CAT is an exam.
    #         Not in this line.
    #     ''')
    #     output = subprocess.run([self.exe, "-nx", "cat"],
    #                             capture_output=True,
    #                             text=True,
    #                             input=arr_inp).stdout
    #     self.assertEqual(output.splitlines(),
    #                      ['1: Hi!', '3: What about this line?', '4: Cat is here but.',
    #                       '6: CAT is an exam.', '7: Not in this line.'])
    
    # def test_simple_separate_except_line_num(self):
    #     arr_inp = textwrap.dedent('''\
    #         Hi!
    #         This is a cat.
    #         What about this line?
    #         Cat is here but.
    #         This also has cat.
    #         CAT is an exam.
    #         Not in this line.
    #     ''')
    #     output = subprocess.run([self.exe, "-n", "-x", "cat"],
    #                             capture_output=True,
    #                             text=True,
    #                             input=arr_inp).stdout
    #     self.assertEqual(output.splitlines(),
    #                      ['1: Hi!', '3: What about this line?', '4: Cat is here but.',
    #                       '6: CAT is an exam.', '7: Not in this line.'])
    
    # def test_simple_separate_except_line_num(self):
    #     arr_inp = textwrap.dedent('''
    #     ''')
    #     output = subprocess.run([self.exe, "cat"],
    #                             capture_output=True,
    #                             text=True,
    #                             input=arr_inp).stdout
    #     self.assertEqual(output.splitlines(), [])


if __name__ == '__main__':
    unittest.main()
