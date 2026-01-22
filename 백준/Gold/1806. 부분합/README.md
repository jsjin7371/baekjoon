# [Gold IV] 부분합 - 1806 

[문제 링크](https://www.acmicpc.net/problem/1806) 

### 성능 요약

메모리: 2804 KB, 시간: 12 ms

# 백준 1806번 코드 평가 리포트

## 📊 총점: 62/100점

---

## 📌 항목별 평가

### 초급 평가

#### 1. 정확성 (15/30점) ⚠️

**심각한 문제점:**
- **스택 오버플로우 위험**: 재귀로 투 포인터를 구현하면 N=100,000일 때 스택이 터집니다
- **시간 초과 가능성**: 재귀 호출 오버헤드로 인해 효율성이 떨어집니다
- **로직 오류**: `endPointer = 0`으로 시작하는데, `prefixSum[0] - prefixSum[0] = 0`이므로 첫 번째 원소를 놓칩니다

**테스트 케이스:**
```
입력:
5 11
1 2 3 4 5

예상 출력: 3 (3+4+4 또는 4+5+2...)
실제로는 정상 작동할 수도 있지만, 큰 입력에서 스택 오버플로우 발생
```

#### 2. 가독성 (15/25점) ⚠️

**좋은 점:**
- `buildPrefixSum`, `getMinimumLength`로 함수를 분리한 시도가 좋습니다
- `prefixSum` 변수명이 의미를 잘 전달합니다

**개선 필요:**
- `isInitialSet = -1`이 매직 넘버입니다 → 상수나 더 명확한 이름 필요
- `getMinimumLength` 함수가 실제로는 "투 포인터로 탐색"하는 함수인데 이름이 결과 중심입니다
- 재귀 로직이 직관적이지 않아 이해하기 어렵습니다

#### 3. 간결성 (12/20점) ⚠️

**불필요한 부분:**
```cpp
if(minimumLength == isInitialSet){
    minimumLength = 0;
    cout << minimumLength;
}
else{
    cout << minimumLength;
}
```
→ 다음과 같이 간결하게 가능:
```cpp
cout << (minimumLength == isInitialSet ? 0 : minimumLength);
```

---

### 중급 평가

#### 4. 효율성 (3/10점) ❌

**문제점:**
- **시간 복잡도**: O(N) + 재귀 오버헤드 → 실질적으로 O(N) 이상
- **공간 복잡도**: O(N) 스택 공간 사용 → 매우 비효율적
- 투 포인터는 반복문으로 구현해야 O(N) 시간, O(1) 스택 공간 달성 가능

**비교:**
```
반복문 방식: 스택 공간 O(1)
재귀 방식: 스택 공간 O(N) → 100,000번 호출 시 위험
```

#### 5. 구조 (8/10점) ✅

**좋은 점:**
- 함수 분리를 시도한 점이 훌륭합니다
- `buildPrefixSum`이 독립적인 역할을 잘 수행합니다

**개선점:**
- 전역 변수 `prefixSum` 사용 → 함수 간 의존성 증가
- `getMinimumLength`가 너무 많은 일을 합니다 (탐색 + 최솟값 갱신)

#### 6. 예외 처리 (1/5점) ❌

**누락된 검증:**
- N, S의 범위 검증 없음
- `prefixSum.size()` 체크는 있지만, 재귀 깊이 제한 없음
- 입력값이 음수일 경우 고려 없음 (문제에서는 자연수지만)

---

## 💡 개선 제안

### 1️⃣ **재귀 → 반복문으로 변경 (필수)**

```cpp
int getMinimumLength(int N, int target){
    int start = 0, end = 1;  // end를 1부터 시작
    int minLen = N + 1;      // 불가능한 큰 값으로 초기화
    
    while(start < N){
        long long sum = prefixSum[end] - prefixSum[start];
        
        if(sum >= target){
            minLen = min(minLen, end - start);
            start++;
        }
        else if(end < N){
            end++;
        }
        else{
            break;
        }
    }
    
    return (minLen == N + 1) ? 0 : minLen;
}
```

### 2️⃣ **전역 변수 제거**

```cpp
int getMinimumLength(const vector<long long>& prefixSum, int target){
    // prefixSum을 매개변수로 받기
    // ...
}

int main(){
    // ...
    vector<long long> prefixSum = buildPrefixSum(N);
    int result = getMinimumLength(prefixSum, S);
    cout << result;
}
```

### 3️⃣ **매직 넘버 제거**

```cpp
const int NOT_FOUND = -1;
const int IMPOSSIBLE = 0;

int minimumLength = NOT_FOUND;
// ...
if(minimumLength == NOT_FOUND){
    cout << IMPOSSIBLE;
}
```

### 4️⃣ **실제로 누적합이 필요한가?**

이 문제는 **누적합 없이** 투 포인터만으로 해결 가능합니다:

```cpp
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, S;
    cin >> N >> S;
    
    vector<int> arr(N);
    for(int i=0; i<N; i++){
        cin >> arr[i];
    }
    
    int start = 0, end = 0;
    int sum = 0;
    int minLen = N + 1;
    
    while(true){
        if(sum >= S){
            minLen = min(minLen, end - start);
            sum -= arr[start];
            start++;
        }
        else if(end < N){
            sum += arr[end];
            end++;
        }
        else{
            break;
        }
    }
    
    cout << (minLen == N + 1 ? 0 : minLen);
    return 0;
}
```

**장점:**
- 공간 복잡도 O(N) → O(N) (입력 배열만)
- 누적합 계산 불필요
- 더 직관적인 투 포인터 구현

---

## 🎓 실무 준비 단계 조언

### 유지보수성
- 재귀 대신 반복문을 사용하면 디버깅이 훨씬 쉽습니다
- 중간에 `cout` 디버깅을 넣어가며 start, end, sum 값을 추적할 수 있습니다
- 6개월 후에 봤을 때 "왜 재귀로 했지?"라는 의문이 들 수 있습니다

### 확장성
- 만약 "구간 합이 S 이하인 최대 길이"로 문제가 바뀐다면?
- 현재 구조에서는 조건문 하나만 바꾸면 되지만, 재귀 구조가 복잡도를 높입니다
- 반복문 구조가 변형에 더 유연합니다

### 일관성
- `isInitialSet = -1`과 `minimumLength = N + 1` 같은 초기값을 일관되게 사용하세요
- "불가능"을 나타내는 값을 한 가지로 통일 (0, -1, INT_MAX 중 선택)

### 테스트 가능성
- 함수 분리는 잘했지만, 전역 변수 때문에 독립적 테스트가 어렵습니다
- `getMinimumLength`에 `prefixSum`을 매개변수로 전달하면 단위 테스트 가능

### 알고리즘 선택
- **투 포인터는 반복문이 정석**입니다
- 재귀는 백트래킹, DFS, 분할정복 같은 특수한 경우에만 사용
- "같은 레벨에서 상태를 업데이트하며 진행"하는 투 포인터는 반복문이 자연스럽습니다

---

## ✅ 최종 평가

**좋은 시도:**
- 함수 분리를 시도한 점
- 변수명이 비교적 명확한 점
- 투 포인터 알고리즘을 선택한 점

**치명적 문제:**
- 재귀로 투 포인터를 구현하면 스택 오버플로우 위험
- 큰 입력(N=100,000)에서 실행 불가능할 가능성 높음
- 불필요하게 누적합을 사용해 메모리 낭비

**개선 방향:**
1. 재귀를 반복문으로 변경 (최우선)
2. 전역 변수 제거
3. 누적합 없이 직접 투 포인터 구현 고려
4. 매직 넘버를 상수로 정의

알고리즘 선택은 좋았지만, **구현 방식에서 큰 실수**가 있었습니다. 투 포인터는 항상 반복문으로 구현하는 것이 표준입니다. 다음 문제에서는 이 점을 꼭 기억하세요! 💪
