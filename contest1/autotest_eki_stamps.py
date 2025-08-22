# Re-adding the original test script structure with more test cases
import subprocess
import os

CPP_FILE = "eki-stamps.cpp"
EXE_FILE = "./eki-stamps"

print("Compiling...")
compile_result = subprocess.run(["g++", "-O2", "-std=c++17", CPP_FILE, "-o", EXE_FILE[2:]])

if compile_result.returncode != 0:
    print("❌ Compilation failed.")
    exit(1)
else:
    print("✅ Compiled successfully.\n")

# Expanded test cases
test_cases = [
    {"input": "4\n8 4 1 2\n"},
    {"input": "6\n2 -5 1 5 3 2\n"},
    {"input": "3\n5 5 5\n"},
    {"input": "4\n1 2 4 3\n"},
    {"input": "5\n1 10 20 21 22\n"},
    {"input": "2\n1 100000\n"},
    {"input": "6\n1 2 3 4 5 6\n"},
    {"input": "6\n6 5 4 3 2 1\n"},
    {"input": "6\n1 100 101 102 103 104\n"},
    {"input": "7\n0 1 1 1 2 3 3\n"},
    {"input": "1\n0\n"},
    {"input": "5\n1 1 2 3 4\n"},
    {"input": "4\n1 1000 2 3\n"},
    {"input": "4\n0 1000 2000 3000\n"},
    {"input": "4\n0 1 2 0\n"},
    {"input": "5\n0 2 5 10 10\n"},
    {"input": "5\n0 0 0 0 1\n"},
    {"input": "6\n10 5 1 1 5 10\n"},
    {"input": "7\n1 2 3 4 5 6 6\n"},
    {"input": "3\n100000 0 100000\n"},
    {"input": "3\n100000 99999 99998\n"}
]

def validate_output(output, input_str):
    try:
        lines = input_str.strip().split("\n")
        n = int(lines[0])
        positions = list(map(int, lines[1].split()))
        output = output.strip()
        if output == "0":
            return True  # Valid failure
        stamp_order = list(map(int, output.strip().split()))

        if len(stamp_order) != n:
            return False

        if sorted(stamp_order) != list(range(1, n + 1)):
            return False

        last_pos = positions[stamp_order[0] - 1]
        last_dist = 0
        for i in range(1, n):
            current_pos = positions[stamp_order[i] - 1]
            dist = abs(current_pos - last_pos)
            if dist < last_dist:
                return False
            last_pos = current_pos
            last_dist = dist

        return True
    except:
        return output.strip() == "0"

print("Running Tests...\n")
passed = 0

for idx, test in enumerate(test_cases):
    print(f"Test Case {idx + 1}:")
    proc = subprocess.Popen(EXE_FILE, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    try:
        out, err = proc.communicate(test["input"], timeout=2)
    except subprocess.TimeoutExpired:
        proc.kill()
        print(f"⏰ Timeout")
        continue

    if validate_output(out, test["input"]):
        print(f"✅ Passed")
        passed += 1
    else:
        print(f"❌ Failed")
        print(f"Input:\n{test['input']}")
        print(f"Output:\n{out.strip()}")
    print()

print(f"Summary: {passed}/{len(test_cases)} tests passed.")
