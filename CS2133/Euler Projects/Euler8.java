
// euler problem 4
// verified correct answer 906609


public class Euler8{
    public static void main(String[] args) {

        int multiple = 1;
        int palindrome = 1;
        int maxPalindrome = 0;

        for (int i = 100; i < 1000 ; i++){
            for (int j = 100; j < 1000; j++){
                multiple = i * j;
                String multipleString = Integer.toString(multiple);

                if (isPalindrome(multipleString)){
                    palindrome = multiple;

                    if (palindrome > maxPalindrome){
                        maxPalindrome = palindrome;
                    }
                }
            }
        }
        System.out.println("Max Palindrome: " + maxPalindrome);
    }

    public static boolean isPalindrome(String s){
        String palindrome = "";

        for (int i = s.length(); i > 0; i--){
            palindrome += s.charAt(i-1);
        }

        if (s.equals(palindrome)){
            return true;
        }
        else return false;
    }
}