import java.util.*;

public class Permutations<E> implements Iterator<List<E>> {
    Permutations<E> P;
    List<E> L = new ArrayList<>();
    List<E> temp;
    boolean next; // true, false, null
    int listSize;
    public E c;
    public int i;
    public static void main(String[] args) {
      
        // creates and adds elements to a test list
        List<String> test = new ArrayList<>();
        test.add("Parker");
        test.add("Adyson");
        test.add("Eli");

        Permutations<String> pTest = new Permutations<>(test);

        int counter = 0;
        
        while (pTest.hasNext()){
            System.out.println(pTest.next()); 
            counter = counter + 1;
        }
        System.out.println("number of permuations: " + counter);
    }

    
    public Permutations(List<E> initialList){

        listSize = initialList.size();
        
        if (initialList.isEmpty()){
            // if list size is 0 hasNext() returns false
            next = false;
        }
        else{
            next = true;

            // stores and removes the first element
            c = initialList.remove(0);

            // creates current permutation
            P = new Permutations<>(initialList); // only holding [1,2] inititally

            // stores current permutation
            if (P.hasNext() == true){
                L = new ArrayList<>(P.next());
            }

           // stores index
            i = 0; 
        }
    }

    @Override
   public boolean hasNext(){
    return next;
    }

    @Override
    public List<E> next(){

        temp = new ArrayList<>(L);
        temp.add(i, c);
        i += 1;

        if (i >= temp.size()){

            if (P.hasNext() == true){
                L = new ArrayList<>(P.next());
                i = 0;
            }
            else if (P.hasNext() == false) {
                this.next = false;
            }
        }
        return temp;
    }
}