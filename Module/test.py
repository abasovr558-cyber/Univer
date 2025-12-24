import sum_module
import random
import time

def sum_pure_python(arr):
    total = 0
    for num in arr:
        total += num
    return total

print("тест: сумма элементов массива")

test_sizes = [1000000, 5000000, 10000000]

print(f"{'Размер':<10} | {'C++ (с)':<10} | {'Python (с)':<12} | {'совпадает?'}")
print("-" * 50)

for size in test_sizes:
    test_data = [random.randint(1, 100) for _ in range(size)]
    
    result = sum_module.sum_array(test_data)
    cpp_sum, cpp_time = result
    
    start_py = time.perf_counter()
    py_sum = sum_pure_python(test_data)
    py_time = time.perf_counter() - start_py
    
    match = cpp_sum == py_sum
    
    print(f"{size:<10} | {cpp_time:<10.2f} | {py_time:<12.2f} | {match}")

