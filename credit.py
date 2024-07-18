import re


def luhn_algorithm(card):
    sum = 0
    boolean = 0

    while (card != 0):
        digit = card % 10
        if (boolean == 0):
            sum += digit
            boolean = not boolean
        else:
            doubled = digit * 2
            if (doubled > 9):
                sum += doubled - 9
                boolean = not boolean
            else:
                sum += doubled
                boolean = not boolean
        card = card // 10
    return sum


def is_valid_card(card):
    sum = luhn_algorithm(card)
    return sum % 10 == 0
    # if (sum % 10 == 0)
    #     print("Passed Luhn")
    #     return true
    # else
    #     print("Failed Luhn")
    #     return false


def find_card_type(card):
    card_copy = card
    if (not is_valid_card(card)):
        return 'i'  # for invalid

    card_copy2 = card_copy
    count = 0
    while (card_copy != 0):    # find card number length
        card_copy = card_copy // 10
        count += 1

    original_card = card_copy2
    while (original_card >= 100):    # find first two digits
        original_card = original_card // 10

    first_two_digits = original_card
    if (first_two_digits == 34 or first_two_digits == 37 and count == 15):
        return 'a'  # for American Express

    if (first_two_digits >= 51 and first_two_digits <= 55 and count == 16):
        return 'm'  # for MasterCard

    while (card_copy2 >= 10):    # find first digit
        card_copy2 = card_copy2 // 10

    first_digit = card_copy2
    if (first_digit == 4 and (count == 13 or count == 16)):
        return 'v'  # for Visa

    return 'u'  # for "unknown", case where not invalid, AE, MC, or V


# Main logic
card = int(input("Card Number: "))      # store card number input
card_type = find_card_type(card)

if (card_type == 'i'):
    print("INVALID\n")
elif (card_type == 'a'):
    print("AMEX\n")
elif (card_type == 'm'):
    print("MASTERCARD\n")
elif (card_type == 'v'):
    print("VISA\n")
else:
    print("INVALID\n")
