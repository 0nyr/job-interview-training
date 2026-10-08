// C++23 recall lab. Read examples() first, then work through TASK 1 to TASK 12.
// Examples execute independently of the tasks. Each task states its objective before explaining the placeholder.
// Task tests intentionally fail until completed. Keep practice edits uncommitted.
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
#include <stack>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using Scores = std::vector<std::pair<std::string, int>>;
using Graph = std::map<std::string, std::vector<std::string>>;

void examples() {
    // A generic lambda can print different containers without copying them.
    const auto show = [](const char* label, auto&& values) {
        std::cout << label << ':';
        for (const auto& value : values) {
            std::cout << ' ' << value;
        }
        std::cout << '\n';
    };

    // vector is a resizable contiguous container. array has a fixed size.
    std::vector<int> numbers{4, 1, 4, 2};
    std::array<int, 3> fixed{2, 5, 8};
    show("Vector", numbers);
    show("Array", fixed);
    std::cout << "Index / last: " << numbers.at(0) << ' ' << numbers.back() << '\n';

    // reserve changes capacity, not size. resize creates or removes elements.
    std::vector<int> buffer;
    buffer.reserve(8);
    std::cout << "Reserved size: " << buffer.size() << '\n';
    buffer.push_back(7);
    buffer.emplace_back(9);
    buffer.resize(4, -1);
    show("Resized", buffer);
    buffer.pop_back();

    // Copying a vector creates independent storage. A reference aliases an object.
    auto copied = numbers;
    auto& alias = copied;
    alias.front() = 99;
    show("Original", numbers);
    show("Copy through reference", copied);

    // auto& permits element updates. const auto& observes without copying.
    for (auto& value : copied) {
        value += 1;
    }
    show("Updated copy", copied);

    // pair groups values, and structured bindings unpack them.
    const std::pair<std::string, int> record{"Ada", 8};
    const auto& [name, score] = record;
    std::cout << "Structured binding: " << name << ' ' << score << '\n';

    // map iterates sorted keys. operator[] inserts absent keys; at() requires one.
    std::map<std::string, int> scores{{"Bob", 9}, {"Ada", 8}};
    scores["Ada"] = 10;
    for (const auto& [user, value] : scores) {
        std::cout << "Map entry: " << user << ' ' << value << '\n';
    }
    std::cout << "Map lookup: " << scores.at("Ada") << '\n';
    auto found = scores.find("Zoe");
    std::cout << "Missing key: " << (found == scores.end()) << '\n';

    // unordered_map provides average constant-time lookup, with unspecified order.
    std::unordered_map<std::string, int> counts;
    for (const auto& word : {"red", "blue", "red"}) {
        ++counts[word];
    }
    std::cout << "Hash count / contains: " << counts.at("red") << ' ' << counts.contains("green") << '\n';

    // set keeps distinct sorted values. unordered_set is useful for membership.
    std::set<int> ordered_set(numbers.begin(), numbers.end());
    std::unordered_set<int> membership{2, 4};
    show("Sorted set", ordered_set);
    std::cout << "Set membership: " << membership.contains(4) << '\n';

    // Algorithms work with iterators. ranges overloads can accept a whole container.
    auto sorted = numbers;
    std::sort(sorted.begin(), sorted.end());
    show("Sorted ascending", sorted);
    std::ranges::sort(sorted, std::greater<int>{});
    show("Sorted descending", sorted);
    std::cout << "Minimum / sum: " << *std::min_element(numbers.begin(), numbers.end())
              << ' ' << std::accumulate(numbers.begin(), numbers.end(), 0) << '\n';

    // A lambda comparator chooses an ordering. It must be false for equal keys.
    Scores by_name{{"Zoe", 9}, {"Ada", 8}};
    std::ranges::sort(by_name, [](const auto& a, const auto& b) { return a.first < b.first; });
    std::cout << "First name: " << by_name.front().first << '\n';

    // Views describe lazy filtering and transformation. Materialize only as needed.
    std::vector<int> samples{-2, 0, 3, 4};
    auto positive_doubles = samples
        | std::views::filter([](int value) { return value > 0; })
        | std::views::transform([](int value) { return value * 2; });
    show("Range view", positive_doubles);

    // Erase by predicate. Reallocation and erasure can invalidate vector iterators.
    auto filtered = numbers;
    std::erase_if(filtered, [](int value) { return value == 4; });
    show("After erasure", filtered);

    // string supports slicing and search. Stream extraction tokenizes whitespace.
    const std::string text = "Hello C++";
    std::cout << "Substring / found: " << text.substr(0, 5) << ' '
              << (text.find("C++") != std::string::npos) << '\n';
    std::istringstream input("red\tblue\nred");
    for (std::string word; input >> word;) {
        std::cout << "Token: " << word << '\n';
    }
    const unsigned char letter = 'Q';
    std::cout << "Lowercase: " << static_cast<char>(std::tolower(letter)) << '\n';

    // Binary-search bounds return iterators into a sorted range.
    const std::vector<int> ordered{1, 3, 3, 7};
    auto lower = std::lower_bound(ordered.begin(), ordered.end(), 3);
    auto upper = std::upper_bound(ordered.begin(), ordered.end(), 3);
    std::cout << "Bound positions: " << std::distance(ordered.begin(), lower)
              << ' ' << std::distance(ordered.begin(), upper) << '\n';

    // deque supports both ends. queue is FIFO, stack is LIFO, and pop returns void.
    std::deque<int> ends{2, 3};
    ends.push_front(1);
    ends.push_back(4);
    show("Deque", ends);
    std::queue<std::string> pending;
    pending.push("first");
    pending.push("second");
    std::cout << "Queue front: " << pending.front() << '\n';
    pending.pop();
    std::stack<int> history;
    history.push(5);
    history.push(8);
    std::cout << "Stack top: " << history.top() << '\n';
    history.pop();

    // priority_queue exposes the largest item by default. greater gives a min-heap.
    std::priority_queue<int> max_heap;
    std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap;
    for (int value : {7, 2, 5}) {
        max_heap.push(value);
        min_heap.push(value);
    }
    std::cout << "Heap tops: " << max_heap.top() << ' ' << min_heap.top() << '\n';
    max_heap.pop();

    // optional represents absence. Cast before division to obtain a real quotient.
    std::optional<int> maybe;
    std::cout << "Optional fallback: " << maybe.value_or(-1) << '\n';
    maybe = 6;
    std::cout << "Optional value: " << *maybe << '\n';
    std::cout << "Integer / real division: " << 7 / 2 << ' ' << static_cast<double>(7) / 2 << '\n';
    std::cout << "Clamped scalar: " << std::clamp(9, 0, 5) << '\n';

    // Capture by value owns a copy. mutable permits updating that captured state.
    int factor = 3;
    auto scale = [factor](int value) { return value * factor; };
    auto countdown = [remaining = 3]() mutable { return --remaining; };
    std::cout << "Captured factor: " << scale(4) << '\n';
    std::cout << "Mutable capture: " << countdown() << ' ' << countdown() << '\n';

    // RAII manages resource lifetime. Moving a unique_ptr transfers ownership.
    auto owner = std::make_unique<std::string>("owned resource");
    auto moved = std::move(owner);
    std::cout << "RAII: " << *moved << "; original pointer empty: " << (owner == nullptr) << '\n';

    // at() checks bounds and throws. Catch a specific exception when appropriate.
    try {
        (void)numbers.at(numbers.size());
    } catch (const std::out_of_range&) {
        std::cout << "Caught: out_of_range\n";
    }
    std::cout << "Examples completed\n";
}


