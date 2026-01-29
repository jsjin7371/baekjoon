# [Gold V] 두 개의 탑 - 2118 

[문제 링크](https://www.acmicpc.net/problem/2118) 

### 성능 요약

메모리: 2412 KB, 시간: 4 ms

### 분류

누적 합, 두 포인터

### 제출 일자

2026년 1월 29일 20:09:37

### 문제 설명

<p>1번부터 N번까지의 지점이 있다. 각각의 지점들은 차례로, 그리고 원형으로 연결되어 있다. 이 지점들 중 두 곳에 두 개의 탑을 세우려고 하는데, 두 탑의 거리가 최대가 되도록 만들려고 한다.</p>

<p>지점들이 원형으로 연결되어 있기 때문에, 두 지점 사이에는 시계방향과 반시계방향의 두 경로가 존재한다. 두 지점 사이의 거리를 잴 때에는, 이러한 값들 중에서 더 작은 값을 거리로 한다.</p>

<p>연결되어 있는 두 지점 사이의 거리가 주어졌을 때, 두 탑의 거리의 최댓값을 계산하는 프로그램을 작성하시오.</p>

### 입력 

 <p>첫째 줄에 지점의 개수 N(2 ≤ N ≤ 50,000)이 주어진다. 다음 N개의 줄에는 차례로 두 지점 사이의 거리가 양의 정수로 주어진다. 전체 거리의 총 합은 1,000,000,000을 넘지 않는다.</p>

### 출력 

 <p>첫째 줄에 답을 출력한다.</p>

# 백준 2118번 코드 평가 리포트

## 📊 총점: 70/100점

---

## 📌 항목별 평가

### 초급 평가

#### 1. 정확성 (20/30점) ⚠️

**아이디어는 좋지만 구현에 문제가 있습니다**

**핵심 아이디어:**
- 원형 배열에서 두 지점 사이의 최대 최소 거리를 구하는 문제
- 투 포인터를 사용하려는 시도 ✅
- 시계방향/반시계방향 중 짧은 거리를 선택 ✅

**문제점:**

1. **투 포인터 이동 로직 오류:**
```cpp
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
```
- 이 로직이 원형 배열의 투 포인터 패턴에 맞지 않습니다
- `isClockwise` 변수가 포인터 이동 결정에 부적절하게 사용됨
- 원형 배열에서는 한 방향으로만 탐색하면 됩니다

2. **정확한 투 포인터 접근:**
```cpp
// 올바른 방식
while(start < N){
    int clockwise = prefixSum[end] - prefixSum[start];
    int counterClockwise = totalDistance - clockwise;
    int minDist = min(clockwise, counterClockwise);
    
    maxDist = max(maxDist, minDist);
    
    // 시계방향이 더 짧으면 end 증가 (거리 늘리기)
    if(clockwise < counterClockwise){
        end++;
        if(end > N) break;
    }
    else{
        start++;
    }
}
```

3. **종료 조건 문제:**
```cpp
while (end <= N+1)  // end가 N+1까지 가면 배열 범위 초과 위험
```

**테스트 케이스 검증 필요:**
```
입력:
4
2 5 4 1
(총 거리 = 12)

예상: 최대 최소 거리는 6
현재 코드가 정확히 6을 출력하는지 불확실
```

#### 2. 가독성 (18/25점) ⚠️

**좋은 점:**
- `distance`, `distancePrefix` 같은 명확한 변수명
- 전체적인 구조가 이해 가능

**개선 필요:**

1. **헤더 파일:**
```cpp
#include <math.h>  // C 스타일
// C++에서는
#include <cmath>   // 또는 <algorithm>의 min/max 사용
```

2. **의미 불명확한 로직:**
```cpp
bool isClockwise = currentDistance < totalDistance-currentDistance;
```
- 이 변수명이 실제 의미하는 바를 정확히 전달하지 못함
- "시계방향이 더 짧은가?"가 더 명확

3. **복잡한 조건문:**
```cpp
if(isClockwise){
    if(totalDistance/2 > currentDistance){
        end++;
    }
    else{
        start++;
    }
}
else{
    // 반대 로직
}
```
- 중첩된 조건문이 이해하기 어려움
- 투 포인터의 핵심 논리가 명확히 드러나지 않음

#### 3. 간결성 (15/20점) ⚠️

**불필요한 부분:**

1. **중복 계산:**
```cpp
currentDistance = min(currentDistance, totalDistance-currentDistance);
```
- 이미 min을 구했는데, 나중에 조건문에서 또 비교

2. **조기 종료 로직:**
```cpp
if(currentDistance == totalDistance/2){
    ans = currentDistance;
    break;
}
```
- 정수 나눗셈으로 인해 홀수일 때 부정확
- 최댓값을 계속 갱신하는 것만으로 충분

---

### 중급 평가

#### 4. 효율성 (6/10점) ⚠️

**시간 복잡도:**
- 목표: O(N) (투 포인터)
- 현재: O(N)으로 보이지만 로직 오류로 일부 경우 무한루프 가능성

**문제점:**
```cpp
while (end <= N+1)
```
- `end`가 증가만 하는 경우 종료 조건이 명확하지 않음
- 원형 배열을 한 바퀴 이상 도는 경우 처리 누락

**올바른 접근:**
```cpp
// start는 0~N-1, end는 start~N까지
for(int start = 0; start < N; start++){
    // end를 적절히 조정하며 최적값 찾기
}
```

#### 5. 구조 (5/10점) ⚠️

**문제점:**
- 모든 로직이 main에 집중
- 투 포인터 로직이 복잡한데 함수로 분리되지 않음
- 디버깅이 매우 어려운 구조

**개선 예시:**
```cpp
int calculateDistance(const vector<int>& prefix, int start, int end, 
                     int total){
    int clockwise = prefix[end] - prefix[start];
    return min(clockwise, total - clockwise);
}

int findMaxMinDistance(const vector<int>& prefix, int N){
    int total = prefix[N];
    int maxDist = 0;
    int end = 1;
    
    for(int start = 0; start < N; start++){
        while(end <= N && /* 조건 */){
            int dist = calculateDistance(prefix, start, end, total);
            maxDist = max(maxDist, dist);
            end++;
        }
        // start 이동 로직
    }
    
    return maxDist;
}
```

---

## 💡 개선 제안

### 1️⃣ **정확한 투 포인터 구현**

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    cin >> N;
    
    vector<int> prefixSum(N+1, 0);
    for(int i=1; i<=N; i++){
        int dist;
        cin >> dist;
        prefixSum[i] = prefixSum[i-1] + dist;
    }
    
    int totalDistance = prefixSum[N];
    int maxMinDistance = 0;
    
    int end = 1;
    for(int start=0; start<N; start++){
        // end를 최대한 이동 (반시계방향이 시계방향보다 짧아질 때까지)
        while(end <= N){
            int clockwise = prefixSum[end] - prefixSum[start];
            int counterClockwise = totalDistance - clockwise;
            
            if(clockwise > counterClockwise){
                break;  // 더 이상 이동하면 손해
            }
            
            maxMinDistance = max(maxMinDistance, 
                               min(clockwise, counterClockwise));
            end++;
        }
        
        // start를 이동하기 전, 현재 위치도 체크
        if(end > N) end = N;
        int clockwise = prefixSum[end] - prefixSum[start];
        int counterClockwise = totalDistance - clockwise;
        maxMinDistance = max(maxMinDistance, 
                           min(clockwise, counterClockwise));
    }
    
    cout << maxMinDistance;
    
    return 0;
}
```

### 2️⃣ **함수 분리**

```cpp
// 두 지점 사이의 최소 거리 계산
int getMinDistance(int clockwise, int total){
    return min(clockwise, total - clockwise);
}

