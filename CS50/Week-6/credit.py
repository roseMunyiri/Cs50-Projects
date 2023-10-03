import re

def main():
    card_number = input("Enter credit card number: ")
    if not card_number.isdigit():
        print("Invalid input. Please enter a valid credit card number.")
        return

    card_type = get_card_type(card_number)
    if card_type == "INVALID":
        print(card_type)
    else:
        if is_valid(card_number):
            print(card_type)
        else:
            print("INVALID")


def get_card_type(card_number):
    if re.match(r"^(34|37)\d{13}$", card_number):
        return "AMEX"
    elif re.match(r"^(51|52|53|54|55)\d{14}$", card_number):
        return "MASTERCARD"
    elif re.match(r"^4\d{12}(\d{3})?$", card_number):
        return "VISA"
    else:
        return "INVALID"


def is_valid(card_number):
    card_number = card_number[::-1]  # Reverse the card number for easier processing
    total = 0
    for i, digit in enumerate(card_number):
        digit = int(digit)
        if i % 2 == 1:  # Double every other digit
            digit *= 2
            if digit > 9:  # If the doubled digit is greater than 9, sum its digits
                digit = digit // 10 + digit % 10
        total += digit
    return total % 10 == 0


if __name__ == "__main__":
    main()
