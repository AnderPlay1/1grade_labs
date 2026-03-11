#include <Arduino.h>
#include <stdint.h>

using char_size_t = uint16_t;

const int CHAR_OK = 0;
const int CHAR_ERR_INVALID_ARG = -1;
const int CHAR_ERR_OVERFLOW = -2;
const int CHAR_ERR_OUT_OF_RANGE = -3;

char_size_t char_length_a(const char *str);
bool char_empty_a(const char *str);

int char_copy_a(char *dest, char_size_t capacity, const char *src);
int char_clear_a(char *str, char_size_t capacity);

int char_resize_a(char *str, char_size_t capacity, char_size_t new_size, char fill_char = '\0');

int char_insert_a(char *str, char_size_t capacity, char_size_t pos, const char *substring);
int char_insert_a(char *str, char_size_t capacity, char_size_t pos, char ch);

int char_erase_a(char *str, char_size_t pos, char_size_t count);
int char_replace_a(char *str, char_size_t capacity, char_size_t pos, char_size_t count, const char *new_substr);

int char_find_a(const char *str, const char *substring, char_size_t pos = 0);
int char_rfind_a(const char *str, const char *substring);

int char_substr_a(const char *str, char *out, char_size_t out_capacity, char_size_t pos, char_size_t count);

int char_append_a(char *str, char_size_t capacity, const char *substring);
int char_append_a(char *str, char_size_t capacity, char ch);

void char_swap_a(char *str1, char_size_t cap1, char *str2, char_size_t cap2);

int char_memory_storage_a(const char *str);
int freeMemory();

static const uint16_t BUF_SIZE = 64;
static const uint32_t ITERATIONS = 1000;

char s1[BUF_SIZE];
char s2[BUF_SIZE];
char sub[BUF_SIZE];

char_size_t char_length_a(const char *str)
{
    if (str == nullptr)
        return 0;

    char_size_t len = 0;
    while (str[len] != '\0')
    {
        ++len;
    }
    return len;
}

bool char_empty_a(const char *str)
{
    return (str == nullptr || str[0] == '\0');
}

int char_copy_a(char *dest, char_size_t capacity, const char *src)
{
    if (dest == nullptr || src == nullptr || capacity == 0)
    {
        return CHAR_ERR_INVALID_ARG;
    }

    char_size_t src_len = char_length_a(src);
    if (src_len + 1 > capacity)
    {
        return CHAR_ERR_OVERFLOW;
    }

    for (char_size_t i = 0; i < src_len; ++i)
    {
        dest[i] = src[i];
    }
    dest[src_len] = '\0';

    return CHAR_OK;
}

int char_clear_a(char *str, char_size_t capacity)
{
    if (str == nullptr || capacity == 0)
    {
        return CHAR_ERR_INVALID_ARG;
    }

    str[0] = '\0';
    return CHAR_OK;
}

int char_resize_a(char *str, char_size_t capacity, char_size_t new_size, char fill_char)
{
    if (str == nullptr || capacity == 0)
    {
        return CHAR_ERR_INVALID_ARG;
    }

    if (new_size + 1 > capacity)
    {
        return CHAR_ERR_OVERFLOW;
    }

    char_size_t old_len = char_length_a(str);

    if (new_size > old_len)
    {
        for (char_size_t i = old_len; i < new_size; ++i)
        {
            str[i] = fill_char;
        }
    }

    str[new_size] = '\0';
    return CHAR_OK;
}

int char_insert_a(char *str, char_size_t capacity, char_size_t pos, const char *substring)
{
    if (str == nullptr || substring == nullptr || capacity == 0)
    {
        return CHAR_ERR_INVALID_ARG;
    }

    char_size_t len = char_length_a(str);
    char_size_t sub_len = char_length_a(substring);

    if (pos > len)
    {
        return CHAR_ERR_OUT_OF_RANGE;
    }

    if (len + sub_len + 1 > capacity)
    {
        return CHAR_ERR_OVERFLOW;
    }

    for (int i = (int)len; i >= (int)pos; --i)
    {
        str[i + sub_len] = str[i];
    }

    for (char_size_t i = 0; i < sub_len; ++i)
    {
        str[pos + i] = substring[i];
    }

    return CHAR_OK;
}

int char_insert_a(char *str, char_size_t capacity, char_size_t pos, char ch)
{
    char temp[2];
    temp[0] = ch;
    temp[1] = '\0';
    return char_insert_a(str, capacity, pos, temp);
}

int char_erase_a(char *str, char_size_t pos, char_size_t count)
{
    if (str == nullptr)
    {
        return CHAR_ERR_INVALID_ARG;
    }

    char_size_t len = char_length_a(str);
    if (pos > len)
    {
        return CHAR_ERR_OUT_OF_RANGE;
    }

    if (pos == len)
    {
        return CHAR_OK;
    }

    if (count == 0 || pos + count > len)
    {
        count = len - pos;
    }

    for (char_size_t i = pos; i + count <= len; ++i)
    {
        str[i] = str[i + count];
    }

    return CHAR_OK;
}