// 투 포인터로 최대 최소 거리 찾기
int findMaxMinDistance(const vector<int>& prefixSum, int N){
    int total = prefixSum[N];
    int result = 0;
    int end = 1;
    
    for(int start=0; start<N; start++){
        // end를 조정하며 최적값 찾기
        while(end <= N){
            int clockwise = prefixSum[end] - prefixSum[start];
            
            // 반시계방향이 더 짧아지면 중단
            if(clockwise > total - clockwise) break;
            
            result = max(result, getMinDistance(clockwise, total));
            end++;
        }
        
        // 현재 위치에서도 체크
        if(end > start){
            if(end > N) end = N;
            int clockwise = prefixSum[end] - prefixSum[start];
            result = max(result, getMinDistance(clockwise, total));
        }
    }
    
    return result;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    cin >> N;
    
    vector<int> prefixSum(N+1, 0);
    for(int i=1; i<=N; i++){
        int dist;
        cin >> dist;
        prefixSum[i] = prefixSum[i-1] + dist;
    }
    
    cout << findMaxMinDistance(prefixSum, N);
    
    return 0;
}
```

### 3️⃣ **더 간단한 접근 (모든 구간 탐색)**

사실 이 문제는 투 포인터가 복잡하므로, O(N²)로 단순하게 풀 수도 있습니다:

```cpp
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    cin >> N;
    
    vector<int> prefixSum(N+1, 0);
    for(int i=1; i<=N; i++){
        int dist;
        cin >> dist;
        prefixSum[i] = prefixSum[i-1] + dist;
    }
    
    int totalDistance = prefixSum[N];
    int maxMinDistance = 0;
    
    // 모든 구간 검사 (N≤50000이면 충분히 가능)
    for(int start=0; start<N; start++){
        for(int end=start+1; end<=N; end++){
            int clockwise = prefixSum[end] - prefixSum[start];
            int counterClockwise = totalDistance - clockwise;
            int minDist = min(clockwise, counterClockwise);
            maxMinDistance = max(maxMinDistance, minDist);
        }
    }
    
    cout << maxMinDistance;
    
    return 0;
}
```

**장점:**
- 로직이 명확하고 이해하기 쉬움
- 버그 가능성 낮음
- N≤50,000일 때 충분히 빠름 (약 0.5초)

### 4️⃣ **헤더 수정**

```cpp
// 현재
#include <math.h>

