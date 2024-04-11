# 프로그램 실행 결과


## [binary search](./binary-search.c)
```shell
$ ./binary-search
```
<details>
<summary>실행 결과</summary>
<pre>
find value:  0  index:  0 1 2 3 4 5 6 
​
middle(3), range(0:6):  1 2 3 4 5 6 7 
middle(1), range(0:2):  1 2 3
middle(0), range(0:0):  1
​
0 is not found!
​
​
find value:  2  index:  0 1 2 3 4 5 6 
​
middle(3), range(0:6):  1 2 3 4 5 6 7 
middle(1), range(0:2):  1 2 3
​
2 is found index: 1
​​
​​
find value:  3  index:  0 1 2 3 4 5 6 
​
middle(3), range(0:6):  1 2 3 4 5 6 7 
middle(1), range(0:2):  1 2 3
middle(2), range(2:2):      3
​
3 is found index: 2
​
​
find value:  5  index:  0 1 2 3 4 5 6 
​
middle(3), range(0:6):  1 2 3 4 5 6 7 
middle(5), range(4:6):          5 6 7 
middle(4), range(4:4):          5
​
5 is found index: 4
​
​
find value:  7  index:  0 1 2 3 4 5 6 
​
middle(3), range(0:6):  1 2 3 4 5 6 7 
middle(5), range(4:6):          5 6 7 
middle(6), range(6:6):              7 
​
7 is found index: 6
​
​
find value:  9  index:  0 1 2 3 4 5 6 
​
middle(3), range(0:6):  1 2 3 4 5 6 7 
middle(5), range(4:6):          5 6 7 
middle(6), range(6:6):              7 
​
9 is not found!
​
​
find value: 10  index:  0 1 2 3 4 5 6 
​
middle(3), range(0:6):  1 2 3 4 5 6 7 
middle(5), range(4:6):          5 6 7 
middle(6), range(6:6):              7 
​
10 is not found!
</pre>
</details>

## [interpolation search](./interpolation-search.c)
```shell
$ ./interpolation-search
```
<details>
<summary>실행 결과</summary>
<pre>
          index:   0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 
          array:  10 12 13 16 18 19 20 21 22 23 24 33 35 42 47 
​
0 is not found!
10 is found index: 0
50 is not found!
20 is found index: 6
47 is found index: 14
32 is not found!
13 is found index: 2
</pre>
</details>

## [lower bound](./lower-bound.c)
```shell
$ ./lower-bound
```
<details>
<summary>실행 결과</summary>
<pre>
Index:  0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 
Value:  1  2  2  3  3  3  4  5  6  6  7  7  8  9 10 
lower_bound(3): 3
</pre>
</details>

## [upper bound](./upper-bound.c)
```shell
$ ./upper-bound
```
<details>
<summary>실행 결과</summary>
<pre>
Index:  0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 
Value:  1  2  2  3  3  3  4  5  6  6  7  7  8  9 10 
upper_bound(3): 6
</pre>
</details>

## [partition](./partition.c)
```shell
$ ./partition
```
<details>
<summary>실행 결과</summary>
<pre>
befor:  9 8 7 6 4 3 2 1 5 
​
parition -> pivot: 5
​
after:  4 3 2 1 5 8 7 6 9 
</pre>
</details>

## [randomized select](./randomized-select.c)
```shell
$ ./randomized-select
```
<details>
<summary>실행 결과</summary>
<pre>
n: 9    lo: 0    hi: 8  k: 4
​
index:    0 1 2 3 4 5 6 7 8 
array:    9 8 7 6 4 3 2 1 5 
​
n: 4    lo: 0    hi: 3  k: 4
​
index:    0 1 2 3 4 5 6 7 8 
array:    4 3 2 1
​
n: 1    lo: 3    hi: 3  k: 1
​
index:    0 1 2 3 4 5 6 7 8 
array:          4
​
4
</pre>
</details>