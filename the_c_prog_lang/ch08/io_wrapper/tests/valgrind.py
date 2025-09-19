import shutil
import subprocess
import re

def check_valgrind_installed():
    return False if shutil.which("valgrind") is None else True

def parse_valgrind_output(output):
    match = re.search(r"definitely lost:\s+(\d+)\s+bytes", output)
    if match:
        lost_bytes = int(match.group(1))
        return lost_bytes
    match = re.search(r"All heap blocks were freed -- no leaks are possible", output)
    if match:
        return 0

def run(exe, input="", args=[]):
    cmd = ["valgrind", "--leak-check=full", exe, *args]

    try:
        result = subprocess.run(cmd, capture_output=True, text=True, input=input, timeout=30)
        return result.stdout, result.stderr, result.returncode
    except subprocess.TimeoutExpired:
        print("❌ Valgrind test timed out.")

