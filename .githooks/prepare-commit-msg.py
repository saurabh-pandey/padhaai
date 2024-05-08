import json
import sys

from pathlib import Path
from subprocess import check_output
from typing import Optional, List, Any


# Global varibles
base_path = Path(__file__).parent


# Helper functions
def check_args() -> bool:
    if len(sys.argv) < 3:
        return False
    if sys.argv[2] != "message":
        return False
    return True

def is_enabled(config: dict) -> bool:
    if config and "enablePrepareCommitMsg" in config:
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

def construct_prefix(changed_files: List[str], config: dict) -> str:
    for f in changed_files:
        path_parts = f.split('/')
        if len(path_parts) == 1:
            return "PADHAAI"
        elif len(path_parts) == 2:
            if path_parts[0] in config["commitPrefix"]:
                return config["commitPrefix"][path_parts[0]]
        else:
            if path_parts[0] in config["commitPrefix"]:
                return config["commitPrefix"][path_parts[0]] + "-" + path_parts[1].upper()
    return ""

# Main
def main():
    print(sys.argv)
    if not check_args():
        return 0
    config_file_path = (base_path / "../config.json").resolve()
    if config_file_path.is_file():
        return 0
    with open(config_file_path) as config_f:
        config = json.load(config_f)
        if not is_enabled(config.data()):
            return 0
        changed_files : List[str] = filter_code_files()
        print(changed_files)
        print(construct_prefix(changed_files))
    return 0

main()
