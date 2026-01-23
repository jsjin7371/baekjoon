#include <iostream>
#include <string>

using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    const string TARGET_WORD = "fox";

    int testCase; 
    cin >> testCase;

    for(int i = 0; i < testCase; i++){
        int n;
        string word;
        cin >> n >> word;

        string stk = "";
        
        for(int j = 0; j < n; j++){
            stk += word[j];

            int len = stk.length();
            if(len >= 3 && stk.substr(len - 3, 3) == TARGET_WORD){
                stk.erase(len - 3, 3);
            }
        }
        
        cout << stk.length() << "\n";
    }

    return 0;
}