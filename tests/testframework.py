import os
import re
import subprocess

CLOX = "../cmake-build-debug/clox"
ASSERT_OK_PATTERN = re.compile("(.*)// ASSERT (.*)",  re.IGNORECASE)
ASSERT_ERR_PATTERN = re.compile("(.*)// ASSERT_ERROR (.*)", re.IGNORECASE)


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
    retcode, output, error = execute_lox(testfile)
    if retcode<0:
        print("[FAILURE] " + testfile)
        print(f"\t Unexpected Failure with Return Code {retcode}")
        print(f"\t Check manual execution {CLOX} {testfile}")
        return False
    expected_out = expected_result(testfile, ASSERT_OK_PATTERN)
    expected_err = expected_result(testfile, ASSERT_ERR_PATTERN)

    ok_out, diff_out = compare(output, expected_out)
    ok_err, diff_err = compare(error, expected_err)
    if ok_out and ok_err:
        print("[SUCCESS] " + testfile)
        return True
    else:
        print("[FAILURE] " + testfile)
        if not ok_out:
            print("\t[FAILURE] OUTPUT COMPARE")
            for line in diff_out:
                print("\t", line)
        if not ok_err:
            print("\t[FAILURE] ERROR COMPARE")
            for line in diff_err:
                print("\t", line)
        return False


def check_none(val):
    if val == None:
        return ''
    return val


def compare(out, exp):
    diffs = []
    lines_out = check_none(out).splitlines()
    lines_exp = check_none(exp).splitlines()

    if len(lines_exp) != len(lines_out):
        diffs.append(
            "\t[FAILURE] NUMBER OF LINES expected: " + str(len(lines_exp)) + ",  Actual: " + str(len(lines_out)))
        diffs.append("\tExpected:")
        for line in lines_exp:
            diffs.append("\t\t>" + line)
        diffs.append("\tActual:")
        for line in lines_out:
            diffs.append("\t\t>" + line)
        return False, diffs
    else:
        ok, diffs = compare_lines(lines_exp, lines_out)
        return ok, diffs


def execute_lox(testfile):
    process = subprocess.run([CLOX, testfile],  stdout=subprocess.PIPE, stderr=subprocess.PIPE, universal_newlines=True)
    output = process.stdout
    error = process.stderr
    return process.returncode, process.stdout, process.stderr


def expected_result(testfile, pattern):
    f = open(testfile, "r")
    result = ""
    for line in f:
        match = pattern.match(line)
        if match:
            if result == "":
                result = match.group(2)
            else:
                result = result + "\n" + match.group(2)
    return result

