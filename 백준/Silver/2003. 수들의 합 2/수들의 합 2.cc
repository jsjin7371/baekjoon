#include <iostream>
#include <vector>

using namespace std;

int main(){
    ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
    
    int N, target;
    cin >> N >> target;

    vector<int> prefixSum(N+1,0);
    vector<int> arr(N+1,0);

    for(int i = 1; i<=N; i++){
        int input;
        cin >> input;

        arr[i] = input;
        prefixSum[i] = prefixSum[i-1] + input;
    }

    int start = 1, end=1, ans=0;
    while(start <= N){
        int currentVal = prefixSum[end] - prefixSum[start] + arr[start];

        if(currentVal == target){
            ans++;
        }

        if(currentVal < target){
            if(end == N){
                break;
            }
            end++;
        }
        else{
            start++;
        }
    }

    cout << ans;

    return 0;
}