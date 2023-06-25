"""
AHCにおいて、全入力に対して実行するスクリプト（並列実行）
実行ファイルは標準エラー出力の最終行にスコアを出力する必要がある
"""

import os
import subprocess
import concurrent.futures
from tqdm import tqdm

input_dir = "tools/in"
exec_command = './a.out'


def process_file(input_file):
    input_path = os.path.join(input_dir, input_file)
    result = subprocess.run([exec_command], stdin=open(input_path, 'r'), capture_output=True, text=True)
    if result.returncode != 0 or result.stderr == "":
        print(f"Error executing {exec_command} for file {input_file}. Return code: {result.returncode}. Standard error: {result.stderr}")
        return None
    score_line = result.stderr.strip().split('\n')[-1]  # Get the last line of the standard error output
    try:
        score = float(score_line)  # Adjust the score calculation method appropriately
        return score
    except ValueError as e:
        print(f"Error converting score to float for file {input_file}. Score line: {score_line}")
        return None


def main():
    input_dir = "tools/in"
    input_files = [f for f in os.listdir(input_dir) if f.endswith(".txt")]

    total_score = 0
    with concurrent.futures.ProcessPoolExecutor() as executor:
        scores = list(tqdm(executor.map(process_file, input_files), total=len(input_files), desc="Processing input files"))
        total_score = sum(score for score in scores if score is not None)

    print(f'Total score: {total_score}')


if __name__ == "__main__":
    main()
