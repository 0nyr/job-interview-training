"""Python 3.13 recall lab. Read examples() first, then work through TASK 1 to TASK 12.

Run this file to execute the independent examples. Each task below starts with its objective, followed by an explanation of the placeholder to change.
Task tests intentionally fail until you implement the requested behavior. Keep practice edits uncommitted. No third-party packages are needed.
"""
from bisect import bisect_left, bisect_right
from collections import Counter, defaultdict, deque
from dataclasses import dataclass
import heapq
from itertools import accumulate
from io import StringIO


def examples() -> None:
    """Run small Python examples without calling any exercise task."""
    # Create a list of integers. Lists are ordered and can contain duplicates.
    numbers = [3, 1, 3, 2]
    print("List:", numbers)

    # Iterate over [start, end): start is included and end is excluded.
    for number in range(2, 5):
        print("Range item:", number)

    # Index from either end, slice a prefix, or reverse with a negative step.
    print("Indexing:", numbers[0], numbers[-1])
    print("Slices:", numbers[:2], numbers[::-1])

    # Copy before changing a list. append changes the list in place.
    copied = numbers.copy()
    copied.append(9)
    print("Original / copy:", numbers, copied)

    # Build a list with a comprehension and filter with a trailing if.
    positive_doubles = [2 * value for value in [-2, 0, 3, 4] if value > 0]
    print("Comprehension:", positive_doubles)

    # enumerate yields (index, value). Unpack each pair in the loop.
    for index, name in enumerate(["Ada", "Bob"]):
        print(f"Name at {index}: {name}")

    # zip pairs items. strict=True raises ValueError if the lengths differ.
    print("Pairs:", list(zip(["Ada", "Bob"], [8, 9], strict=True)))

    # Unpack the first item separately and collect the remainder in a list.
    head, *tail = numbers
    print(f"Unpacking: {head=}, {tail=}")

    # Dictionary keys are unique. Assigning an existing key replaces its value.
    scores = {"Ada": 8, "Bob": 9}
    scores["Ada"] = 10
    print("Dictionary:", scores, "missing score:", scores.get("Zoe", 0))
    print("Dictionary comprehension:", {name: len(name) for name in scores})

    # A set stores distinct values. Use | for union and & for intersection.
    print("Distinct values:", set(numbers))
    print("Set operations:", {1, 2} | {2, 3}, {1, 2} & {2, 3})

    # Counter counts occurrences. Missing keys have a count of zero.
    counts = Counter(["red", "blue", "red"])
    print("Counter:", dict(counts), "missing count:", counts["green"])

    # defaultdict creates a fresh list when a key is first accessed.
    groups = defaultdict(list)
    for name in ["Ada", "Alan", "Bob"]:
        groups[name[0]].append(name)
    print("Grouping:", dict(groups))

    # sorted returns a new list. A key function selects the comparison value.
    words = ["pear", "fig", "watermelon"]
    print("Sorted by length:", sorted(words, key=len))
    print("Sorted descending:", sorted(numbers, reverse=True))
    print("Lambda key:", sorted([("Ada", 8), ("Bob", 9)], key=lambda item: item[1]))

    # list.sort changes the list in place and returns None.
    sortable = numbers.copy()
    returned = sortable.sort()
    print("In-place sort:", sortable, "return value:", returned)

    # any and all consume conditions. min accepts a key and an empty-input default.
    print("Any / all:", any(x < 0 for x in numbers), all(x > 0 for x in numbers))
    print("Shortest word:", min(words, key=len, default=""))

    # strip removes surrounding whitespace. lower changes letter case.
    print("Strip / lower:", repr("  Hello  ".strip()), "Hello".lower())

    # split without an argument separates on whitespace. join inserts a separator.
    print("Split:", "Ada\tBob\nZoe".split())
    print("Join:", ", ".join(["Ada", "Bob", "Zoe"]))

    # A min-heap exposes its smallest item first. heapify changes the list in place.
    heap = [7, 2, 5]
    heapq.heapify(heap)
    heapq.heappush(heap, 1)
    print("Heap minimum:", heapq.heappop(heap))
    print("Largest 2:", heapq.nlargest(2, heap))

    # Bisect finds insertion positions in a sorted list, before or after equal items.
    ordered = [1, 3, 3, 7]
    print("Insertion positions:", bisect_left(ordered, 3), bisect_right(ordered, 3))

    # A deque supports a FIFO queue: append at the right and remove from the left.
    queue = deque(["first", "second"])
    queue.append("third")
    print("Queue front:", queue.popleft(), "remaining:", list(queue))

    # yield produces values lazily. Calling the function creates a generator.
    def countdown(start):
        while start > 0:
            yield start
            start -= 1

    countdown_values = countdown(3)
    print("Next generated value:", next(countdown_values))
    print("Remaining generated values:", list(countdown_values))
    print("Library accumulation:", list(accumulate([2, -1, 4])))

    # None is a safe default when each call needs its own mutable object.
    def make_settings(settings=None):
        if settings is None:
            settings = {}
        return settings

    print("Independent defaults:", make_settings() is not make_settings())

    # / marks positional-only parameters. Parameters after * are keyword-only.
    def greeting(name, /, prefix="Hello", *, excited=False):
        return f"{prefix}, {name}" + ("!" if excited else ".")

    print("Parameters:", greeting("Ada", excited=True))

    # A dataclass generates initialization and a readable representation.
    # frozen=True prevents reassignment of its fields.
    @dataclass(frozen=True)
    class Candidate:
        name: str
        score: int = 0

    print("Dataclass:", Candidate(name="Ada", score=8))

    # A context manager closes this in-memory text stream when the block ends.
    with StringIO("first line\nsecond line\n") as stream:
        print("Stream line:", stream.readline().strip())
    print("Stream closed:", stream.closed)

    # Catch a specific exception when an operation can fail.
    try:
        int("not an integer")
    except ValueError as error:
        print("Caught:", type(error).__name__)


