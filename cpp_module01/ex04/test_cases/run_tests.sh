#!/bin/sh

set -e

cd "$(dirname "$0")/.."
make

./replace test_cases/01_basic_input.txt fish cat
diff -u test_cases/01_basic_expected.txt test_cases/01_basic_input.txt.replace

./replace test_cases/02_no_match_input.txt zombie brain
diff -u test_cases/02_no_match_expected.txt test_cases/02_no_match_input.txt.replace

./replace test_cases/03_multiple_same_line_input.txt aa Z
diff -u test_cases/03_multiple_same_line_expected.txt test_cases/03_multiple_same_line_input.txt.replace

./replace test_cases/04_blank_lines_input.txt line LINE
diff -u test_cases/04_blank_lines_expected.txt test_cases/04_blank_lines_input.txt.replace

./replace test_cases/05_remove_input.txt erase ""
diff -u test_cases/05_remove_expected.txt test_cases/05_remove_input.txt.replace

./replace test_cases/06_case_sensitive_input.txt cat dog
diff -u test_cases/06_case_sensitive_expected.txt test_cases/06_case_sensitive_input.txt.replace
