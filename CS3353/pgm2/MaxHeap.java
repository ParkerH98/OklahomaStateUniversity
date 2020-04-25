package CS3353.PA2;

import java.util.ArrayList;
import java.io.*;

public class MaxHeap {

    private ArrayList<Integer> heapArray;

    public MaxHeap() {
        heapArray = new ArrayList<>();
    }

    // Series of helper methods to get parents
    // and children and other data.
    public int getMax() {
        return this.heapArray.get(0);
    }

    public int size() {
        return heapArray.size();
    }

    public int getParent(int index) {
        return (index - 1) / 2;
    }

    public int getLeftChild(int index) {
        return (index * 2) + 1;
    }

    public int getRightChild(int index) {
        return (index * 2) + 2;
    }

    public boolean hasLeft(int index) {
        return getLeftChild(index) < heapArray.size();
    }

    public boolean hasRight(int index) {
        return getLeftChild(index) < heapArray.size();
    }

    public void insert(int element) {

        heapArray.add(element);

        int curIndex = heapArray.size() - 1;
        upheap(curIndex);
    }

    // Used with insertions. Item is inserted in last
    // index and is upheapArrayed until in correct position.
    // element is int being added to heap
    public void upheap(int index) {

        while (index > 0) {

            int parentIndex = getParent(index);

            if (heapArray.get(index) >= heapArray.get(parentIndex)) {

                swap(index, parentIndex);
                index = parentIndex;
            }

            else break;
        }
    }

    public int remove() {

        int popped = heapArray.get(0);

        heapArray.set(0, heapArray.get(heapArray.size() - 1));
        heapArray.remove(heapArray.size() - 1);

        downheap(0);

        return popped;
    }

    public void downheap(int index) {

        while (index <= heapArray.size() - 1) {

            if (hasLeft(index) == false)
                break;

            int leftIndex = getLeftChild(index);
            int rightIndex = getRightChild(index);

            if (heapArray.get(index) < heapArray.get(leftIndex) || heapArray.get(0) < heapArray.get(getLeftChild(index))) {

                // finds max value of children
                int willSwap1 = Math.max(heapArray.get(leftIndex), heapArray.get(rightIndex));
                int willSwap2 = heapArray.indexOf(willSwap1);

                swap(willSwap2, index);

                index = willSwap2;
            }

            else break;
        }
    }

    // Swaps elements at index1 and index2.
    public void swap(int index1, int index2) {
        int temp = heapArray.get(index1);
        heapArray.set(index1, heapArray.get(index2));
        heapArray.set(index2, temp);
    }

    public void printLinear() {

        for (Integer integer : heapArray) {

            System.out.print(integer + " ");
        }

        System.out.println();
    }

    // Preorder traversals traverse nodes root, left, right
    public void printPreOrder(int rootIndex){

        if (rootIndex > heapArray.size() - 1){
            return;
        }

        System.out.print(heapArray.get(rootIndex) + " ");

        if (hasLeft(rootIndex)){
            printPreOrder(getLeftChild(rootIndex));
        }

        if (hasRight(rootIndex)){
            printPreOrder(getRightChild(rootIndex));
        }
    }

    public void printInOrder(int rootIndex){

        if (rootIndex > heapArray.size() - 1){
            return;
        }

        if (hasLeft(rootIndex)){
            printInOrder(getLeftChild(rootIndex));
        }

        System.out.print(heapArray.get(rootIndex) + " ");
      
        if (hasRight(rootIndex)){
            printInOrder(getRightChild(rootIndex));
        }
    }

    public void printPostOrder(int rootIndex){

        if (rootIndex > heapArray.size() - 1){
            return;
        }

        if (hasLeft(rootIndex)){
            printPostOrder(getLeftChild(rootIndex));
        }
      
        if (hasRight(rootIndex)){
            printPostOrder(getRightChild(rootIndex));
        }

        System.out.print(heapArray.get(rootIndex) + " ");
    }

    
    public static void main(String[] args) {

        MaxHeap test = new MaxHeap();
        String inFile = args[0];
        File fileName = new File(inFile);
        String readInput;
        String[] commands;
        String[] dotCommands;

        try {

            BufferedReader in = new BufferedReader(new FileReader(fileName));

            while ((readInput = in.readLine()) != null){

                commands = readInput.split(" ");

                for (String command : commands) {

                    if (command == commands[0]) continue;

                    System.out.println();
                    System.out.println("Operation: " + command);
                    System.out.print("Heap before: ");

                    if (commands[0].equals("pre")){
                        test.printPreOrder(0);
                    }

                    else if (commands[0].equals("in")){
                        test.printInOrder(0);
                    }

                    else if (commands[0].equals("post")){
                        test.printPostOrder(0);
                    }                   

                    if (command.contains(".")){

                        dotCommands = command.split("\\.");

                        int willInsert = Integer.parseInt(dotCommands[0]);
                        test.insert(willInsert);
                    }

                    else test.remove();

                    System.out.println();
                    System.out.print("Heap after: ");

                    if (commands[0].equals("pre")){
                        test.printPreOrder(0);
                    }

                    else if (commands[0].equals("in")){
                        test.printInOrder(0);
                    }

                    else if (commands[0].equals("post")){
                        test.printPostOrder(0);
                    }
                    System.out.println();
                }
            }
        } catch (FileNotFoundException e) {
            System.out.println("FILE NOT FOUND");;
        }
          catch (IOException e){
            e.printStackTrace();
        }
    }
}