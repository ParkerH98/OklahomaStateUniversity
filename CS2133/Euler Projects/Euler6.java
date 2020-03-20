// Euler problem 5
// verified correct answer 232792560

public class Euler6{
    public static void main(String[] args) {

        int min = 0;

        for (int i = 1; i < 2_000_000_000;i++){
            boolean multiple = true;

            for (int j = 1; j < 21; j++){

                if (i % j != 0){
                    multiple = false;
                    break;
                }
            }
            if (multiple == true){
                min = i;
                break;
            }
        }
        System.out.println(min);
    }
}