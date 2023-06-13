import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Objects;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String str = reader.readLine();
        int count = Integer.parseInt(str);
        Deque deck = new Deque();
        while(count != 0) {
            String operation = reader.readLine();
            String[] command = operation.split(" ");
            //System.out.println(operation);
            if (operation.equals("pop_front")) {
                if (deck.isEmpty()) {
                   System.out.println("error");  
                } else {
                    System.out.println(deck.pop_front());
                }
            }
            if (operation.equals("pop_back")) {
                if (deck.isEmpty()) {
                   System.out.println("error");  
                } else {
                    System.out.println(deck.pop_back());
                }
            }
            if (operation.equals("clear")) {
                deck.clear();
                System.out.println("ok");
            }
            if (operation.equals("back")) {
                if (deck.isEmpty()) {
                   System.out.println("error");  
                } else {
                    System.out.println(deck.back());
                }
            }
            if (operation.equals("front")) {
                if (deck.isEmpty()) {
                   System.out.println("error");  
                } else {
                    System.out.println(deck.front());
                }
            }
            if (operation.equals( "size")) {
                System.out.println(deck.size());
            }
            if (operation.equals("exit")) {
                System.out.println("bye");
                break;
            } 
            if (command.length == 2){
                int num = Integer.parseInt(command[1]);
                if (command[0].equals("push_back")){
                    deck.push_back(num);
                    System.out.println("ok");
                } else {
                    deck.push_front(num);
                    System.out.println("ok");
                }
            }
            count -= 1;
        }
    }

    public static class Deque {
        private int[] array;
        private int size;
        private int front;
        private int back;
        private int capacity;

        Deque () {
            capacity = 3;
            array = new int[capacity];
            front = -1;
            back = 0;
            size = 0;
        }

        public boolean isEmpty() {
            return (size == 0);
        }
        public void resize(){
            int[] array2 = new int[capacity * 2];
            front = back + 1;
            for (int i = 0; i < capacity; i++) {
                if (front == 0) {
                    front = capacity * 2 - 1;
                } else {
                    front--;
                }
                array2[front] = array[front % capacity];
            }
            array = array2;
            capacity *= 2;
        }

        public void push_front(int x) {
            if (size == capacity) {
                resize();
            }
            if (isEmpty()){
                front = -1;
                back = 0;
                array[0] = x;
            } else if (front == 0) {
                front = capacity - 1;
                array[front] = x;
            } else {
                array[--front] = x;
            }
            size += 1;
        }
        
        public void push_back(int x) {
            if (size == capacity) {
                resize();
            }
            if (isEmpty()){
                front = -1;
                back = 0;
                array[back] = x;
            } else if (back == capacity - 1) {
                back = 0;
                array[back] = x;
            } else {
                array[++back] = x;
            }
            size += 1;
        }

        public int pop_front() {
            int answer = array[front];
            array[front] = 0;
            if (front == capacity - 1){
                front = 0;
            } else {
                front++;
            }
            size -= 1;
            return answer;
        }
        public int pop_back() {
            int answer = array[back];
            array[back] = 0;
            if (back == 0){
                back = capacity - 1;
            } else {
                back--;
            }
            size -= 1;
            return answer;
        }
        public int size() {
            return size;
        }
        public int front() {
            return array[front];
        }
        public int back() {
            return array[back];
        }
        public void clear() {
            front = -1;
            back = 0;
            size = 0;
        }
    }
}