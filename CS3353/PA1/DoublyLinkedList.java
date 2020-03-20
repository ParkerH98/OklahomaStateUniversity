import java.io.*;



public class DoublyLinkedList {

    private Node head; // DLL keeps track of head node

    private class Node{
        // instance variables for Node object
        // Nodes will have next and previous node pointers
        int element;
        private Node next;
        private Node prev;

        // default constructor
        public Node (int element){
            this.element = element;
            this.next = null;
            this.prev = null;
        }
    }

    public void insert(int element){

        Node newNode = new Node(element); // first, allocate memory for new node
        Node checkNode = head;

        while (checkNode != null){ // will iterate until the end of list

            if (checkNode.element == element) System.out.println("DUPLICATE KEY");
            checkNode = checkNode.next; // iterates through list
        }
        

        if (head != null){
            head.prev = newNode; // sets a prev pointer for the old head
        }

        newNode.next = head; // next, assign pointers to new node
        newNode.prev = null;

        head = newNode; //change pointers from the old head to the new one
        
    }

    public void insertAfter(int elementToAdd, int prev){

        Node newNode = new Node(elementToAdd); // first, allocate memory for new node

        Node checkNode = head;

        while (checkNode != null){ // will iterate until the end of list

            if (checkNode.element == elementToAdd) System.out.println("DUPLICATE KEY");
            checkNode = checkNode.next; // iterates through list
        }

        Node previousNode = head;

        while (previousNode != null && previousNode.element != prev){ // will iterate until previous is found

            previousNode = previousNode.next; // iterates through list
        }

        newNode.next = previousNode.next; // next of new node to the next of the previous node
        previousNode.next.prev = newNode; // prev of next of previousNode to new node
        previousNode.next = newNode; // next of previous node to the new node
        newNode.prev = previousNode; // prev of new node to previous node
    }

    public void delete(int delete){

        Node toDelete = head;

        while (toDelete != null && toDelete.element != delete){
            toDelete = toDelete.next;
        }

        if (toDelete == head){
            head = head.next;
        }

        toDelete.next.prev = toDelete.prev;
        toDelete.prev.next = toDelete.next;
    }

    public void search(int find){

        Node search = head; // sets current to head for startig point of search
        
        while (search != null){ // loops to check every node

            if (search.next == null && search.element != find) System.out.println("NOT FOUND");
            if (search.element == find){

                System.out.println("FOUND");
                break;

            }
            else{
                search = search.next;
            }
        }
    }

    public void printList(){

        Node temp = head;

        if (temp == null) System.out.print("EMPTY LIST");

        while (temp != null){

            System.out.print( " " + temp.element + " -->");
            temp = temp.next;
        }
        System.out.println();
    }

    public static void main(String[] args) {

        DoublyLinkedList test = new DoublyLinkedList();

        String inFileName = args[0]; // file pathname
        File inFile = new File(inFileName);

        String instructions;
        
        //String[] commands = String[];
        String[] commands;
      
        try {

            BufferedReader in = new BufferedReader(new FileReader(inFile));

            while ((instructions = in.readLine()) != null){

                commands = instructions.split(" ");
                
                for (String command : commands) {
                    try {
                        
                        System.out.println();
                        System.out.println("Operation: " + command);
                        System.out.print("List before: ");
                        test.printList();
                      
                        int tempNum = Integer.parseInt(command.substring(0, 1));
                        String tempCommand = command.substring(2);
           
                        if (command.contains("_")){ // this handles the 'insert after' command
                            int tempNum2 = Integer.parseInt(command.substring(5));
                            test.insertAfter(tempNum, tempNum2);
                        }

                        if (tempCommand.equals("in")) test.insert(tempNum);
                        else if (tempCommand.equals("del")) test.delete(tempNum);
                        else if (tempCommand.equals("sch")) test.search(tempNum);

                        System.out.print("List after: ");
                        test.printList();
                
                    } catch (Exception e) {
                        continue;
                    }
                }
            }
        } catch (FileNotFoundException e) {
            
            System.out.println("FILE NOT FOUND");
        }
        catch (Exception e){
            e.printStackTrace();
        }
    }
}
