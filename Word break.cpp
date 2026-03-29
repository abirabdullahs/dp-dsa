// C++ program to implement word break.
#include <bits/stdc++.h>
using namespace std;

// Function to check if the given string can be broken
// down into words from the word list
bool wordBreakRec(int i, string &s, vector<string> &dictionary)
{

    // If end of string is reached,
    // return true.
    if (i == s.length())
        return true;

    int n = s.length();
    string prefix = "";

    // Try every prefix
    for (int j = i; j < n; j++)
    {
        prefix += s[j];

        // if the prefix s[i..j] is a dictionary word
        // and rest of the string can also be broken into
        // valid words, return true
        if (find(dictionary.begin(), dictionary.end(), prefix) != dictionary.end() &&
            wordBreakRec(j + 1, s, dictionary))
        {
            return true;
        }
    }

    return false;
}

bool wordBreak(string &s, vector<string> &dictionary)
{
    return wordBreakRec(0, s, dictionary);
}

int main()
{
    string s = "ilike";

    vector<string> dictionary = {"i", "like", "gfg"};

    cout << (wordBreak(s, dictionary) ? "true" : "false") << endl;

    return 0;
}