int char_replace_a(char *str, char_size_t capacity, char_size_t pos, char_size_t count, const char *new_substr)
{
    if (str == nullptr || new_substr == nullptr)
    {
        return CHAR_ERR_INVALID_ARG;
    }

    char_size_t len = char_length_a(str);
    if (pos > len)
    {
        return CHAR_ERR_OUT_OF_RANGE;
    }

    if (count == 0 || pos + count > len)
    {
        count = len - pos;
    }

    char temp[64];

    if (capacity > sizeof(temp))
    {
        return CHAR_ERR_OVERFLOW;
    }

    int rc = char_copy_a(temp, sizeof(temp), str);
    if (rc != CHAR_OK)
        return rc;

    rc = char_erase_a(temp, pos, count);
    if (rc != CHAR_OK)
        return rc;

    rc = char_insert_a(temp, sizeof(temp), pos, new_substr);
    if (rc != CHAR_OK)
        return rc;

    return char_copy_a(str, capacity, temp);
}

int char_find_a(const char *str, const char *substring, char_size_t pos)
{
    if (str == nullptr || substring == nullptr)
    {
        return -1;
    }

    char_size_t len = char_length_a(str);
    char_size_t sub_len = char_length_a(substring);

    if (sub_len == 0)
    {
        return (pos <= len) ? pos : -1;
    }

    if (pos > len || sub_len > len)
    {
        return -1;
    }

    for (char_size_t i = pos; i + sub_len <= len; ++i)
    {
        bool match = true;
        for (char_size_t j = 0; j < sub_len; ++j)
        {
            if (str[i + j] != substring[j])
            {
                match = false;
                break;
            }
        }
        if (match)
            return (int)i;
    }

    return -1;
}

int char_rfind_a(const char *str, const char *substring)
{
    if (str == nullptr || substring == nullptr)
    {
        return -1;
    }

    char_size_t len = char_length_a(str);
    char_size_t sub_len = char_length_a(substring);

    if (sub_len == 0)
        return (int)len;
    if (sub_len > len)
        return -1;

    for (int i = (int)(len - sub_len); i >= 0; --i)
    {
        bool match = true;
        for (char_size_t j = 0; j < sub_len; ++j)
        {
            if (str[i + j] != substring[j])
            {
                match = false;
                break;
            }
        }
        if (match)
            return i;
    }

    return -1;
}

int char_substr_a(const char *str, char *out, char_size_t out_capacity, char_size_t pos, char_size_t count)
{
    if (str == nullptr || out == nullptr || out_capacity == 0)
    {
        return CHAR_ERR_INVALID_ARG;
    }

    char_size_t len = char_length_a(str);
    if (pos > len)
    {
        return CHAR_ERR_OUT_OF_RANGE;
    }

    if (count == 0 || pos + count > len)
    {
        count = len - pos;
    }

    if (count + 1 > out_capacity)
    {
        return CHAR_ERR_OVERFLOW;
    }

    for (char_size_t i = 0; i < count; ++i)
    {
        out[i] = str[pos + i];
    }
    out[count] = '\0';

    return CHAR_OK;
}

int char_append_a(char *str, char_size_t capacity, const char *substring)
{
    if (str == nullptr || substring == nullptr)
    {
        return CHAR_ERR_INVALID_ARG;
    }

    return char_insert_a(str, capacity, char_length_a(str), substring);
}

int char_append_a(char *str, char_size_t capacity, char ch)
{
    char temp[2];
    temp[0] = ch;
    temp[1] = '\0';
    return char_append_a(str, capacity, temp);
}

void char_swap_a(char *str1, char_size_t cap1, char *str2, char_size_t cap2)
{
    if (str1 == nullptr || str2 == nullptr)
        return;

    char temp[64];

    if (cap1 > sizeof(temp) || cap2 > sizeof(temp))
        return;
    if (char_copy_a(temp, sizeof(temp), str1) != CHAR_OK)
        return;
    if (char_copy_a(str1, cap1, str2) != CHAR_OK)
        return;
    if (char_copy_a(str2, cap2, temp) != CHAR_OK)
        return;
}

int char_memory_storage_a(const char *str)
{
    if (str == nullptr)
        return 0;
    return (int)char_length_a(str) + 1;
}

#if defined(__AVR__)
extern unsigned int __heap_start;
extern void *__brkval;

int freeMemory()
{
    int v;
    return (int)&v - (__brkval == 0 ? (int)&__heap_start : (int)__brkval);
}
#else
int freeMemory()
{
    return -1;
}
#endif

void printHeader(const __FlashStringHelper *title)
{
    Serial.println();
    Serial.println(F("========================================"));
    Serial.println(title);
    Serial.println(F("========================================"));
}

unsigned long measure_append()
{
    char_clear_a(s1, BUF_SIZE);
    char_copy_a(s1, BUF_SIZE, "Hello");

    unsigned long start = micros();
    for (uint32_t i = 0; i < ITERATIONS; ++i)
    {
        char_append_a(s1, BUF_SIZE, "!");
        char_erase_a(s1, 5, 1);
    }
    unsigned long finish = micros();
    return (finish - start) / ITERATIONS;
}

