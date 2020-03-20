import java.util.ArrayList;

/**
 * MIN HEAP
 * 
 * Insertion and removal are functional
 */



public class MinHeap {

    private ArrayList<Integer> heapArray;

    public MinHeap() {
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

    public int search(int find){

       return heapArray.indexOf(find);

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

            if (heapArray.get(index) <= heapArray.get(parentIndex)) {

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



        while (hasLeft(index)){

            int leftIndex = getLeftChild(index);
            int smallIndex = leftIndex;

            if (hasRight(index)){
                int rightIndex = getRightChild(index);
                if (rightIndex < leftIndex){
                    smallIndex = rightIndex; // smallest of two values
                }
            }

            if (heapArray.get(smallIndex) < heapArray.get(index)){
                swap(index, smallIndex);
                index = smallIndex;
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

    public static void main(String[] args) {
        

        MinHeap test = new MinHeap();

        test.insert(7);
        test.insert(4);
        test.insert(11);
        test.insert(5);
        test.insert(27);
        test.insert(1);
        test.insert(15);
        test.insert(2);

        test.remove();
        test.remove();
      

        test.printLinear();
    }
}