# [Gold V] 개똥벌레 - 3020 

[문제 링크](https://www.acmicpc.net/problem/3020) 

### 성능 요약

메모리: 5932 KB, 시간: 24 ms

### 분류

이분 탐색, 누적 합, 차분 배열 트릭

### 제출 일자

2026년 1월 27일 21:16:04

### 문제 설명

<p>개똥벌레 한 마리가 장애물(석순과 종유석)로 가득찬 동굴에 들어갔다. 동굴의 길이는 N미터이고, 높이는 H미터이다. (N은 짝수) 첫 번째 장애물은 항상 석순이고, 그 다음에는 종유석과 석순이 번갈아가면서 등장한다.</p>

<p>아래 그림은 길이가 14미터이고 높이가 5미터인 동굴이다. (예제 그림)</p>

<p style="text-align: center;"><img alt="" src="https://upload.acmicpc.net/c6fd496d-ccf5-4f9d-a06e-32b121fc6a82/-/preview/" style="width: 271px; height: 108px;"></p>

<p>이 개똥벌레는 장애물을 피하지 않는다. 자신이 지나갈 구간을 정한 다음 일직선으로 지나가면서 만나는 모든 장애물을 파괴한다.</p>

<p>위의 그림에서 4번째 구간으로 개똥벌레가 날아간다면 파괴해야하는 장애물의 수는 총 여덟개이다. (4번째 구간은 길이가 3인 석순과 길이가 4인 석순의 중간지점을 말한다)</p>

<p style="text-align: center;"><img alt="" src="https://upload.acmicpc.net/bfcbb94f-0e15-4ff9-b2ef-43e07c7ee503/-/preview/" style="width: 292px; height: 108px;"></p>

<p>하지만, 첫 번째 구간이나 다섯 번째 구간으로 날아간다면 개똥벌레는 장애물 일곱개만 파괴하면 된다.</p>

<p>동굴의 크기와 높이, 모든 장애물의 크기가 주어진다. 이때, 개똥벌레가 파괴해야하는 장애물의 최솟값과 그러한 구간이 총 몇 개 있는지 구하는 프로그램을 작성하시오.</p>

### 입력 

 <p>첫째 줄에 N과 H가 주어진다. N은 항상 짝수이다. (2 ≤ N ≤ 200,000, 2 ≤ H ≤ 500,000)</p>

<p>다음 N개 줄에는 장애물의 크기가 순서대로 주어진다. 장애물의 크기는 H보다 작은 양수이다.</p>

### 출력 

 <p>첫째 줄에 개똥벌레가 파괴해야 하는 장애물의 최솟값과 그러한 구간의 수를 공백으로 구분하여 출력한다.</p>

# 백준 3020번 코드 평가 리포트

## 📊 총점: 82/100점

---

## 📌 항목별 평가

### 초급 평가

#### 1. 정확성 (28/30점) ✅

**매우 잘했습니다!**
- 석순(아래)과 종유석(위)을 분리해서 카운팅하는 핵심 아이디어가 정확합니다
- 역방향 누적합을 사용해 "높이 h 이상에 걸리는 장애물 수"를 계산하는 로직이 완벽합니다
- 최솟값과 그 개수를 동시에 구하는 로직이 정확합니다

**작은 감점 이유:**
- `least = 200000`으로 초기화했는데, 최대 장애물 수는 N/2 + N/2 = N = 200,000입니다
- 안전하지만 `200001` 또는 `INT_MAX`가 더 명확합니다
- 실제로는 문제없지만, 정확한 상한을 사용하는 습관이 중요합니다

**알고리즘 검증:**
```
예제: N=6, H=7
석순(짝수 인덱스): 1, 5, 3 (아래에서 올라옴)
종유석(홀수 인덱스): 3, 4, 2 (위에서 내려옴)

높이 4를 지날 때:
- 석순 중 높이 4 이상: 5 (1개)
- 종유석 중 높이 (7-4+1)=4 이상: 4, 3 (2개)
- 총 3개 ✅
```

#### 2. 가독성 (18/25점) ⚠️

**좋은 점:**
- 변수명이 대체로 의미를 전달합니다
- 전체적인 로직 흐름이 이해 가능합니다

**개선 필요:**
- **변수명 혼란**: `unlayerObjectSum`과 `uplayerObjectSum`이 오타처럼 보입니다
  - `unlayer` → `bottom` 또는 `stalagmite` (석순)
  - `uplayer` → `top` 또는 `stalactite` (종유석)
  
- **일관성 부족**: 
  ```cpp
  // 현재
  unlayerObjectSum  // camelCase + 긴 이름
  isEven           // camelCase
  cnt              // 축약형
  
  // 개선
  bottomCount      // 일관된 camelCase
  isEven           // 유지
  obstacleCount    // 명확한 이름
  ```

- **매직 넘버**: `200000`이 직접 코드에 등장
  ```cpp
  const int MAX_OBSTACLES = 200000;
  int least = MAX_OBSTACLES;
  ```

#### 3. 간결성 (17/20점) ✅

**잘된 점:**
- 불필요한 코드가 거의 없습니다
- 중복 없이 효율적으로 작성했습니다

**소소한 개선:**
```cpp
// 현재
if(isEven){
    unlayerObjectSum[input]++;
}
else{
    uplayerObjectSum[input]++;
}
isEven = !isEven;

// 개선 (가독성 향상)
(isEven ? unlayerObjectSum : uplayerObjectSum)[input]++;
isEven = !isEven;

// 또는 인덱스 활용
(i % 2 == 0 ? bottomCount : topCount)[input]++;
```

---

### 중급 평가

#### 4. 효율성 (10/10점) ✅

**완벽합니다!**
- **시간 복잡도**: O(N + H) - 최적입니다
  - 입력 처리: O(N)
  - 역방향 누적합: O(H)
  - 높이 순회: O(H)
- **공간 복잡도**: O(H) - 필요한 만큼만 사용

**최적화 분석:**
```
단순 접근: 각 높이마다 모든 장애물 체크 → O(H × N) = 시간 초과
누적합 접근: 전처리 후 O(1) 조회 → O(N + H) = 통과 ✅
```

**역방향 누적합의 이해:**
```
석순 배열 [1, 0, 1, 0, 1]
높이 5부터 역순으로:
5: 1
4: 1 (4이상)
3: 2 (3이상) 
2: 2 (2이상)
1: 3 (1이상)

→ "높이 h 이상에 걸리는 장애물 수"를 O(1)에 조회
```

#### 5. 구조 (7/10점) ⚠️

**개선 필요:**
- 모든 로직이 `main` 함수에 집중되어 있습니다
- 입력 처리, 누적합 계산, 최솟값 찾기를 분리하면 더 좋습니다

**개선 예시:**
```cpp
void readObstacles(int N, vector<int>& bottom, vector<int>& top){
    bool isBottom = true;
    for(int i=0; i<N; i++){
        int height;
        cin >> height;
        (isBottom ? bottom : top)[height]++;
        isBottom = !isBottom;
    }
}

void buildReversePrefixSum(vector<int>& arr){
    for(int i = arr.size()-2; i > 0; i--){
        arr[i] += arr[i+1];
    }
}

pair<int, int> findMinObstacles(const vector<int>& bottom, 
                                const vector<int>& top, int H){
    int minObstacles = INT_MAX;
    int count = 0;
    
    for(int h=1; h<=H; h++){
        int obstacles = bottom[h] + top[H-h+1];
        if(obstacles < minObstacles){
            minObstacles = obstacles;
            count = 1;
        }
        else if(obstacles == minObstacles){
            count++;
        }
    }
    
    return {minObstacles, count};
}
```

---

## 💡 개선 제안

### 1️⃣ **변수명 개선**

```cpp
// 현재
vector<int> unlayerObjectSum(H+1,0);  // 오타처럼 보임
vector<int> uplayerObjectSum(H+1,0);

// 개선 1: 영어 정확히
vector<int> bottomObstacles(H+1, 0);  // 석순
vector<int> topObstacles(H+1, 0);     // 종유석

// 개선 2: 실제 용어 사용
vector<int> stalagmite(H+1, 0);       // 석순
vector<int> stalactite(H+1, 0);       // 종유석

// 개선 3: 의미 기반
vector<int> fromBottom(H+1, 0);
vector<int> fromTop(H+1, 0);
```

### 2️⃣ **함수 분리**

```cpp
const int MAX_N = 200000;

void readObstacles(int N, vector<int>& bottom, vector<int>& top){
    for(int i=0; i<N; i++){
        int height;
        cin >> height;
        (i % 2 == 0 ? bottom : top)[height]++;
    }
}

void buildCumulativeCount(vector<int>& obstacles){
    int H = obstacles.size() - 1;
    for(int i = H-1; i > 0; i--){
        obstacles[i] += obstacles[i+1];
    }
}

pair<int, int> findMinimumPath(const vector<int>& bottom, 
                               const vector<int>& top, int H){
    int minCount = MAX_N + 1;
    int frequency = 0;
    
    for(int height=1; height<=H; height++){
        int current = bottom[height] + top[H-height+1];
        
        if(current < minCount){
            minCount = current;
            frequency = 1;
        }
        else if(current == minCount){
            frequency++;
        }
    }
    
    return {minCount, frequency};
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, H;
    cin >> N >> H;
    
    vector<int> bottomObstacles(H+1, 0);
    vector<int> topObstacles(H+1, 0);
    
    readObstacles(N, bottomObstacles, topObstacles);
    
    buildCumulativeCount(bottomObstacles);
    buildCumulativeCount(topObstacles);
    
    auto [minObstacles, pathCount] = findMinimumPath(
        bottomObstacles, topObstacles, H
    );
    
    cout << minObstacles << "\n" << pathCount;
    
    return 0;
}
```

### 3️⃣ **상수 정의**

```cpp
const int MAX_N = 200000;
const int MAX_H = 500000;

int main(){
    // ...
    int least = MAX_N + 1;  // 명확한 초기값
    // ...
}
```

### 4️⃣ **주석 추가 (핵심 로직)**

```cpp
// 역방향 누적합: "높이 h 이상에 걸리는 장애물 수" 계산
for(int i = H-1; i > 0; i--){
    bottomObstacles[i] = bottomObstacles[i+1] + bottomObstacles[i];
    topObstacles[i] = topObstacles[i+1] + topObstacles[i];
}

// 각 높이에서 부딪히는 장애물 수 계산
for(int h=1; h<=H; h++){
    // 석순은 h 이상, 종유석은 (H-h+1) 이상에서 걸림
    int obstacles = bottomObstacles[h] + topObstacles[H-h+1];
    // ...
}
```

### 5️⃣ **인덱스 활용으로 간결화**

```cpp
// isEven 불필요
for(int i=0; i<N; i++){
    int height;
    cin >> height;
    
    if(i % 2 == 0){
        bottomObstacles[height]++;
    }
    else{
        topObstacles[height]++;
    }
}
```

---

## 🎓 실무 준비 단계 조언

### 유지보수성

**현재 상태:**
- 로직이 main에 몰려있어 6개월 후 보면 이해하기 어려울 수 있습니다
- 특히 `unlayerObjectSum[i] + uplayerObjectSum[H-i+1]`이 왜 정답인지 즉시 파악하기 어렵습니다

**개선 후:**
```cpp
// 함수명과 주석으로 의도 명확히
int obstacles = calculateObstaclesAtHeight(bottom, top, height, H);

// 또는
// 높이 h를 지날 때: 아래에서 h 이상 + 위에서 (H-h+1) 이상
int obstacles = bottom[h] + top[H-h+1];
```

### 확장성

**현재 구조의 장점:**
- 역방향 누적합 패턴을 사용해 다른 쿼리에도 대응 가능
- 예: "높이 범위 [a, b]에서 최소 장애물"도 쉽게 확장 가능

**확장 시나리오:**
1. "장애물을 k개 이하로 지나가는 높이는?"
   ```cpp
   for(int h=1; h<=H; h++){
       if(bottom[h] + top[H-h+1] <= k){
           cout << h << " ";
       }
   }
   ```

2. "각 높이별 장애물 수 출력"
   - 이미 계산되어 있어 O(H)에 출력 가능

### 일관성

**개선 필요:**
```cpp
// 혼재된 스타일
unlayerObjectSum  // 긴 camelCase
isEven            // 짧은 camelCase
cnt               // 축약
least             // 단어

// 통일된 스타일
bottomObstacleCount  // 명확한 camelCase
isBottomObstacle     // 명확한 camelCase
obstacleCount        // 명확한 camelCase
minimumObstacles     // 명확한 camelCase
```

### 테스트 가능성

**현재 문제:**
- cin 직접 사용으로 테스트 데이터 주입 어려움
- 로직이 main에 있어 독립 테스트 불가능

**개선 후:**
```cpp
void testReversePrefix(){
    vector<int> arr = {0, 1, 0, 1, 0, 1};
    buildCumulativeCount(arr);
    
    // arr[3] = 높이 3 이상 장애물 수
    assert(arr[3] == 2);  // 높이 3, 5
    assert(arr[1] == 3);  // 높이 1, 3, 5
}

void testFindMinimum(){
    vector<int> bottom = {0, 3, 2, 2, 1, 1};  // 역누적합 완료
    vector<int> top = {0, 2, 2, 3, 3, 3};
    
    auto [minObs, cnt] = findMinimumPath(bottom, top, 5);
    
    assert(minObs == 3);
    assert(cnt == 2);
}
```

### 알고리즘 패턴

**역방향 누적합 패턴 인식:**
```
일반 누적합: "1부터 i까지의 합" → prefix[i] = prefix[i-1] + arr[i]
역방향 누적합: "i부터 끝까지의 합" → suffix[i] = suffix[i+1] + arr[i]

이 문제: "높이 h 이상에 걸리는 개수" = 역방향 누적합!
```

**비슷한 패턴의 문제:**
- 구간 쿼리에서 "x 이상", "x 이하" 조건
- 정렬된 배열에서 범위 카운팅
- Fenwick Tree, Segment Tree의 기초

---

## ✅ 최종 평가

**뛰어난 점:**
- 역방향 누적합 아이디어가 탁월합니다 🌟
- 석순/종유석을 분리해 처리하는 통찰력이 훌륭합니다
- 시간 복잡도 O(N+H) 최적화 완벽
- 최솟값과 개수를 동시에 구하는 로직 정확

**개선할 점:**
- 변수명이 오타처럼 보임 (`unlayer`, `uplayer`)
- 함수 분리로 모듈화 필요
- 매직 넘버를 상수로 정의
- 핵심 로직에 주석 추가

**성장 궤적:**
1. **1806번**: 재귀 투 포인터 (부적절) - 62점
2. **2559번**: 슬라이딩 윈도우 (좋음) - 78점
3. **16139번**: 2차원 누적합 (완벽) - 88점
4. **3020번**: 역방향 누적합 (탁월) - 82점

**지속적으로 높은 수준을 유지하고 있습니다!** 

특히 이번 문제에서:
- ✅ 문제를 정확히 이해하고 최적의 알고리즘 선택
- ✅ 역방향 누적합이라는 고급 테크닉 활용
- ✅ 효율적인 구현

다음 단계:
- 변수명 선택에 더 신중하기 (오타 없이, 명확하게)
- 함수 분리 습관 들이기
- 핵심 로직에 간단한 주석 추가

실력이 매우 탄탄합니다! 계속 이렇게 하시면 90점대 후반도 충분히 가능합니다! 💪🚀
