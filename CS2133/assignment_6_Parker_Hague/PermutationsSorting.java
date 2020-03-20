import java.util.ArrayList;
import java.util.*;
import java.lang.*;

public class PermutationsSorting{
    
    public static void main(String[] args) {
        
        int initial = 1;
        while (true){
            ArrayList<Comparable> array = new ArrayList<Comparable>();
            for (int i = 0; i < initial; i++){
                array.add(Math.random() * 999);
            }

            ArrayList<Comparable> sorted = new ArrayList<Comparable>(npSort(array));

            printP(sorted);
        }
    }


    public static void printP(ArrayList<Comparable> temp) {
		System.out.print("[");
		for (int i = 0; i < temp.size(); i++) {
			if(i == temp.size() - 1) {
				System.out.print(temp.get(i));
				break;
			}
			System.out.print(temp.get(i) + ", ");
		}
		System.out.print("]\n");
	}



    public static ArrayList<Comparable> npSort(ArrayList<Comparable> arrayList){
        Permutations<Comparable> perm = new Permutations<Comparable>(arrayList);
        while (perm.hasNext()){

            ArrayList<Comparable> working = new ArrayList<Comparable>(perm.next());
            boolean isSorted = true;
            for (int i = 0; i < working.size() - 1; i++){
                if (working.get(i).compareTo(working.get(i + 1)) >= 0){
                    isSorted = false;
                    break;
                }
            }

            if (isSorted){
                return working;
            }
        }
        return null;
    }
}