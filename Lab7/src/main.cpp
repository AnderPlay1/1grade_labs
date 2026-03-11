#include <iostream>
#include <iomanip>
#include <string>
#include <chrono>
#include <cstring>

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

static void part1_demo()
{
    cout << "==================== Part 1 ====================\n";
    cout << "Manual testing of char array library functions.\n\n";

    char *s = char_create("Hello");
    char *other = char_create("World");

    print_string_state("Initial s", s);
    print_string_state("Initial other", other);
    cout << "Length(s): " << char_length(s) << '\n';
    cout << "Empty(s): " << (char_empty(s) ? "true" : "false") << "\n\n";

    cout << "Append \"!!!\" to s\n";
    cout << "Result code: " << char_append(&s, "!!!") << '\n';
    print_string_state("s", s);
    cout << '\n';

    cout << "Insert ',' at position 5\n";
    cout << "Result code: " << char_insert(&s, 5, ',') << '\n';
    print_string_state("s", s);
    cout << '\n';

    cout << "Erase 2 chars from position 5\n";
    cout << "Result code: " << char_erase(&s, 5, 2) << '\n';
    print_string_state("s", s);
    cout << '\n';

    cout << "Replace from position 5 count 3 with \"---\"\n";
    cout << "Result code: " << char_replace(&s, 5, 3, "---") << '\n';
    print_string_state("s", s);
    cout << '\n';

    cout << "Resize s to 12 with fill char '*'\n";
    cout << "Result code: " << char_resize(&s, 12, '*') << '\n';
    print_string_state("s", s);
    cout << '\n';

    cout << "Find \"lo\": " << char_find(s, "lo") << '\n';
    cout << "RFind \"*\": " << char_rfind(s, "*") << '\n';

    char *sub = char_substr(s, 2, 5);
    print_string_state("Substring s[2..6]", sub);
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