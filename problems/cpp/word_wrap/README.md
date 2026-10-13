# Word wrapping in C++23

Implement `std::string& task_01_format_text_in_place(std::string& text, int width)` in `main.cpp`. Format the caller's string directly and return its reference. The starter throws an exception until you replace its body. No completed implementation is included.

## Contract

Return the input words in their original order, packed greedily into left-aligned lines. Put the next word on the current line whenever it fits, counting the single separating space toward `width`. Otherwise, start a new line with that word.

- Existing newlines are word separators and do not force output line breaks.
- Treat the 6 ASCII whitespace characters (space, tab, newline, carriage return, form feed and vertical tab) as word separators.
- Preserve each word's bytes, case and punctuation. Never split a word. A word longer than `width` occupies a line by itself, and the next word starts a new line.
- Use exactly one space between words on a line and one `\n` between lines. Add no leading or trailing spaces or newlines.
- Return `""` for empty or whitespace-only input when `width` is positive.
- Throw `std::invalid_argument` when `width <= 0`, including for empty input.
- Width counts `std::string` bytes, rather than Unicode display columns. There is no hyphenation or justification.

TASK 1 modifies the supplied string directly and returns a mutable reference to that same string. Use constant auxiliary space, without constructing a second formatted string or storing a collection of words. Reject an invalid width before making any changes. Calling TASK 1 again with the same width must leave the formatted text unchanged.

For example, `"one two three"` at width `7` becomes `"one two\nthree"`. `"elephant cat dog"` at width `7` becomes `"elephant\ncat dog"`. `"one\n two"` at width `7` becomes `"one two"`.

## Run

From the private workspace root, enter its development shell and run:

```bash
nix develop path:./nix-dev
python src/train.py job-interview-training/problems/cpp/word_wrap --examples
python src/train.py job-interview-training/problems/cpp/word_wrap --task 1
python src/train.py job-interview-training/problems/cpp/word_wrap
```

The examples display fixed inputs and expected outputs without calling the learner function. Initially the example check passes and the task fails. `--task task_01_format_text_in_place` also selects the task. Read `test.cpp` for the 28 cases, including reference identity, repeated calls, unchanged text on invalid widths, and preservation of non-ASCII bytes and embedded NUL bytes. The native check reports every failed case, with actual output before expected output. The constant-space requirement needs source review, which these functional tests cannot establish.

For a standalone native check, run these commands from the public repository root:

```bash
mkdir -p .build
g++ -std=c++23 -Wall -Wextra -Wpedantic -O0 -g problems/cpp/word_wrap/test.cpp -o .build/word-wrap-test
./.build/word-wrap-test 01
```

Keep the `TRAINING_TEST` guard and test expectations intact. Implement the function, then explain the time and extra-space complexity in terms of input length and output length.
