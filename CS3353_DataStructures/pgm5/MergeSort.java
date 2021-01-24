
import java.io.*;
import java.util.*;

public class MergeSort {

    public void merge(int[] toSort, int leftBound, int middle, int rightBound) {


        int sizeL = middle - leftBound + 1;
        int sizeR = rightBound - middle;

        int[] firstHalf = new int[sizeL];
        int[] secondHalf = new int[sizeR];

        // adds elements to subarray
        for (int i = 0; i < sizeL; i++) {

            firstHalf[i] = toSort[leftBound + i];
        }

        // adds elements to subarray
        for (int j = 0; j < sizeR; j++) {

            secondHalf[j] = toSort[1 + middle + j];
        }

        // indices to check of subarrays
        int i = 0;
        int j = 0;
        int k = leftBound;

        while (i < sizeL && j < sizeR) {

            if (firstHalf[i] <= secondHalf[j]) {

                toSort[k] = firstHalf[i];
                i++;
            }

            else {
                toSort[k] = secondHalf[j];
                j++;
            }

            k++;
        }

        // adds elements that did not need sorting
        while (i < sizeL) {

            toSort[k] = firstHalf[i];
            i++;
            k++;
        }

        while (j < sizeR) {

            toSort[k] = secondHalf[j];
            j++;
            k++;
        }
    }

    public void sort(int[] toSort, int leftBound, int rightBound) {

        if (leftBound < rightBound) {

            // gets middle of bounds
            int middle = (leftBound + rightBound) / 2;

            sort(toSort, leftBound, middle);
            sort(toSort, middle + 1, rightBound);

            merge(toSort, leftBound, middle, rightBound);
        }
    }

    
    public void printArray(int[] print) {

        for (Integer num : print) {

            System.out.println(num);
        }
    }


    public void rangePrint(int[] array, int leftR, int rightR){

        if (leftR == 0) leftR = 1;

        for (int i = leftR - 1; i <= rightR - 1; i++){

            System.out.println(array[i]);
        }
    }

    public static void main(String[] args) throws IOException {

        // Use when debugging
        //String inFile = "Numbers.txt";
        //File fileName = new File(inFile);
        
        MergeSort test = new MergeSort();

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

            System.out.println("\nBefore: ");
            test.printArray(numbersToSort);

            test.sort(numbersToSort, 0, numbersToSort.length - 1);

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