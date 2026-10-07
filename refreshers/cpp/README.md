# C++23 recall lab

Open `main.cpp`, run the examples, then work through TASK 01 to TASK 12. Each function starts with executable code demonstrating a related feature. Modify it to satisfy the requested behavior. `test.cpp` contains native function checks and `test.py` exposes them as separately reported tasks. No completed answer file is included.

From the workspace root:

```bash
python src/train.py job-interview-training/refreshers/cpp --run
python src/train.py job-interview-training/refreshers/cpp --task test_01_unique_ordered
python src/train.py job-interview-training/refreshers/cpp
```

Initially the example test passes and the 12 task tests fail. Compiler diagnostics include source locations. Keep the `TRAINING_TEST` guard around the normal entry point so the test harness can include the learner functions. Discuss complexity, ownership, and iterator validity as you practice. Code changes stay uncommitted during practice.
