import java.util.Scanner;
import java.util.ArrayList;
import java.util.Collections;

class SegmentTree {
    ArrayList<Integer> sum;
    int size;

    SegmentTree(ArrayList<Integer> array) {
        sum = new ArrayList<Integer>(Collections.nCopies(4 * array.size(), 0));
        buildTree(array, 0, 0, array.size());
    }

    void buildTree(ArrayList<Integer> array, int v, int left, int right) {
        if (left == right - 1) {
            sum.set(v, array.get(left));
        } else {
            int middle = (left + right) / 2;
            buildTree(array, 2 * v + 1, left, middle);
            buildTree(array, 2 * v + 2, middle, right);
            sum.set(v, sum.get(2 * v + 1) + getParitySign(middle - left) * sum.get(2 * v + 2));
        }
    }

    void update(int v, int left, int right, int index, int newValue) {
        if (left == right - 1) {
            sum.set(v, newValue);
        } else {
            int middle = (left + right) / 2;
            if (index < middle) {
                update(2 * v + 1, left, middle, index, newValue);
            } else {
                update(2 * v + 2, middle, right, index, newValue);
            }
            sum.set(v, sum.get(2 * v + 1) + getParitySign(middle - left) * sum.get(2 * v + 2));
        }
    }

    int query(int v, int treeLeft, int treeRight, int queryLeft, int queryRight) {
        if (treeLeft >= queryRight || treeRight <= queryLeft) {
            return 0;
        }
        if (queryLeft <= treeLeft && treeRight <= queryRight) {
            return sum.get(v);
        }
        int middle = (treeLeft + treeRight) / 2;
        return query(2 * v + 1, treeLeft, middle, queryLeft, queryRight) +
                getParitySign(middle - Math.max(treeLeft, queryLeft)) * query(2 * v + 2, middle, treeRight, queryLeft, queryRight);
    }

    static int getParitySign(int a) {
        if (a % 2 == 0 || a < 0) {
            return 1;
        }
        return -1;
    }
}

public class Main {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int n = input.nextInt();
        ArrayList<Integer> array = new ArrayList<Integer>();
        for (int i = 0; i < n; ++i) {
            array.add(input.nextInt());
        }
        int m = input.nextInt();
        SegmentTree stree = new SegmentTree(array);
        processRequests(m, n, stree, input);
    }

    static void processRequests(int m, int n, SegmentTree stree, Scanner input) {
        int id, index, value, left, right;
        for (int k = 0; k < m; ++k) {
            id = input.nextInt();
            if (id == 0) {
                index = input.nextInt();
                value = input.nextInt();
                stree.update(0, 0, n, index - 1, value);
            } else if (id == 1) {
                left = input.nextInt();
                right = input.nextInt();
                System.out.println(stree.query(0, 0, n, left - 1, right));
            }
        }
    }
}