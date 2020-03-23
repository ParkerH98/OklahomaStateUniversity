
/*** 
 * Parker Hague
 * 
 * CS3353
 * Programming Assignment 3
 * 
 * 
 * HashTable with chaining
 */



import java.io.*;

public class HashChain{

    // instance variables
    private HashNode[] table;
    private int size;
    private int tableSize;



    // constructor with size defined
    public HashChain(int tableSize){

        this.tableSize = tableSize;
        table = new HashNode[tableSize];
    }


    public void insert(int toInsert){


        // checks if all indices in table are used
        if (isFull() == true){

            System.out.println("TABLE IS FULL");
            System.out.println("EXECUTION TERMINATED");
            System.exit(0);
        }

        if (size >= .6 * table.length){
            //resize();
        }

        int index = hashFunc(toInsert);
        HashNode newEntry = new HashNode(toInsert);

        if (table[index] == null){
            table[index] = newEntry;
        }

        else{

            // checks if duplicate is first element
            HashNode head = table[index];
            if (head.data == toInsert){
                System.out.println("DUPLICATE KEY: " + head.data);
                return;
            }

            // checks if duplicate is subsequent elements
            while (head.next != null){

                head = head.next;
                if (head.data == toInsert){
                    System.out.println("DUPLICATE KEY: " + head.data);
                    return;
                }
            }

            // inserts into table and moves pointers
            newEntry.next = table[index];
            table[index] = newEntry;
        }
        size++;
    }


    public void delete(int toDelete){

        int index = hashFunc(toDelete);
    
        HashNode first = table[index];
        HashNode temp = first;

        if (first == null){
            return;
        }
    
        if (first.data == toDelete){ // if removal is first in index
    
            table[index] = first.next;
            size--;
            return;
        }

        if (first.next.data == toDelete){ // if removal is second in index

            first.next = null;
            size--;
            return;
        }
    
        while(temp.next.data != toDelete){
    
            temp = temp.next;
    
            if (temp.next == null){
                return;
            }
    
            size--;
    
            if (temp.next.next == null){ // means it's the last item in the index
                temp.next = null;
                return;
            }
         
            table[index] = first;
            temp.next = temp.next.next;
        }
        temp.next = null;
    }

    
    public int hashFunc(Object toHash){

        int hash = toHash.hashCode();
        int index = hash % table.length;
        return index;
    }


    public void resize(){

        int primeSize = prime();

        HashNode[] newTable = new HashNode[primeSize]; // creates new table with double the length

        for (int i = 0; i < table.length; i++){

            HashNode head = table[i]; // going to go through each element in index


            if (head == null){ // no elements in index
                continue;
            }
         

            if (head != null && head.next == null){ // if only one element in index

                int index = head.hashCode() % newTable.length;

                if (newTable[index] == null){
                    newTable[index] = head;
                }
                else{
                    head.next = newTable[index];
                    newTable[index] = head;
                }
                continue;
            }
  

            while (head != null){ // more than two elements in index

                HashNode temp = head.next;

                int index = temp.hashCode() % newTable.length;

                newTable[index] = temp;

                head.next = newTable[index];
                newTable[index] = head;
                head = temp;
            }
        }
        table = newTable;
    }


    public int prime(){

		for (int i = table.length - 1; i >= 1; i++){

            int temp = 0;
            
			for (int j = 2; j <= (int) Math.sqrt(i); j++){

				if (i % j == 0){
					temp++;
                }
                
				if (temp == 0){
					return i;
				}
			}
		}
		return 3;
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
                System.out.println("FOUND");
                return true;
            }
            find = find.next;
        }
        System.out.println("NOT FOUND");
        return false;
    }


    public boolean isEmpty(int index){
        return (table[index] == null);
    }


    public boolean isFull(){

        int count = 0;
        for (int i = 0; i < table.length; i++){
            
            if (isEmpty(i) == false){
                count++;
            }
        }

        if (count == table.length){
            return true;
        }
        return false;
    }


    public static void main(String[] args) {

        HashChain test;
        String inFileName = args[0]; // file pathname
        //String inFileName = "HashFile.txt"; // file pathname
        File inFile = new File(inFileName);

        String instructions;
        
        String[] commands;
        String[] dotCommands;
      
        try {

            BufferedReader in = new BufferedReader(new FileReader(inFile));

            while ((instructions = in.readLine()) != null){

                commands = instructions.split(" ");

                int tableSize = Integer.parseInt(commands[0]);
                test = new HashChain(tableSize);

                for (String command : commands) {
                
                
                    if (command == commands[0]) continue;

                    if (command.contains(".")){

                        dotCommands = command.split("\\.");

                        int operand = Integer.parseInt(dotCommands[0]);
                        String operator = dotCommands[1];

                        System.out.println("TABLE BEFORE: ");
                        test.printHashTable();

                        if (operator.equals("in")){

                            test.insert(operand);
                        }
                        
                        if (operator.equals("del")){

                            test.delete(operand);
                        }
                        if (operator.equals("sch")){

                            test.search(operand);
                        }

                        System.out.println("TABLE AFTER: ");
                        test.printHashTable();
                    }
                }

                test.printHashTable();
            }

        } catch (FileNotFoundException e) {
            
            System.out.println("FILE NOT FOUND");
        }
        catch (Exception e){
            e.printStackTrace();
        }
    }
}