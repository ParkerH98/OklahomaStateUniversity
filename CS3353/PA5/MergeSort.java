package CS3353.PA5;
import java.util.ArrayList;

public class MergeSort{


    public int middleIndex(ArrayList a){

        int length = a.size();
        int midIndex = length / 2;
        return midIndex;
    }






    public ArrayList merge(ArrayList toSort, int leftBound, int middle, int rightBound){

        if (toSort.size() == 1) return toSort;


        middle = middleIndex(toSort);
        int sizeL = middle - leftBound + 1;
        int sizeR = rightBound - middle;



        ArrayList <Integer> firstHalf = new ArrayList<>(sizeL);
        ArrayList <Integer> secondHalf = new ArrayList<>(sizeR);

        // adds elements to subarray from 0 to m - 1
        for (int i = 0; i < middle - 1; i++){

            firstHalf.add((Integer)toSort.get(i));
        }


        // adds elements to subarray from m to n + 1
        for (int i = middle; i < toSort.size() + 1; i++){

            secondHalf.add((Integer)toSort.get(i));
        }

      
        // indices to check of subarrays
        int i = 0;
        int j = 0;
        int k = leftBound;

        while (i <= sizeL && j <= sizeR){


            if (firstHalf.get(i) <= secondHalf.get(j)){

                toSort.set(k, firstHalf.get(i));
                i++;
            }
            else{
                toSort.set(k, secondHalf.get(j));
                j++;
            }

            k++;
        }

        // adds elements that did not need sorting
        while (i < sizeL){
            toSort.set(k, firstHalf.get(i));
            i++;
            k++;
        }

        while (j < sizeR){

            toSort.set(k, secondHalf.get(j));
            j++;
            k++;

        }

        return toSort;
    }




    public ArrayList sort(ArrayList toSort, int leftBound, int rightBound){


        if (leftBound < rightBound){


            // gets middle of bounds
            int middle = (leftBound + rightBound) / 2;

            sort(toSort, leftBound, middle);
            sort(toSort, middle + 1, rightBound);

            merge(toSort, leftBound, middle, rightBound);

        }

        return toSort;
    }


    public void printArray(ArrayList<Integer> print) {

        for (Integer num : print) {

            System.out.println(num);
            
        }


    }





    public static void main(String[] args) {
        

    }



}