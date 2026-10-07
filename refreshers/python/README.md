# Python recall lab

Open `main.py`, run the examples, then work through TASK 01 to TASK 12. Each function initially demonstrates a nearby language feature; change it to meet the requested contract. Read the corresponding checks in `test.py` when the required behavior is unclear. No completed answer file is included.

## What to do

The functions contain runnable code, but their starting behavior deliberately does not satisfy the TASK comments. Your job is to change that behavior. A function having a body does not mean the task is completed.

For TASK 01, `unique_ordered([3, 1, 3, 2])` currently returns `[1, 2, 3]` because it sorts the distinct values. The task requires `[3, 1, 2]`: keep the first occurrence of each value in its original order. Change the body of `unique_ordered` to achieve that, then run its named test. Do not change the test's expected answer.

For TASK 02, the starting dictionary comprehension keeps the last event seen for each user. The requested behavior is to keep the largest timestamp, even when events arrive out of order. These coincide for some inputs, but not all. Each task's tests include cases that expose the difference.

1. Read one TASK comment and compare its requested behavior with the existing function.
2. Run the named task check to see a failing example.
3. Edit only that function in `main.py`, save it, and rerun the check.
4. When it shows 🟢, proceed to the next task. 🔴 means the checks have not passed; read the accompanying failure or error.

`--run` only runs demonstrations. It does not validate your answers. `test_00_examples_run` only checks that the examples execute successfully; it is not a completed practice task. Use the test command without `--run` to validate your changes. In the assertion messages, the function's actual result appears before the expected result.

From the workspace root:

```bash
python src/train.py job-interview-training/refreshers/python --run
python src/train.py job-interview-training/refreshers/python --task test_01_unique_ordered
python src/train.py job-interview-training/refreshers/python
```

Initially the example test passes and the 12 task tests fail. Work in short groups of tasks, explain the time and memory complexity, and record which operations required a hint. Code changes stay uncommitted during practice. Review the diff before deliberately restoring a file for another attempt.
