from testframework import execute_test

success = 0
count = 0


def run_test(file):
    global success
    global count
    if execute_test(file):
        success=success+1
    count = count + 1


if __name__ == "__main__":
    print("============================================================== RUNNING TESTS")
    run_test("chapter22/expressions.lox")
    run_test("chapter22/missing_semicolon.lox")
    run_test("chapter22/globalvars.lox")
    run_test("chapter22/invalidassignment.lox")
    run_test("chapter22/localvars.lox")
    run_test("chapter22/simplelocal.lox")
    run_test("chapter22/localvarerrors_1.lox")
    run_test("chapter22/localvarerrors_2.lox")
    run_test("chapter23/ifthenelse.lox")
    run_test("chapter23/and_or.lox")
    run_test("chapter23/while.lox")
    run_test("chapter23/forloop.lox")
    run_test("chapter24/functions.lox")
    print("============================================================== SUMMARY")
    print(f"Total Tests: {count}, Success: {success}, Failures: {count-success}")
    print("==============================================================")