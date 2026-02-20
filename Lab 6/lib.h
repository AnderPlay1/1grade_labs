#include <iostream>
#include <iomanip>
#include <limits>
#include <string>

using namespace std;

// 1) Input integer
inline int readInt(const string &prompt, int minV, int maxV)
{
    while (true)
    {
        cout << prompt;
        string s;
        cin >> s;
        try
        {
            size_t pos;
            int x = stoi(s, &pos);

            // если остались лишние символы (например 3.14)
            if (pos != s.length())
            {
                cout << "Not pure integer\n";
                continue;
            }

            if (x < minV || x > maxV)
            {
                cout << "Out of range.\n";
                continue;
            }
            return x;
        }
        catch (...)
        {
            cout << "Invalid input. Please enter an integer.\n";
        }
    }
}

// 2) Input array (uses readInt)
inline void readArray(int *a, int n, const string &name, int minV, int maxV)
{
    cout << "Enter " << n << " integers for " << name << ":\n";
    for (int i = 0; i < n; ++i)
        a[i] = readInt("  " + name + "[" + to_string(i) + "]: ", minV, maxV);
}

// 3) Input matrix (uses readInt / readArray idea)
inline void readMatrix(int *m, int r, int c, const string &name, int minV, int maxV)
{
    cout << "Enter matrix " << name << " (" << r << "x" << c << "):\n";
    for (int i = 0; i < r; ++i)
        for (int j = 0; j < c; ++j)
            m[i * c + j] = readInt("  " + name + "[" + to_string(i) + "][" + to_string(j) + "]: ", minV, maxV);
}

// 4) Output integer
inline void printInt(const string &label, int x)
{
    cout << label << ": ";
    cout << x << "\n";
}

// 5) Output array
inline void printArray(const string &label, const int *a, int n)
{
    cout << label << " (" << n << "): ";
    for (int i = 0; i < n; ++i)
        cout << setw(6) << a[i];
    cout << "\n";
}

// 6) Output matrix
inline void printMatrix(const string &label, const int *m, int r, int c)
{
    cout << label << " (" << r << "x" << c << "):\n";
    for (int i = 0; i < r; ++i)
    {
        for (int j = 0; j < c; ++j)
            cout << setw(6) << m[i * c + j];
        cout << "\n";
    }
}