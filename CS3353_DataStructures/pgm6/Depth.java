// Parker Hague
// pgm6
// BreadthFirstSearch

import java.util.Iterator;
import java.util.LinkedList;
import java.util.*;
import java.io.*;

class Depth {
	private int V;
	private int discoveryTime[];
	private int finishTime[];
	private int time = 0;
    private int num = 0;
    

    private LinkedList<Integer> top = new LinkedList<>();
    private LinkedList<Integer> adjacent[];


    void addEdge(int v, int w) {
		adjacent[v].add(w);
	}
    

	Depth(int v) {
		V = v;
		discoveryTime = new int[v];
		finishTime = new int[v];

		adjacent = new LinkedList[v];

		for (int i = 0; i < v; ++i){

            adjacent[i] = new LinkedList<Integer>();
        }
	}


	private void dfs(int v, boolean visited[]) {
        int t;
		visited[v] = true;
		int temp = v + 1;

		time = time + 1;
		discoveryTime[num] = time;

		Iterator<Integer> i = adjacent[v].listIterator();
		while (i.hasNext()) {
			int n = i.next();

			if (!visited[n])
				dfs(n, visited);
			else {
				time = time + 1;
                finishTime[num] = time;
                t = finishTime[num];
                top.add(t);
                
                System.out.format("Num: %d --> %d / %d\n", temp, discoveryTime[num], finishTime[num]);
                if (num == visited.length - 1) break;
				num++;
			}
        }
	}


	void dfs(int v) {
		boolean visited[] = new boolean[V];

		dfs(v, visited);

		for (int i = 0; i < V; i++) {
			if (!visited[i]) {
				dfs(i, visited);
			}
		}
    }


    public void topologicalSort(LinkedList<Integer> n){

        int min = 99999999;
        System.out.println("Top Sort: ");
    
        for (int i = n.size() - 1; i > 0; i--){
            if (n.get(i) < min){
                min = n.get(i);

                n.set(i, min);
            } 
            System.out.print(n.get(i) + " ");
        }
    }
    

    public static void main(String[] args) {

        try{

            String matrixData[] = null;
            int matrixSize;
            int matrix[][] = new int[8][8];
            String dataLine;

            System.out.println();
            System.out.println("Enter file name: ");
            Scanner scan = new Scanner(System.in);
            String fileName = scan.nextLine();
            System.out.println("Enter a source node");
            int source = scan.nextInt();
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
        
            Depth test = new Depth(matrixSize);

            for (int i = 0; i < matrixSize; i++) {
                for (int j = 0; j < matrixSize; j++) {
                    System.out.print(matrix[i][j] + " ");
                }
                System.out.println();
            }

            for (int i = 0; i < matrixSize; i++) {
                for (int j = 0; j < matrixSize; j++) {
                    if (matrix[i][j] == 1) {
                        test.addEdge(i, j);
                    }
                }
            }

            System.out.println("\nDepth First Search: ");
            System.out.println("Format: discovery time / finished time");
            test.dfs(source);
            test.topologicalSort(test.top);

        }catch(Exception e){
            e.printStackTrace();
        }
    }
}