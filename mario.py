
while True:
    try:
        height = int(input("Height: "))
        if 0 < height <= 8:
            break
        else:
            print("Invalid height. Please enter a number between 1 and 8 (inclusive).")
    except ValueError:
        print("Invalid height. Please enter a number.")

for i in range(height):
    # Left side spaces
    for j in range(height - i - 1):
        print(" ", end="")

    # Left side hashes
    for j in range(i + 1):
        print("#", end="")

    # Center gap
    print("  ", end="")

    # Right side hashes
    for j in range(i + 1):
        print("#", end="")

    # Move to the next line
    print()
