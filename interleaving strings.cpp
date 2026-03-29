#include <bits/stdc++.h>
using namespace std;

// ─────────────────────────────────────────
// Interleaving Strings
// Given s1, s2, s3 — check if s3 is formed
// by interleaving s1 and s2
// ─────────────────────────────────────────
// dp[i][j] = true if s3[0..i+j-1] can be formed
//            by interleaving s1[0..i-1] & s2[0..j-1]

bool isInterleave(string& s1, string& s2, string& s3) {
    int n = s1.size(), m = s2.size(), k = s3.size();

    if (n + m != k) return false;

    vector<vector<bool>> dp(n+1, vector<bool>(m+1, false));

    dp[0][0] = true;

    // Only s1 used
    for (int i = 1; i <= n; i++)
        dp[i][0] = dp[i-1][0] && (s1[i-1] == s3[i-1]);

    // Only s2 used
    for (int j = 1; j <= m; j++)
        dp[0][j] = dp[0][j-1] && (s2[j-1] == s3[j-1]);

    // Fill table
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            char c = s3[i+j-1];
            dp[i][j] = (dp[i-1][j] && s1[i-1] == c) ||
                       (dp[i][j-1] && s2[j-1] == c);
        }
    }

    return dp[n][m];
}

// ─────────────────────────────────────────
// Reconstruct one valid interleaving
// ─────────────────────────────────────────
string reconstruct(string& s1, string& s2, string& s3) {
    int n = s1.size(), m = s2.size();
    vector<vector<bool>> dp(n+1, vector<bool>(m+1, false));

    dp[0][0] = true;
    for (int i = 1; i <= n; i++)
        dp[i][0] = dp[i-1][0] && (s1[i-1] == s3[i-1]);
    for (int j = 1; j <= m; j++)
        dp[0][j] = dp[0][j-1] && (s2[j-1] == s3[j-1]);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            char c = s3[i+j-1];
            dp[i][j] = (dp[i-1][j] && s1[i-1] == c) ||
                       (dp[i][j-1] && s2[j-1] == c);
        }

    if (!dp[n][m]) return "Not an interleaving!";

    // Backtrack
    string res = "";
    int i = n, j = m;
    while (i > 0 || j > 0) {
        char c = s3[i+j-1];
        if (i > 0 && dp[i-1][j] && s1[i-1] == c)
            { res += 'A'; i--; }  // took from s1
        else
            { res += 'B'; j--; }  // took from s2
    }
    reverse(res.begin(), res.end());
    return res; // 'A' = from s1, 'B' = from s2
}

// ─────────────────────────────────────────
// Main
// ─────────────────────────────────────────
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s1 = "aabcc";
    string s2 = "dbbca";
    string s3 = "aadbbcbcac";  // true
    string s4 = "aadbbbaccc"; // false

    cout << "s1 = " << s1 << "\n";
    cout << "s2 = " << s2 << "\n\n";

    cout << "s3 = " << s3 << " → "
         << (isInterleave(s1, s2, s3) ? "YES ✓" : "NO ✗") << "\n";
    cout << "s4 = " << s4 << " → "
         << (isInterleave(s1, s2, s4) ? "YES ✓" : "NO ✗") << "\n\n";

    cout << "Source trace for s3:\n";
    string trace = reconstruct(s1, s2, s3);
    for (int i = 0; i < s3.size(); i++)
        cout << s3[i] << "(" << trace[i] << ") ";
    cout << "\n";

    return 0;
}
