/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

// calculates minimum number of spaces required to split pi with constraints
// that elements in b should be in inp set

// for given example:
//output : 3 spaces -> {"314", "15926535897", "9323", "8462643383279"}
#include <iostream>
#include <vector>
#include <unordered_map>
#include <climits>

using namespace std;

string pi = "3141592653589793238462643383279";
vector<string> inp{"3", "314", "49", "9001", "15926535897", "9323", "8462643383279", "9", "93238462643383279"};
int N = pi.length();
unordered_map<string, bool> exists;
vector<int> dp(N, 0), vis(N, 0);

int check(int pos){
    
    if (pos == N) return 0;
    string cur = "";
    if (vis[pos]) return dp[pos];
    int ans = INT_MAX;
    vis[pos] = 1;
    for (int j = pos; j < N; j++){
        cur += pi[j];
        int other = check(j+1);
        if (exists[cur]){
            //cout << cur << "\t" << other << "\t" << ans <<"\t"  << '\n';
            if (other != -1)
               ans = min(ans, 1 + other);
    
        }
        
    }
    
    if (ans == INT_MAX) ans = -1;
    dp[pos] = ans;
    return ans;
    
}

int main()
{
    for (auto c : inp)
        exists[c] = 1;
   
    cout<< check(0) -1 << endl;

    return 0;
}
