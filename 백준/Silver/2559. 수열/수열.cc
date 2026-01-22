#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<int> buildPrefixSum(int N, int K){
    vector<int> prefixSum;
    queue<int> queue;
    int sum = 0;

    for(int i=1; i<=N; i++){
        int input;
        cin >> input;
        sum += input;
        queue.push(input); 
        
        if(i > K){
            sum -= queue.front();
            prefixSum.push_back(sum);
            queue.pop();
        }
        else if (i == K){
            prefixSum.push_back(sum);
        }
    }

    return prefixSum;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N, K;
    cin >> N >> K;
    vector<int> continuousTemp = buildPrefixSum(N, K);

    const int NOT_FOUND = -10000001;
    int maxTemp = NOT_FOUND;
    for(int i=0; i<continuousTemp.size(); i++){
        maxTemp = maxTemp < continuousTemp[i] ? continuousTemp[i] : maxTemp;
    }
    cout << maxTemp;

    return 0;
}