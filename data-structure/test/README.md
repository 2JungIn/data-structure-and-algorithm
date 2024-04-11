# 프로그램 실행 결과


## [pair-test](./pair-test.c)
```shell
$ ./pair-test
```
<details>
<summary>실행 결과</summary>
<pre>
*** make_pair(10, "hello world") & get_first() & get_second() ***
first: 10 second: hello world!
*****************************************************************
​
********** set_first(123) & set_second("new second") ************
first: 123 second: new second
*****************************************************************
​
************************** swap_elem() **************************
first: new second second: 123
*****************************************************************
</pre>
</details>


## [single-linked-list-test](./single-linked-list-test.c)
```shell
$ ./single-linked-list-test
```
<details>
<summary>실행 결과</summary>
<pre>
[3] [2] [1] 
[2] [1] 
[2] 
[1] [2] [3] 
[2] [3] 
[2] 
[1] [2] [3] [4] [5] 
1 is found!
32767 is not found!
at(0) = 0x4a9b4b0
at(2) = 0x4a9b5f0
at(-1) = (nil)
at(999) = (nil)
[10] [10] [10] [1] [2] [3] [4] [5] 
[10] [1] [3] [4] [5] 
front(): 10
back(): 5
[5] [4] [3] [1] [10] 
front(): 5
back(): 10
</pre>
</details>

## [double-linked-list-test](./double-linked-list-test.c)
```shell
$ ./double-linked-list-test
```
<details>
<summary>실행 결과</summary>
<pre>
[3] [2] [1] 
[2] [1] 
[2] 
[1] [2] [3] 
[2] [3] 
[2] 
[1] [2] [3] [4] [5] 
1 is found!
32767 is not found!
at(0) = 0x4a9b510
at(2) = 0x4a9b670
at(-1) = (nil)
at(999) = (nil)
[10] [20] [30] [1] [2] [3] [4] [5] 
[20] [1] [3] [4] [5] 
front(): 20
back(): 5
[5] [4] [3] [1] [20] 
front(): 5
back(): 20
</pre>
</details>

## [stack-test](./stack-test.c)
```shell
$ ./stack-test
```
<details>
<summary>실행 결과</summary>
<pre>
origin: Now i won.
reverse: .now i woN
</pre>
</details>

## [array-stack-test](./array-stack-test.c)
```shell
$ ./array-stack-test
```
<details>
<summary>실행 결과</summary>
<pre>
origin: Now i won.123456789
reverse: .now i woN
</pre>
</details>

## [queue-test](./queue-test.c)
```shell
$ echo "30 3" | ./queue-test
```
<details>
<summary>실행 결과</summary>
<pre>
<3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 4, 8, 13, 17, 22, 26, 1, 7, 14, 20, 28, 5, 16, 25, 10, 23, 11, 2, 19, 29>
</pre>
</details>


## [array-queue-test](./array-queue-test.c)
```shell
$ echo "30 3" | ./array-queue-test
```
<details>
<summary>실행 결과</summary>
<pre>
<3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 4, 8, 13, 17, 22, 26, 1, 7, 14, 20, 28, 5, 16, 25, 10, 23, 11, 2, 19, 29>
</pre>
</details>

## [deque-test](./deque-test.c)
```shell
$ ./deque-test
```
<details>
<summary>실행 결과</summary>
<pre>
3 6
2 5
1 4
</pre>
</details>

## [array-deque-test](./array-deque-test.c)
```shell
$ ./array-deque-test
```
<details>
<summary>실행 결과</summary>
<pre>
3 6
2 5
1 4
</pre>
</details>

## [vector-test](./vector-test.c)
```shell
$ ./vector-test
```
<details>
<summary>실행 결과</summary>
<pre>
[0] [1] [2] [3] [4] 
[1] [2] [3] [4] [0] 
[2] [3] [4] [0] [1] 
[3] [4] [0] [1] [2] 
[4] [0] [1] [2] [3] 
[0] [1] [2] [3] [4] 
​
[4] [0] [1] [2] [3] 
[3] [4] [0] [1] [2] 
[2] [3] [4] [0] [1] 
[1] [2] [3] [4] [0] 
[0] [1] [2] [3] [4] 
​
[0] [1] [2] [10] [3] [4] 
[0] [1] [2] [10] [3] 
[0] [1] [2] [10] 
[10] [2] [1] [0] 
[10] 
</pre>
</details>

## [heap-test](./heap-test.c)
```shell
$ ./heap-test
```
<details>
<summary>실행 결과</summary>
<pre>
18 17 13 16 8 10 12 9 15 2 7 1 5 4 11 0 6 3 14 
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 
18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0 
</pre>
</details>

## [priority-queue-test](./priority-queue-test.c)
```shell
$ ./priority-queue-test
```
<details>
<summary>실행 결과</summary>
<pre>
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 
</pre>
</details>

