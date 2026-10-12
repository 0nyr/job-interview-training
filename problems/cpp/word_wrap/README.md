# Word wrapping in C++23

Implement `std::string task_01_format_text(const std::string& text, int width)` in `main.cpp`. This is a function implementation problem. The starter throws an exception until you replace its body. No completed implementation is included.

## Contract

Return the input words in their original order, packed greedily into left-aligned lines. Put the next word on the current line whenever it fits, counting the single separating space toward `width`. Otherwise, start a new line with that word.

- Treat the 6 ASCII whitespace characters (space, tab, newline, carriage return, form feed and vertical tab) as word separators. Existing newlines do not force output line breaks.
- Preserve each word's bytes, case and punctuation. Never split a word. A word longer than `width` occupies a line by itself, and the next word starts a new line.
- Use exactly one space between words on a line and one `\n` between lines. Add no leading or trailing spaces or newlines.
- Return `""` for empty or whitespace-only input when `width` is positive.
- Throw `std::invalid_argument` when `width <= 0`, including for empty input.
- Leave the input unchanged. Width counts `std::string` bytes, rather than Unicode display columns. There is no hyphenation or justification.

For example, `"one two three"` at width `7` becomes `"one two\nthree"`. `"elephant cat dog"` at width `7` becomes `"elephant\ncat dog"`. `"one\n two"` at width `7` becomes `"one two"`.

## Run

From the private workspace root, enter its development shell and run:

```bash
nix develop path:./nix-dev
python src/train.py job-interview-training/problems/cpp/word_wrap --examples
python src/train.py job-interview-training/problems/cpp/word_wrap --task 1
python src/train.py job-interview-training/problems/cpp/word_wrap
```

The examples display fixed inputs and expected outputs without calling your function. Initially the example check passes and TASK 1 fails. `--task task_01_format_text` also selects the task. Read `test.cpp` for the individual cases. The task check runs all 27 cases and reports every failed case, with actual output before expected output.

For a standalone native check, run these commands from the public repository root:

```bash
mkdir -p .build
g++ -std=c++23 -Wall -Wextra -Wpedantic -O0 -g problems/cpp/word_wrap/test.cpp -o .build/word-wrap-test
./.build/word-wrap-test 01
```

Keep the `TRAINING_TEST` guard and test expectations intact. Implement the function, then explain the time and extra-space complexity in terms of input length and output length.
