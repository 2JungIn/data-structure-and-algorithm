# 프로그램 실행 결과


## [bubble sort](./bubble-sort.c)
```shell
$ ./bubble-sort
```
<details>
<summary>실행 결과</summary>
<pre>
arr: 5 1 4 2 8 
​
0th: 1 4 2 5 8 
1th: 1 2 4 5 8​​
2th: 1 2 4 5 8 
3th: 1 2 4 5 8 
</pre>
</details>

## [insertion sort](./insertion-sort.c)
```shell
$ ./insertion-sort
```
<details>
<summary>실행 결과</summary>
<pre>
arr: 31 25 12 22 11 
​
0th: 25 31 12 22 11 
1th: 12 25 31 22 11 
2th: 12 22 25 31 11 
3th: 11 12 22 25 31 
</pre>
</details>

## [selection sort](./selection-sort.c)
```shell
$ ./selection-sort
```
<details>
<summary>실행 결과</summary>
<pre>
arr: 64 25 12 22 11 
​
0th: 11 25 12 22 64 
1th: 11 12 25 22 64 
2th: 11 12 22 25 64 
3th: 11 12 22 25 64 
</pre>
</details>

## [partial selection sort](./partial-selection-sort.c)
```shell
$ ./partial-selection-sort
```
<details>
<summary>실행 결과</summary>
<pre>
arr:  7 10  4  3 20 15 
​
0th:  3 10  4  7 20 15 
1th:  3  4 10  7 20 15 
2th:  3  4  7 10 20 15 
</pre>
</details>

## [shell sort](./shell-sort.c)
```shell
$ ./shell-sort
```
<details>
<summary>실행 결과</summary>
<pre>
arr: 62 83 18 53  7 17 95 86 47 69 25 28 
​
        62 83 18 53  7 17 95 86 47 69 25 28 
gap: 6
before: 62                95
after:  62                95
before:    83                86
after:     83                86
before:       18                47
after:        18                47
before:          53                69
after:           53                69
before:              7                25
after:               7                25
before:                17                28
after:                 17                28
​        62 83 18 53  7 17 95 86 47 69 25 28
gap: 3
before: 62       53       95       69
after:  53       62       95       69
before:    83        7       86       25
after:      7       83       86       25
before:       18       17       47       28 
after:        17       18       47       28 
before: 53       62       95       69
after:  53       62       95       69
before:     7       83       86       25
after:      7       83       86       25
before:       17       18       47       28 
after:        17       18       47       28 
before: 53       62       95       69
after:  53       62       69       95
before:     7       83       86       25
after:      7       25       83       86
before:       17       18       47       28 
after:        17       18       28       47 
​​        53  7 17 62 25 18 69 83 28 95 86 47 
gap: 1
before: 53  7 17 62 25 18 69 83 28 95 86 47 
after:   7 53 17 62 25 18 69 83 28 95 86 47 
before:  7 53 17 62 25 18 69 83 28 95 86 47 
after:   7 17 53 62 25 18 69 83 28 95 86 47 
before:  7 17 53 62 25 18 69 83 28 95 86 47 
after:   7 17 53 62 25 18 69 83 28 95 86 47 
before:  7 17 53 62 25 18 69 83 28 95 86 47 
after:   7 17 25 53 62 18 69 83 28 95 86 47 
before:  7 17 25 53 62 18 69 83 28 95 86 47 
after:   7 17 18 25 53 62 69 83 28 95 86 47 
before:  7 17 18 25 53 62 69 83 28 95 86 47 
after:   7 17 18 25 53 62 69 83 28 95 86 47 
before:  7 17 18 25 53 62 69 83 28 95 86 47 
after:   7 17 18 25 53 62 69 83 28 95 86 47 
before:  7 17 18 25 53 62 69 83 28 95 86 47 
after:   7 17 18 25 28 53 62 69 83 95 86 47 
before:  7 17 18 25 28 53 62 69 83 95 86 47 
after:   7 17 18 25 28 53 62 69 83 95 86 47 
before:  7 17 18 25 28 53 62 69 83 95 86 47 
after:   7 17 18 25 28 53 62 69 83 86 95 47 
before:  7 17 18 25 28 53 62 69 83 86 95 47 
after:   7 17 18 25 28 47 53 62 69 83 86 95
​ 
arr:  7 17 18 25 28 47 53 62 69 83 86 95 
</pre>
</details>