## [binary-tree-test](./binary-tree-test.c)
```shell
$ ./binary-tree-test
```
<details>
<summary>실행 결과</summary>
<pre>
[8] [4] [2] [1] [3] [6] [5] [7] [12] [10] [9] [11] [14] [13] [15] 
[1] [2] [3] [4] [5] [6] [7] [8] [9] [10] [11] [12] [13] [14] [15] 
[1] [3] [2] [5] [7] [6] [4] [9] [11] [10] [13] [15] [14] [12] [8] 
binary tree size: 15
[1] [2] [3] [4] [5] [6] [7] [8] [9] [10] [11] [12] [13] [14] [15] 
min: 1
max: 15
binary tree size: 15
[1] [2] [3] [4] [5] [6] [7] [8] [9] [10] [11] [12] [13] [14] [15] 
4 is found!
9999 is not found!
1 (height: 1)
binary tree size: 14
[2] [3] [4] [5] [6] [7] [8] [9] [10] [11] [12] [13] [14] [15] 
2 (height: 2)
binary tree size: 13
[3] [4] [5] [6] [7] [8] [9] [10] [11] [12] [13] [14] [15] 
3 (height: 1)
binary tree size: 12
[4] [5] [6] [7] [8] [9] [10] [11] [12] [13] [14] [15] 
4 (height: 3)
binary tree size: 11
[5] [6] [7] [8] [9] [10] [11] [12] [13] [14] [15] 
5 (height: 1)
binary tree size: 10
[6] [7] [8] [9] [10] [11] [12] [13] [14] [15] 
6 (height: 2)
binary tree size: 9
[7] [8] [9] [10] [11] [12] [13] [14] [15] 
7 (height: 1)
binary tree size: 8
[8] [9] [10] [11] [12] [13] [14] [15] 
8 (height: 4)
binary tree size: 7
[9] [10] [11] [12] [13] [14] [15] 
9 (height: 1)
binary tree size: 6
[10] [11] [12] [13] [14] [15] 
10 (height: 2)
binary tree size: 5
[11] [12] [13] [14] [15] 
11 (height: 1)
binary tree size: 4
[12] [13] [14] [15] 
12 (height: 3)
binary tree size: 3
[13] [14] [15] 
13 (height: 1)
binary tree size: 2
[14] [15] 
14 (height: 2)
binary tree size: 1
[15] 
15 (height: 1)
binary tree size: 0
</pre>
</details>

## [avl-tree-test](./avl-tree-test.c)
```shell
$ ./avl-tree-test
```
<details>
<summary>실행 결과</summary>
<pre>
[2] [1] [3] 
[1] [2] [3] 
[1] [3] [2] 
avl tree size: 3
[1] [2] [3] 
[2] [1] [3] 
[1] [2] [3] 
[1] [3] [2] 
avl tree size: 3
[1] [2] [3] 
min: 1
max: 15
[8] [4] [2] [1] [3] [6] [5] [7] [12] [10] [9] [11] [14] [13] [15] 
[1] [2] [3] [4] [5] [6] [7] [8] [9] [10] [11] [12] [13] [14] [15] 
[1] [3] [2] [5] [7] [6] [4] [9] [11] [10] [13] [15] [14] [12] [8] 
avl tree size: 15
[1] [2] [3] [4] [5] [6] [7] [8] [9] [10] [11] [12] [13] [14] [15] 
[1] [2] [3] [4] [5] [6] [7] [8] [9] [10] [11] [12] [13] [14] [15] 
4 is found!
9999 is not found!
1 (height: 1)
avl tree size: 14
[2] [3] [4] [5] [6] [7] [8] [9] [10] [11] [12] [13] [14] [15] 
2 (height: 2)
avl tree size: 13
[3] [4] [5] [6] [7] [8] [9] [10] [11] [12] [13] [14] [15] 
3 (height: 1)
avl tree size: 12
[4] [5] [6] [7] [8] [9] [10] [11] [12] [13] [14] [15] 
4 (height: 2)
avl tree size: 11
[5] [6] [7] [8] [9] [10] [11] [12] [13] [14] [15] 
5 (height: 1)
avl tree size: 10
[6] [7] [8] [9] [10] [11] [12] [13] [14] [15] 
6 (height: 2)
avl tree size: 9
[7] [8] [9] [10] [11] [12] [13] [14] [15] 
7 (height: 1)
avl tree size: 8
[8] [9] [10] [11] [12] [13] [14] [15] 
8 (height: 2)
avl tree size: 7
[9] [10] [11] [12] [13] [14] [15] 
9 (height: 1)
avl tree size: 6
[10] [11] [12] [13] [14] [15] 
10 (height: 2)
avl tree size: 5
[11] [12] [13] [14] [15] 
11 (height: 1)
avl tree size: 4
[12] [13] [14] [15] 
12 (height: 2)
avl tree size: 3
[13] [14] [15] 
13 (height: 1)
avl tree size: 2
[14] [15] 
14 (height: 2)
avl tree size: 1
[15] 
15 (height: 1)
avl tree size: 0
</pre>
</details>

