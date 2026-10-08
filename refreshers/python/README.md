# Python recall lab

Read `examples()` at the top of `main.py`, then run it to refresh your Python syntax. Each example has an introductory comment and executes independently of the tasks. Work through TASK 1 to TASK 12 below it. No completed answer file is included.

## What to do

Each task function is named `task_XX_description`, such as `task_03_word_counts`. Its docstring states the objective first. After a blank line, it explains the current placeholder and the behavior to change. The starter bodies execute, but deliberately fail the task contracts.

For TASK 1, `task_01_unique_ordered([3, 1, 3, 2])` must return `[3, 1, 2]`, preserving the first occurrence of each value. The placeholder returns `[1, 2, 3]` because it sorts the distinct values. Modify the function, then run `--task 1` to check it. Do not change the test's expected answer.

1. Read a task's objective and placeholder explanation.
2. Run `--task X`, replacing `X` with its number, to see a failing example.
3. Edit that task function in `main.py`, save it, and rerun the check.
4. When it shows 🟢, proceed to the next task. 🔴 means the checks have not passed. Read the accompanying failure or error.

`--examples` runs the independent examples without checking your answers. Run without that flag to validate all tasks, or select one with `--task X`. In assertion messages, the actual result appears before the expected result.

From the workspace root:

```bash
python src/train.py job-interview-training/refreshers/python --examples
python src/train.py job-interview-training/refreshers/python --task 1
python src/train.py job-interview-training/refreshers/python --task 3
python src/train.py job-interview-training/refreshers/python
```

Function names such as `--task task_03_word_counts`, test method names such as `--task test_03_word_counts`, and full unittest IDs are also accepted. `--task 0` selects `test_00_examples_run`, which checks that the examples run independently of the task implementations. It is not a practice task.

Initially the example check passes and all 12 task tests fail. Read the corresponding checks in `test.py` when the contract is unclear. Work in short groups of tasks, explain the time and memory complexity, and record which operations required a hint. Keep practice changes uncommitted and review the diff before deliberately restoring a file for another attempt.
