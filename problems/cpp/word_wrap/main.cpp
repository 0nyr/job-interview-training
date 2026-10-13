// C++23 word-wrapping problem. Implement TASK 1, then run their tests.
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

// TASK 1: Format text directly into greedy, left-aligned lines of at most width bytes, and return a std::string& referring to that same caller-owned string. Treat exactly the 6 ASCII whitespace characters (space, tab, newline, carriage return, form feed and vertical tab) as word separators, including existing line breaks. Preserve every word's bytes and order. Use one space between words on a line and one '\n' between lines, with no leading or trailing whitespace. Never split a word: an overlong word occupies its own line. Empty or whitespace-only text becomes an empty string. Throw std::invalid_argument for width <= 0 before changing text, even for empty input. Use constant auxiliary space without a second formatted string or a collection of words. Reformatting with the same width must leave the result unchanged. Width counts bytes, not Unicode display columns.

// The function is unimplemented. Replace the exception with your in-place implementation and add any headers you need.
std::string& task_01_format_text_in_place(std::string& text, int width) {
    (void)text;
    (void)width;
    throw std::logic_error("TASK 1 is not implemented");
}

#ifndef TRAINING_TEST
int main() {
    examples();
}
#endif
