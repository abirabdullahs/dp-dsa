#include <iostream>
using namespace std;

bool isMatchRec(string t, string p, int n, int m) {
  
    // If pattern is empty, then text must also be 
    // empty
    if (m == 0) {
        return n == 0;
    }

    // If text is empty, then pattern can have characters
    // followed by *s
    if (n == 0) {
        return (m >= 2 && p[m - 1] == '*') && 
                 isMatchRec(t, p, n, m - 2);
    }

    // If last characters of both string and pattern 
    // match, or pattern has '.'
    if (t[n - 1] == p[m - 1] || p[m - 1] == '.') {
        return isMatchRec(t, p, n - 1, m - 1);
    }

    // Handle '*' in the pattern
    if (p[m - 1] == '*' && m > 1) {
      
        // Check if '*' can represent zero occurrences 
        // of the preceding character
        bool zero = isMatchRec(t, p, n, m - 2);

        // Check if '*' can represent one or more occurrences 
        // of the preceding character
        bool oneOrMore = (p[m - 2] == t[n - 1] || p[m - 2] == '.') &&
                                       isMatchRec(t, p, n - 1, m);

        return zero || oneOrMore;
    }

    // If no match
    return false;
}

// Wrapper function
bool isMatch(string t, string p) {
    return isMatchRec(t, p, t.size(), p.size());
}

int main() {
    cout << boolalpha << isMatch("aab", "a.*") << endl; 
    cout << boolalpha << isMatch("aa", "a") << endl;    
    cout << boolalpha << isMatch("aa", "a*") << endl;   
    cout << boolalpha << isMatch("ab", ".*") << endl;  
    cout << boolalpha << isMatch("mississippi", "mis*is*p*.") << endl; 
    return 0;
}
