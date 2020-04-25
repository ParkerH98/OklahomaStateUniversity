package CS3353.PA1;

import java.io.*;

/**
 * 
 * Stack is an arrray based data structure.
 * Stacks are usually FILO, First In Last Out.
 * Items are inserted and removed from the top (like a plate dispenser).
 * 
 */


public class Stack{

    private int max; // max number of entries in stack
    private int top = -1; // keeps track of the top of the and amount of entries

    int[] stackArray;

    public Stack(int n){
        stackArray = new int[n];
        max = n;
    }


    public void push(int a){
        if (top <= max - 1){

            stackArray[top + 1] = a;
            top++;
        }
        else System.out.println("Stack Overflow");
    }

    public int pop(){

        int popped = 0;
        if (top < 0) System.out.println("Stack is already empty");

        else{

            stackArray[top] = popped;
            top--;
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


    public static void main(String[] args) {
        

        String inFileName = args[0]; // file pathname
        File inFile = new File(inFileName);

        String instructions;
        
        //String[] commands = String[];
        String[] commands;
      
        try {

            BufferedReader in = new BufferedReader(new FileReader(inFile));

            while ((instructions = in.readLine()) != null){

                commands = instructions.split(" ");
                int stackLength = Integer.parseInt(commands[0]);

                Stack test = new Stack(stackLength);

                
                for (String command : commands) {

                    if (command == commands[0]) continue; // this ignores the '10' at the beginning of the string
                    else{

                        System.out.println();
                        System.out.println("Operation: " + command);
                        System.out.println();

                        System.out.println("List before: ");
                        test.printStack();
                        System.out.println();

                
                    try {
                        int temp = Integer.parseInt(command.substring(0, 1));
                        test.push(temp);

                    } catch (NumberFormatException e) {
                        test.pop();
                    }

                        System.out.println("List after: ");
                        test.printStack();
                        System.out.println();
                    }
                }
            }
        } catch (FileNotFoundException e) {
            
            System.out.println("FILE NOT FOUND");
        }
        catch (Exception e){
            e.printStackTrace();
        }
    }
}