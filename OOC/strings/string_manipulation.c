#include "string_manipulation.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/cdefs.h>

void get_string(struct String *str, unsigned int size) {
 
    if (size > MAX_STRING_SIZE || size < MIN_STRING_SIZE ) {
        puts("Invalid size");
        puts("Size must be between 1 and 512");
        return;
    }

    str->str = malloc(size * sizeof(char));
    
    fgets(str->str, size, stdin);

    int i = 0;
    while (str->str[i] != '\n') {
       i++;
    }

    str->str[i] = '\0';
    str->size = i;
}

void to_lower(struct String *str) {
    for (int i = 0; i < str->size; i++) {
        if (str->str[i] >= 'A' && str->str[i] <= 'Z') {
            str->str[i] += 32;
        }
    }
}

void to_upper(struct String *str) {
    for (int i = 0; i < str->size; i++) {
        if (str->str[i] >= 'a' && str->str[i] <= 'z') {
            str->str[i] -= 32;
        }
    }
}

void reverse(struct String *str) {
    for (int i = 0; i < str->size / 2; i++) {
        char temp = str->str[i];
        str->str[i] = str->str[str->size - i - 1];
        str->str[str->size - i - 1] = temp;
    }
}

void replace(struct String *original, char old_char, char new_char) {

    for (int i = 0; i < original->size; i++) {
        if (original->str[i] == old_char) {
            original->str[i] = new_char;
        }
    }
}

void concatenate(struct String *original, struct String *addition) {
    int original_length = length(original);
    int addition_length = length(addition);

    if (addition_length == 0) {
        return;
    }

    for (int i = 0; i < addition_length; i++) {
        original->str[original_length + i] = addition->str[i];
    }

    original->size += addition_length;
    original->str[original->size] = '\0';
}

void clear_string(struct String *str) {
    free(str->str);
    str->str = malloc(sizeof(char) * DEFAULT_SIZE);
    str->size = 0;
}

unsigned int length(struct String *str) {
    unsigned int i;
    for (i = 0; str->str[i] != '\0'; i++);
    return i;
}

void from_int(struct String *str, unsigned int n) {
    if (n == 0) {
        str->str[0] = '0';
        str->str[1] = '\0';
        str->size = 1;
        return;
    }

    int i = 0;
    while (n > 0) {
        str->str[i] = n % 10 + '0';
        n /= 10;
        i++;
    }

    str->str[i] = '\0';
    str->size = i;
    reverse(str);
}

int to_int(struct String *str) {
    int n = 0;
    for (int i = 0; i < str->size; i++) {
        n *= 10;
        n += str->str[i] - '0';
    }
    return n;
}

void from_double(struct String *str, double d) {
    if (d == 0) {
        str->str[0] = '0';
        str->str[1] = '\0';
        str->size = 1;
        return;
    }

    unsigned int int_part = (unsigned int) d;
    from_int(str, int_part);

    long long unsigned int decimal_part = (long long unsigned int) ((d - int_part) * 1000000000000000);
    
    struct String *append = new_string();
    
    append->str = malloc(sizeof(char));
    append->str[0] = '.';
    concatenate(str, append);
    
    append->clear_string(append);
    append->from_int(append, decimal_part);
    concatenate(str, append);

    str->size = length(str);
}

double to_double(struct String *str) {
    double d = 0;
    int i = 0;
    while (str->str[i] != '.') {
        d *= 10;
        d += str->str[i] - '0';
        i++;
    }

    i++;
    double decimal_part = 0;
    double decimal_multiplier = 0.1;
    while (str->str[i] != '\0') {
        decimal_part += (str->str[i] - '0') * decimal_multiplier;
        decimal_multiplier /= 10;
        i++;
    }

    return d + decimal_part;
}

void delete_string(struct String *s ) {
    free(s->str);
}

struct String *new_string() {
    
    struct String *string = malloc(sizeof(struct String));
    string->size = 0;
    string->str = NULL;
    
    string->get_string = get_string;
    string->to_lower = to_lower;
    string->to_upper = to_upper;
    string->reverse = reverse;
    string->replace = replace;
    string->concatenate = concatenate;
    string->clear_string = clear_string;
    string->length = length;
    string->from_int = from_int;
    string->to_int = to_int;
    string->from_double = from_double;
    string->to_double = to_double;
    string->delete_string = delete_string;

    return string;
}
