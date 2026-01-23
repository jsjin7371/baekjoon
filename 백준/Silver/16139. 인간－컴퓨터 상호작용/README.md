# [Silver I] 인간-컴퓨터 상호작용 - 16139 

[문제 링크](https://www.acmicpc.net/problem/16139) 

### 성능 요약

메모리: 23568 KB, 시간: 112 ms

### 분류

누적 합

### 제출 일자

2026년 1월 23일 20:52:14

# 백준 16139번 코드 평가 리포트

## 📊 총점: 88/100점

---

## 📌 항목별 평가

### 초급 평가

#### 1. 정확성 (30/30점) ✅

**완벽합니다!**
- 2차원 누적합 알고리즘을 정확하게 구현했습니다
- 각 알파벳별로 누적합을 따로 관리하는 아이디어가 탁월합니다
- 쿼리 처리를 O(1)에 해결하는 핵심 로직이 완벽합니다
- 인덱싱 처리(`r+1`, `l`)가 정확합니다

**테스트 검증:**
```
입력: "seungjaehwang", 알파벳 'a', 구간 [0, 5]
- 's'(0), 'e'(1), 'u'(2), 'n'(3), 'g'(4), 'j'(5), 'a'(6)
- 구간 [0,5]에 'a' = 0개
- alphabetsPrefixSum[0][6] - alphabetsPrefixSum[0][0] = 0 ✅
```

#### 2. 가독성 (22/25점) ✅

**잘된 점:**
- `alphabetsPrefixSum`이라는 변수명이 의도를 명확히 전달합니다
- 2차원 벡터를 사용해 각 알파벳별 누적합을 저장하는 구조가 직관적입니다
- 전체적인 코드 흐름을 이해하기 쉽습니다

**소소한 개선점:**
- `rep` 변수가 불필요합니다 → `word.size()`를 직접 사용해도 됩니다
- `alphabetSum` 변수를 선언했지만 사용하지 않습니다 (불필요한 변수)
- `targetWord`보다 `targetChar` 또는 `alpha`가 더 정확한 이름입니다

```cpp
// 현재
int rep = word.size();
for(int i=1; i<=rep; i++){...}

// 개선
for(int i=1; i<=word.size(); i++){...}
// 또는
int n = word.size();
for(int i=1; i<=n; i++){...}
```

#### 3. 간결성 (20/20점) ✅

**훌륭합니다!**
- 불필요한 코드가 거의 없습니다 (alphabetSum 제외)
- 중복 없이 효율적으로 작성했습니다
- 핵심 로직이 명확하게 드러납니다

---

### 중급 평가

#### 4. 효율성 (10/10점) ✅

**완벽한 최적화!**
- **전처리 시간복잡도**: O(N × 26) = O(N) (상수 계수 무시)
- **쿼리 시간복잡도**: O(1)
- **전체 시간복잡도**: O(N × 26 + Q) = O(N + Q)

**메모리 복잡도**: O(26 × N) = O(N) (상수 계수 무시)

이 문제의 최적 솔루션입니다! 다른 방법은 없습니다.

**성능 분석:**
```
N = 200,000, Q = 200,000인 경우
- 단순 반복: O(N × Q) = 40,000,000,000 (시간 초과)
- 누적합 사용: O(N + Q) = 400,000 (0.01초 이내)
```

#### 5. 구조 (6/10점) ⚠️

**개선 필요:**
- 모든 로직이 `main` 함수에 집중되어 있습니다
- 전처리와 쿼리 처리를 함수로 분리하면 더 좋습니다

**개선 예시:**
```cpp
void buildAlphabetPrefixSum(const string& word, 
                           vector<vector<int>>& prefixSum){
    int n = word.size();
    for(int i=1; i<=n; i++){
        int alphabetNum = word[i-1] - 'a';
        prefixSum[alphabetNum][i]++;
        
        for(int j=0; j<26; j++){
            prefixSum[j][i] += prefixSum[j][i-1];
        }
    }
}

int queryCharCount(const vector<vector<int>>& prefixSum, 
                   char targetChar, int l, int r){
    int index = targetChar - 'a';
    return prefixSum[index][r+1] - prefixSum[index][l];
}
```

**장점:**
- 각 기능을 독립적으로 테스트 가능
- 코드 재사용성 증가
- 디버깅 용이

#### 6. 예외 처리 (0/5점) ❌

**완전히 누락:**
- 입력 검증이 전혀 없습니다
- 잘못된 입력에 대한 방어가 없습니다

**위험한 케이스:**
```cpp
// 1. 범위 초과
// l, r이 문자열 범위를 벗어나면?
if(l < 0 || r >= word.size() || l > r){
    // 에러 처리
}

// 2. 대문자 입력
// targetWord가 'A'라면? (문제는 소문자만 보장)
if(targetChar < 'a' || targetChar > 'z'){
    // 에러 처리
}

// 3. 빈 문자열
if(word.empty()){
    // 에러 처리
}
```

**참고:** 백준 온라인 저지에서는 입력이 보장되지만, 실무에서는 치명적입니다.

---

## 💡 개선 제안

### 1️⃣ **불필요한 변수 제거**

```cpp
// 현재
vector<int> alphabetSum(26,0);  // 사용하지 않음
int rep = word.size();          // 불필요

// 개선 (제거)
int n = word.size();
for(int i=1; i<=n; i++){
    // ...
}
```

### 2️⃣ **함수 분리**

```cpp
const int ALPHABET_SIZE = 26;

void buildAlphabetPrefixSum(const string& word, 
                           vector<vector<int>>& prefixSum){
    int n = word.size();
    for(int i=1; i<=n; i++){
        int alphabetIdx = word[i-1] - 'a';
        prefixSum[alphabetIdx][i]++;
        
        for(int j=0; j<ALPHABET_SIZE; j++){
            prefixSum[j][i] += prefixSum[j][i-1];
        }
    }
}

int queryAlphabetCount(const vector<vector<int>>& prefixSum, 
                      char targetChar, int left, int right){
    int charIdx = targetChar - 'a';
    return prefixSum[charIdx][right+1] - prefixSum[charIdx][left];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    string word;
    int q;
    cin >> word >> q;

    vector<vector<int>> alphabetsPrefixSum(ALPHABET_SIZE, 
                                          vector<int>(word.size()+1, 0));
    
    buildAlphabetPrefixSum(word, alphabetsPrefixSum);

    for(int i=0; i<q; i++){
        char targetChar;
        int l, r;
        cin >> targetChar >> l >> r;
        
        cout << queryAlphabetCount(alphabetsPrefixSum, targetChar, l, r) 
             << "\n";
    }

    return 0;
}
```

### 3️⃣ **상수 정의**

```cpp
// 현재
vector<vector<int>> alphabetsPrefixSum(26, ...);
for(int j=0; j<26; j++){...}

// 개선
const int ALPHABET_SIZE = 26;
const char FIRST_CHAR = 'a';

vector<vector<int>> alphabetsPrefixSum(ALPHABET_SIZE, ...);
for(int j=0; j<ALPHABET_SIZE; j++){...}

int alphabetIdx = targetChar - FIRST_CHAR;
```

### 4️⃣ **변수명 개선**

```cpp
// 현재
char targetWord;      // 실제로는 문자 하나
int index;           // 너무 일반적

// 개선
char targetChar;     // 또는 alpha, ch
int charIndex;       // 또는 alphaIdx
```

### 5️⃣ **입력 검증 추가 (실무용)**

```cpp
int queryAlphabetCount(const vector<vector<int>>& prefixSum, 
                      char targetChar, int left, int right, int maxLen){
    // 범위 검증
    if(left < 0 || right >= maxLen || left > right){
        return -1;  // 또는 예외 처리
    }
    
    // 문자 검증
    if(targetChar < 'a' || targetChar > 'z'){
        return -1;
    }
    
    int charIdx = targetChar - 'a';
    return prefixSum[charIdx][right+1] - prefixSum[charIdx][left];
}
```

---

## 🎓 실무 준비 단계 조언

### 유지보수성

**좋은 점:**
- 2차원 누적합이라는 명확한 패턴을 사용해 나중에 봐도 이해하기 쉽습니다

**개선점:**
- 핵심 로직에 주석 추가하면 더 좋습니다
```cpp
// 각 알파벳의 누적 등장 횟수를 계산
for(int i=1; i<=n; i++){
    int alphabetIdx = word[i-1] - 'a';
    
    // 현재 위치의 알파벳 카운트 증가
    prefixSum[alphabetIdx][i]++;
    
    // 이전 위치까지의 누적합 더하기
    for(int j=0; j<26; j++){
        prefixSum[j][i] += prefixSum[j][i-1];
    }
}
```

### 확장성

**현재 구조의 장점:**
- 알파벳을 다른 문자 집합으로 쉽게 확장 가능
- 쿼리 종류가 바뀌어도 누적합 배열은 재사용 가능

**확장 시나리오:**
1. "특정 구간에서 모음 개수"를 구한다면?
   ```cpp
   bool isVowel(char c){
       return c=='a' || c=='e' || c=='i' || c=='o' || c=='u';
   }
   
   int vowelCount = 0;
   for(char vowel : {'a','e','i','o','u'}){
       vowelCount += queryAlphabetCount(..., vowel, l, r);
   }
   ```

2. "가장 많이 등장한 알파벳"을 구한다면?
   - 현재 구조로 모든 알파벳을 순회하며 쉽게 해결 가능

### 일관성

**개선 필요:**
- 변수명 스타일 통일
  ```cpp
  // 혼재
  alphabetsPrefixSum  // camelCase
  targetWord         // camelCase
  q                  // 단일 문자
  
  // 통일
  alphabetPrefixSum  // s 제거, 일관성
  targetChar         // 정확한 의미
  queryCount         // 명확한 이름
  ```

- 인덱스 변수 통일
  ```cpp
  // 현재
  i, j (이중 루프)
  i (쿼리 루프)
  
  // 개선
  i, j (누적합 구축)
  q (쿼리 루프) 또는 queryIdx
  ```

### 테스트 가능성

**현재 문제:**
- 모든 로직이 main에 있어 단위 테스트 불가능
- cin을 직접 사용해 테스트 데이터 주입이 어려움

**개선 후:**
```cpp
// 함수 분리 후 단위 테스트 가능
void testPrefixSum(){
    string word = "appa";
    vector<vector<int>> prefixSum(26, vector<int>(5, 0));
    
    buildAlphabetPrefixSum(word, prefixSum);
    
    // 테스트: 'p'가 [0,3]에 2개
    assert(queryAlphabetCount(prefixSum, 'p', 0, 3) == 2);
    
    // 테스트: 'a'가 [0,3]에 2개
    assert(queryAlphabetCount(prefixSum, 'a', 0, 3) == 2);
    
    cout << "All tests passed!\n";
}
```

### 알고리즘 이해도

**탁월합니다!**
- 누적합의 핵심을 정확히 이해했습니다
- 2차원으로 확장하는 아이디어가 훌륭합니다
- 인덱싱 오프셋(`r+1`, `l`)을 정확히 처리했습니다

**패턴 인식:**
이 문제는 "다중 쿼리 + 구간 합" 패턴입니다. 앞으로 비슷한 문제를 보면:
1. 전처리로 누적합/DP 배열 구축 → O(N)
2. 각 쿼리를 O(1) 또는 O(logN)에 처리
3. 전체 O(N + Q) 또는 O(N + QlogN)

---

## ✅ 최종 평가

**뛰어난 점:**
- 알고리즘 선택과 구현이 완벽합니다 🌟
- 2차원 누적합을 정확하게 이해하고 적용했습니다
- 시간 복잡도 최적화가 완벽합니다
- 코드가 간결하고 이해하기 쉽습니다

**개선할 점:**
- 함수 분리로 구조화 필요
- 불필요한 변수(`alphabetSum`, `rep`) 제거
- 예외 처리 추가 (실무 관점)
- 변수명 통일성 개선

**성장 궤적:**
1. **1806번**: 재귀로 투 포인터 (부적절한 구현) - 62점
2. **2559번**: 슬라이딩 윈도우 + 큐 (좋은 접근, 약간 복잡) - 78점
3. **16139번**: 2차원 누적합 (완벽한 알고리즘, 깔끔한 구현) - 88점

**확실히 성장하고 있습니다!** 알고리즘 이해도와 구현 능력이 눈에 띄게 향상되었습니다. 다음 단계는:
- 함수 분리와 모듈화
- 입력 검증과 예외 처리
- 더 명확한 변수명 선택

이 세 가지만 개선하면 실무 수준의 코드가 됩니다! 💪

**추천 다음 문제:**
- 구간 합 심화 (세그먼트 트리, 펜윅 트리)
- 2차원 누적합 문제
- DP와 누적합을 결합한 문제

계속 이렇게 성장하세요! 정말 잘하고 있습니다! 🚀
