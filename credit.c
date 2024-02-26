# include <stdio.h>
# include <cs50.h>

long luhn_algorithm(long card);
bool is_valid_card(long card);
char find_card_type(long card);


int main(void){
    long card = get_long("Card Number: ");      // store card number input
    char card_type = find_card_type(card);
    if (card_type == 'i'){
        printf("INVALID\n");
    } else if (card_type == 'a'){
        printf("AMEX\n");
    } else if (card_type == 'm'){
        printf("MASTERCARD\n");
    } else if (card_type == 'v'){
        printf("VISA\n");
    } else{
        printf("INVALID\n");
    }
}


long luhn_algorithm(long card){
    long sum = 0;
    int boolean = 0;

    while (card != 0) {
        int digit = card % 10;
        if (boolean == 0){
            sum += digit;
            boolean = !boolean;
        } else {
            int doubled = digit * 2;
            if (doubled > 9){
                sum += doubled - 9;
                boolean = !boolean;
            } else{
                sum +=doubled;
                boolean = !boolean;
            }
        }
        card = card / 10;
    }
    return sum;
}


bool is_valid_card(long card) {
    long sum = luhn_algorithm(card);
    if (sum % 10 == 0) {
        return true;
    } else {
        return false;
    }
}


char find_card_type(long card){
    long card_copy = card;
    if (!is_valid_card(card)) {
        return 'i';  // for invalid
    }
    long card_copy2 = card_copy;
    int count = 0;
    while(card_copy !=0){    // find card number length
        card_copy = card_copy / 10;
        count +=1;
    }

    long original_card = card_copy2;
    while(original_card >= 100){    // find first two digits
        original_card = original_card / 10;
    }

    int first_two_digits = original_card;
    if (first_two_digits == 34 || first_two_digits == 37){
        if (count == 15){
            return 'a';  // for American Express
        }
    }

    if (first_two_digits >= 51 && first_two_digits <= 55){
        if (count == 16){
            return 'm';  // for MasterCard
        }
    }

    while(card_copy2 >= 10){    // find first digit
        card_copy2 = card_copy2 / 10;
    }
    int first_digit = card_copy2;
    if (first_digit == 4){
        if (count == 13 || count == 16){
            return 'v';  // for Visa
        }
    }
    return 'u';  // for "unknown", case where not invalid, AE, MC, or V
}