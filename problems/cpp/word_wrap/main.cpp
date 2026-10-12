// C++23 word-wrapping problem. Implement TASK 1, then run its tests.
#include <iostream>
#include <stdexcept>
#include <string>

void examples() {
    // These fixed examples illustrate the contract without calling the task.
    std::cout << "Input: one two three, width: 7\n"
              << "Expected text:\none two\nthree\n\n";
    // An indivisible word can exceed the width. The next word starts a new line.
    std::cout << "Input: elephant cat, width: 4\n"
              << "Expected text:\nelephant\ncat\n"
              << "Examples completed\n";
}

// TASK 1: Format text into greedy, left-aligned lines of at most width characters. Treat ASCII whitespace (space, tab, newline, carriage return, form feed and vertical tab) as word separators and preserve every word's bytes and order. Use one space between words on a line and one '\n' between lines. Never split a word: an overlong word occupies its own line. Return an empty string for empty or whitespace-only text. Add no leading or trailing whitespace. Throw std::invalid_argument for width <= 0, even for empty text. Width counts bytes, not Unicode display columns. Leave the input unchanged.

// The function is unimplemented. Replace the exception with your implementation and add any headers you need.
std::string task_01_format_text(const std::string& text, int width) {
    (void)text;
    (void)width;
    throw std::logic_error("TASK 1 is not implemented");
}

#ifndef TRAINING_TEST
int main() {
    examples();
}
#endif
