import sys

if len(sys.argv) == 3:
    try:
        number1 = float(sys.argv[1])
        number2 = float(sys.argv[2])
        result = number1 * number2
        print(result)
    except Exception as e:
        print(f"Error: {e}")
else:
    print("Not enough arguments.")

