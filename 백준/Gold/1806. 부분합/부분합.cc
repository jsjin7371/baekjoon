#include <iostream>
#include <vector>

using namespace std;

vector<long long> prefixSum;

void buildPrefixSum(int N){
    prefixSum.resize(N+1, 0);

    for(int i=1; i<=N; i++){
        int input;
        cin >> input;
        prefixSum[i] = prefixSum[i-1] + input;
    }
}

int getMinimumLength(int startPointer, int endPointer, int target, int minimumLength){   
    if(startPointer == prefixSum.size()){
        return minimumLength;
    }
    else if(endPointer == prefixSum.size()){
        return minimumLength;
    }
    
    int isInitialSet = -1;
    long long sum = prefixSum[endPointer] - prefixSum[startPointer];
   
    if(sum < target){
        endPointer++; 
    }
    else if(sum >= target){   
        if(minimumLength == isInitialSet){
            minimumLength = endPointer - startPointer;
        }
        else if(minimumLength > endPointer - startPointer){
            minimumLength = endPointer - startPointer;
        }
        startPointer++;
    }

    minimumLength = getMinimumLength(startPointer, endPointer, target, minimumLength);
    return minimumLength;
}

int main(){
    ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

    int N, S;
    cin >> N >> S;
    
    buildPrefixSum(N);

    int startPointer = 0, endPointer = 0;
    int isInitialSet = -1;
    int minimumLength = isInitialSet;

    minimumLength = getMinimumLength(startPointer, endPointer, S, minimumLength);

    if(minimumLength == isInitialSet){
        minimumLength = 0;
        cout << minimumLength;
    }
    else{
        cout << minimumLength;
    }

    return 0;
}   