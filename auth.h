#ifndef AUTH_H
#define AUTH_H

#include <stdbool.h>

#define USERDATA_FILE "userdata.csv"
#define ROLE "admin"

// Function declarations
bool sign_up(const char *username, const char *password);
bool sign_in(const char *username, const char *password);
char *hash_password(const char *password);
bool file_exists(const char *filename);

#endif // AUTH_H

