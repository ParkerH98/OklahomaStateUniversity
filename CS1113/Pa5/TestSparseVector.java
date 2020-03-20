import java.util.ArrayList;
import java.util.Random;

// CS 1113 Pa3
// Parker Hague
// 60863
// 11/18/18

public class TestSparseVector
{
    public static void main(String[] args) {
        
        int N = Integer.parseInt(args[0]); //dimension of vector
        int M = Integer.parseInt(args[1]); //number of non-zero elements

        double[] dimension = new double[N];

        Random random = new Random();
        int randomIndex;

        ArrayList<Integer> Index = new ArrayList<>(4);
        for (int i = 1; i < 5; i++ ){
            Index.add(i);
        }

        SparseVector sparseVector1 = new SparseVector(dimension);

        for (int i = 0; i < M; i++){
            randomIndex = random.nextInt(4);
            dimension[randomIndex] = Math.random();
            Index.remove(randomIndex);
        }

        StdArrayIO.print(dimension);

    }
}