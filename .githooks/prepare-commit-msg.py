import json
import sys

from pathlib import Path
from subprocess import check_output
from typing import Optional, List


base_path = Path(__file__).parent


def check_args() -> bool:
    if len(sys.argv) < 3:
        return False
    if sys.argv[2] != "message":
        return False
    return True

def is_enabled() -> bool:
    config_file_path = (base_path / "../config.json").resolve()
    with open(config_file_path) as config_f:
        config = json.load(config_f)
        print(config)
        if "enablePrepareCommitMsg" in config:
            return config["enablePrepareCommitMsg"]
    return False

def filter_code_files() -> List[str]:
    diff_output = check_output(["git",
                                      "diff",
                                      "--cached",
                                      "--name-only",
                                      "--diff-filter=ACDMR"]).decode()
    # print(changed_files_str)
    diff_output_list = diff_output.split("\n")
    changed_files = []
    for diff_line in diff_output_list:
        # Filter all empty lines
        if len(diff_line) > 0:
            changed_files.append(diff_line)
    return changed_files

def main():
    print(sys.argv)
    if not check_args():
        return 0
    if not is_enabled():
        return 0
    changed_files : List[str] = filter_code_files()
    print(changed_files)
    return 0

main()
