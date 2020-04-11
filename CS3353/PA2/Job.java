package CS3353.PA2;

/**
 * Parker Hague
 * Completed: 03/08/2020
 * Work Time: approx 20 hours
 * 
 * 
 * Job Scheduling priority queue implemented 
 * using a min heap. 
 * 
 * 
 * This program takes in a file input of jobs
 * and processes them by them priority and arrival time.
 * Jobs are not executed until they have arrived. The
 * Job with the highest priority (-10) will be executed 
 * first and the Job with the lowest priority (10) will
 * be executed last.
 */


import java.io.*;

public class Job {

    // instance variables
    public String jobName;
    public int priority;
    public int arrivalTime;
    public int length;


    // constructor for Job object
    public Job(String jobName, int priority, int arrivalTime, int length){

        this.jobName = jobName;
        this.priority = priority;
        this.arrivalTime = arrivalTime;
        this.length = length;
    }

    // alternate constructor for an empty Job object
    public Job(){

        this.jobName = "null";
        this.arrivalTime = -11111;
    }

    // decements the current Job by 1
    public void decLength(){

        if (this.length == 0) return;
        int tLength = this.length;
        tLength--; 

        this.length = tLength;
    }


    public static void main(String[] args) {
        

        // variables to set up file input
        String inFile = args[0];
        
        File fileName = new File(inFile);
        String readInput;
        String[] commands;
        String[] dotCommands;

        // global time counter
        int timeSlice = 0;

        // Initializing Job objects
        Job tNewJob;
        Job currentJob = new Job();
        Job arrival = new Job();
   

        // schedule is the working heap that sorts
        // jobs by highest priority
        JobHeap schedule = new JobHeap();

        // arrivalTimes is a Heap that sorts jobs by the 
        // earliest job arrival
        JobHeap arrivalTimes = new JobHeap();

        try { // try needed for file input

            BufferedReader in = new BufferedReader(new FileReader(fileName)); // reads file input

            while ((readInput = in.readLine()) != null){

                commands = readInput.split("\n"); // separates each job by the new line and stores them in an array

                for (String command : commands) {

                    dotCommands = command.split(" "); // further separates the jobs into corresponding instance variables

                    // stores the strings into temporay variables
                    String tJobName = dotCommands[0];
                    int tPriority = Integer.parseInt(dotCommands[1]);
                    int tArrivalTime = Integer.parseInt(dotCommands[2]);
                    int tLength = Integer.parseInt(dotCommands[3]);

                    tNewJob = new Job(tJobName, tPriority, tArrivalTime, tLength); // creates temporary Job object
                    arrivalTimes.insertA(tNewJob); // sorts inserted Jobs by arrival time
                }
            }
            in.close();

        } catch (FileNotFoundException e) { // needed for file input
            System.out.println("FILE NOT FOUND");;
        }
          catch (IOException e){ // needed for file input
            e.printStackTrace();
        }
      

        // main simulation loop
        while (arrivalTimes.size() > 1 || schedule.size() != 0){ // gurantees all jobs get processed

            System.out.print("Time Slice #" + timeSlice);

            // handles when arrival time heap is empty 
            if (arrivalTimes.size() == 0){
                arrival = new Job("Done", 10, -11111, -11111); //allows Job to be caught later in loop
            }

            arrival = arrivalTimes.highestPriority(); // arrival is set to the Job with next closest arrival time
            
     
            // executes if a job arrived
            if (arrival.arrivalTime == timeSlice){

                if (arrival.arrivalTime != -11111){ // will happen if arrivalTime heap is empty

                    while (arrival.arrivalTime == timeSlice){ // handles Jobs with same arrival time

                        arrivalTimes.removeA(); // remove job from arrival times heap
                        schedule.insert(arrival); // inserts job into schedule heap to be processed by priority
                        System.out.println(" -" + arrival.jobName + " arrived");
                        arrival = arrivalTimes.highestPriority(); // arrival set to Job with next closet arrival 
                    }
                }
                
                // currentJob is the job with the highest priority
                // that gets its length decremented
                currentJob = schedule.highestPriority();

                // if the current job has available length
                if (currentJob.length != 0){
                    System.out.print("     -Executing " + currentJob.jobName + " " + currentJob.priority + " " + currentJob.length);
                    currentJob.decLength(); // decrements length
                }
                
                // if the current job doesn't have decrementable length
                if (currentJob.length <= 0){
                    schedule.remove(); // removes from the priority heap
                }
            }


            // executes when a new job doesn't arrive
            else{

                // executes if priority heap is not empty
                if (schedule.highestPriority() != null){

                    currentJob = schedule.highestPriority(); // sets current job to the Job with the highest priority

                    // checks for available length
                    if (currentJob.length != 0){
                        System.out.print("     -Executing " + currentJob.jobName + " " + currentJob.priority + " " + currentJob.length);
                        currentJob.decLength();
                    }

                    // removes if current job has zero length
                    if (currentJob.length <= 0){
                        schedule.remove();
                    }
                }
            }

            timeSlice++; // increments the global counter
            System.out.println();
        }

        System.out.println("Simulation Complete."); // prints when heaps have been fully processed
    }
}