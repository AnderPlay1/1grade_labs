#ifndef CHAR_ARRAY_LIB_H
#define CHAR_ARRAY_LIB_H

inline constexpr int CHAR_NPOS = -1;
inline constexpr int CHAR_SUCCESS = 0;
inline constexpr int CHAR_ERR_INVALID_ARG = -1;
inline constexpr int CHAR_ERR_ALLOC = -2;

int char_length(const char *str);
bool char_empty(const char *str);

char *char_create(const char *src);
void char_destroy(char **str);

int char_resize(char **str, int new_size, char fill_char = '\0');
void char_clear(char **str);

int char_insert(char **str, int pos, const char *substring);
int char_insert(char **str, int pos, char ch);

int char_erase(char **str, int pos, int count = CHAR_NPOS);

int char_replace(char **str, int pos, int count, const char *new_substr);

int char_find(const char *str, const char *substring, int pos = 0);
int char_rfind(const char *str, const char *substring, int pos = CHAR_NPOS);

char *char_substr(const char *str, int pos, int count = CHAR_NPOS);

int char_append(char **str, const char *substring);
int char_append(char **str, char ch);

void char_swap(char **str1, char **str2);

int char_memory_storage(const char *str);

#endif