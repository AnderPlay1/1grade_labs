#include <iostream>
#include <iomanip>
#include <string>
#include <chrono>
#include <cstring>

#include "lib.h"
#include "char_array_lib.h"

using namespace std;

static void print_string_state(const char *label, const char *str)
{
    cout << label << ": ";
    if (str == nullptr)
    {
        cout << "nullptr";
    }
    else
    {
        cout << '"' << str << '"';
    }
    cout << '\n';
}

static char *input_char_string(const string &prompt)
{
    cout << prompt;
    string temp;
    cin >> temp;
    return char_create(temp.c_str());
}

static char readCharValue(const string &prompt)
{
    while (true)
    {
        cout << prompt << endl;
        string s;
        getline(cin, s);
        if (s.size() == 1)
        {
            return s[0];
        }
        cout << "Please enter exactly one character.\n";
    }
}

static void part1_demo()
{
    cout << "==================== Part 1 ====================\n";
    cout << "Manual testing of char array library functions.\n\n";

    char *s = input_char_string("Enter first string: ");
    char *other = input_char_string("Enter second string: ");
    char temp;
    char *str_temp;
    int temp_pos, temp_pos1;
    print_string_state("Initial s", s);
    print_string_state("Initial other", other);
    cout << "Length(s): " << char_length(s) << '\n';
    cout << "Empty(s): " << (char_empty(s) ? "true" : "false") << "\n\n";

    str_temp = input_char_string("Insert string to append: ");
    cout << "Append " << str_temp << " to s\n";
    cout << "Result code: " << char_append(&s, str_temp) << '\n';
    print_string_state("s", s);
    cout << '\n';

    temp = readCharValue("Insert char value to insert: ");
    temp_pos = readInt("Insert position of isertion: ", 0, char_length(s));
    cout << "Insert '" << temp << "' at position" << temp_pos << "\n";
    cout << "Result code: " << char_insert(&s, temp_pos, temp) << '\n';
    print_string_state("s", s);
    cout << '\n';

    temp_pos = readInt("Insert count of chars to erase: ", 0, char_length(s));
    temp_pos1 = readInt("Insert position of erase: ", 0, char_length(s));
    cout << "Erase " << temp_pos << " chars from position " << temp_pos1 << "\n";
    cout << "Result code: " << char_erase(&s, temp_pos, temp_pos1) << '\n';
    print_string_state("s", s);
    cout << '\n';

    temp_pos1 = readInt("Insert position of replace: ", 0, char_length(s));
    temp_pos = readInt("Insert count of chars to replace: ", 0, char_length(s));
    str_temp = input_char_string("Insert string to replace with: ");
    cout << "Replace from position " << temp_pos1 << " count " << temp_pos << " with " << str_temp << "\n";
    cout << "Result code: " << char_replace(&s, temp_pos1, temp_pos, str_temp) << '\n';
    print_string_state("s", s);
    cout << '\n';

    temp_pos = readInt("Insert int to resize: ", 0, 100);
    temp = readCharValue("Insert char value to resize: ");
    cout << "Resize s to " << temp_pos << " with fill char " << temp << "\n";
    cout << "Result code: " << char_resize(&s, temp_pos, temp) << '\n';
    print_string_state("s", s);
    cout << '\n';

    str_temp = input_char_string("Insert string to find: ");
    cout << "Find " << str_temp << " : " << char_find(s, str_temp) << '\n';

    str_temp = input_char_string("Insert string to rfind: ");
    cout << "RFind " << str_temp << " : " << char_rfind(s, str_temp) << '\n';

    temp_pos1 = readInt("Insert start position of substring: ", 0, char_length(s));
    temp_pos = readInt("Insert end position of substring: ", temp_pos1, char_length(s));
    char *sub = char_substr(s, temp_pos1, temp_pos);
    print_string_state("Substring ", sub);
    char_destroy(&sub);
    cout << '\n';

    cout << "Swap s and other\n";
    char_swap(&s, &other);
    print_string_state("s", s);
    print_string_state("other", other);
    cout << '\n';

    cout << "Clear s\n";
    char_clear(&s);
    print_string_state("s", s);
    cout << "Empty(s): " << (char_empty(s) ? "true" : "false") << "\n\n";

    cout << "Boundary checks:\n";
    cout << "Insert into nullptr string pointer value holder:\n";
    char *null_str = nullptr;
    cout << "append(nullptr-holder, \"abc\"): " << char_append(&null_str, "abc") << '\n';
    print_string_state("null_str", null_str);

    cout << "find(nullptr, \"a\"): " << char_find(nullptr, "a") << '\n';
    cout << "erase(out of range): " << char_erase(&other, 100, 1) << '\n';
    cout << "replace(out of range): " << char_replace(&other, 100, 2, "X") << '\n';
    cout << '\n';

    char_destroy(&s);
    char_destroy(&other);
    char_destroy(&null_str);
}

static long long measure_char_append_case(const char *base, const char *add, int iterations)
{
    char *s = char_create(base);
    auto start = chrono::high_resolution_clock::now();

    for (int i = 0; i < iterations; ++i)
    {
        char_append(&s, add);
        char_erase(&s, char_length(base), char_length(add));
    }

    auto end = chrono::high_resolution_clock::now();
    char_destroy(&s);

    return chrono::duration_cast<chrono::nanoseconds>(end - start).count() / iterations;
}

static long long measure_std_append_case(const string &base, const string &add, int iterations)
{
    string s = base;
    auto start = chrono::high_resolution_clock::now();

    for (int i = 0; i < iterations; ++i)
    {
        s.append(add);
        s.erase(base.size(), add.size());
    }

    auto end = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::nanoseconds>(end - start).count() / iterations;
}

static void print_benchmark_row(const string &label, const char *cstr, const string &sstr, int iterations)
{
    long long char_time = measure_char_append_case(cstr, "!", iterations);
    long long std_time = measure_std_append_case(sstr, "!", iterations);

    cout << left << setw(18) << label
         << "|" << setw(18) << char_time
         << "|" << setw(20) << std_time
         << "|" << setw(16) << char_memory_storage(cstr)
         << "|" << setw(20) << (sizeof(string) + sstr.capacity() + 1)
         << '\n';
}

static void part2_demo()
{
    cout << "==================== Part 2 ====================\n";
    cout << "Performance and memory comparison with std::string.\n\n";

    const int iterations = 50000;

    string short_std = "Hello";
    string medium_std(200, 'a');
    string long_std(1500, 'b');

    char *short_char = char_create(short_std.c_str());
    char *medium_char = char_create(medium_std.c_str());
    char *long_char = char_create(long_std.c_str());

    cout << left
         << setw(18) << "Function"
         << "|" << setw(18) << "char* avg (ns)"
         << "|" << setw(20) << "std::string avg (ns)"
         << "|" << setw(16) << "char* bytes"
         << "|" << setw(20) << "std::string bytes"
         << '\n';

    cout << string(92, '-') << '\n';

    print_benchmark_row("append short", short_char, short_std, iterations);
    print_benchmark_row("append medium", medium_char, medium_std, iterations);
    print_benchmark_row("append long", long_char, long_std, iterations);

    char_destroy(&short_char);
    char_destroy(&medium_char);
    char_destroy(&long_char);
}

int main()
{
    part1_demo();
    cout << '\n';
    part2_demo();
    return 0;
}