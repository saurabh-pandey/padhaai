Contains all the stuffs done for the book:
The C Programming Language by K & R

Use the following for compilation:
gcc -Wall -Wextra -pedantic -Werror <source_file_name>.c

In order to run test:
1. Goto the chapter folder. E.g. ch01
2. Run tests using python -m unittest
3. In order to run a specific test run: python -m unittest tests/test_<test_name>.py

NOTE
1. In order to pass file as input to programs that use getchar() use: ./a.out < input.txt
2. If providing input from terminal to programs that use getchar() CTRL+d acts as EOF

TODO
1. Add a git hook to automatically append the book's initials and chapter no to commit message.
2. Explore how to test these programs
