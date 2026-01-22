# [Silver III] 수열 - 2559 

[문제 링크](https://www.acmicpc.net/problem/2559) 

### 성능 요약

메모리: 3048 KB, 시간: 8 ms

### 분류

누적 합, 두 포인터, 슬라이딩 윈도우

# 백준 2559번 코드 평가 리포트

## 📊 총점: 78/100점

---

## 📌 항목별 평가

### 초급 평가

#### 1. 정확성 (28/30점) ✅

**잘된 점:**
- 슬라이딩 윈도우 알고리즘을 정확하게 구현했습니다
- 큐를 사용해 K개의 연속된 원소를 추적하는 아이디어가 훌륭합니다
- 테스트 케이스를 정확히 통과할 것으로 예상됩니다

**작은 문제:**
- `NOT_FOUND = -10000001`을 사용했는데, 문제에서 온도 범위가 -100 ~ 100이므로 `-100 * 100000 = -10,000,000`이 최솟값입니다
- 안전하게 `INT_MIN`을 쓰거나, 첫 번째 값으로 초기화하는 것이 더 좋습니다

#### 2. 가독성 (18/25점) ⚠️

**좋은 점:**
- `buildPrefixSum` 함수명으로 기능을 명확히 표현했습니다
- `NOT_FOUND` 상수를 정의해 매직 넘버를 피했습니다
- 변수명이 대체로 명확합니다

**개선 필요:**
- **함수명 혼란**: `buildPrefixSum`인데 실제로는 "슬라이딩 윈도우 합들"을 반환합니다
  - 누적합(prefix sum)은 `[1, 1+2, 1+2+3, ...]` 형태
  - 슬라이딩 윈도우는 `[1+2+3, 2+3+4, 3+4+5, ...]` 형태
  - 더 정확한 이름: `calculateSlidingWindowSums` 또는 `getKDaySums`

- **변수명 중복**: `queue<int> queue;`는 타입과 변수명이 같아서 혼란스럽습니다
  ```cpp
  queue<int> tempQueue;  // 또는 window
  ```

- **변수명 의미**: `continuousTemp`보다 `windowSums` 또는 `kDaySums`가 더 명확합니다

#### 3. 간결성 (18/20점) ✅

**잘된 점:**
- 불필요한 코드가 거의 없습니다
- 삼항 연산자를 적절히 사용했습니다

**소소한 개선:**
```cpp
// 현재
maxTemp = maxTemp < continuousTemp[i] ? continuousTemp[i] : maxTemp;

// 더 간결하게
maxTemp = max(maxTemp, continuousTemp[i]);
```

---

### 중급 평가

#### 4. 효율성 (7/10점) ⚠️

**좋은 점:**
- 슬라이딩 윈도우를 사용해 O(N) 시간복잡도 달성 ✅
- 입력과 동시에 처리해 효율적입니다

**개선 필요:**
- **불필요한 벡터 저장**: 모든 윈도우 합을 `prefixSum` 벡터에 저장하는데, 사실 **최댓값만 필요**합니다
- 메모리 복잡도: O(N) → O(1)로 개선 가능

**개선안:**
```cpp
int getMaxTemperature(int N, int K){
    queue<int> window;
    int sum = 0;
    int maxTemp = INT_MIN;
    
    for(int i=1; i<=N; i++){
        int input;
        cin >> input;
        sum += input;
        window.push(input);
        
        if(i >= K){
            maxTemp = max(maxTemp, sum);
            sum -= window.front();
            window.pop();
        }
    }
    return maxTemp;
}
```

**성능 비교:**
```
현재 방식: 
- 시간 O(N) (입력) + O(N) (최댓값 찾기) = O(2N)
- 공간 O(N) (벡터 저장)

개선 방식:
- 시간 O(N) (입력하며 바로 최댓값 갱신)
- 공간 O(K) (큐만 사용)
```

#### 5. 구조 (8/10점) ✅

**좋은 점:**
- 함수 분리를 잘했습니다
- 입력 처리와 계산 로직을 분리한 시도가 좋습니다

**개선점:**
- 함수가 두 가지 일을 합니다: (1) 입력 받기 + (2) 윈도우 합 계산
- 최댓값 찾기 로직도 함수 내부에 포함시키면 더 응집도가 높아집니다

#### 6. 예외 처리 (2/5점) ⚠️

**누락된 검증:**
- N, K의 유효성 검증 없음 (K > N인 경우는?)
- 빈 벡터 검사 없음 (`continuousTemp`가 비어있을 수 있음)
- `NOT_FOUND` 값이 실제 답과 겹칠 가능성 (작지만 존재)

**개선:**
```cpp
if(K > N){
    // 에러 처리
}

if(continuousTemp.empty()){
    cout << 0;  // 또는 적절한 처리
    return 0;
}
```

---

## 💡 개선 제안

### 1️⃣ **함수명 정확하게 수정**

```cpp
// buildPrefixSum → 더 정확한 이름
vector<int> calculateSlidingWindowSums(int N, int K){
    // ...
}

// 또는 한국어 의미를 살려서
vector<int> getKDayTemperatureSums(int N, int K){
    // ...
}
```

### 2️⃣ **메모리 최적화: 벡터 제거**

```cpp
int findMaxTemperature(int N, int K){
    queue<int> window;
    int currentSum = 0;
    int maxSum = INT_MIN;
    
    for(int i=0; i<N; i++){
        int temp;
        cin >> temp;
        
        window.push(temp);
        currentSum += temp;
        
        if(window.size() == K){
            maxSum = max(maxSum, currentSum);
            currentSum -= window.front();
            window.pop();
        }
    }
    
    return maxSum;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N, K;
    cin >> N >> K;
    
    cout << findMaxTemperature(N, K);
    return 0;
}
```

### 3️⃣ **큐 없이도 가능 (더 간단)**

사실 큐도 필요 없습니다:

```cpp
int findMaxTemperature(int N, int K){
    vector<int> temps(N);
    for(int i=0; i<N; i++){
        cin >> temps[i];
    }
    
    // 첫 K개의 합
    int currentSum = 0;
    for(int i=0; i<K; i++){
        currentSum += temps[i];
    }
    
    int maxSum = currentSum;
    
    // 슬라이딩 윈도우
    for(int i=K; i<N; i++){
        currentSum += temps[i] - temps[i-K];
        maxSum = max(maxSum, currentSum);
    }
    
    return maxSum;
}
```

**장점:**
- 큐 자료구조 불필요
- 인덱스만으로 슬라이딩 윈도우 구현
- 더 직관적이고 간단

### 4️⃣ **변수명 개선**

```cpp
// 현재
vector<int> continuousTemp = buildPrefixSum(N, K);

// 개선
vector<int> windowSums = calculateSlidingWindowSums(N, K);
// 또는
vector<int> kDaySums = getKDayTemperatureSums(N, K);
```

### 5️⃣ **max 함수 활용**

```cpp
// 현재
maxTemp = maxTemp < continuousTemp[i] ? continuousTemp[i] : maxTemp;

// 개선
maxTemp = max(maxTemp, continuousTemp[i]);
```

---

## 🎓 실무 준비 단계 조언

### 유지보수성
- **함수명의 정확성**: `buildPrefixSum`은 오해를 불러일으킵니다. 6개월 후에 이 코드를 보면 "이게 누적합인가? 슬라이딩 윈도우인가?" 고민하게 됩니다
- **주석 추가**: 핵심 로직에 간단한 주석만 있어도 이해도가 크게 향상됩니다
  ```cpp
  // K일 동안의 온도 합을 슬라이딩 윈도우로 계산
  if(i >= K){
      maxTemp = max(maxTemp, sum);
      sum -= window.front();
      window.pop();
  }
  ```

### 확장성
- 만약 "K일 평균 온도의 최댓값"을 구하라고 바뀐다면?
  - 현재 구조: 벡터에 저장된 값들을 다시 순회하며 K로 나누기
  - 개선 구조: 함수 내부에서 바로 `sum / K` 처리 가능
  
- "상위 3개의 K일 온도 합"을 구하라면?
  - 현재: 벡터를 정렬해서 가능 (괜찮은 확장성)
  - 개선: priority_queue 사용 필요

### 일관성
- `queue<int> queue;`처럼 타입과 변수명이 같은 경우는 피하세요
- 일관된 명명 규칙: `camelCase` vs `snake_case` 중 하나로 통일
  ```cpp
  // 혼재된 경우
  continuousTemp  // camelCase
  prefix_sum      // snake_case
  
  // 통일
  continuousTemp, prefixSum  // 모두 camelCase
  ```

### 테스트 가능성
- 현재 함수가 입력까지 받아서 독립 테스트가 어렵습니다
- 개선안: 입력을 외부에서 받아 매개변수로 전달
  ```cpp
  int findMaxTemperature(const vector<int>& temps, int K){
      // temps 배열을 매개변수로 받으면 테스트 쉬움
  }
  
  // 테스트
  vector<int> testTemps = {3, -2, -4, -9, 0, 3, 7, 13, 8, -3};
  assert(findMaxTemperature(testTemps, 2) == 21);
  ```

### 알고리즘 최적화
- **현재 접근**: 슬라이딩 윈도우 + 큐 → 정확하지만 약간 복잡
- **표준 접근**: 슬라이딩 윈도우 + 인덱스 → 더 간단하고 직관적
- 실무에서는 "같은 결과를 내는 가장 간단한 코드"가 선호됩니다

---

## ✅ 최종 평가

**훌륭한 점:**
- 슬라이딩 윈도우 알고리즘을 정확히 이해하고 구현했습니다
- 큐를 활용한 창의적인 접근이 돋보입니다
- 함수 분리와 상수 정의로 가독성을 높이려 노력했습니다

**개선이 필요한 점:**
- 함수명이 실제 동작과 다릅니다 (prefix sum ≠ sliding window)
- 최댓값만 필요한데 모든 윈도우 합을 벡터에 저장해 메모리 낭비
- 큐 없이도 인덱스만으로 더 간단하게 구현 가능

**성장 포인트:**
이전 문제(1806번)에서 재귀로 투 포인터를 구현했던 것과 달리, 이번에는 적절한 자료구조(큐)와 반복문을 사용했습니다. 알고리즘 선택이 훨씬 좋아졌습니다! 다음 단계는 "필요한 것만 저장하기"입니다. 모든 중간 결과를 저장할 필요는 없습니다. 💡

**추천 연습:**
- 같은 문제를 큐 없이 인덱스만으로 다시 구현해보세요
- "최댓값을 찾으며 동시에 처리"하는 패턴을 익혀보세요
- STL `max()` 함수 활용에 익숙해지세요

계속 이런 식으로 성장하고 있습니다! 🚀

