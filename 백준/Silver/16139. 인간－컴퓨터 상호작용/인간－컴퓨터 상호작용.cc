#include <iostream>
#include <string>

using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    string word = "";
    int q;
    cin >> word >> q;

    for(int i=0; i<q; i++){
        char targetWord;
        int l, r;
        cin >> targetWord >> l >> r;

        int count = 0;
        for(int j=l; j <=r; j++){
            if(word[j] == targetWord){
                count++;
            }
        }
        cout << count << "\n";
    }

    return 0;
}