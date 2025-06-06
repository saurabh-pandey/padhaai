import pathlib
import subprocess
import textwrap
import unittest


class TestSimpleSort(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        p = pathlib.Path(__file__)
        cls.exe = pathlib.Path(p.parents[1] / 'bin' / p.stem[len("test_"):])
    
    def test_simple(self):
        arr_inp = textwrap.dedent('''\
            hello
            world
            zoo
            like
            rat
            abc
            vote
            done
        ''')
        output = subprocess.run([self.exe],
                                capture_output=True,
                                text=True,
                                input=arr_inp).stdout
        self.assertEqual(output.splitlines(),
                         ['Input some lines below to sort:',
                          'Sorted output:',
                          'abc', 'done', 'hello', 'like', 'rat', 'vote', 'world', 'zoo'])
    
    def test_case_sensitive(self):
        arr_inp = textwrap.dedent('''\
            hello
            Hello
            World
            world
        ''')
        output = subprocess.run([self.exe],
                                capture_output=True,
                                text=True,
                                input=arr_inp).stdout
        self.assertEqual(output.splitlines(),
                         ['Input some lines below to sort:',
                          'Sorted output:',
                          'Hello', 'World', 'hello', 'world'])
    
    def test_empty(self):
        arr_inp = textwrap.dedent('''
        ''')
        output = subprocess.run([self.exe],
                                capture_output=True,
                                text=True,
                                input=arr_inp).stdout
        self.assertEqual(output.splitlines(),
                         ['Input some lines below to sort:',
                          'Sorted output:',
                          ''])
    
    def test_sentences(self):
        arr_inp = textwrap.dedent('''\
            How are you?
            I am fine.
            Thank you!
            A small sentence.
            Where is the zoo?
            Not sure.
        ''')
        output = subprocess.run([self.exe],
                                capture_output=True,
                                text=True,
                                input=arr_inp).stdout
        self.assertEqual(output.splitlines(),
                         ['Input some lines below to sort:',
                          'Sorted output:',
                          'A small sentence.',
                          'How are you?',
                          'I am fine.',
                          'Not sure.',
                          'Thank you!',
                          'Where is the zoo?'])

if __name__ == '__main__':
    unittest.main()