// TASK 1: Return distinct integers in first-occurrence order without modifying the input. For example, {3, 1, 3, 2} must produce {3, 1, 2}.

// The placeholder uses a sorted set. Change it to retain the original order of first appearances.
std::vector<int> task_01_unique_ordered(const std::vector<int>& values) {
    std::set<int> unique(values.begin(), values.end());
    return {unique.begin(), unique.end()};
}

// TASK 2: Return the maximum timestamp for each user, even when events arrive out of order. Timestamps may be negative. Empty input must produce an empty map.

// The placeholder overwrites each entry with the last timestamp encountered. Keep the maximum instead, without assuming timestamps start at zero.
std::map<std::string, int> task_02_latest_per_user(const Scores& events) {
    std::map<std::string, int> latest;
    for (const auto& [user, timestamp] : events) {
        latest[user] = timestamp;
    }
    return latest;
}

// TASK 3: Split the text on whitespace, lowercase each ASCII token, and count its occurrences. Keep punctuation attached to tokens. Whitespace-only input must produce an empty map.

// The placeholder counts tokens with their original case. Normalize each token before counting. Pass unsigned-char values to std::tolower.
std::map<std::string, int> task_03_word_counts(const std::string& text) {
    std::istringstream input(text);
    std::map<std::string, int> counts;
    for (std::string word; input >> word;) {
        ++counts[word];
    }
    return counts;
}

