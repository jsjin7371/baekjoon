#include <iostream>

using namespace std;

int main(){
    ios::sync_with_stdio(false);
	cin.tie(0);

    int arr[6];
    int N, T, P, sum=0;

    cin >> N;
    for(int i=0; i<6; i++) {cin >> arr[i];}
    cin >> T >> P;
    
    for(int i=0; i<6; i++){
        sum += arr[i] / T;
        if(arr[i] % T != 0)
            sum++;
    }

    cout << sum << "\n" << N / P << " " << N % P;

    return 0;
}