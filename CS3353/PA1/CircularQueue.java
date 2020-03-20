import java.io.*;




/**
 * 
 * Queue is an arrray based data structure.
 * Queues are usually FIFO, First In First Out.
 * Items are inserted in the bottom and removed from the top (like waiting in line)
 * 
 */




public class CircularQueue{

    private int length;
    private int size, front, rear = 0;
    private int[] queueArray;

    public CircularQueue(int n){
        queueArray = new int[n];

        length = n;
    }

    public void enqueue(int a){

        if (length == rear){
            System.out.println("OVERFLOW");
            System.exit(0);
        }

        queueArray[rear] = a;
        size++;
        rear++;
    }


    public void dequeue(){

        int deq = 0;
        deq = queueArray[front];
        if (this.isEmpty()) System.out.println("Queue is already empty");

        queueArray[front] = 0;
       
        for (int i = 0; i < rear; i++){
            queueArray[i] = queueArray[i + 1];
        }

        size--;
        rear--;

        System.out.println("DELETED: " + deq);

    }

    // helper method
    public int size(){
        return this.size;
    }

    // helper method
    public Boolean isEmpty(){
        return (size == 0);
    }


    public void printQueue(){

        if (isEmpty()) System.out.print("EMPTY");

        else{
            for (int i = front; i < this.length; i++) {
          
                System.out.print(" " + queueArray[i] + "->");
            }
        }
        System.out.println();
    }


    public static void main(String[] args) {
        

        String inFileName = args[0]; // file pathname
        File inFile = new File(inFileName);

        String instructions;
        
        String[] commands;
      
        try {

            BufferedReader in = new BufferedReader(new FileReader(inFile));

            while ((instructions = in.readLine()) != null){

                commands = instructions.split(" ");
                int queueLength = Integer.parseInt(commands[0]);

                CircularQueue test = new CircularQueue(queueLength);


                
                for (String command : commands) {
                    try {

                        if (command == commands[0]) continue; // this ignores the '10' at the beginning of the string
                        
                        System.out.println();
                        System.out.println("Operation: " + command);
                        System.out.print("List before: ");
                        test.printQueue();
                      
                        int tempNum = Integer.parseInt(command.substring(0, 1));
                        String tempCommand = command.substring(2);

                        if (tempCommand.equals("in")) test.enqueue(tempNum);;
             
                        System.out.print("List after: ");
                        test.printQueue();
                
                    } catch (Exception e) {
                        test.dequeue();
                        System.out.print("List after: ");
                        test.printQueue();
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