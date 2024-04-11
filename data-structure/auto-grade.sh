make clean
make all
clear

echo "test/pair-test"
valgrind --leak-check=full --error-limit=no test/pair-test
echo ""

echo "test/single-linked-list-test"
valgrind --leak-check=full --error-limit=no test/single-linked-list-test
echo ""

echo "test/double-linked-list-test"
valgrind --leak-check=full --error-limit=no test/double-linked-list-test
echo ""

echo "test/stack-test"
valgrind --leak-check=full --error-limit=no test/stack-test
echo ""

echo "test/array-stack-test"
valgrind --leak-check=full --error-limit=no test/array-stack-test
echo ""

echo "test/queue-test"
echo "30 3" | valgrind --leak-check=full --error-limit=no test/queue-test
echo ""

echo "test/array-queue-test"
echo "30 3" | valgrind --leak-check=full --error-limit=no "test/array-queue-test"
echo ""

echo "test/deque-test"
valgrind --leak-check=full --error-limit=no test/deque-test
echo ""

echo "test/array-deque-test"
valgrind --leak-check=full --error-limit=no test/array-deque-test
echo ""

echo "test/vector-test"
valgrind --leak-check=full --error-limit=no test/vector-test
echo ""

echo "test/heap-test"
valgrind --leak-check=full --error-limit=no test/heap-test
echo ""

echo "test/priority-queue-test"
valgrind --leak-check=full --error-limit=no test/priority-queue-test
echo ""

echo "test/binary-tree-test"
valgrind --leak-check=full --error-limit=no test/binary-tree-test
echo ""

echo "test/avl-tree-test"
valgrind --leak-check=full --error-limit=no test/avl-tree-test
echo ""

echo "test/red-black-tree-test"
valgrind --leak-check=full --error-limit=no test/red-black-tree-test
echo ""

echo "test/hash-table-test"
valgrind --leak-check=full --error-limit=no test/hash-table-test
echo ""

echo "test/graph-test"
valgrind --leak-check=full --error-limit=no test/graph-test
echo ""