import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Objects;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String str = reader.readLine();
        int count = Integer.parseInt(str);
        int length = 200008;
        Deque deck = new Deque(length);
        while(count != 0){
            String operation = reader.readLine();
            String[] command = operation.split(" ");
            //System.out.println(operation);
            if (Objects.equals(operation,"pop_front")) {
                deck.pop_front();
            }
            if (Objects.equals(operation, "pop_back")) {
                deck.pop_back();
            }
            if (Objects.equals(operation, "clear")) {
                deck.clear();
            }
            if (Objects.equals(operation, "back")) {
                deck.back();
            }
            if (Objects.equals(operation, "front")) {
                deck.front();
            }
            if (Objects.equals(operation, "size")) {
                deck.size();
            }
            if (Objects.equals(operation, "exit")) {
                System.out.println("bye\n");
                break;
            }
            if (command.length == 2){
                int num = Integer.parseInt(command[1]);
                if (command[0].equals("push_back"))
                    deck.push_back(num);
                else
                    deck.push_front(num);
            }
            count = count - 1;
        }
    }

    public static class Deque {
        private int[] queue;
        private int size;
        private int front;
        private int back;

        Deque (int maxnumber) {
            queue = new int[maxnumber];
            front = 100000;
            back = 99999;
            size = 0;
        }

        public boolean isEmpty() {
            return (size == 0);
        }

        public void push_front(int x) {
            front = front - 1;
            queue[front] = x;
            System.out.println("ok");
            size = size + 1;
        }
        public void push_back(int x) {
            back = back + 1;
            queue[back] = x;
            System.out.println("ok");
            size = size + 1;
        }

        public void pop_front() {
            if (isEmpty()) {
                System.out.println("error");
            } else {
                System.out.println(queue[front]);
                front = front + 1;
                size = size - 1;
            }
        }
        public void pop_back() {
            if (isEmpty()) {
                System.out.println("error");
            } else {
                System.out.println(queue[back]);
                back = back - 1;
                size = size - 1;
            }
        }
        public int size() {
            System.out.println(size);
            return size;
        }
        public void front() {
            if (isEmpty()) {
                System.out.println("error");
            } else
                System.out.println(queue[front]);
        }
        public void back() {
            if (isEmpty()) {
                System.out.println("error");
            } else
                System.out.println(queue[back]);
        }
        public void clear() {
            front = 100000;
            back = 99999;
            size = 0;
            System.out.println("ok");
        }
    }
}