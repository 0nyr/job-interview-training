# C++23 recall lab

Read `examples()` near the top of `main.cpp`, then run it to refresh C++ syntax and standard-library operations. The commented demonstrations execute independently of the learner functions. Work through TASK 1 to TASK 12 below them. `test.cpp` contains native checks and `test.py` reports each task separately. No completed answer file is included.

## What to do

Each task is named `task_XX_description`, such as `task_03_word_counts`, with its full C++ signature. The preceding comment states `TASK X:` and the objective first. After a blank line, a separate comment explains the placeholder. The starter functions compile but deliberately do not satisfy their task contracts.

For TASK 1, `task_01_unique_ordered({3, 1, 3, 2})` must return `{3, 1, 2}`, preserving first-occurrence order. Its placeholder returns `{1, 2, 3}` because it uses a sorted set. Change the task function, save the file, and run `--task 1`. Do not change the tests' expected answers.

Work on one function at a time: read its TASK comment, run its check, edit the function, and rerun the check. 🟢 means the task's checks pass. 🔴 means they have not passed; the output explains the failed condition or compilation/runtime error.

`--examples` executes demonstrations without validating answers. `test_00_examples_run` is only a check that the examples execute, not a completed practice task. Run without `--examples` to validate your changes.

From the workspace root:

```bash
python src/train.py job-interview-training/refreshers/cpp --examples
python src/train.py job-interview-training/refreshers/cpp --task 1
python src/train.py job-interview-training/refreshers/cpp --task task_03_word_counts
python src/train.py job-interview-training/refreshers/cpp
```

Initially the example test passes and the 12 task tests fail. `--task 0` selects the example smoke check. Numeric selectors, task function names, test method names, and full unittest IDs are supported. Compiler diagnostics include source locations. Keep the `TRAINING_TEST` guard around the normal entry point so the test harness can include the learner functions. Discuss complexity, ownership, and iterator validity as you practice. Code changes stay uncommitted during practice.
