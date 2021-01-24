
// Euler problem 30
// verified correct answer

public class Euler17{




    public static void main(String[] args){

        long start = System.currentTimeMillis();

        int answer;
        answer = 0;
    
        for(int i = 2; i < 10000000; i++) answer += fifthPow(i);

        System.out.println(answer);

        long finish = System.currentTimeMillis();
      
        System.out.println("Time taken: " + (finish - start) + " milliseconds");
    }



  public static int fifthPow(int number){
    int tempNum = number;
    int temp = 0;
    int sum = 0;

    while (tempNum > 0){
      temp = tempNum % 10;
      tempNum /= 10;

      sum += Math.pow(temp, 5);

      if(sum > number) break;
    }

    if (sum == number) return sum;
    else return 0;
  }
}