"""Console checks for the greeting exercise."""
import sys
from pathlib import Path
import subprocess
import unittest


class Tasks(unittest.TestCase):
    def test_01_greeting(self):
        result = subprocess.run([sys.executable, str(Path(__file__).with_name("main.py"))], input="", capture_output=True, text=True, timeout=5)
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertEqual(result.stdout, "Hello World\n")


if __name__ == "__main__":
    unittest.main()