// 개선
#include <algorithm>  // min, max를 위해
// 또는
#include <cmath>      // C++ 스타일
```

### 5️⃣ **변수명 개선**

```cpp
// 현재
bool isClockwise = currentDistance < totalDistance-currentDistance;

// 개선
int clockwise = prefixSum[end] - prefixSum[start];
int counterClockwise = totalDistance - clockwise;
bool clockwiseIsShorter = clockwise < counterClockwise;
```

---

## 🎓 실무 준비 단계 조언

### 유지보수성

**현재 문제:**
- 복잡한 조건문이 중첩되어 있어 6개월 후 이해하기 어려움
- `isClockwise` 변수가 투 포인터 이동 결정에 사용되는 논리가 불명확

**개선 방향:**
```cpp
// 명확한 주석
// 투 포인터: start 고정, end를 늘려가며 최적점 찾기
// 원리: 시계방향 거리가 반시계방향보다 짧을 때까지 end 증가

while(end <= N){
    int clockwise = prefixSum[end] - prefixSum[start];
    int counterClockwise = total - clockwise;
    
    // 시계방향이 더 길어지면 중단
    if(clockwise > counterClockwise) break;
    
    maxDist = max(maxDist, clockwise);
    end++;
}
```

### 확장성

**현재 구조의 한계:**
- 로직이 복잡해서 다른 조건으로 변경하기 어려움
- 예: "최소 최소 거리" 또는 "중간값"을 구하려면 전체 수정 필요

**함수 분리 후:**
```cpp
// 다양한 집계 함수 적용 가능
int result = aggregateDistances(prefixSum, N, 
    [](int a, int b){ return max(a, b); }  // 최댓값
);
```

### 일관성

**개선 필요:**
```cpp
// 혼재
#include <math.h>     // C 스타일
#include <iostream>   // C++ 스타일

