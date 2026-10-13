#define TRAINING_TEST
#include "main.cpp"
#include <iomanip>
#include <iostream>
#include <limits>
#include <memory>
#include <sstream>
#include <type_traits>
#include <utility>
#include <vector>

static_assert(std::is_same_v<decltype(task_01_format_text_in_place(std::declval<std::string&>(), 1)), std::string&>,
              "TASK 1 must return a mutable std::string reference");

struct Case {
    const char* name;
    std::string text;
    int width;
    std::string expected;
    bool invalid_width = false;
};

std::string display(const std::string& text) {
    std::string escaped;
    for (char character : text) {
        switch (character) {
        case '\n': escaped += "\\n"; break;
        case '\r': escaped += "\\r"; break;
        case '\t': escaped += "\\t"; break;
        case '\f': escaped += "\\f"; break;
        case '\v': escaped += "\\v"; break;
        default:
            const auto byte = static_cast<unsigned char>(character);
            if (byte < 32 || byte >= 127) {
                constexpr char digits[] = "0123456789ABCDEF";
                escaped += "\\x";
                escaped += digits[byte >> 4];
                escaped += digits[byte & 15];
            } else {
                escaped += character;
            }
        }
    }
    std::ostringstream output;
    output << std::quoted(escaped);
    return output.str();
}

int run_task() {
    const std::vector<Case> cases{
        {"empty text", "", 8, ""},
        {"whitespace only", " \t\r\n\f\v ", 8, ""},
        {"single short word", "cat", 8, "cat"},
        {"single word exactly fits", "hello", 5, "hello"},
        {"single overlong word", "elephant", 4, "elephant"},
        {"line exactly fits", "one two", 7, "one two"},
        {"one space exceeds width", "one two", 6, "one\ntwo"},
        {"greedy multi-line packing", "one two three four five", 9, "one two\nthree\nfour five"},
        {"next word exactly fills line", "a bb ccc dddd", 8, "a bb ccc\ndddd"},
        {"all words fit", "one two three", 30, "one two three"},
        {"leading and trailing spaces", "   one two   ", 7, "one two"},
        {"repeated spaces", "one    two  three", 7, "one two\nthree"},
        {"all ASCII separators", " one\ttwo\nthree\rfour\ffive\vsix ", 9, "one two\nthree\nfour five\nsix"},
        {"existing line breaks normalized", "one\n\n two\r\nthree", 20, "one two three"},
        {"overlong first word", "elephant cat dog", 7, "elephant\ncat dog"},
        {"overlong middle word", "a bb elephant c dd", 4, "a bb\nelephant\nc dd"},
        {"overlong last word", "cat dog elephant", 7, "cat dog\nelephant"},
        {"consecutive overlong words", "elephant giraffe cat", 3, "elephant\ngiraffe\ncat"},
        {"word at width followed by a word", "abcd e", 4, "abcd\ne"},
        {"width one", "a b cc d", 1, "a\nb\ncc\nd"},
        {"punctuation and case preserved", "Hello, C++! Keep-case.", 11, "Hello, C++!\nKeep-case."},
        {"non-ASCII bytes and embedded NUL preserved", std::string("\x80\xA0\xFF x\0y", 7), 3,
         std::string("\x80\xA0\xFF\nx\0y", 7)},
        {"maximum width", "one two", std::numeric_limits<int>::max(), "one two"},
        {"zero width", "one two", 0, "", true},
        {"negative width", "one two", -3, "", true},
        {"empty text with zero width", "", 0, "", true},
        {"whitespace with negative width", " \t\n", -1, "", true},
        {"minimum width", "a", std::numeric_limits<int>::min(), "", true},
    };

    int failures = 0;
    for (const auto& item : cases) {
        auto input = item.text;
        bool passed = false;
        try {
            const auto* actual = std::addressof(task_01_format_text_in_place(input, item.width));
            if (actual != std::addressof(input)) {
                std::cerr << "FAIL " << item.name << ": returned reference must refer to the caller's string\n";
            } else if (item.invalid_width) {
                std::cerr << "FAIL " << item.name << ": expected std::invalid_argument\n";
            } else if (*actual != item.expected) {
                std::cerr << "FAIL " << item.name << ": actual " << display(*actual)
                          << ", expected " << display(item.expected) << '\n';
            } else {
                passed = true;
                auto& repeated = task_01_format_text_in_place(input, item.width);
                if (std::addressof(repeated) != std::addressof(input) || input != item.expected) {
                    passed = false;
                    std::cerr << "FAIL " << item.name << ": repeated formatting must preserve text and reference identity\n";
                }
            }
        } catch (const std::invalid_argument& error) {
            passed = item.invalid_width;
            if (!passed) {
                std::cerr << "FAIL " << item.name << ": unexpected invalid_argument: " << error.what() << '\n';
            }
        } catch (const std::exception& error) {
            passed = false;
            std::cerr << "FAIL " << item.name << ": unexpected exception: " << error.what() << '\n';
        }
        if (item.invalid_width && input != item.text) {
            passed = false;
            std::cerr << "FAIL " << item.name << ": input must remain unchanged when width is invalid\n";
        }
        if (!passed) {
            ++failures;
        }
    }
    std::cout << cases.size() - failures << '/' << cases.size() << " cases passed\n";
    return failures == 0 ? 0 : 1;
}

int main(int argc, char** argv) {
    if (argc != 2 || std::string(argv[1]) != "01") {
        std::cerr << "Usage: test 01\n";
        return 2;
    }
    return run_task();
}
