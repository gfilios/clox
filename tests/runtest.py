import os
import re

CLOX = "../cmake-build-debug/clox"
ASSERT_PATTERN = re.compile("(.*)//(.*)")


def print_lines(header, lines):
    print("\t\t " + header + ":")
    for line in lines:
        print("\t\t" + line)


def compare_lines(lines_exp, lines_out):
    ok = True
    diffs = []
    for i in range(len(lines_out)):
        line_exp = lines_exp[i].strip()
        line_out = lines_out[i].strip()
        if line_exp == line_out:
            diffs.append("\t\t[OK], line " + str(i) + ", [" + line_out + "]")
        else:
            ok = False
            diffs.append("\t\t[FAILED], line " + str(i) + ", expected [" + line_exp + "],  Actual [" + line_out + "]")
    return ok, diffs


def execute_test(testfile):
    output = execute_lox(testfile)
    expected = expected_result(testfile)

    lines_out = output.splitlines()
    lines_exp = expected.splitlines()

    if len(lines_exp) != len(lines_out):
        print("\t[FAILED] Lines - expected: " + str(len(lines_exp)) + ",  Actual: " + str(len(lines_out)))
        print_lines("Expected", lines_exp)
        print_lines("Expected", lines_out)
    else:
        ok, diff = compare_lines(lines_exp, lines_out)
        if ok:
            print("[OK] " + testfile)
        else:
            print("[FAILED] " + testfile)
            print_lines("Details Comparison", diff)


def execute_lox(testfile):
    stream = os.popen(CLOX + " " + testfile)
    output = stream.read()
    stream.close()
    return output


def expected_result(testfile):
    f = open(testfile, "r")
    result = ""
    for line in f:
        match = ASSERT_PATTERN.match(line)
        if match:
            if result == "":
                result = match.group(2)
            else:
                result = result + "\n" + match.group(2)
    return result


if __name__ == "__main__":
    # expected = expected_result("chapter16/constants.lox")
    execute_test("chapter16/constants.lox")