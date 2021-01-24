import java.io.*;
import java.util.*;

public class BucketSort{

    // supporting node class
    public class BucketNode{

        BucketNode next;
        BucketNode prev;
        int element;

        public BucketNode(int element){
            this.element = element;
            this.next = null;
            this.prev = null;
        }

        public void setNext(BucketNode toSet){

            this.next = toSet;

            if (this.next != null) this.next.setPrev(this);
        }

        public void setPrev(BucketNode prev) {
            this.prev = prev;
        }
    }
    
    BucketNode head;
    BucketNode[] buckets;
    ArrayList<Integer> sorted;
    int bucketSize;
    int max;
    int min;

    // constructor
    public BucketSort(int bucketSize){
        this.bucketSize = bucketSize;
        buckets = new BucketNode[bucketSize];
        sorted = new ArrayList<>(bucketSize);
    }


    // main bucket sort method
    public void bucketSort(int[] toSort, int bucketSize){

        this.bucketSize = bucketSize;

        // gets min and max for makeIndex method
        setMax(toSort);
        setMin(toSort);

        // distributes unsorted array across bucketArray
        for (int i = 0; i < toSort.length; i++) {

            int bucketIndex = makeIndex(toSort[i]);
            BucketNode toAdd = new BucketNode(toSort[i]);

            // if there isn't a node already
            if (buckets[bucketIndex] == null){

                buckets[bucketIndex] = toAdd; // if head is null (0 index is null)
            } 

            else{

                // inserts into buckets and moves pointers
                toAdd.next = buckets[bucketIndex];
                buckets[bucketIndex] = toAdd;
            }
        }

        // Now, buckets are filled. The buckets need to be sorted
        for (int i = 0; i < buckets.length; i++){

            int[] tempArry = convertArray(buckets[i]);

            insertionT(tempArry);

            for (int j = 0; j < tempArry.length; j++) {

                sorted.add(tempArry[j]);
            }
        } // All elements have been added to list in sorted order
    }

    // best case: O(n) avg case: O(n^2) worst case: O(n^2)
    public void insertionT(int[] arr){

        int n = arr.length; 

        for (int i = 1; i < n; ++i) { 

            int compare = arr[i]; 
            int j = i - 1; 
  
    
            // compares and moves index if less than compare
            while (j >= 0 && arr[j] > compare) { 
                arr[j + 1] = arr[j]; 
                j = j - 1; 
            } 
            arr[j + 1] = compare; 
        } 
    }


    // find length of linked list inside bucketArray
    public int findLength(BucketNode headR){

        BucketNode current = headR; 

        int count = 0; 
        while (current != null) 
        { 
            count++; 
            current = current.next; 
        } 
        return count; 
    }


    public int[] convertArray(BucketNode headR){

        // Find the length of the 
        // given linked list 
        int len = findLength(headR);
  

        // rlength 
        int []arr = new int[len]; 
  
        int index = 0; 
        BucketNode curr = headR; 
  
        // Traverse the Linked List and add the 
        // elements to the array one by one 
        while (curr != null) { 

        arr[index++] = curr.element; 
        curr = curr.next; 
        } 

        return arr;
    }


    // returns index for even distribution into bucket array
    public int makeIndex(int toDistribute){

        int max = this.max;
        int min = this.min;
        int length = buckets.length;
        int range = ((max - min) / length) + 1;

        int upperRange;
        int lowerRange;
        int index;

        for (int i = 1; i <= buckets.length; i++) {

            // doesn't have to run completely through if min is found
            if (toDistribute == min){
                index = 0;
                return index;
            }

            // doesn't have to run completely through if max is found
            if (toDistribute == max){
                index = buckets.length - 1;
                return index;
            }

            // I had to do this because the lower bound on the first iteration will be the min
            if (i == 1){

                upperRange = i * range;
                lowerRange = min;
            }

            // iterate through ranges until range is found
            else {

                upperRange = i * range;
                lowerRange = ((i - 1) * range) + 1;
            }

            // assigns index if range conditions are met
            if (toDistribute >= lowerRange && toDistribute <= upperRange){

                index = i - 1;
                return index;
            }
        }
        return 0;
    }
    

    // prints array vertically
    public void printArray(int[] print) {

        for (int num : print) {

            System.out.println(num);
        }
    }


    // prints sorted list
    public void printArray() {

        ArrayList<Integer> toPrint = sorted;

        for (int num : toPrint) {

            System.out.println(num);
        }
    }


    // finds and sets max
    public int setMax(int[] findMax){

        int max = -99999;

        for (int i = 0; i < findMax.length; i++){

            if (findMax[i] > max) max = findMax[i];
        }
        this.max = max;
        return max;
    }


    // finds and sets min
    public int setMin(int[] findMin){

        int min = 9999999;

        for (int i = 0; i < findMin.length; i++){

            if (findMin[i] < min) min = findMin[i];
        }
        this.min = min;
        return min;
    }


    // prints bucketArray
    public void printBucket(){

        for (int i = 0; i < buckets.length; i++){

            System.out.print(i + ": ");
            BucketNode first = buckets[i];

            while(first != null){

                System.out.print(first.element + " ");
                first = first.next;
            }
            System.out.println();
        }
        System.out.println();
    }


    // prints numbers within the range leftR - rightR inclusive
    public void rangePrint(int[] array, int leftR, int rightR){

        if (leftR == 0) leftR = 1;

        for (int i = leftR - 1; i <= rightR - 1; i++){

            System.out.println(array[i]);
        }
    }


    public static void main(String[] args) {


        // Use when debugging
        //String inFile = "Numbers.txt";
        //File fileName = new File(inFile);
        

        // sets up program output format
        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter file name: ");
        File fileName = new File(scanner.nextLine());

        System.out.println("Enter left range: ");
        int lr = scanner.nextInt();

        System.out.println("Enter right range: ");
        int rr = scanner.nextInt();


        // variables to set up file input
        String readInput;
        String numberString = "";
        String[] numbers;
        int[] numbersToSort;

        try { // try needed for file input

            BufferedReader in = new BufferedReader(new FileReader(fileName)); // reads file input

            while ((readInput = in.readLine()) != null){
       
                numberString += readInput + " ";
            }

            numbers = numberString.split(" "); // converts from string to an array of strings
            numbersToSort = new int[numbers.length]; // initializes main array

            for (int i = 0; i < numbers.length; i++) { // copies elements from string array to int array

                numbersToSort[i] = Integer.parseInt(numbers[i]);  
            }

            // after setup, now sorting begins

            BucketSort test = new BucketSort(numbersToSort.length);

            System.out.println("\nBefore: ");
            test.printArray(numbersToSort);

            test.bucketSort(numbersToSort, numbersToSort.length);
            System.out.println("\nAfter: ");
            test.rangePrint(numbersToSort, lr, rr);

            in.close();

        } catch (FileNotFoundException e) { // needed for file input
            System.out.println("FILE NOT FOUND");;
        }
          catch (IOException e){ // needed for file input
            e.printStackTrace();
        }
    }
}