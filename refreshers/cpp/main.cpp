// C++23 recall lab. Run this file, then search for TASK.
// Examples already execute. Modify each function to meet its TASK contract.
// Keep practice edits uncommitted. The test harness includes this file.
#include <algorithm>
#include <array>
#include <cctype>
#include <deque>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <numeric>
#include <optional>
#include <queue>
#include <ranges>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using Scores = std::vector<std::pair<std::string, int>>;
using Graph = std::map<std::string, std::vector<std::string>>;

std::vector<int> unique_ordered(const std::vector<int>& values) {
    // const& borrows without copying. std::set stores distinct, sorted values.
    // TASK 01: retain FIRST occurrence order, without modifying values.
    std::set<int> unique(values.begin(), values.end());
    return {unique.begin(), unique.end()};
}

std::map<std::string, int> latest_per_user(const Scores& events) {
    // Structured bindings unpack pairs. operator[] inserts a default value.
    // TASK 02: keep the maximum timestamp per user, even for unsorted events.
    // Timestamps may be negative; a default 0 is not a valid initial maximum.
    std::map<std::string, int> latest;
    for (const auto& [user, timestamp] : events) {
        latest[user] = timestamp;
    }
    return latest;
}

std::map<std::string, int> word_counts(const std::string& text) {
    // stream >> token splits on whitespace. ++counts[token] inserts then adds.
    // TASK 03: lowercase each ASCII token before counting. Keep punctuation.
    // For std::tolower, convert char to unsigned char before passing it.
    std::istringstream input(text);
    std::map<std::string, int> counts;
    for (std::string word; input >> word;) {
        ++counts[word];
    }
    return counts;
}

Scores rank_scores(Scores scores) {
    // Passing by value allows sorting the local copy without changing input.
    // TASK 04: highest score first, breaking ties by ascending name.
    // A comparator must be strict: do not use >= for equal elements.
    std::ranges::sort(scores, [](const auto& a, const auto& b) {
        return a.first < b.first;
    });
    return scores;
}

std::vector<int> even_squares(const std::vector<int>& values) {
    // Views describe lazy operations. This loop materializes the result.
    // TASK 05: collect squared even values in input order, including negatives.
    // Inputs in this exercise have squares representable by int.
    std::vector<int> result;
    for (int value : values | std::views::filter([](int x) { return x % 2 == 0; })) {
        result.push_back(value);
    }
    return result;
}

std::vector<int> smallest_k(const std::vector<int>& values, int k) {
    // priority_queue is a MAX-heap by default. std::greater<int> reverses it.
    // TASK 06: return up to k SMALLEST values, sorted ascending with duplicates.
    // k <= 0 returns an empty vector. Do not modify the input.
    std::priority_queue<int> heap(values.begin(), values.end());
    std::vector<int> result;
    while (k-- > 0 && !heap.empty()) {
        result.push_back(heap.top());
        heap.pop();
    }
    return result;
}

std::size_t equal_range_count(const std::vector<int>& values, int target) {
    // Precondition: values is sorted. lower_bound returns an iterator.
    // TASK 07: count target occurrences using lower_bound and upper_bound.
    auto first = std::lower_bound(values.begin(), values.end(), target);
    return static_cast<std::size_t>(std::distance(values.begin(), first));
}

std::map<std::string, int> bfs_distances(const Graph& graph, const std::string& start) {
    // std::queue is FIFO. std::stack is LIFO. front() observes; pop() removes.
    // TASK 08: compute distances to ALL reachable vertices, including cycles.
    // Missing adjacency entries mean no outgoing edges. Include start at 0.
    std::map<std::string, int> distances{{start, 0}};
    std::queue<std::string> pending;
    pending.push(start);
    while (!pending.empty()) {
        auto node = pending.front();
        pending.pop();
        auto neighbors = graph.find(node);
        if (neighbors == graph.end()) {
            continue;
        }
        for (const auto& neighbor : neighbors->second) {
            if (!distances.contains(neighbor)) {
                distances[neighbor] = distances.at(node) + 1;
                // Complete the traversal here.
            }
        }
    }
    return distances;
}

std::vector<int> running_totals(const std::vector<int>& values) {
    // reserve allocates capacity; it does not create elements like resize.
    // TASK 09: return cumulative sums. Assume sums fit in int.
    // std::partial_sum is a library alternative to a running accumulator.
    std::vector<int> result;
    result.reserve(values.size());
    for (int value : values) {
        result.push_back(value);
    }
    return result;
}

std::vector<int> clamp_copy(const std::vector<int>& values, int low, int high) {
    // TASK 10: return a copy with every value clamped to [low, high].
    // Precondition: low <= high. Preserve the caller's vector.
    // std::clamp is available; iterating with auto& permits modification.
    auto result = values;
    (void)low;
    (void)high;
    return result;
}

std::optional<double> safe_divide(int numerator, int denominator) {
    // optional represents a value or its absence; *result accesses the value.
    // TASK 11: return nullopt for zero denominator, otherwise REAL division.
    if (denominator == 0) {
        return std::nullopt;
    }
    return numerator / denominator;
}

auto make_counter(int start) {
    // Capture by value owns the state. mutable allows changing that state.
    // TASK 12: each call returns the current value, then increments it.
    // Copies of the closure must have independent state. Never capture a
    // local variable by reference in a closure that outlives the function.
    return [start]() mutable { return start; };
}

#ifndef TRAINING_TEST
int main() {
    const std::vector<int> values{3, 1, 3, 2};
    std::cout << "Unique:";
    for (int value : unique_ordered(values)) {
        std::cout << ' ' << value;
    }
    std::cout << '\n';
    for (const auto& [name, score] : rank_scores({{"Ada", 8}, {"Bob", 9}})) {
        std::cout << name << ": " << score << '\n';
    }
    // RAII: unique_ptr releases its resource automatically at scope exit.
    auto owner = std::make_unique<std::string>("owned resource");
    auto moved = std::move(owner); // Transfers ownership; owner is now null.
    std::cout << "RAII: " << *moved << '\n';
    std::array<int, 3> fixed{1, 2, 3};
    std::cout << "Sum: " << std::accumulate(fixed.begin(), fixed.end(), 0) << '\n';
    std::unordered_map<std::string, int> counts{{"Ada", 2}};
    std::cout << "Contains: " << counts.contains("Ada") << '\n';
    std::vector<int> filtered{1, 2, 3, 4};
    std::erase_if(filtered, [](int x) { return x % 2 == 0; });
    // Reallocation invalidates vector iterators and references. Erasure also
    // invalidates those at or after the erased position. Do not reuse them.
    // map has sorted keys and logarithmic lookup. unordered_map has average
    // constant lookup but unspecified iteration order and linear worst case.
    std::cout << "Examples completed\n";
}
#endif
