// Parker Hague
// Euler problem 31
// verified correct answer 73682

public class Euler11{
    public static void main(String[] args) {
        int coinSum = 200;

        int[] coins = {1, 2, 5, 10, 20, 50, 100, 200};
        int[] coinCombo = new int[coinSum + 1];
        coinCombo[0] = 1;

        for (int i = 0; i < coins.length; i++){
            for (int j = coins[i]; j <= coinSum; j++){

                coinCombo[j] += coinCombo[j - coins[i]];
            }
        }

        System.out.println(coinCombo[200]);
    }
}