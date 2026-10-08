"""Task contracts. Run with the workspace CLI or python -m unittest -v test."""
import subprocess
import sys
import unittest
from pathlib import Path

import main


class Tasks(unittest.TestCase):
    def test_00_examples_run(self):
        result = subprocess.run([sys.executable, str(Path(__file__).with_name("main.py"))],
                                capture_output=True, text=True, timeout=5)
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertIn("Caught: ValueError", result.stdout)

    def test_01_unique_ordered(self):
        values = [3, 1, 3, 2, 1]
        self.assertEqual(main.unique_ordered(values), [3, 1, 2])
        self.assertEqual(values, [3, 1, 3, 2, 1])
        self.assertEqual(main.unique_ordered([]), [])

    def test_02_latest_per_user(self):
        self.assertEqual(main.latest_per_user([("a", 8), ("b", -2), ("a", 3), ("b", -5)]),
                         {"a": 8, "b": -2})
        self.assertEqual(main.latest_per_user([]), {})

    def test_03_word_counts(self):
        self.assertEqual(main.word_counts([" Cat ", "cat", "DOG", "", "  "]), {"cat": 2, "dog": 1})
        self.assertEqual(main.word_counts([]), {})
        # Normalize each entry without splitting or collapsing internal whitespace.
        cases = [
            ([" New York ", "new york"], {"new york": 2}),
            ([" a\tb ", "A\tB"], {"a\tb": 2}),
            (["A  B", "a b"], {"a  b": 1, "a b": 1}),
        ]
        for words, expected in cases:
            with self.subTest(words=words):
                self.assertEqual(main.word_counts(words), expected)

    def test_04_rank_scores(self):
        data = [("Zoe", 9), ("Ada", 8), ("Bob", 9)]
        self.assertEqual(main.rank_scores(data), [("Bob", 9), ("Zoe", 9), ("Ada", 8)])
        self.assertEqual(data[0], ("Zoe", 9))
        self.assertEqual(main.rank_scores([]), [])

    def test_05_indexed_even_squares(self):
        self.assertEqual(main.indexed_even_squares([3, 2, -4, 5, 0]), [(1, 4), (2, 16), (4, 0)])
        self.assertEqual(main.indexed_even_squares([]), [])

    def test_06_pair_totals(self):
        self.assertEqual(main.pair_totals([2, -1], [3, 4]), [5, 3])
        self.assertEqual(main.pair_totals([], []), [])
        for left, right in [([1], []), ([], [1]), ([1, 2], [3]), ([1], [2, 3])]:
            with self.subTest(left=left, right=right):
                with self.assertRaises(ValueError):
                    main.pair_totals(left, right)

    def test_07_normalize_words(self):
        self.assertEqual(main.normalize_words("  Hello\tPYTHON\n world  "), "hello-python-world")
        self.assertEqual(main.normalize_words(" \t"), "")

    def test_08_smallest_k(self):
        values = [5, 1, 1, -2, 3]
        self.assertEqual(main.smallest_k(values, 3), [-2, 1, 1])
        self.assertEqual(main.smallest_k(values, 99), [-2, 1, 1, 3, 5])
        self.assertEqual(main.smallest_k(values, 0), [])
        self.assertEqual(main.smallest_k(values, -1), [])
        self.assertEqual(main.smallest_k([], 2), [])
        self.assertEqual(values, [5, 1, 1, -2, 3])

    def test_09_first_at_least(self):
        for values, target, expected in [([1, 2, 2, 4], 2, 1), ([1, 4], 2, 1),
                                          ([1, 4], 5, 2), ([1, 4], 0, 0), ([], 2, 0)]:
            with self.subTest(values=values, target=target):
                self.assertEqual(main.first_at_least(values, target), expected)

    def test_10_bfs_distances(self):
        graph = {"a": ["b", "c"], "b": ["a", "d"], "c": ["d"], "d": ["e"], "z": []}
        self.assertEqual(main.bfs_distances(graph, "a"), {"a": 0, "b": 1, "c": 1, "d": 2, "e": 3})
        self.assertEqual(main.bfs_distances({}, "x"), {"x": 0})
        graph = {"a": ["a", "b", "b"], "b": ["a", "b", "c", "c"], "z": ["z"]}
        self.assertEqual(main.bfs_distances(graph, "a"), {"a": 0, "b": 1, "c": 2})

    def test_11_running_totals(self):
        self.assertEqual(list(main.running_totals(iter([2, -1, 4]))), [2, 1, 5])
        self.assertEqual(list(main.running_totals([])), [])
        def source():
            yield 7
            raise RuntimeError("Do not consume ahead")
        iterator = main.running_totals(source())
        self.assertIs(iter(iterator), iterator)
        self.assertEqual(next(iterator), 7)

        consumed = []

        def tracked_source():
            for value in (2, -1, 4):
                consumed.append(value)
                yield value

        iterator = main.running_totals(tracked_source())
        self.assertEqual(consumed, [], "Constructing the result must not consume input")
        for expected_total, expected_consumed in [(2, [2]), (1, [2, -1]), (5, [2, -1, 4])]:
            with self.subTest(expected_total=expected_total):
                self.assertEqual(next(iterator), expected_total)
                self.assertEqual(consumed, expected_consumed, "Consume exactly one item per yield")
        with self.assertRaises(StopIteration):
            next(iterator)

    def test_12_append_copy(self):
        values = [1]
        result = main.append_copy(2, values)
        self.assertEqual(result, [1, 2])
        self.assertEqual(values, [1])
        self.assertIsNot(result, values)
        self.assertEqual(main.append_copy(8), [8])
        self.assertEqual(main.append_copy(9), [9])
        empty = []
        result = main.append_copy(2, empty)
        self.assertEqual(result, [2])
        self.assertEqual(empty, [])
        self.assertIsNot(result, empty)

        first = main.append_copy(8)
        first.append(99)
        second = main.append_copy(9)
        self.assertEqual(first, [8, 99])
        self.assertEqual(second, [9])
        self.assertIsNot(first, second)


if __name__ == "__main__":
    unittest.main()
