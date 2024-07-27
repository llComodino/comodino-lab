#ifndef STRING_MANIPULATION_H
#define STRING_MANIPULATION_H

#define MAX_STRING_SIZE 512
#define MIN_STRING_SIZE 1
#define DEFAULT_SIZE 32

struct String {
    char *str;
    unsigned int size;
    void (*get_string)(struct String *str, unsigned int size);
    void (*to_lower)(struct String *str);
    void (*to_upper)(struct String *str);
    void (*reverse)(struct String *str);
    void (*replace)(struct String *original, char old_char, char new_char);
    void (*concatenate)(struct String *original, struct String *addition);
    void (*clear_string)(struct String *str);
    unsigned int (*length)(struct String *str);
    void (*from_int)(struct String *str, unsigned int n);
    int (*to_int)(struct String *str);
    void (*from_double)(struct String *str, double d);
    double (*to_double)(struct String *str);
    void (*delete_string)(struct String *s);
};

struct String *new_string();
void get_string(struct String *str, unsigned int size);
void to_lower(struct String *str);
void to_upper(struct String *str);
void reverse(struct String *str);
void replace(struct String *original, char old_char, char new_char);
void concatenate(struct String *original, struct String *addition);
void clear_string(struct String *str);
unsigned int length(struct String *str);
void from_int(struct String *str, unsigned int n);
int to_int(struct String *str);
void from_double(struct String *str, double d);
double to_double(struct String *str);
void delete_string(struct String *s);

#endif // STRING_MANIPULATION_H