unsigned long measure_insert()
{
    char_clear_a(s1, BUF_SIZE);
    char_copy_a(s1, BUF_SIZE, "Hello");

    unsigned long start = micros();
    for (uint32_t i = 0; i < ITERATIONS; ++i)
    {
        char_insert_a(s1, BUF_SIZE, 5, '!');
        char_erase_a(s1, 5, 1);
    }
    unsigned long finish = micros();
    return (finish - start) / ITERATIONS;
}

unsigned long measure_find()
{
    char_clear_a(s1, BUF_SIZE);
    char_copy_a(s1, BUF_SIZE, "Hello Arduino Hello");

    volatile int pos = -1;
    unsigned long start = micros();
    for (uint32_t i = 0; i < ITERATIONS; ++i)
    {
        pos = char_find_a(s1, "Arduino", 0);
    }
    unsigned long finish = micros();
    (void)pos;
    return (finish - start) / ITERATIONS;
}

unsigned long measure_replace()
{
    char_clear_a(s1, BUF_SIZE);
    char_copy_a(s1, BUF_SIZE, "Hello World");

    unsigned long start = micros();
    for (uint32_t i = 0; i < ITERATIONS; ++i)
    {
        char_replace_a(s1, BUF_SIZE, 6, 5, "UNO");
        char_replace_a(s1, BUF_SIZE, 6, 3, "World");
    }
    unsigned long finish = micros();
    return (finish - start) / ITERATIONS;
}

void runPart1()
{
    printHeader(F("Part 1. Functional test"));

    char_copy_a(s1, BUF_SIZE, "Hello");
    char_copy_a(s2, BUF_SIZE, "World");

    Serial.print(F("Initial s1: "));
    Serial.println(s1);

    Serial.print(F("Length: "));
    Serial.println(char_length_a(s1));

    Serial.print(F("Empty: "));
    Serial.println(char_empty_a(s1) ? F("true") : F("false"));

    char_append_a(s1, BUF_SIZE, " Arduino");
    Serial.print(F("Append: "));
    Serial.println(s1);

    char_insert_a(s1, BUF_SIZE, 5, ',');
    Serial.print(F("Insert: "));
    Serial.println(s1);

    char_erase_a(s1, 5, 1);
    Serial.print(F("Erase: "));
    Serial.println(s1);

    char_replace_a(s1, BUF_SIZE, 6, 7, "UNO");
    Serial.print(F("Replace: "));
    Serial.println(s1);

    Serial.print(F("Find 'UNO': "));
    Serial.println(char_find_a(s1, "UNO", 0));

    Serial.print(F("RFind 'l': "));
    Serial.println(char_rfind_a(s1, "l"));

    char_substr_a(s1, sub, BUF_SIZE, 6, 3);
    Serial.print(F("Substr: "));
    Serial.println(sub);

    char_swap_a(s1, BUF_SIZE, s2, BUF_SIZE);
    Serial.print(F("Swap s1: "));
    Serial.println(s1);
    Serial.print(F("Swap s2: "));
    Serial.println(s2);

    char_clear_a(s1, BUF_SIZE);
    Serial.print(F("Clear s1 -> '"));
    Serial.print(s1);
    Serial.println(F("'"));
}

void runPart2()
{
    printHeader(F("Part 2. Benchmark"));

    int ramBefore;
    int ramAfter;
    unsigned long t;

    Serial.println(F("Function | Time(us) | RAM delta(bytes)"));

    ramBefore = freeMemory();
    t = measure_append();
    ramAfter = freeMemory();
    Serial.print(F("append | "));
    Serial.print(t);
    Serial.print(F(" | "));
    Serial.println(ramBefore - ramAfter);

    ramBefore = freeMemory();
    t = measure_insert();
    ramAfter = freeMemory();
    Serial.print(F("insert | "));
    Serial.print(t);
    Serial.print(F(" | "));
    Serial.println(ramBefore - ramAfter);

    ramBefore = freeMemory();
    t = measure_find();
    ramAfter = freeMemory();
    Serial.print(F("find | "));
    Serial.print(t);
    Serial.print(F(" | "));
    Serial.println(ramBefore - ramAfter);

    ramBefore = freeMemory();
    t = measure_replace();
    ramAfter = freeMemory();
    Serial.print(F("replace | "));
    Serial.print(t);
    Serial.print(F(" | "));
    Serial.println(ramBefore - ramAfter);

    Serial.println();
}

void setup()
{
    Serial.begin(115200);
    delay(1000);

    printHeader(F("Arduino char array library"));
    Serial.println(F("Fixed-buffer implementation without dynamic allocation."));
    Serial.print(F("Buffer size: "));
    Serial.println(BUF_SIZE);
    Serial.print(F("Iterations: "));
    Serial.println(ITERATIONS);

    runPart1();
    runPart2();
}

void loop()
{
}