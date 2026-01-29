#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

int main(){
    ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

    int N;
    cin >> N;

    vector<int> distance(N+1,0);
    vector<int> distancePrefix(N+2,0);
    for(int i = 1; i<=N; i++){
        cin >> distance[i];
        distancePrefix[i+1] = distancePrefix[i] + distance[i];
    }

    int start=1, end=1;
    int totalDistance = distancePrefix[N+1];
    int ans = 0;

    while (end <= N+1){
        int currentDistance = distancePrefix[end] - distancePrefix[start];
        bool isClockwise = currentDistance < totalDistance-currentDistance;
        currentDistance = min(currentDistance, totalDistance-currentDistance);
        
        

        if(currentDistance == totalDistance/2){
            ans = currentDistance;
            break;
        }

        ans = max(currentDistance, ans);

        if(isClockwise){
            if(totalDistance/2 > currentDistance){
                end++;
            }
            else{
                start++;
            }
        }
        else{
            if(totalDistance/2 > currentDistance){
                start++;
            }
            else{
                end++;
            }
        }

    }

    cout<<ans;
    
    return 0;
}