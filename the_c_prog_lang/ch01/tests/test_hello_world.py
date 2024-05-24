import subprocess
# import logging
# import sys

inp1 = '''This is a long text. With multiple lines. Let's see what happens.
This will be a very interesting way to drive C programs with getchar.
If it works then it is a simple way to test such C code.
Nice!
'''

inp2 = '''abc
def
'''

# This one is without input just to capture the output
# print(subprocess.run(['./a.out'], capture_output=True, text=True).stdout)

# This one is with input and capture the output
# print(subprocess.run(['./a.out'], capture_output=True, text=True, input=inp).stdout)

import unittest

class TestHelloWorld(unittest.TestCase):

    def test_upper(self):
        # log= logging.getLogger( "TestHelloWorld.test_upper" )
        # run_output = subprocess.run(['./a.out'], capture_output=True, text=True, input=inp1).stdout
        # log.debug("\n\nRun output = %s\n", run_output)
        print(subprocess.run(['./a.out'], capture_output=True, text=True, input=inp1).stdout)

    def test_isupper(self):
        print(subprocess.run(['./a.out'], capture_output=True, text=True, input=inp2).stdout)
    
    def test_empty(self):
        print(subprocess.run(['./a.out'], capture_output=True, text=True, input="").stdout)


if __name__ == '__main__':
    # logging.basicConfig( stream=sys.stderr )
    # logging.getLogger( "SomeTest.testSomething" ).setLevel(logging.DEBUG )
    unittest.main()
