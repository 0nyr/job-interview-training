#define TRAINING_TEST
#include "main.cpp"
#include <cmath>
#include <stdexcept>

void check(bool condition, const std::string& message) {
    if (!condition) {
        throw std::runtime_error(message);
    }
}

void run_task(const std::string& task) {
    if (task == "01") {
        const std::vector<int> values{3, 1, 3, 2, 1};
        check(unique_ordered(values) == std::vector<int>({3, 1, 2}), "preserve first-occurrence order: expected [3, 1, 2]");
        check(unique_ordered({}).empty(), "empty input must produce empty output");
    } else if (task == "02") {
        check(latest_per_user({{"a", 8}, {"b", -2}, {"a", 3}, {"b", -5}}) ==
              std::map<std::string, int>({{"a", 8}, {"b", -2}}), "keep each user's maximum, including negative timestamps");
        check(latest_per_user({}).empty(), "empty events");
    } else if (task == "03") {
        check(word_counts(" Cat\tcat DOG\n dog! ") == std::map<std::string, int>({{"cat", 2}, {"dog", 1}, {"dog!", 1}}),
              "lowercase tokens, split whitespace, retain punctuation");
        check(word_counts(" \t").empty(), "whitespace contains no words");
    } else if (task == "04") {
        const Scores scores{{"Zoe", 9}, {"Ada", 8}, {"Bob", 9}};
        check(rank_scores(scores) == Scores({{"Bob", 9}, {"Zoe", 9}, {"Ada", 8}}), "descending score, then ascending name");
        check(rank_scores({}).empty(), "empty ranking");
        check(rank_scores({{"A", 1}, {"A", 1}}).size() == 2, "retain duplicate scores");
    } else if (task == "05") {
        check(even_squares({3, 2, -4, 5, 0}) == std::vector<int>({4, 16, 0}), "square even values, preserve order");
        check(even_squares({}).empty(), "empty input");
    } else if (task == "06") {
        const std::vector<int> values{5, 1, 1, -2, 3};
        check(smallest_k(values, 3) == std::vector<int>({-2, 1, 1}), "smallest 3 ascending, duplicates retained");
        check(smallest_k(values, 99) == std::vector<int>({-2, 1, 1, 3, 5}), "k greater than size");
        check(smallest_k(values, 0).empty() && smallest_k(values, -1).empty(), "nonpositive k");
        check(smallest_k({}, 2).empty(), "empty input");
    } else if (task == "07") {
        check(equal_range_count({1, 2, 2, 4}, 2) == 2, "two occurrences of 2");
        check(equal_range_count({1, 4}, 2) == 0, "absent target");
        check(equal_range_count({}, 2) == 0, "empty input");
        check(equal_range_count({2, 2, 2}, 2) == 3, "all values equal");
    } else if (task == "08") {
        Graph graph{{"a", {"b", "c"}}, {"b", {"a", "d"}}, {"c", {"d"}}, {"d", {"e"}}, {"z", {}}};
        check(bfs_distances(graph, "a") == std::map<std::string, int>({{"a", 0}, {"b", 1}, {"c", 1}, {"d", 2}, {"e", 3}}),
              "BFS must traverse beyond direct neighbors and handle cycles");
        check(bfs_distances({}, "x") == std::map<std::string, int>({{"x", 0}}), "missing start adjacency");
    } else if (task == "09") {
        check(running_totals({2, -1, 4}) == std::vector<int>({2, 1, 5}), "cumulative sums");
        check(running_totals({}).empty(), "empty input");
    } else if (task == "10") {
        const std::vector<int> values{-5, 0, 3, 9};
        check(clamp_copy(values, 0, 4) == std::vector<int>({0, 0, 3, 4}), "clamp to inclusive bounds");
        check(clamp_copy(values, 2, 2) == std::vector<int>({2, 2, 2, 2}), "equal bounds");
        check(clamp_copy({}, 0, 1).empty(), "empty input");
    } else if (task == "11") {
        auto result = safe_divide(3, 2);
        check(result.has_value() && std::abs(*result - 1.5) < 1e-12, "real division: 3/2 = 1.5");
        check(!safe_divide(3, 0).has_value(), "zero denominator returns nullopt");
        result = safe_divide(-3, 2);
        check(result.has_value() && std::abs(*result + 1.5) < 1e-12, "negative numerator");
    } else if (task == "12") {
        auto counter = make_counter(4);
        check(counter() == 4, "first call returns start");
        check(counter() == 5, "second call increments");
        auto copy = counter;
        check(counter() == 6 && copy() == 6, "copies own independent state");
        check(counter() == 7, "original state persists");
        auto other = make_counter(-1);
        check(other() == -1 && other() == 0, "separate counter");
    } else {
        throw std::runtime_error("Unknown task: " + task);
    }
}

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: test TASK_NUMBER\n";
        return 2;
    }
    try {
        run_task(argv[1]);
        std::cout << "PASS " << argv[1] << '\n';
    } catch (const std::exception& error) {
        std::cerr << "FAIL " << argv[1] << ": " << error.what() << '\n';
        return 1;
    }
}
