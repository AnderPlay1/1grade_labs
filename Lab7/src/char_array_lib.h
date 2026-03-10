#include <new>

const int CHAR_NPOS = -1;
const int CHAR_SUCCESS = 0;
const int CHAR_ERR_INVALID_ARG = -1;
const int CHAR_ERR_ALLOC = -2;

static void copy_chars(char *dest, const char *src, int count)
{
    for (int i = 0; i < count; ++i)
    {
        dest[i] = src[i];
    }
}

int char_length(const char *str)
{
    if (str == nullptr)
    {
        return 0;
    }

    int len = 0;
    while (str[len] != '\0')
    {
        ++len;
    }
    return len;
}

bool char_empty(const char *str)
{
    return (str == nullptr || str[0] == '\0');
}

char *char_create(const char *src)
{
    if (src == nullptr)
    {
        return nullptr;
    }

    int len = char_length(src);
    char *result = new (std::nothrow) char[len + 1];
    if (result == nullptr)
    {
        return nullptr;
    }

    copy_chars(result, src, len);
    result[len] = '\0';
    return result;
}

void char_destroy(char **str)
{
    if (str == nullptr)
    {
        return;
    }

    delete[] *str;
    *str = nullptr;
}

int char_resize(char **str, int new_size, char fill_char)
{
    if (str == nullptr || new_size < 0)
    {
        return CHAR_ERR_INVALID_ARG;
    }

    int old_size = (*str == nullptr) ? 0 : char_length(*str);

    char *new_str = new (std::nothrow) char[new_size + 1];
    if (new_str == nullptr)
    {
        return CHAR_ERR_ALLOC;
    }

    int copy_count = (old_size < new_size) ? old_size : new_size;

    if (*str != nullptr)
    {
        copy_chars(new_str, *str, copy_count);
    }

    for (int i = copy_count; i < new_size; ++i)
    {
        new_str[i] = fill_char;
    }

    new_str[new_size] = '\0';

    delete[] *str;
    *str = new_str;

    return CHAR_SUCCESS;
}

void char_clear(char **str)
{
    if (str == nullptr)
    {
        return;
    }

    delete[] *str;
    *str = nullptr;
}

int char_insert(char **str, int pos, const char *substring)
{
    if (str == nullptr || substring == nullptr)
    {
        return CHAR_ERR_INVALID_ARG;
    }

    int len = (*str == nullptr) ? 0 : char_length(*str);
    int sub_len = char_length(substring);

    if (pos < 0 || pos > len)
    {
        return CHAR_ERR_INVALID_ARG;
    }

    char *new_str = new (std::nothrow) char[len + sub_len + 1];
    if (new_str == nullptr)
    {
        return CHAR_ERR_ALLOC;
    }

    for (int i = 0; i < pos; ++i)
    {
        new_str[i] = (*str)[i];
    }

    for (int i = 0; i < sub_len; ++i)
    {
        new_str[pos + i] = substring[i];
    }

    for (int i = pos; i < len; ++i)
    {
        new_str[sub_len + i] = (*str)[i];
    }

    new_str[len + sub_len] = '\0';

    delete[] *str;
    *str = new_str;

    return CHAR_SUCCESS;
}

int char_insert(char **str, int pos, char ch)
{
    char temp[2];
    temp[0] = ch;
    temp[1] = '\0';
    return char_insert(str, pos, temp);
}

int char_erase(char **str, int pos, int count)
{
    if (str == nullptr || *str == nullptr)
    {
        return CHAR_ERR_INVALID_ARG;
    }

    int len = char_length(*str);

    if (pos < 0 || pos > len)
    {
        return CHAR_ERR_INVALID_ARG;
    }

    if (pos == len)
    {
        return CHAR_SUCCESS;
    }

    if (count == CHAR_NPOS || count <= 0 || pos + count > len)
    {
        count = len - pos;
    }

    int new_len = len - count;
    char *new_str = new (std::nothrow) char[new_len + 1];
    if (new_str == nullptr)
    {
        return CHAR_ERR_ALLOC;
    }

    int idx = 0;

    for (int i = 0; i < pos; ++i)
    {
        new_str[idx++] = (*str)[i];
    }

    for (int i = pos + count; i < len; ++i)
    {
        new_str[idx++] = (*str)[i];
    }

    new_str[idx] = '\0';

    delete[] *str;
    *str = new_str;

    return CHAR_SUCCESS;
}

