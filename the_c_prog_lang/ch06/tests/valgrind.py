import shutil
import subprocess
import sys
import re
# import textwrap

def check_valgrind_installed():
    if shutil.which("valgrind") is None:
        print("❌ Valgrind is not installed. Aborting test.")
        sys.exit(1)
    print("✅ Valgrind found.")

def run(exe_path, input, args=[]):
    cmd = [
        "valgrind",
        "--leak-check=full",
        # "--error-exitcode=1",  # Fail if any errors are found
        # "--log-fd=1",          # Output directly to stdout
        # "--track-origins=yes",
        exe_path,
        *args
    ]
    # if args:
    #     cmd += args

    try:
        # cmd = ["valgrind", "--leak-check=full", "/home/saurabh/kaam/github/padhaai/the_c_prog_lang/ch06/bin/word_count"]
        # print("Valgrind command = ", cmd)
        # input = textwrap.dedent('''\
        #     this is a multiple line example and this is the first line
        #     another sentence that makes it two line
        #     this is the third line now what next
        #     now i have added a fourth line to see if it works
        #     finally a fifth line to finish things
        # ''')
        result = subprocess.run(
            cmd,
            capture_output=True,
            text=True,
            input=input,
            # stdout=subprocess.PIPE,
            # stderr=subprocess.STDOUT,
            # env={"PYTHONMALLOC": "malloc", **dict(**dict(os.environ))},  # optional
            timeout=30  # prevent hanging forever
        )
        return result.stdout, result.stderr, result.returncode
    except subprocess.TimeoutExpired:
        print("❌ Valgrind test timed out.")
        sys.exit(1)

def parse_valgrind_output(output):
    # Look for line: "definitely lost: X bytes in Y blocks"
    match = re.search(r"definitely lost:\s+(\d+)\s+bytes", output)
    if match:
        lost_bytes = int(match.group(1))
        return lost_bytes
    match = re.search(r"All heap blocks were freed -- no leaks are possible", output)
    if match:
        return 0

def main():
    exe_path = "/home/saurabh/kaam/github/padhaai/the_c_prog_lang/ch06/bin/word_count < ~/inp.txt"  # Replace with actual path

    check_valgrind_installed()
    stdout, stderr, retcode = run(exe_path, "abc def")

    print("🧪 Valgrind Output:\n", stdout)
    print("🧪 Valgrind Error:\n", stderr)

    lost_bytes = parse_valgrind_output(stderr)
    if lost_bytes == -1:
        print("⚠️ Could not parse Valgrind output. Possibly malformed?")
        sys.exit(2)
    elif lost_bytes > 0:
        print(f"❌ Memory leak detected: {lost_bytes} bytes definitely lost.")
        sys.exit(1)
    else:
        print("✅ No memory leaks detected.")

if __name__ == "__main__":
    import os
    main()
