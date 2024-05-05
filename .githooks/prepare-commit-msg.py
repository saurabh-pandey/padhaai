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

def is_disabled() -> bool:
    config_file_path = (base_path / "../config.json").resolve()
    with open(config_file_path) as config_f:
        config = json.load(config_f)
        print(config)
        if "enablePrepareCommitMsg" in config:
            return config["enablePrepareCommitMsg"]
    return False


def main():
    print(sys.argv)
    if not check_args():
        return 0
    if is_disabled():
        return 0
    return 0

main()