// TASK 4: Return name/score pairs sorted by highest score first, breaking ties by ascending name. Leave the caller's vector unchanged and retain duplicates.

// The placeholder sorts its local copy only by name. Change the comparator to implement both rules. The comparison must be strict, including for equal entries.
Scores task_04_rank_scores(Scores scores) {
    std::ranges::sort(scores, [](const auto& a, const auto& b) {
        return a.first < b.first;
    });
    return scores;
}

// TASK 5: Return squared even values in input order, including negative even values and zero, without modifying the input. Assume every square fits in int.

// The placeholder filters even values but leaves them unchanged. Transform each selected value before adding it to the result.
std::vector<int> task_05_even_squares(const std::vector<int>& values) {
    std::vector<int> result;
    for (int value : values | std::views::filter([](int x) { return x % 2 == 0; })) {
        result.push_back(value);
    }
    return result;
}

// TASK 6: Return up to k smallest values in ascending order, retaining duplicates and leaving the input unchanged. Return an empty vector when k <= 0.

// The placeholder extracts the largest values from a max-heap. Change the heap ordering or selection strategy to satisfy the task.
std::vector<int> task_06_smallest_k(const std::vector<int>& values, int k) {
    std::priority_queue<int> heap(values.begin(), values.end());
    std::vector<int> result;
    while (k-- > 0 && !heap.empty()) {
        result.push_back(heap.top());
        heap.pop();
    }
    return result;
}

// TASK 7: Given a sorted vector, return the number of occurrences of target, including zero when it is absent. Use the lower and upper insertion boundaries.

// The placeholder returns the index of the lower boundary. Compute the distance between the two boundaries instead.
std::size_t task_07_equal_range_count(const std::vector<int>& values, int target) {
    auto first = std::lower_bound(values.begin(), values.end(), target);
    return static_cast<std::size_t>(std::distance(values.begin(), first));
}

// TASK 8: Return the shortest edge count from start to each reachable vertex, including start at distance 0. Handle cycles and omit unreachable vertices. Missing adjacency entries mean no outgoing edges.

// The placeholder records immediate neighbors but never explores them. Complete the FIFO traversal so it reaches more distant vertices.
std::map<std::string, int> task_08_bfs_distances(const Graph& graph, const std::string& start) {
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

// TASK 9: Return cumulative sums in input order without modifying the input. For example, {2, -1, 4} must produce {2, 1, 5}. Assume all sums fit in int.

// The placeholder reserves capacity and copies the original values. Accumulate the values as you populate the result.
std::vector<int> task_09_running_totals(const std::vector<int>& values) {
    std::vector<int> result;
    result.reserve(values.size());
    for (int value : values) {
        result.push_back(value);
    }
    return result;
}

// TASK 10: Return a new vector with every value clamped to the inclusive interval [low, high], leaving the input unchanged. Assume low <= high.

// The placeholder returns an unchanged copy. Apply the bounds to every element in that copy.
std::vector<int> task_10_clamp_copy(const std::vector<int>& values, int low, int high) {
    auto result = values;
    (void)low;
    (void)high;
    return result;
}

// TASK 11: Return std::nullopt for a zero denominator, otherwise return the real-valued quotient of the two integers.

// The placeholder performs integer division before converting the result. Ensure the division itself uses floating-point arithmetic.
std::optional<double> task_11_safe_divide(int numerator, int denominator) {
    if (denominator == 0) {
        return std::nullopt;
    }
    return numerator / denominator;
}

// TASK 12: Return a callable whose first call returns start and each subsequent call returns the next integer. Copies of the callable must own independent state. Assume counter values stay representable by int.

// The placeholder captures start by value but never updates it. Modify the captured state without borrowing a local variable that goes out of scope.
auto task_12_make_counter(int start) {
    return [start]() mutable { return start; };
}

#ifndef TRAINING_TEST
int main() {
    examples();
}
#endif
