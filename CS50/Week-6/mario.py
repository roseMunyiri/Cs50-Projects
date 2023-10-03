# TODO

def main():
    height = 0
    while height < 1 or height > 8:
        height = int(input("Enter height: "))

    for rows in range(height):
        # Print spaces before the hashes to make a right-aligned pyramid
        for spaces in range(height - rows - 1):
            print(" ", end="")

        # Print hashes for each column
        for columns in range(rows + 1):
            print("#", end="")

        # Print the gap between the two sides of the pyramid
        print("  ", end="")

        # Print the hashes for the second side of the pyramid
        for columns in range(rows + 1):
            print("#", end="")

        print()  # Move to the next line

if __name__ == "__main__":
    main()
