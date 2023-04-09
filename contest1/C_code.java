
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Objects;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String str = reader.readLine();
        int count = Integer.parseInt(str);
        int length = 200001;
        Queue queue = new Queue(length);
        while(count != 0){
            String operation = reader.readLine();
            String[] command = operation.split(" ");
            //System.out.println(operation);
            if (Objects.equals(operation,"dequeue")) {
                queue.dequeue();
            }
            if (Objects.equals(operation, "size")) {
                queue.size();
            }
            if (Objects.equals(operation, "clear")) {
                queue.clear();
            }
            if (Objects.equals(operation, "front")) {
                queue.front();
            }
            if (Objects.equals(operation, "min")) {
                queue.min();
            }
            if (command.length == 2){
                int num = Integer.parseInt(command[1]);
                queue.enqueue(num);
            }
            count--;
        }
    }
    public static class StackArr {
        private int[] s;
        private int[] m;
        private int top;

        StackArr(int number) {
            s = new int[number];
            m = new int[number];
            top = -1;
        }

        public boolean isempty() {
            return (top == -1);
        }
        public void push(int x) {
            if (isempty()) {
                m[++top] = x;
            } else {
                m[++top] = Math.min(x, m[top - 1]);
            }
            s[top] = x;
        }
        public int pop() {
            if (isempty()) {
                return 0;
            }
            return s[top--];
        }
        public int back() {
            if (isempty()) {
                return -1;
            }
            return s[top];
        }
        public void clear_stack() {
            top = -1;
        }
        public int min_stack() {
            return m[top];
        }
    }
    public static class Queue {
        StackArr s1;
        StackArr s2;
        private int size;
        private int front;
        private int back;
        Queue (int maxnumber) {
            size = 0;
            s1 = new StackArr(maxnumber);
            s2 = new StackArr(maxnumber);
        }
        public void enqueue(int x) {
            s1.push(x);
            size = size + 1;
            System.out.println("ok");
        }
        public void dequeue() {
            if (s1.isempty() && s2.isempty()){
                System.out.println("error");
            } else {
                if (s2.isempty()) {
                    while (!s1.isempty()) {
                        s2.push(s1.pop());
                    }
                }
                System.out.println(s2.pop());
                size = size -1;
            }
        }
        public int size() {
            System.out.println(size);
            return size;
        }
        public void front() {
            if (s1.isempty() && s2.isempty()){
                System.out.println("error");
            } else {
                if (s2.isempty()) {
                    while (!s1.isempty()) {
                        s2.push(s1.pop());
                    }
                }
                System.out.println(s2.back());
            }
        }
        public void clear() {
            s1.clear_stack();
            s2.clear_stack();
            System.out.println("ok");
            size = 0;
        }
        public void min() {
            if (s1.isempty() && s2.isempty()){
                System.out.println("error");
            } else {
                if (s1.isempty()){
                    System.out.println(s2.min_stack());
                }
                else if (s2.isempty()){
                    System.out.println(s1.min_stack());
                }
                else {
                    System.out.println(Math.min(s1.min_stack(), s2.min_stack()));
                }
            }
        }
    }
}