int char_replace(char **str, int pos, int count, const char *new_substr)
{
    if (str == nullptr || *str == nullptr || new_substr == nullptr)
    {
        return CHAR_ERR_INVALID_ARG;
    }

    int len = char_length(*str);

    if (pos < 0 || pos > len)
    {
        return CHAR_ERR_INVALID_ARG;
    }

    if (count == CHAR_NPOS || count < 0 || pos + count > len)
    {
        count = len - pos;
    }

    int new_sub_len = char_length(new_substr);
    int new_len = len - count + new_sub_len;

    char *new_str = new (std::nothrow) char[new_len + 1];
    if (new_str == nullptr)
    {
        return CHAR_ERR_ALLOC;
    }

    int idx = 0;

    for (int i = 0; i < pos; ++i)
    {
        new_str[idx++] = (*str)[i];
    }

    for (int i = 0; i < new_sub_len; ++i)
    {
        new_str[idx++] = new_substr[i];
    }

    for (int i = pos + count; i < len; ++i)
    {
        new_str[idx++] = (*str)[i];
    }

    new_str[idx] = '\0';

    delete[] *str;
    *str = new_str;

    return CHAR_SUCCESS;
}

int char_find(const char *str, const char *substring, int pos)
{
    if (str == nullptr || substring == nullptr || pos < 0)
    {
        return CHAR_NPOS;
    }

    int len = char_length(str);
    int sub_len = char_length(substring);

    if (sub_len == 0)
    {
        return (pos <= len) ? pos : CHAR_NPOS;
    }

    if (pos > len || sub_len > len)
    {
        return CHAR_NPOS;
    }

    for (int i = pos; i <= len - sub_len; ++i)
    {
        bool match = true;
        for (int j = 0; j < sub_len; ++j)
        {
            if (str[i + j] != substring[j])
            {
                match = false;
                break;
            }
        }
        if (match)
        {
            return i;
        }
    }

    return CHAR_NPOS;
}

int char_rfind(const char *str, const char *substring, int pos)
{
    if (str == nullptr || substring == nullptr)
    {
        return CHAR_NPOS;
    }

    int len = char_length(str);
    int sub_len = char_length(substring);

    if (sub_len == 0)
    {
        if (pos == CHAR_NPOS || pos > len)
        {
            return len;
        }
        return pos;
    }

    if (sub_len > len)
    {
        return CHAR_NPOS;
    }

    int start = len - sub_len;
    if (pos != CHAR_NPOS && pos < start)
    {
        start = pos;
    }

    for (int i = start; i >= 0; --i)
    {
        bool match = true;
        for (int j = 0; j < sub_len; ++j)
        {
            if (str[i + j] != substring[j])
            {
                match = false;
                break;
            }
        }
        if (match)
        {
            return i;
        }
    }

    return CHAR_NPOS;
}

char *char_substr(const char *str, int pos, int count)
{
    if (str == nullptr)
    {
        return nullptr;
    }

    int len = char_length(str);

    if (pos < 0 || pos > len)
    {
        return nullptr;
    }

    if (pos == len)
    {
        char *empty = new (std::nothrow) char[1];
        if (empty == nullptr)
        {
            return nullptr;
        }
        empty[0] = '\0';
        return empty;
    }

    if (count == CHAR_NPOS || count < 0 || pos + count > len)
    {
        count = len - pos;
    }

    char *result = new (std::nothrow) char[count + 1];
    if (result == nullptr)
    {
        return nullptr;
    }

    for (int i = 0; i < count; ++i)
    {
        result[i] = str[pos + i];
    }

    result[count] = '\0';
    return result;
}

int char_append(char **str, const char *substring)
{
    if (str == nullptr || substring == nullptr)
    {
        return CHAR_ERR_INVALID_ARG;
    }

    if (*str == nullptr)
    {
        *str = char_create("");
        if (*str == nullptr)
        {
            return CHAR_ERR_ALLOC;
        }
    }

    int len = char_length(*str);
    return char_insert(str, len, substring);
}

int char_append(char **str, char ch)
{
    char temp[2];
    temp[0] = ch;
    temp[1] = '\0';
    return char_append(str, temp);
}

void char_swap(char **str1, char **str2)
{
    if (str1 == nullptr || str2 == nullptr)
    {
        return;
    }

    char *temp = *str1;
    *str1 = *str2;
    *str2 = temp;
}

int char_memory_storage(const char *str)
{
    if (str == nullptr)
    {
        return 0;
    }
    return char_length(str) + 1;
}