"""Python coordinates the compiled C++ function checks."""
import os
import subprocess
import unittest


class Tasks(unittest.TestCase):
    def check_task(self, number):
        result = subprocess.run([os.environ["TRAINING_TEST_BINARY"], number],
                                capture_output=True, text=True, timeout=5)
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)

    def test_00_examples_run(self):
        result = subprocess.run([os.environ["TRAINING_MAIN_BINARY"]],
                                capture_output=True, text=True, timeout=5)
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertIn("Examples completed", result.stdout)

    def test_01_unique_ordered(self): self.check_task("01")
    def test_02_latest_per_user(self): self.check_task("02")
    def test_03_word_counts(self): self.check_task("03")
    def test_04_rank_scores(self): self.check_task("04")
    def test_05_even_squares(self): self.check_task("05")
    def test_06_smallest_k(self): self.check_task("06")
    def test_07_equal_range_count(self): self.check_task("07")
    def test_08_bfs_distances(self): self.check_task("08")
    def test_09_running_totals(self): self.check_task("09")
    def test_10_clamp_copy(self): self.check_task("10")
    def test_11_safe_divide(self): self.check_task("11")
    def test_12_make_counter(self): self.check_task("12")


if __name__ == "__main__":
    unittest.main()
