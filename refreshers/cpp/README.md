# C++23 recall lab

Open `main.cpp`, run the examples, then work through TASK 01 to TASK 12. Each function starts with executable code demonstrating a related feature. Modify it to satisfy the requested behavior. `test.cpp` contains native function checks and `test.py` exposes them as separately reported tasks. No completed answer file is included.

## What to do

The starting functions compile, but deliberately do not meet the TASK comments. Change each function's behavior to satisfy its task. A function having an implementation does not mean the exercise is completed.

For TASK 01, `unique_ordered({3, 1, 3, 2})` currently returns `{1, 2, 3}` because `std::set` stores values in sorted order. The task requires `{3, 1, 2}`, preserving the order of first occurrences. Modify `unique_ordered`, save `main.cpp`, and run the named check. Do not modify the expected answers in the tests.

Work on one function at a time: read its TASK comment, run its check, edit the function, and rerun the check. 🟢 means the task's checks pass. 🔴 means they have not passed; the output explains the failed condition or compilation/runtime error.

`--run` executes demonstrations without validating answers. `test_00_examples_run` is only a check that the examples execute, not a completed practice task. Run without `--run` to validate your changes.

From the workspace root:

```bash
python src/train.py job-interview-training/refreshers/cpp --run
python src/train.py job-interview-training/refreshers/cpp --task test_01_unique_ordered
python src/train.py job-interview-training/refreshers/cpp
```

Initially the example test passes and the 12 task tests fail. Compiler diagnostics include source locations. Keep the `TRAINING_TEST` guard around the normal entry point so the test harness can include the learner functions. Discuss complexity, ownership, and iterator validity as you practice. Code changes stay uncommitted during practice.