## [red-black-tree-test](./red-black-tree-test.c)
```shell
$ ./red-black-tree-test
```
<details>
<summary>실행 결과</summary>
<pre>
[2] [1] [3] 
[1] [2] [3] 
[1] [3] [2] 
red black tree size: 3
[1] [2] [3] 
[2] [1] [3] 
[1] [2] [3] 
[1] [3] [2] 
red black tree size: 3
[1] [2] [3] 
min: 1
max: 15
[4] [2] [1] [3] [8] [6] [5] [7] [10] [9] [12] [11] [14] [13] [15] 
[1] [2] [3] [4] [5] [6] [7] [8] [9] [10] [11] [12] [13] [14] [15] 
[1] [3] [2] [5] [7] [6] [9] [11] [13] [15] [14] [12] [10] [8] [4] 
red black tree size: 15
[1] [2] [3] [4] [5] [6] [7] [8] [9] [10] [11] [12] [13] [14] [15] 
min: 1
max: 15
[1] [2] [3] [4] [5] [6] [7] [8] [9] [10] [11] [12] [13] [14] [15] 
4 is found!
9999 is not found!
1 (height: 1)
red black tree size: 14
[2] [3] [4] [5] [6] [7] [8] [9] [10] [11] [12] [13] [14] [15] 
2 (height: 2)
red black tree size: 13
[3] [4] [5] [6] [7] [8] [9] [10] [11] [12] [13] [14] [15] 
3 (height: 1)
red black tree size: 12
[4] [5] [6] [7] [8] [9] [10] [11] [12] [13] [14] [15] 
4 (height: 3)
red black tree size: 11
[5] [6] [7] [8] [9] [10] [11] [12] [13] [14] [15] 
5 (height: 1)
red black tree size: 10
[6] [7] [8] [9] [10] [11] [12] [13] [14] [15] 
6 (height: 2)
red black tree size: 9
[7] [8] [9] [10] [11] [12] [13] [14] [15] 
7 (height: 1)
red black tree size: 8
[8] [9] [10] [11] [12] [13] [14] [15] 
8 (height: 2)
red black tree size: 7
[9] [10] [11] [12] [13] [14] [15] 
9 (height: 1)
red black tree size: 6
[10] [11] [12] [13] [14] [15] 
10 (height: 4)
red black tree size: 5
[11] [12] [13] [14] [15] 
11 (height: 1)
red black tree size: 4
[12] [13] [14] [15] 
12 (height: 3)
red black tree size: 3
[13] [14] [15] 
13 (height: 1)
red black tree size: 2
[14] [15] 
14 (height: 2)
red black tree size: 1
[15] 
15 (height: 1)
red black tree size: 0
</pre>
</details>

## [hash-table-test](./hash-table-test.c)
```shell
$ ./hash-table-test
```
<details>
<summary>실행 결과</summary>
<pre>
hash value: 14222002
hash table size: 5
index: 1
key: userB value: hello
​
index: 2
key: userC value: hello
​
index: 3
key: userD value: hello
​
index: 4
key: userE value: hello
​
index: 5
key: userF value: hello
​
​
not found!
hash table size: 5
index: 1
key: userB value: chage!
​
index: 2
key: userC value: chage!
​
index: 3
key: userD value: chage!
​
index: 4
key: userE value: chage!
​
index: 5
key: userF value: chage!
​
</pre>
</details>

## [graph-test](./graph-test.c)
```shell
$ ./graph-test
```
<details>
<summary>실행 결과</summary>
<pre>
graph size: 7
key: 0 value: [1] [2] 
key: 1 value: [0] [3] [4] 
key: 2 value: [0] [4] 
key: 3 value: [1] [6] 
key: 4 value: [1] [2] [6] 
key: 5 value: [6] 
key: 6 value: [3] [4] [5] 
​
graph size: 7
key: 0 value: [1] [2] 
key: 1 value: [0] [3] [4] 
key: 2 value: [0] [4] 
key: 3 value: [1] [6] 
key: 4 value: [1] [2] [6] 
key: 5 value: [6] 
key: 6 value: [3] [4] [5] 
​
DFS(): [0] [1] [3] [6] [4] [2] [5] 
BFS(): [0] [1] [2] [3] [4] [6] [5] 
DFS_iter(): [0] [2] [4] [6] [5] [3] [1] 
graph size: 6
key: 1 value: [3] [4] 
key: 2 value: [4] 
key: 3 value: [1] [6] 
key: 4 value: [1] [2] [6] 
key: 5 value: [6] 
key: 6 value: [3] [4] [5] 
</pre>
</details>