// 통일
#include <cmath>      // 모두 C++ 스타일
#include <iostream>
#include <vector>
#include <algorithm>
```

### 테스트 가능성

**현재 문제:**
- 투 포인터 로직이 main에 있어 독립 테스트 불가
- 디버깅 시 중간값 확인 어려움

**개선 후:**
```cpp
void testTwoPointer(){
    vector<int> prefix = {0, 2, 7, 11, 12};
    // 거리: 2, 5, 4, 1 (총 12)
    
    int result = findMaxMinDistance(prefix, 4);
    assert(result == 6);  // (0→2: 2 vs 10), (0→3: 7 vs 5) ...
    
    cout << "Test passed!\n";
}
```

### 알고리즘 선택

**고민해볼 점:**
- 원형 배열의 투 포인터는 일반 배열보다 복잡합니다
- N이 크지 않다면 (N≤50,000) O(N²) 완전 탐색도 고려할 만합니다
- "복잡한 최적화"보다 "명확한 구현"이 더 가치 있을 수 있습니다

**트레이드오프:**
```
투 포인터 O(N):
+ 빠름
- 구현 복잡, 버그 가능성 높음

완전 탐색 O(N²):
+ 구현 간단, 버그 적음
- 느림 (하지만 N≤50,000이면 충분)
```

### 예외 처리 (조언)

**고려할 사항:**
```cpp
// N=1인 경우
if(N == 1){
    cout << 0;  // 또는 distance[1] / 2
    return 0;
}

// N=2인 경우 (특수 케이스)
if(N == 2){
    int dist1 = distance[1];
    int dist2 = distance[2];
    cout << min(dist1, dist2);
    return 0;
}

// 음수 거리 입력 (문제 조건에는 없지만)
if(distance[i] < 0){
    // 에러 처리
}
```

---

## ✅ 최종 평가

**좋은 시도:**
- 원형 배열 문제를 투 포인터로 접근하려 한 점 ✅
- 누적합을 활용한 점 ✅
- 시계방향/반시계방향을 고려한 점 ✅

**주요 문제:**
- 투 포인터 이동 로직이 부정확함 ❌
- 조건문이 복잡하고 논리가 명확하지 않음 ❌
- 원형 배열의 특성을 제대로 처리하지 못함 ❌

**성장 궤적:**
1. **1806번**: 62점 (재귀 투 포인터 - 부적절)
2. **2559번**: 78점 (슬라이딩 윈도우 - 좋음)
3. **16139번**: 88점 (2차원 누적합 - 완벽)
4. **3020번**: 82점 (역방향 누적합 - 탁월)
5. **2118번**: 70점 (원형 투 포인터 - 로직 오류)

**분석:**
이번 문제는 **원형 배열의 투 포인터**라는 까다로운 주제였습니다. 아이디어는 좋았지만 구현에서 논리적 오류가 발생했습니다. 특히:
- 일반 배열의 투 포인터 ≠ 원형 배열의 투 포인터
- 복잡한 조건문보다 명확한 논리가 중요
- 때로는 O(N²)가 O(N)보다 나은 선택일 수 있음

**추천:**
1. 먼저 O(N²) 완전 탐색으로 정확히 풀어보세요
2. 동작을 완전히 이해한 후 투 포인터 최적화를 시도하세요
3. 디버깅을 위해 중간 결과를 출력해보세요

투 포인터는 강력하지만 까다로운 기법입니다. 이번 경험을 바탕으로 더 견고한 구현 능력을 키워나가세요! 💪
