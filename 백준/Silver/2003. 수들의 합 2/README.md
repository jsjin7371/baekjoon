# [Silver IV] 수들의 합 2 - 2003 

[문제 링크](https://www.acmicpc.net/problem/2003) 

### 성능 요약

메모리: 2180 KB, 시간: 0 ms

### 분류

브루트포스 알고리즘, 누적 합, 두 포인터

### 제출 일자

2026년 1월 31일 22:49:11

### 문제 설명

<p>N개의 수로 된 수열 A[1], A[2], …, A[N] 이 있다. 이 수열의 i번째 수부터 j번째 수까지의 합 A[i] + A[i+1] + … + A[j-1] + A[j]가 M이 되는 경우의 수를 구하는 프로그램을 작성하시오.</p>

### 입력 

 <p>첫째 줄에 N(1 ≤ N ≤ 10,000), M(1 ≤ M ≤ 300,000,000)이 주어진다. 다음 줄에는 A[1], A[2], …, A[N]이 공백으로 분리되어 주어진다. 각각의 A[x]는 30,000을 넘지 않는 자연수이다.</p>

### 출력 

 <p>첫째 줄에 경우의 수를 출력한다.</p>

# 백준 2003번 코드 평가 리포트

## 📊 총점: 75/100점

---

## 📌 항목별 평가

### 초급 평가

#### 1. 정확성 (22/30점) ⚠️

**아이디어는 정확하지만 구현에 문제가 있습니다**

**핵심 아이디어:**
- 투 포인터로 연속된 부분합을 찾는 문제 ✅
- 누적합을 사용한 점 ✅

**치명적인 버그:**

```cpp
int currentVal = prefixSum[end] - prefixSum[start] + arr[start];
```

이 수식이 **잘못되었습니다!**

**문제 분석:**
```
prefixSum[i] = arr[1] + arr[2] + ... + arr[i]

구간 [start, end]의 합:
= arr[start] + arr[start+1] + ... + arr[end]
= prefixSum[end] - prefixSum[start-1]

현재 코드:
= prefixSum[end] - prefixSum[start] + arr[start]
= (arr[1]~arr[end]) - (arr[1]~arr[start]) + arr[start]
= arr[start+1] + arr[start+2] + ... + arr[end] + arr[start]
= 틀림! (arr[start]가 중복됨)
```

**올바른 수식:**
```cpp
// 방법 1: 누적합 사용
int currentVal = prefixSum[end] - prefixSum[start-1];

// 방법 2: 직접 계산 (누적합 불필요)
int currentSum = 0;
for(int i=start; i<=end; i++){
    currentSum += arr[i];
}
```

**테스트 케이스 검증:**
```
입력:
4 2
1 1 1 1

예상 출력: 3 (구간 [1,2], [2,3], [3,4])

현재 코드:
start=1, end=1: prefixSum[1]-prefixSum[1]+arr[1] = 1-1+1 = 1 (X)
start=1, end=2: prefixSum[2]-prefixSum[1]+arr[1] = 2-1+1 = 2 (O) ans++
start=2, end=2: prefixSum[2]-prefixSum[2]+arr[2] = 2-2+1 = 1 (X)
...

정확한 답을 얻을 가능성 낮음
```

**추가 버그:**
```cpp
if(end == N){
    break;
}
```
- start를 증가시켜야 할 상황에서도 break하므로 일부 경우를 놓칠 수 있음

#### 2. 가독성 (20/25점) ✅

**좋은 점:**
- 변수명이 비교적 명확합니다 (`prefixSum`, `target`, `currentVal`)
- 전체적인 흐름을 이해할 수 있습니다
- 코드가 간결합니다

**소소한 개선:**
```cpp
// 현재
int currentVal  // 값이라기보다 "합"

// 개선
int currentSum  // 더 명확
int rangeSum    // 구간 합 의미 강조
```

#### 3. 간결성 (18/20점) ✅

**잘된 점:**
- 불필요한 코드가 거의 없습니다
- 로직이 간결합니다

**약간의 중복:**
```cpp
vector<int> arr(N+1,0);  // 실제로는 불필요
// prefixSum만 있어도 충분하거나
// arr만 있어도 충분함
```

---

### 중급 평가

#### 4. 효율성 (8/10점) ✅

**시간 복잡도:**
- 목표: O(N)
- 달성: O(N) ✅

**공간 복잡도:**
- O(N) (누적합 배열)
- 사실 누적합 없이도 가능 → O(1) 공간 가능

**누적합 없는 더 효율적인 방법:**
```cpp
int start=0, end=0;
int currentSum = 0;
int count = 0;

while(start < N){
    if(currentSum < target && end < N){
        currentSum += arr[end];
        end++;
    }
    else if(currentSum == target){
        count++;
        currentSum -= arr[start];
        start++;
    }
    else{
        currentSum -= arr[start];
        start++;
    }
}
```

**장점:**
- 공간 복잡도 O(1)
- 누적합 계산 불필요
- 더 직관적

#### 5. 구조 (7/10점) ⚠️

**개선 필요:**
- 모든 로직이 main에 집중
- 투 포인터 로직을 함수로 분리하면 더 좋음

**개선 예시:**
```cpp
int countSubarraysWithSum(const vector<int>& arr, int target){
    int n = arr.size() - 1;  // 0번 인덱스 제외
    int count = 0;
    int start = 1, end = 1;
    int currentSum = 0;
    
    while(start <= n){
        // 투 포인터 로직
        // ...
    }
    
    return count;
}

int main(){
    // 입력 처리
    int result = countSubarraysWithSum(arr, target);
    cout << result;
}
```

---

## 💡 개선 제안

### 1️⃣ **버그 수정: 누적합 수식 올바르게**

```cpp
#include <iostream>
#include <vector>

using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, target;
    cin >> N >> target;
    
    vector<int> prefixSum(N+1, 0);
    
    for(int i=1; i<=N; i++){
        int input;
        cin >> input;
        prefixSum[i] = prefixSum[i-1] + input;
    }
    
    int start = 1, end = 1;
    int count = 0;
    
    while(start <= N){
        // 올바른 구간 합 계산
        int currentSum = prefixSum[end] - prefixSum[start-1];
        
        if(currentSum == target){
            count++;
            end++;
        }
        else if(currentSum < target){
            end++;
        }
        else{  // currentSum > target
            start++;
        }
        
        // end가 범위를 벗어나면 start만 증가
        if(end > N){
            start++;
            end = start;
        }
    }
    
    cout << count;
    
    return 0;
}
```

### 2️⃣ **더 나은 방법: 누적합 없이 투 포인터**

```cpp
#include <iostream>
#include <vector>

using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, target;
    cin >> N >> target;
    
    vector<int> arr(N);
    for(int i=0; i<N; i++){
        cin >> arr[i];
    }
    
    int start = 0, end = 0;
    int currentSum = 0;
    int count = 0;
    
    while(end < N){
        currentSum += arr[end];
        
        // 합이 target보다 크면 start 이동
        while(currentSum > target && start <= end){
            currentSum -= arr[start];
            start++;
        }
        
        // 합이 target과 같으면 카운트
        if(currentSum == target){
            count++;
        }
        
        end++;
    }
    
    cout << count;
    
    return 0;
}
```

**장점:**
- 누적합 배열 불필요 → 메모리 절약
- 로직이 더 명확
- 표준 투 포인터 패턴

### 3️⃣ **함수 분리**

```cpp
int countSubarraysWithSum(const vector<int>& arr, int target){
    int n = arr.size();
    int start = 0, end = 0;
    int currentSum = 0;
    int count = 0;
    
    while(end < n){
        currentSum += arr[end];
        
        while(currentSum > target && start <= end){
            currentSum -= arr[start];
            start++;
        }
        
        if(currentSum == target){
            count++;
        }
        
        end++;
    }
    
    return count;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, target;
    cin >> N >> target;
    
    vector<int> arr(N);
    for(int i=0; i<N; i++){
        cin >> arr[i];
    }
    
    cout << countSubarraysWithSum(arr, target);
    
    return 0;
}
```

### 4️⃣ **변수명 개선**

```cpp
// 현재
int ans = 0;
int currentVal;

// 개선
int count = 0;        // 더 명확
int currentSum;       // 값보다 합
int rangeSum;         // 구간 합 강조
```

### 5️⃣ **종료 조건 개선**

```cpp
// 현재 - 버그 가능성
if(end == N){
    break;
}

// 개선 1 - 명확한 조건
if(end > N){
    start++;
    end = start;
}

// 개선 2 - while 조건 활용
while(end < N){
    // 로직
}
```

---

## 🎓 실무 준비 단계 조언

### 유지보수성

**현재 문제:**
```cpp
int currentVal = prefixSum[end] - prefixSum[start] + arr[start];
```
- 이 수식이 왜 필요한지 주석이 없으면 이해하기 어려움
- 실제로 틀린 수식이라 더욱 혼란스러움

**개선 후:**
```cpp
// 구간 [start, end]의 합 계산
// prefixSum[i] = arr[0] + arr[1] + ... + arr[i-1]
int rangeSum = prefixSum[end] - prefixSum[start];

// 또는 더 명확하게
// 구간 합 = 전체에서 시작 전까지 빼기
int rangeSum = prefixSum[end] - prefixSum[start-1];  // 1-based
```

### 확장성

**현재 구조:**
- 누적합을 사용하면 구간 쿼리에 유리
- 하지만 이 문제는 단순 순회라 불필요

**확장 시나리오:**
1. "구간 합이 K 이하인 개수"로 변경된다면?
   ```cpp
   // while 조건만 수정
   while(currentSum > target && start <= end){
       currentSum -= arr[start];
       start++;
   }
   
   if(currentSum <= target){  // 조건 변경
       count++;
   }
   ```

2. "특정 구간 [L, R]의 합을 여러 번 쿼리"한다면?
   - 누적합이 유용함 (O(1) 쿼리)

### 일관성

**개선 필요:**
```cpp
// 인덱스 스타일 혼재
vector<int> prefixSum(N+1,0);  // 1-based
vector<int> arr(N+1,0);        // 1-based

// 표준적으로는 0-based가 더 일관적
vector<int> arr(N);            // 0-based
for(int i=0; i<N; i++){
    cin >> arr[i];
}
```

**1-based vs 0-based:**
```
1-based (현재):
+ 수학적 표기와 일치 (첫 번째 원소가 arr[1])
- C++ 표준과 다름
- 0번 인덱스 낭비

0-based (권장):
+ C++ STL과 일치
+ 메모리 낭비 없음
+ 대부분의 알고리즘과 호환
- 누적합 인덱싱 주의 필요
```

### 테스트 가능성

**현재 문제:**
- 모든 로직이 main에 있어 단위 테스트 불가
- cin 직접 사용으로 테스트 데이터 주입 어려움

**개선 후:**
```cpp
void testCountSubarrays(){
    vector<int> test1 = {1, 1, 1, 1};
    assert(countSubarraysWithSum(test1, 2) == 3);
    
    vector<int> test2 = {1, 2, 3, 4};
    assert(countSubarraysWithSum(test2, 5) == 2);  // [2,3], [1,2,3] -> 아니 [2,3], [1,4]
    
    vector<int> test3 = {1, 2, 3, 4, 5};
    assert(countSubarraysWithSum(test3, 7) == 2);  // [3,4], [2,3,2] -> 아니 [3,4]만
    
    cout << "All tests passed!\n";
}
```

### 알고리즘 이해

**투 포인터의 핵심:**
```
1. 두 포인터 start, end를 유지
2. 조건에 따라 포인터 이동
   - 합이 작으면: end 증가 (구간 확장)
   - 합이 크면: start 증가 (구간 축소)
   - 합이 같으면: 카운트하고 이동
3. 모든 구간을 O(N) 시간에 탐색
```

**이 문제의 패턴:**
- "연속된 부분 배열의 합 = K"
- 전형적인 투 포인터 문제
- 누적합보다 직접 계산이 더 직관적

### 예외 처리 (조언)

**고려할 사항:**
```cpp
// N=0인 경우
if(N == 0){
    cout << 0;
    return 0;
}

// target이 음수인 경우 (문제에는 없지만)
if(target < 0){
    cout << 0;
    return 0;
}

// 배열에 음수가 있는 경우
// 현재 투 포인터 로직은 양수만 가정
// 음수가 있으면 다른 접근 필요 (해시맵 등)
```

---

## ✅ 최종 평가

**좋은 시도:**
- 투 포인터 알고리즘 선택 ✅
- 누적합을 활용하려 한 점 ✅
- 코드 구조가 간결한 점 ✅

**치명적 문제:**
- 구간 합 계산 수식 오류 ❌
  ```cpp
  prefixSum[end] - prefixSum[start] + arr[start]  // 틀림!
  ```
- 종료 조건 버그 (일부 경우 조기 종료) ❌

**성장 궤적:**
1. **1806번**: 62점 (재귀 투 포인터 - 부적절)
2. **2559번**: 78점 (슬라이딩 윈도우 - 좋음)
3. **16139번**: 88점 (2차원 누적합 - 완벽)
4. **3020번**: 82점 (역방향 누적합 - 탁월)
5. **2118번**: 70점 (원형 투 포인터 - 로직 오류)
6. **2003번**: 75점 (투 포인터 - 수식 오류)

**분석:**
이번에는 **수식 실수**가 주요 문제였습니다. 알고리즘 선택은 완벽했지만, 구간 합을 계산하는 수식에서 실수했습니다.

```
정확한 수식:
prefixSum[end] - prefixSum[start-1]  // 구간 [start, end]

잘못된 수식:
prefixSum[end] - prefixSum[start] + arr[start]  // 의미 불명
```

**교훈:**
- 누적합 수식은 항상 신중하게!
- `prefixSum[i]`가 정확히 무엇을 의미하는지 명확히 정의
- 사실 이 문제는 누적합 없이도 풀 수 있음 (더 간단)

**추천:**
1. 누적합 없이 직접 계산하는 투 포인터로 다시 구현해보세요
2. 테스트 케이스를 손으로 추적하며 수식 검증하세요
3. 함수 분리로 독립적인 테스트를 해보세요

다음 문제에서는 수식을 더 신중하게 검토하세요! 알고리즘 이해는 충분하니 구현 정확도만 높이면 됩니다! 💪
