import subprocess

CPP_FILE = "find-the-word.cpp"
EXE_FILE = "./find-the-word"

print("Compiling...")
compile_result = subprocess.run(["g++", "-O2", "-std=c++17", CPP_FILE, "-o", EXE_FILE[2:]])

if compile_result.returncode != 0:
    print("❌ Compilation failed.")
    exit(1)
else:
    print("✅ Compiled successfully.\n")
test_cases = [
    # 1×1 grid, word length 1
    {"input": "1 A\nA\n",                                            "expected": "1"},
    {"input": "1 A\nB\n",                                            "expected": "0"},

    # 2×2 grid, word length 1  (just count the X’s)
    {"input": "2 X\nXX\nYX\n",                                       "expected": "3"},

    # 2×2 grid, word length 2, no double-count
    {"input": "2 XY\nXY\nYX\n",                                      "expected": "4"},

    # 3×3 grid, simple horizontal forward
    {"input": "3 ABC\nABC\nDEF\nGHI\n",                              "expected": "1"},

    # 3×3 grid, simple horizontal backward
    {"input": "3 CBA\nABC\nDEF\nGHI\n",                              "expected": "1"},

    # Sample 1 from problem
    {"input": "4 BUG\nBAGO\nUUBB\nBOBG\nGEGO\n",                     "expected": "1"},

    # Sample 2 from problem
    {"input": "3 XYZ\nXYZ\nYYZ\nZZZ\n",                              "expected": "3"},

    # Overlapping ABA, each segment once
    {"input": "3 ABA\nABA\nBAB\nABA\n",                              "expected": "4"},

    # All-A’s 3×3, each segment once
    {"input": "3 AAA\nAAA\nAAA\nAAA\n",                              "expected": "8"},

    # 4×4 grid, ABCD rows only (reverse uses DCBA, different word)
    {"input": "4 ABCD\nABCD\nDCBA\nABCD\nDCBA\n",                    "expected": "4"},

    # Word longer than grid
    {"input": "3 LONG\nABC\nDEF\nGHI\n",                             "expected": "0"},

    # Main diagonal HELLO
    {"input": "5 HELLO\nHXXXX\nEXXXX\nLXLXX\nLXXOX\nOXXXH\n",        "expected": "1"},

    # No TEST anywhere once we dedupe
    {"input": "4 TEST\nTSXX\nESTX\nXEST\nXXES\n",                    "expected": "0"},

    # CAT in staggered rows and one column, no double-count
    {"input": "5 CAT\nCATXX\nXCATX\nXXCAT\nXXXCA\nXXXXC\n",          "expected": "4"},

    # DOG cannot be formed in this grid
    {"input": "5 DOG\nDXOGD\nXOGDX\nOGDXO\nGDXOG\nDXOGX\n",          "expected": "0"},

    # Single-letter Z case
    {"input": "4 Z\nZABC\nDZQZ\nZZZZ\nQWER\n",                       "expected": "7"},
]



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

    output = out.strip()
    expected = test["expected"]

    if output == expected:
        print(f"✅ Passed (Output: {output})")
        passed += 1
    else:
        print(f"❌ Failed")
        print(f"Input:\n{test['input'].strip()}")
        print(f"Expected: {expected}")
        print(f"Got:      {output}")
        if err:
            print(f"stderr: {err.strip()}")
    print()

print(f"Summary: {passed}/{len(test_cases)} tests passed.")