## [merge sort](./merge-sort.c)
```shell
$ ./merge-sort
```
<details>
<summary>실행 결과</summary>
<pre>
arr: 3 4 2 1 7 5 8 9 0 6 
​
left arr: 3 
right arr: 4 
arr(0:1): 3 4 
​
left arr: 3 4 
right arr: 2 
arr(0:2): 2 3 4 
​
left arr: 1 
right arr: 7 
arr(3:4): 1 7 
​
left arr: 2 3 4 
right arr: 1 7 
arr(0:4): 1 2 3 4 7 
​
left arr: 5 
right arr: 8 
arr(5:6): 5 8 
​
left arr: 5 8 
right arr: 9 
arr(5:7): 5 8 9 
​
left arr: 0 
right arr: 6 
arr(8:9): 0 6 
​
left arr: 5 8 9 
right arr: 0 6 
arr(5:9): 0 5 6 8 9 
​
left arr: 1 2 3 4 7 
right arr: 0 5 6 8 9 
arr(0:9): 0 1 2 3 4 5 6 7 8 9 
​​
arr: 0 1 2 3 4 5 6 7 8 9 
</pre>
</details>

## [quick sort](./quick-sort.c)
```shell
$ ./quick-sort
```
<details>
<summary>실행 결과</summary>
<pre>
                before:  5  3  7  6  2  1  4 
​
pivot( 6), i( 2), j( 6)  5  3  7  6  2  1  4 
pivot( 6), i( 3), j( 5)  5  3  4  6  2  1  7 
pivot( 6), i( 5), j( 4)  5  3  4  1  2  6  7 
pivot( 4), i( 0), j( 4)  5  3  4  1  2
pivot( 4), i( 2), j( 3)  2  3  4  1  5
pivot( 4), i( 3), j( 2)  2  3  1  4  5
pivot( 3), i( 1), j( 2)  2  3  1
pivot( 3), i( 2), j( 1)  2  1  3
pivot( 2), i( 0), j( 1)  2  1
pivot( 2), i( 1), j( 0)  1  2
pivot( 4), i( 3), j( 3)           4  5
pivot( 6), i( 5), j( 5)                 6  7 
​
​                 after:  1  2  3  4  5  6  7 
</pre>
</details>


## [randomized quick sort](./randomized-quick-sort.c)
```shell
$ ./randomized-quick-sort
```
<details>
<summary>실행 결과</summary>
<pre>
index:    0 1 2 3 4 5 6 7 8 9 
array:    9 8 7 6 5 4 3 2 1 0 
​
pivot:    3
index:    0 1 2 3 4 5 6 7 8 9 
array:    0 2 1
​
pivot:    2
index:    0 1 2 3 4 5 6 7 8 9 
array:    0 1
​
pivot:    0
index:    0 1 2 3 4 5 6 7 8 9 
array:            5 4 9 8 7 6 
​
pivot:    5
index:    0 1 2 3 4 5 6 7 8 9 
array:                9 8 7 6 
​
pivot:    7
index:    0 1 2 3 4 5 6 7 8 9 
array:                    9 8 
​
pivot:    8
index:    0 1 2 3 4 5 6 7 8 9 
array:    0 1 2 3 4 5 6 7 8 9 
</pre>
</details>

## [quick sort 3way](./quick-sort-3way.c)
```shell
$ ./quick-sort-3way
```
<details>
<summary>실행 결과</summary>
<pre>
index:     0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 
array:     7  7  7  6  3  3  8  8  2  6  8  5  4  2  2 
key = 7
index:     0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 
array:     6  3  3  2  2  2  6  4  5  7  7  7  8  8  8 
​
key = 6
index:     0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 
array:     3  3  2  2  2  4  5  6  6
​
key = 3
index:     0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 
array:     2  2  2  3  3  5  4
​
key = 2
index:     0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 
array:     2  2  2
​
key = 5
index:     0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 
array:               4  5
​
key = 8
index:     0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 
array:                             8  8  8
​
index:     0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 
array:     2  2  2  3  3  4  5  6  6  7  7  7  8  8  8 
</pre>
</details>


## [radix sort](./radix-sort.c)
```shell
$ ./radix-sort
```
<details>
<summary>실행 결과</summary>
<pre>
정렬하기 전의 배열:             170 045 075 090 002 024 802 066 
​
1의 자리를 기준으로 정렬:       170 090 002 802 024 090 002 066 
10의 자리를 기준으로 정렬:      002 802 002 024 066 002 002 066 
100의 자리를 기준으로 정렬:     002 002 024 066 002 002 066 066 
​
정렬한 후의 배열:               002 002 024 066 002 002 066 066
</pre>
</details>

## [bucket sort](./bucket-sort.c)
```shell
$ ./bucket-sort
```
<details>
<summary>실행 결과</summary>
<pre>
62 72 96 15 64 18 60 40 67 49 2 20 1 61 6 
​
before:
 0:   2  1  6 
 1:  15 18 
 2:  20 
 3:  
 4:  40 49 
 5:  
 6:  62 64 60 67 61 
 7:  72 
 8:  
 9:  96 
​
after:
 0:   1  2  6 
 1:  15 18 
 2:  20 
 3:  
 4:  40 49 
 5:  
 6:  60 61 62 64 67 
 7:  72 
 8:  
 9:  96 
​
1 2 6 15 18 20 40 49 60 61 62 64 67 72 96
</pre>
</details>