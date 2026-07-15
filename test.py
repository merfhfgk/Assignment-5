import subprocess

def run_tests():
    executable = './calc' if os.name != 'nt' else 'calc.exe'
    
    
    commands = [
        "10 + 5",
        "10 / -2",
        "var x = 10",
        "x * 2",
        "max(10, 20)",
        "def f(x) { x * 2 }",
        "f(3)",
        "integral(f, 0, 10)"
    ]
    
    expected_results = [15.0, -5.0, 10.0, 20.0, 20.0, 0.0, 6.0, 100.0]

    print("testing...\n")
    
    input_data = "\n".join(commands) + "\n"
    
    process = subprocess.Popen(
        [executable],
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True
    )
    
    stdout, stderr = process.communicate(input=input_data)
    
    actual_numbers = []
    for line in stdout.split('\n'):
        cleaned = line.replace(">", "").replace("input:", "").replace("test", "").strip()
        if not cleaned: continue
        try:
            val = float(cleaned)
            actual_numbers.append(val)
        except ValueError:
            pass
    
    passed = 0
    print("Results:")
    
    for i in range(len(commands)):
        cmd = commands[i]
        expected = expected_results[i]
        
        if i < len(actual_numbers):
            actual = actual_numbers[i]
            is_success = abs(actual - expected) < 1.0 if "integral" in cmd else actual == expected
            
            if is_success:
                print(f"PASS: {cmd} == {actual}")
                passed += 1
            else:
                print(f"FAIL: {cmd}")
                print(f"Expected: {expected}, Actual output: {actual}")
        else:
            print(f"FAIL: {cmd} (No result at all)")
            
    print(f"\nResult: {passed}/{len(commands)} tests were passed")
    
    if len(actual_numbers) < len(commands):
        print(stdout)
        if stderr:
            print("Error (stderr):", stderr)

if __name__ == "__main__":
    run_tests()
