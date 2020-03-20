import java.io.*;

// ({}[]{}()[]))]

public class Matching{

    public class Stack{

        private int max; // max number of entries in stack
        private int top = -1; // keeps track of the top of the and amount of entries
        private int size = 0;
        char[] stackArray;

        public Stack(int n){
            stackArray = new char[n];
            max = n;
        }

        public void push(char a){
            if (top <= max - 1){

                stackArray[top + 1] = a;
                top++;
                size++;
            }
            else System.out.println("Stack Overflow");
        }

        public char pop(){

            char popped = 0;
            if (top < 0) System.out.println("Stack is already empty");

            else{

                stackArray[top] = popped;
                top--;
                size--;
            }
            return popped;
        }

        public void printStack(){

            if (top == -1) System.out.println("EMPTY");

            for (int i = top; i > -1; i--) {
            
                if (top == -1) continue;
                else System.out.println(stackArray[i]);
            }
        }

        public int size(){
            return this.size;
        }
    }

    public Boolean matchCompare(String toMatch){

        
        Stack mStack = new Stack(14);


        for (int i = 0; i < toMatch.length(); i++){


            if (toMatch.charAt(i) == '[') mStack.push('['); 

            else if (toMatch.charAt(i) == '(') mStack.push('('); 

            else if (toMatch.charAt(i) == '{') mStack.push('{');


            else if (toMatch.charAt(i) == ']') {

                if (mStack.size == 0) return false;
                else if (mStack.pop() != '[') return false;
            }

            else if (toMatch.charAt(i) == ')') {

                if (mStack.size == 0) return false;
                else if (mStack.pop() != '(') return false;
            }

            else if (toMatch.charAt(i) == '}') {

                if (mStack.size == 0) return false;
                else if (mStack.pop() != '{') return false;
            }
        }

        if (mStack.size == 0) return true;
        else return false;
    }

    public static void main(String[] args) {
        
        Matching test = new Matching();

        String inFileName = args[0]; // file pathname
        File inFile = new File(inFileName);

        String instructions;

        try {

            BufferedReader in = new BufferedReader(new FileReader(inFile));

            while ((instructions = in.readLine()) != null){

                if (test.matchCompare(instructions)) System.out.println("CORRECT");
                else System.out.println("INCORRECT");
            }
        } catch (FileNotFoundException e) {
            System.out.println("FILE NOT FOUND");
        }
        catch (Exception e){
            e.printStackTrace();
        }
    }



        

}