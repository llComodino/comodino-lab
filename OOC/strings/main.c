#include "string_manipulation.h"
#include <stdio.h>
#include <stdlib.h>

#define BUFFER 100

int main (void) {
    // Messing around with strings and methods
    // Also with pointers, therefore memory allocation
    // and deallocation is required

    struct String *str = new_string();

    printf("Enter a string: ");
    str->get_string(str, BUFFER);

    printf("The string is: %s\n", str->str);
    printf("The length of the string is: %d\n", str->length(str));
    
    str->to_upper(str);
    printf("To upper: %s\n", str->str);
    
    str->to_lower(str);
    printf("To lower: %s\n\n", str->str);


    // --------------------------------------------- //
    
    struct String *str2 = new_string();

    printf("Enter a new string: ");
    str2->get_string(str2, BUFFER);

    printf("The new string is: %s\n", str2->str);
    
    str2->concatenate(str, str2);
    printf("Concatenated string [str + str2]: %s\n\n", str->str);

    // --------------------------------------------- //
    
    // Testing character replacement

    char selected_char;
    printf("Enter a character to replace: ");
    scanf("%c", &selected_char);

    char replacement_char;
    printf("Enter a character to replace with: ");
    scanf(" %c", &replacement_char);

    getchar(); // Clearing input buffer

    str->replace(str, selected_char, replacement_char);
    printf("Replaced character: %s\n\n", str->str);

    // --------------------------------------------- //

    // Clearing previous inputs, testing conversions

    str->clear_string(str);
    str2->clear_string(str2);

    printf("Enter an integer: ");
    str->get_string(str, BUFFER);

    printf("Enter a decimal (will be converted to double): ");
    str2->get_string(str2, BUFFER);

    printf("The integer is: %d\n", str->to_int(str));
    printf("The decimal is: %lf\n\n", str2->to_double(str2));

    // --------------------------------------------- //
    
    // Clearing previous inputs, testing inverted conversions

    str->clear_string(str);
    str2->clear_string(str2);

    str->from_int(str, 123);
    str2->from_double(str2, 123.456);

    puts("Testing inverted conversions:\nString from int: 123\nString from double: 123.456");
    printf("The integer is: %s\n", str->str);
    printf("The decimal is: %s\n\n", str2->str);

    // --------------------------------------------- //
    
    // Freeing memory
    // This is not necessary, but it's good practice
    
    str->delete_string(str);
    str2->delete_string(str2);

    free(str);
    free(str2);

    return 0;
}
