#include <iostream>
#include <vector>

using namespace std;

int main(){
    ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

    int N, H;
    cin >> N >> H;

    vector<int> unlayerObjectSum(H+1,0);
    vector<int> uplayerObjectSum(H+1,0);
    bool isEven = true;

    for(int i=0; i<N; i++){
        int input;
        cin >> input;

        if(isEven){
            unlayerObjectSum[input]++;
        }
        else{
            uplayerObjectSum[input]++;
        }
        isEven = !isEven; 
    }

    for(int i = H-1; i>0; i--){
        unlayerObjectSum[i] = unlayerObjectSum[i+1] + unlayerObjectSum[i];
        uplayerObjectSum[i] = uplayerObjectSum[i+1] + uplayerObjectSum[i];
    }

    int least = 200000;
    int cnt = 0;
    for(int i=1; i<=H; i++){
        if(unlayerObjectSum[i] + uplayerObjectSum[H-i+1] < least){
            least = unlayerObjectSum[i] + uplayerObjectSum[H-i+1];
            cnt = 1;
        }
        else if(unlayerObjectSum[i] + uplayerObjectSum[H-i+1] == least){
            cnt++;
        }
    }

    cout << least << "\n" << cnt;
}