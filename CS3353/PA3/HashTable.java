public class HashTable{

    



    private HashNode[] table;
    private int size;
    private int tableSize;


    public HashTable(int tableSize){

        this.tableSize = tableSize;
        table = new HashNode[tableSize];
    }




    public void insert(int toInsert){

        int index = hashFunc(toInsert);

        HashNode newEntry = new HashNode(toInsert);

        if (table[index] == null){
            table[index] = newEntry;
        }
        else{
            newEntry.next = table[index];
            table[index] = newEntry;
        }
    }

    public void delete(int numData) {
		int loc = hashFunc(numData);
		HashNode start = table[loc];
		HashNode end = start;
		//System.out.println(size);


		if (search(numData)) {
			if (start.data == numData) {
				size--;
				table[loc] = start.next;
				return;
			}

			while (end.next != null && end.next.data != numData) {
				end = end.next;
				if (end.next == null) {
					//System.out.println("\n" + numData + "not found\n");
					return;
				}
				size--;
				if (end.next.next == null) {
					end.next = null;
					return;
				}
				end.next = end.next.next;
				table[loc] = start;
			}
		}
	}

    


    public int hashFunc(Object toHash){

        int hash = toHash.hashCode();
        int index = hash % table.length;
        return index;
    }


    public void printHashTable(){

        for (int i = 0; i < table.length; i++){

            System.out.print(i + ": ");
            HashNode first = table[i];

            while(first != null){

                System.out.print(first.data + " ");
                first = first.next;
            }
            System.out.println();
        }
        System.out.println();
    }

    public boolean search(int toSearch){

        int index = hashFunc(toSearch);
        HashNode find = table[index];

        while(find != null){

            if (find.data == toSearch){
                return true;
            }
            find = find.next;
        }
        return false;
    }


    public static void main(String[] args) {
        
        HashTable test = new HashTable(13);


        
        test.insert(1);
        test.insert(2);
        test.insert(15);
        test.insert(5);
        test.insert(7);
        test.insert(11);
        test.insert(12);


        test.printHashTable();


        System.out.println(test.search(2));

        test.delete(2);

        System.out.println(test.search(2));

        test.printHashTable();

        

    }
}