// Parker Hague
// pgm6
// BreadthFirstSearch

import java.util.Iterator;
import java.util.LinkedList;
import java.util.*;
import java.io.*;


public class Breadth{
 
    private int numVertices;
	private LinkedList<Integer> adjacent[];


    // constructor for BFS
	Breadth(int v){
		numVertices = v;
		adjacent = new LinkedList[v];
		for (int i = 0; i < v; ++i) {
			adjacent[i] = new LinkedList();
		}
	}


	public void bfs(int s){
		boolean visited[] = new boolean[numVertices];

		LinkedList<Integer> list = new LinkedList<>();

		visited[s] = true;
        list.add(s);

		while (list.size() != 0) {
           
			s = list.poll();

			Iterator<Integer> it = adjacent[s].listIterator();

			while (it.hasNext()){
                int n = it.next();
      
				if (!visited[n]) {
             
					visited[n] = true;
                    list.add(n);
				}
            }
            System.out.print(s + " ");  
        }
        System.out.println();
    }
    

    public void addEdge(int v, int w){
		adjacent[v].add(w);
    }
    

    public static void main(String[] args) {
        
        Breadth test;

        try{

            String matrixData[] = null;
            int matrixSize;
            int matrix[][] = new int[8][8];
            String dataLine;

            System.out.println("Enter file name: ");
            Scanner scann = new Scanner(System.in);
            String fileName = scann.nextLine();
            System.out.println("Enter a source node");
            int source = scann.nextInt();
            //String fileName = "Matrix.txt";
            File file = new File(fileName);

            Scanner sc = new Scanner(file);
            int n = 0;

            while (sc.hasNextLine()) {
                dataLine = sc.nextLine();
                matrixData = dataLine.split(" ");

                for (int i = 0; i < matrixData.length; i++) {
                    matrix[n][i] = Integer.parseInt(matrixData[i]);
                }
                n++;
            }

            matrixSize = matrixData.length;

            test = new Breadth(matrixSize);

            System.out.println();
            System.out.println("Matrice from " + "\"" + fileName + "\"");
            System.out.println();

            // prints matrice from .txt file
            for (int i = 0; i < matrixSize; i++) {
                System.out.print((i + 1) + ": ");
                for (int j = 0; j < matrixSize; j++) {
                    System.out.print(matrix[i][j] + " ");
                }
                System.out.println();
            }

            // adds edges based on the matrice
            for (int i = 0; i < matrixSize; i++) {
                for (int j = 0; j < matrixSize; j++) {
                    if (matrix[i][j] == 1) {
                        test.addEdge(i, j);
                    }
                }
            }

            // runs the bfs from the source cmd line node
            System.out.println("\nBreadth First Search: ");
            System.out.println("Node Traversal: ");
            test.bfs(source);

        }catch(FileNotFoundException e){
            System.out.println("FILE NOT FOUND");
        }
    }
}