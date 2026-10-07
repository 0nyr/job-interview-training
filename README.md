# Job interview training

Reusable Python 3.13 and C++23 exercises for refreshing language fluency. Each refresher combines runnable examples with numbered modification prompts. The examples work immediately; the corresponding task tests initially fail until the requested modifications are completed.

## Exercises

- `refreshers/python/`: 12 tasks covering Python containers, iteration, sorting, heaps, binary search, BFS, generators, and mutation.
- `refreshers/cpp/`: 12 tasks covering C++ containers, algorithms, ranges, heaps, binary search, BFS, references, optional values, and lambda state, with ownership examples.
- `vim/python/` and `vim/cpp/`: small greeting exercises for practicing editor commands.
- `vim/rust/`: original Rust Vim exercise, runnable manually. Rust is not supported by the workspace runner yet.

Edit each directory's `main.py` or `main.cpp`. Keep practice edits uncommitted to preserve reusable starting points. Only commit deliberate improvements to the exercise material.

## Exercise contract

Each directory has exactly one learner file, `main.py` or `main.cpp`, plus `test.py` containing standard-library unittest cases. Use descriptive method names such as `test_01_unique_ordered`. Each method represents one task and may check several edge cases. Tests must be independent, since the runner executes each method in a fresh process.

Python function tests import `main`. Console tests execute `main.py` with `sys.executable` and use `subprocess.run` to supply input and inspect output. Keep the learner's demonstration entry point under `if __name__ == "__main__"` so importing functions does not run it.

For C++, `test.py` executes the absolute path in `TRAINING_MAIN_BINARY` for console tests. Function exercises can add a `test.cpp` harness, compiled separately. The harness defines `TRAINING_TEST` before including `main.cpp`, whose normal entry point is guarded by `#ifndef TRAINING_TEST`. The harness accepts a task identifier, exits with `0` on success, and writes diagnostics and exits nonzero on failure. `test.py` calls it using `TRAINING_TEST_BINARY`. Do not compile the learner file separately into the harness as well: it is already included.

The runner supplies these environment variables after building executables. It sets the working directory to the exercise directory. Standard files need no external dependencies. Example subprocess calls use a 5-second timeout; increase those local limits as well as the runner timeout when authoring a legitimately longer task.

## Run without the private workspace

Python:

```bash
cd refreshers/python
python3 main.py
python3 -m unittest -v test
python3 -m unittest -v test.Tasks.test_01_unique_ordered
```

C++ (from this repository's root):

```bash
mkdir -p .build
g++ -std=c++23 -Wall -Wextra -Wpedantic -O0 -g refreshers/cpp/main.cpp -o .build/cpp-main
g++ -std=c++23 -Wall -Wextra -Wpedantic -O0 -g refreshers/cpp/test.cpp -o .build/cpp-test
./.build/cpp-main
./.build/cpp-test 01
TRAINING_MAIN_BINARY="$PWD/.build/cpp-main" TRAINING_TEST_BINARY="$PWD/.build/cpp-test" python3 -m unittest discover -s refreshers/cpp -p test.py -v
```

In the parent workspace, enter its Nix shell and use `python src/train.py job-interview-training/refreshers/python` or the corresponding C++ directory. Add `--run` to execute examples, or `--task test_01_unique_ordered` to check a single task. The Nix shell lives in the parent workspace, not this public repository.
