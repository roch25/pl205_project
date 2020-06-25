#define IS_UPPER_CASE(x) (x > 64 && x < 91)
#define IS_LOWER_CASE(x) (x > 96 && x < 123)
#define IS_APOSTROPHE(x) x == 39
#define IS_SPACE(x) x == 32
#define IS_FULLPOINT(x) x == 46

int validate_name(char name[25]);
int validate_phone_number(char value[]);
int check_dupilcate_contact_details(char *name, char *phone_num);