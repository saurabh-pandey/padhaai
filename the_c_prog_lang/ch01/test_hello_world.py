import subprocess

inp = '''This is a long text. With multiple lines. Let's see what happens.
This will be a very interesting way to drive C programs with getchar.
If it works then it is a simple way to test such C code.
Nice!
'''

# print(subprocess.run(['./a.out'], capture_output=True, text=True).stdout)
print(subprocess.run(['./a.out'], capture_output=True, text=True, input=inp).stdout)
