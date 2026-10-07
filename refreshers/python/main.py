"""Python 3.13 recall lab. Run this file, then search for TASK.

The examples already execute. Modify each function to satisfy its TASK contract.
Tests check the requested behavior, so task failures are expected at first.
Keep practice edits uncommitted. No third-party packages are needed.
"""
from bisect import bisect_left, bisect_right
from collections import Counter, defaultdict, deque
from dataclasses import dataclass
import heapq
from itertools import accumulate


def unique_ordered(values: list[int]) -> list[int]:
    # set removes duplicates; sorted produces a new list.
    # TASK 01: retain the FIRST occurrence order instead of sorting.
    # Example: [3, 1, 3, 2] -> [3, 1, 2]. Input must remain unchanged.
    return sorted(set(values))


def latest_per_user(events: list[tuple[str, int]]) -> dict[str, int]:
    # Unpacking in a comprehension is handy. Repeated keys overwrite values.
    # TASK 02: keep the maximum timestamp per user, even for unsorted events.
    # Timestamps may be negative. Empty input returns {}.
    return {user: timestamp for user, timestamp in events}


def word_counts(words: list[str]) -> dict[str, int]:
    # Counter behaves like a dictionary with zero for absent keys.
    # TASK 03: strip whitespace, lowercase, and omit empty words before counting.
    return dict(Counter(words))


def rank_scores(scores: list[tuple[str, int]]) -> list[tuple[str, int]]:
    # key is a callable; tuples are compared lexicographically.
    # TASK 04: highest score first, breaking ties by ascending name.
    return sorted(scores, key=lambda item: item[0])


def indexed_even_squares(values: list[int]) -> list[tuple[int, int]]:
    # enumerate provides (index, value). The trailing if filters entries.
    # TASK 05: return (original index, squared value) for even VALUES only.
    return [(i, value) for i, value in enumerate(values) if i % 2 == 0]


def pair_totals(left: list[int], right: list[int]) -> list[int]:
    # zip stops at the shortest input unless strict=True is requested.
    # TASK 06: add each pair and reject unequal lengths with ValueError.
    return [a * b for a, b in zip(left, right)]


def normalize_words(text: str) -> str:
    # split() collapses arbitrary whitespace; join() assembles an iterable.
    # TASK 07: lowercase the words and join them with a single hyphen.
    return " ".join(text.split())


def smallest_k(values: list[int], k: int) -> list[int]:
    # heapq offers nsmallest/nlargest; a Python heap is normally a min-heap.
    # TASK 08: return up to k SMALLEST values in ascending order, with duplicates.
    # k <= 0 returns []; do not mutate values.
    return heapq.nlargest(k, values)


def first_at_least(values: list[int], target: int) -> int:
    # Precondition: values is sorted. Insertion indices can equal len(values).
    # TASK 09: return the first index whose value is >= target.
    # bisect_left and bisect_right differ when equal values exist.
    return bisect_right(values, target)


def bfs_distances(graph: dict[str, list[str]], start: str) -> dict[str, int]:
    # deque.popleft() is useful for FIFO traversal, unlike list.pop(0).
    # TASK 10: return shortest edge counts for ALL vertices reachable from start.
    # Include start at distance 0, ignore unreachable vertices, handle cycles.
    # A missing adjacency entry means no outgoing edges.
    distances = {start: 0}
    pending = deque([start])
    while pending:
        node = pending.popleft()
        for neighbor in graph.get(node, []):
            if neighbor not in distances:
                distances[neighbor] = distances[node] + 1
                # Complete the traversal here.
    return distances


def running_totals(values):
    # yield makes a generator. It processes values as the caller iterates.
    # TASK 11: lazily yield cumulative sums, accepting any iterable.
    # Example: iter([2, -1, 4]) -> yields 2, 1, 5.
    for value in values:
        yield value


def append_copy(value: int, values: list[int] | None = None) -> list[int]:
    # None avoids a shared mutable default such as values=[].
    # TASK 12: return a NEW list with value appended, never modify the input.
    # Separate calls without values must remain independent.
    if values is None:
        values = []
    values.append(value)
    return values


@dataclass(frozen=True)
class Candidate:
    name: str
    score: int = 0


def examples() -> None:
    numbers = [3, 1, 3, 2]
    print("Unique:", unique_ordered(numbers))
    print("Counts:", word_counts(["Python", " python ", "Python"]))
    print("Ranking:", rank_scores([("Ada", 8), ("Bob", 9)]))
    print("Heap:", smallest_k(numbers, 2))
    print("Generator:", list(running_totals([2, -1, 4])))
    print("Slices:", numbers[:2], numbers[::-1])
    print("Any / all:", any(x < 0 for x in numbers), all(x > 0 for x in numbers))
    print("Min by key:", min(["long", "hi"], key=len, default=""))
    print("Set operations:", {1, 2} | {2, 3}, {1, 2} & {2, 3})
    groups = defaultdict(list)
    for name in ["Ada", "Alan", "Bob"]:
        groups[name[0]].append(name)
    print("Grouping:", dict(groups))
    head, *tail = numbers
    print(f"Unpacking: {head=}, {tail=}")
    print("Dataclass:", Candidate(name="Ada", score=8))
    print("Library accumulation:", list(accumulate([2, -1, 4])))
    # dict.get(key, default), sorted(..., reverse=True), and list.sort() are
    # worth recalling. sort() changes a list in place and returns None.
    # Function parameters: def f(a, /, b=0, *, flag=False, **kwargs).
    # / means positional-only; * begins keyword-only parameters.
    # Context managers close resources: with open(path) as stream: ...
    try:
        int("not an integer")
    except ValueError as error:
        print("Caught:", type(error).__name__)


if __name__ == "__main__":
    examples()
