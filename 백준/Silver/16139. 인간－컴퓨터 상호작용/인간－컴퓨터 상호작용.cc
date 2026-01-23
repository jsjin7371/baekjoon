#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    string word = "";
    int q;
    cin >> word >> q;

    vector<vector<int>> alphabetsPrefixSum(26,vector<int>(word.size()+1,0));
    vector<int> alphabetSum(26,0);

    int rep = word.size();
    for(int i=1; i<=rep; i++){
        int alphabetNum = word[i-1] - 'a';
        
        alphabetsPrefixSum[alphabetNum][i]++;

        for(int j=0; j<26; j++){
            alphabetsPrefixSum[j][i] += alphabetsPrefixSum[j][i-1];
        }
    }

    for(int i=0; i<q; i++){
        char targetWord;
        int l, r;
        cin >> targetWord >> l >> r;
        
        int ans, index = targetWord - 'a';
        ans = alphabetsPrefixSum[index][r+1]-alphabetsPrefixSum[index][l];
        cout << ans << "\n";
    }

    return 0;
}