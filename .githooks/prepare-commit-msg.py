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

def construct_prefix(changed_files: List[str], config: dict) -> tuple:
    prefixes = ["", "", ""]
    for f in changed_files:
        path_parts = f.split('/')
        if len(path_parts) == 1:
            prefixes[0] = "PADHAAI"
        elif len(path_parts) == 2:
            if path_parts[0] in config["commitPrefix"]:
                prefixes[1] = config["commitPrefix"][path_parts[0]]
            else:
                prefixes[0] = "PADHAAI"
        else:
            if path_parts[0] in config["commitPrefix"]:
                prefixes[2] = config["commitPrefix"][path_parts[0]] + "-" + path_parts[1].upper()
            else:
                prefixes[0] = "PADHAAI"
    return tuple(prefixes)

def update_commit_message(commit_prefix):
    commit_msg_filepath = sys.argv[1]
    with open(commit_msg_filepath, 'r+') as f:
        content = f.read()
        f.seek(0, 0)
        f.write(f"{commit_prefix}: {content}")


# Main
def main():
    if not check_args():
        return 0
    config_file_path = (base_path / "../config.json").resolve()
    if not config_file_path.is_file():
        return 0
    with open(config_file_path) as config_f:
        config = json.load(config_f)
        if not is_enabled(config):
            return 0
        changed_files : List[str] = filter_code_files()
        prefixes = construct_prefix(changed_files, config)
        for prefix in prefixes:
            if len(prefix) > 0:
                update_commit_message(prefix)
                break
    return 0

main()
