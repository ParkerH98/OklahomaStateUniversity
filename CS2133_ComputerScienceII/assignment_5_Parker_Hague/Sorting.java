
// O(n log n) running times are faster and more efficient than O(n^2) running times. 
// O(n^2) relies on nested loops for each element in an array, while O(n log n) 
// breaks the array into smaller, sorted pieces that are merged into the sorted list.
// Dividing the subset will always be faster than nested loops.


import java.util.Arrays;

public class Sorting{

    // initial array length
    static int n = 10;
    static final long timeout = 20000;
    static boolean bubbleIsDone = false;
    static boolean mergeIsDone = false;

    public static void main(String[] args) {
        

        double[] bubbleA; // Bubble Sort array  O(n^2)
		double[] mergeA; // Merge Sort array  O(n log n)

        while (bubbleIsDone == false && mergeIsDone ==  false){


            try {
                
                bubbleA = new double[n];
                mergeA = new double[n];

                makeArray(bubbleA);
                makeArray(mergeA);

                if (bubbleIsDone == false){

                    long before = System.currentTimeMillis();
                    bubbleSort(bubbleA);
    
                    if (bubbleIsDone == false){
                        long after = System.currentTimeMillis();
                        System.out.printf("Bubble sort:%4slength: %d%4smilliseconds: %d\n"," ", n, " ", (after - before));
                    }
                }


                if (mergeIsDone == false) {
                    long before = System.currentTimeMillis();
                    mergeSort(mergeA);
                    if (mergeIsDone == false) {
                        long after = System.currentTimeMillis();
                        System.out.printf("Merge sort:%5slength: %d%4smilliseconds: %d\n"," ", n, " ", (after - before));
                    }
                }
                
                n *= 10;
            } 
            
            catch (OutOfMemoryError e) {
                
                System.out.println("Merge sort memory limit reached at length 10^8");
				System.out.println("Program terminating.");
				System.exit(0);
            }
        }
    }


    public static void bubbleSort(double[] a){
        long before = System.currentTimeMillis();

        boolean swapped;

        for (int i = 1; i < a.length - 1; i++){

            swapped = false;

            for (int j = 0; j < a.length - i - 1; j++){


                if (a[j] > a[j + 1]){
                    
                    double temp = a[j];
                    a[j] = a[j + 1];
                    a[j + 1] = temp;

                    swapped = true;
                }
            }
            if (swapped == false) break;

            if ((System.currentTimeMillis() - before) > timeout){

                System.out.println("Bubble sort execution time exceeded twenty seconds at length " + n);
				System.out.println("Bubble sort terminating.");
                bubbleIsDone = true;
                break;
            }
        }
    }

    public static double[] mergeSort(double[] a){
		if (a.length == 1) {
			return a;
		}
		int middle = (a.length / 2);
		
		double[] leftA = Arrays.copyOfRange(a, 0, middle);	
		double[] rightA = Arrays.copyOfRange(a, middle, a.length);
		
		leftA = mergeSort(leftA);
		rightA = mergeSort(rightA);
		
		double[] sorted = new double[leftA.length + rightA.length];
		
		int i = 0; 
		int j = 0; 
		int k = 0; 
		
		while (i < leftA.length && j < rightA.length) {
			
			sorted[k] = (leftA[i] < rightA[j]) ? leftA[i] : rightA[j];
			
			if (sorted[k] == leftA[i]) {
				k++;
				i++;
			}
			else if (sorted[k] == rightA[j]) {
				j++;
				k++;
			}
        }
        
		while (i < leftA.length) {
			sorted[k] = leftA[i];
			k++;
			i++;
		}
			
		while (j < rightA.length) {
			sorted[k] = rightA[j];
			k++;
			j++;
		}
			
		return sorted;
	}


    public static double[] makeArray(double[] array) {
		for (int i = 0; i < array.length; i++) {
			array[i] = Math.random();
		}
		return array;
    }
}