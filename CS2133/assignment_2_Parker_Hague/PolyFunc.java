public class PolyFunc extends Function{

    public static void main(String[] args) {
        // Test function p 4x^4 + 7x^2 + 3x + 4
        // Test function q 8x^5 + 4x^4 + 9x^3 + 6x^2 + 2x + 10

        int[] numbersP =  {4, 3, 7, 0, 4};
        PolyFunc p = new PolyFunc(numbersP);

        int[] numbersQ = {10, 2, 6, 9, 4, 8};
        PolyFunc q = new PolyFunc(numbersQ);

        if (p.coefficients[2] != 7)
        System.out.println("Constructor Test: Failed");

        if (p.degree() != 4)
        System.out.println("degree(): Failed");

        System.out.println("toString(): " + p.toString());

        System.out.println(p.toString() + "\n" + q.toString() + "\n" + p.add(q));

        if (p.evaluate(2) != 102)
        System.out.println("evaluate(): Failed");
        
    }

    private int[] coefficients;

    public PolyFunc(int[] coefficients){
        this.coefficients = coefficients;
    }

    public int degree(){
        return this.coefficients.length - 1;
    }

    public String toString(){
        String term = "";
        for (int i = this.degree(); i >= 0; i--){
            if (this.coefficients[i] != 0 && i > 1){ // handles non-zero terms
                term += this.coefficients[i] + "x^" + i + " + ";
            }
            else if (this.coefficients[i] != 0 && i == 1){ // handles terms with exponent of 1
                term += this.coefficients[i] + "x + ";
            }
            else if(this.coefficients[i] != 0 && i == 0){ // handles terms without exponent
                term += this.coefficients[i] + " ";
            }
        }
        return term;
    }

    public PolyFunc add(PolyFunc a){
        if (a.coefficients.length < this.coefficients.length){

            int[] addPolyA = new int[this.coefficients.length];

            for (int i = 0; i < a.coefficients.length; i++){
                addPolyA[i] = a.coefficients[i] + this.coefficients[i];
            }

            for (int j = a.coefficients.length; j < this.coefficients.length; j++){
                addPolyA[j] = this.coefficients[j];
            }

            PolyFunc addA = new PolyFunc(addPolyA);
            return addA;
        }

        else{
            int[] addPolyThis = new int[a.coefficients.length];

            for (int i = 0; i < this.coefficients.length; i++){
             addPolyThis[i] = a.coefficients[i] + this.coefficients[i];
            }

            for (int j = this.coefficients.length; j < a.coefficients.length; j++){
            addPolyThis[j] = a.coefficients[j];
            }
            
            PolyFunc addThis = new PolyFunc(addPolyThis);
            return addThis;
        }
    }

    public double evaluate(double x){
        double value = 0;

        for(int i = this.coefficients.length - 1; i >= 0; i--){

            if (i > 0){
                value += Math.pow(x, i) * coefficients[i];
            }
            else value += this.coefficients[i];
        }
        return value;
    }
}


/**
 * This class serves to hold all the methods needed
 * to solve problems with polynomials. Since this class
 * extends function, it will also need its own evaluate 
 * method. The evaluate method in each class in called
 * upon by findRoot()
 */