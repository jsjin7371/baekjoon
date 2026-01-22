#include <iostream>
#include <vector>

using namespace std;

int main(){
    ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

    int N,M;
    cin >> N >> M;
    
    int list[100001] = {0};
    
    for(int repeat=1; repeat<=N; repeat++){
        int input;
        cin >> input;
        list[repeat] = list[repeat-1] + input;
    }

    for(int repeat=0; repeat<M; repeat++){
        int i, j;
        cin >> i >> j;

        int ans = list[j] - list[i-1];
        cout << ans << "\n";
    }

    return 0;
}