def task_01_unique_ordered(values: list[int]) -> list[int]:
    """TASK 1: Return distinct integers in their first-occurrence order, without modifying the input. For example, [3, 1, 3, 2] must produce [3, 1, 2].

    The placeholder sorts the distinct values. Replace it with an implementation that preserves their original order.
    """
    return sorted(set(values))


def task_02_latest_per_user(events: list[tuple[str, int]]) -> dict[str, int]:
    """TASK 2: Return the maximum timestamp for each user, even when events arrive out of order. Timestamps may be negative. Empty input must return {}.

    The placeholder dictionary comprehension keeps the last timestamp encountered for each user. Change it to retain the maximum.
    """
    return {user: timestamp for user, timestamp in events}


def task_03_word_counts(words: list[str]) -> dict[str, int]:
    """TASK 3: Strip surrounding whitespace and lowercase each entry, then count the normalized entries. Omit entries that become empty and preserve whitespace inside each entry.

    The placeholder counts entries exactly as received. Normalize each entry before counting, without splitting it into separate words.
    """
    return dict(Counter(words))


def task_04_rank_scores(scores: list[tuple[str, int]]) -> list[tuple[str, int]]:
    """TASK 4: Return (name, score) pairs sorted by highest score first, breaking ties by ascending name. Leave the input unchanged.

    The placeholder sorts only by name. Change the sorting key to apply both ordering rules.
    """
    return sorted(scores, key=lambda item: item[0])


def task_05_indexed_even_squares(values: list[int]) -> list[tuple[int, int]]:
    """TASK 5: Return (original index, squared value) pairs for even values only. Preserve input order and include negative even values and zero.

    The placeholder filters even indices and leaves values unchanged. Change both the filter and the value in each result pair.
    """
    return [(i, value) for i, value in enumerate(values) if i % 2 == 0]


def task_06_pair_totals(left: list[int], right: list[int]) -> list[int]:
    """TASK 6: Return the elementwise sums of the two lists. Raise ValueError if their lengths differ. Two empty lists must produce [].

    The placeholder multiplies pairs and silently truncates to the shorter input. Replace multiplication with addition and enforce equal lengths.
    """
    return [a * b for a, b in zip(left, right)]


def task_07_normalize_words(text: str) -> str:
    """TASK 7: Split the text on whitespace, lowercase its words, and join them with a single hyphen. Whitespace-only input must produce an empty string.

    The placeholder rejoins words with spaces and preserves their case. Change the normalization and separator.
    """
    return " ".join(text.split())


def task_08_smallest_k(values: list[int], k: int) -> list[int]:
    """TASK 8: Return up to k smallest values in ascending order, preserving duplicates and leaving the input unchanged. Return [] when k <= 0.

    The placeholder selects the largest values. Change the selection to satisfy the requested order and edge cases.
    """
    return heapq.nlargest(k, values)


def task_09_first_at_least(values: list[int], target: int) -> int:
    """TASK 9: Given a sorted list, return the first index whose value is at least target. Return len(values) if no value qualifies, including 0 for an empty list.

    The placeholder uses bisect_right, which skips values equal to target. Choose the insertion position that includes the first equal value.
    """
    return bisect_right(values, target)


def task_10_bfs_distances(graph: dict[str, list[str]], start: str) -> dict[str, int]:
    """TASK 10: Return the shortest number of edges from start to every reachable vertex, including start at distance 0. Handle cycles and omit unreachable vertices. A missing adjacency entry means no outgoing edges.

    The placeholder records immediate neighbors but never explores them. Complete the queue-based traversal so it reaches more distant vertices.
    """
    distances = {start: 0}
    pending = deque([start])
    while pending:
        node = pending.popleft()
        for neighbor in graph.get(node, []):
            if neighbor not in distances:
                distances[neighbor] = distances[node] + 1
                # Complete the traversal here.
    return distances


def task_11_running_totals(values):
    """TASK 11: Lazily yield cumulative sums from any iterable. For example, iter([2, -1, 4]) must yield 2, 1, 5. Consume one input item per yielded result and produce nothing for empty input.

    The placeholder yields the original values. Track the running sum while preserving lazy consumption.
    """
    for value in values:
        yield value


def task_12_append_copy(value: int, values: list[int] | None = None) -> list[int]:
    """TASK 12: Return a new list containing the supplied values followed by value, without modifying the input. When values is omitted, return [value]. Separate calls must remain independent.

    The placeholder appends directly to the supplied list. Create an independent result before modifying it.
    """
    if values is None:
        values = []
    values.append(value)
    return values


if __name__ == "__main__":
    examples()
