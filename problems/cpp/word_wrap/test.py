"""Run the native word-wrapping contract through the workspace runner."""
import os
import subprocess
import unittest


class Tasks(unittest.TestCase):
    def test_00_examples_run(self):
        result = subprocess.run([os.environ["TRAINING_MAIN_BINARY"]],
                                capture_output=True, text=True, timeout=5)
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertIn("Examples completed", result.stdout)

    def test_01_format_text_in_place(self):
        result = subprocess.run([os.environ["TRAINING_TEST_BINARY"], "01"],
                                capture_output=True, text=True, timeout=5)
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)


if __name__ == "__main__":
    unittest.main()
