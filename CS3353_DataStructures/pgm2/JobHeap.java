package CS3353.PA2;

import java.util.ArrayList;
import java.util.Comparator;
import java.io.*;



public class JobHeap extends Job implements Comparator{

    private ArrayList<Job> heapArray;

    public JobHeap() {
        this.heapArray = new ArrayList<>();
    }
 
    // Series of helper methods to get parents
    // and children and other data.
    public Job highestPriority() {
        Job temp = new Job();
        if (heapArray.isEmpty()) return temp;
        return heapArray.get(0);
    }

    public boolean isEmpty(){
        if (heapArray.size() == 0) return true;
        else return false;
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
        return index * 2 + 2;
    }

    public boolean hasLeft(int index) {
        return getLeftChild(index) < this.heapArray.size() - 1;
    }

    public boolean hasRight(int index) {
        return getLeftChild(index) < this.heapArray.size() - 1;
    }


    public void insert(Job element) {

        int curIndex = heapArray.size() - 1;

        heapArray.add(element);

        upheap(curIndex);
    }

    public void insertA(Job element) {

        int curIndex = heapArray.size() - 1;

        heapArray.add(element);

        upheapA(curIndex);
    }



    // Used with insertions. Item is inserted in last
    // index and is upheapArrayed until in correct position.
    // element is int being added to heap
    public void upheap(int index) {

        while (index > 0) {

            int parentIndex = getParent(index);

            if (compare(heapArray.get(index), heapArray.get(parentIndex)) >= 0) break;

            swap(index, parentIndex);
            index = parentIndex;   
        }
    }


    public void upheapA(int index) {

        while (index > 0) {

            int parentIndex = getParent(index);

            if (anotherCompare(heapArray.get(index), heapArray.get(parentIndex)) >= 0) break;

            swap(index, parentIndex);
            index = parentIndex;
        }
    }

    public Job remove() {

        if (heapArray.size() == 0){
            Job temp = new Job();
            return temp;
        }

        Job popped = heapArray.get(0);

        swap(0, heapArray.size() - 1);
        heapArray.remove(heapArray.size() - 1);
        downheap();
        return popped;
    }

    public Job removeA() {

        if (heapArray.size() == 0){
            Job temp = new Job();
            return temp;
        }

        Job popped = heapArray.get(0);

        swap(0, heapArray.size() - 1);
        heapArray.remove(heapArray.size() - 1);
        downheapA();
        return popped;
    }

    public void downheap() {
    
        int index = 0;

        while (hasLeft(index)){

            int leftIndex = getLeftChild(index);
            int smallIndex = leftIndex;

            if (hasRight(index)){
                int rightIndex = getRightChild(index);

                
                if (compare(heapArray.get(leftIndex), heapArray.get(rightIndex)) > 0){
                    smallIndex = rightIndex; // smallest of two values
                }
            }

            if (compare(heapArray.get(smallIndex), heapArray.get(index)) >= 0) break;

            swap(index, smallIndex);
            index = smallIndex;  
        }
    }

    public void downheapA() {

        int index = 0;

        while (hasLeft(index)){

            int leftIndex = getLeftChild(index);
            int smallIndex = leftIndex;

            if (hasRight(index) != false){
                int rightIndex = getRightChild(index);
                if (anotherCompare(heapArray.get(leftIndex), heapArray.get(rightIndex)) > 0){
                    smallIndex = rightIndex; // smallest of two values
                }
            }

            if (anotherCompare(heapArray.get(smallIndex), heapArray.get(index)) >= 0) break;

            swap(index, smallIndex);
            index = smallIndex;  
        }
    }

    // Swaps elements at index1 and index2.
    public void swap(int index1, int index2) {
        Job temp = heapArray.get(index1);
        heapArray.set(index1, heapArray.get(index2));
        heapArray.set(index2, temp);
    }

    public void printLinear() {

        for (Job integer : heapArray) {

            System.out.print(integer.jobName + " ");
        }

        System.out.println();
    }


    @Override
    public int compare(Object o1, Object o2) {
        
        // return -1 if o1 < o2
        // reuturn 0 if equal
        // return 1 if o1 > o2

        Job j1 = (Job) o1;
        Job j2 = (Job) o2;

        if (j1.priority < j2.priority) return -1;
        if (j1.priority == j2.priority) return 0;
        if (j1.priority > j2.priority) return 1;
        else return 0;
    }

    public int anotherCompare(Object o1, Object o2){

        // return -1 if o1 < o2
        // reuturn 0 if equal
        // return 1 if o1 > o2

        Job j1 = (Job) o1;
        Job j2 = (Job) o2;

        if (j1.arrivalTime < j2.arrivalTime) return -1;
        if (j1.arrivalTime == j2.arrivalTime) return 0;
        if (j1.arrivalTime > j2.arrivalTime) return 1;
        else return 0;

    }

    public static void main(String[] args) {

        String inFile = "JobFile.txt";
        File fileName = new File(inFile);
        String readInput;
        String[] commands;
        String[] dotCommands;
        Job tNewJob;
        JobHeap schedule = new JobHeap();
        JobHeap arrivalTimes = new JobHeap();

        try {

            BufferedReader in = new BufferedReader(new FileReader(fileName)); // reads file input

            while ((readInput = in.readLine()) != null){

                commands = readInput.split("\n"); // separates each job by the new line and stores them in an array

                for (String command : commands) {

                    dotCommands = command.split(" "); // further separates the jobs into corresponding instance variables

                    // stores the strings into temporay variables
                    String tJobName = dotCommands[0];
                    int tPriority = Integer.parseInt(dotCommands[1]);
                    int tArrivalTime = Integer.parseInt(dotCommands[2]);
                    int tLength = Integer.parseInt(dotCommands[3]);

                    tNewJob = new Job(tJobName, tPriority, tArrivalTime, tLength);

                    schedule.insert(tNewJob);
                    arrivalTimes.insertA(tNewJob);
                }
            }

            in.close();
            schedule.printLinear();

        } catch (FileNotFoundException e) {
            System.out.println("FILE NOT FOUND");;
        }
          catch (IOException e){
            e.printStackTrace();
        }
    }
}