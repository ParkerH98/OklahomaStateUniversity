// CS 1113 Lab 1
// Parker Hague
// 60863
// September 4, 2018

public class Lab1 {
    public static void main (String[] args) {
        System.out.println("Lab 1 for Parker Hague, Section 60863");
        // Initializations:
        //   Declare integer iA and initialize by converting args[0] to integer
        //   Declare integer iB and initialize by converting args[1] to integer
        //   Declare double dX and initialize by converting args[2] to double
        //   Declare double dY and initialize by converting args[3] to double
        int iA = Integer.parseInt(args[0]);
        int iB = Integer.parseInt(args[1]);
        double dX = Double.parseDouble(args[2]);
        double dY = Double.parseDouble(args[3]);


        int iResult = 0; 
        double dResult = 0.0; 

        // Calculate 2 * iA % iB and assign to iResult
        iResult = 2 * iA % iB;
        System.out.println("   calc 1: iResult = " + iResult);

        // Calculate 2 * ( iA % iB ) and assign to iResult
        iResult = 2 * (iA % iB);
        System.out.println("   calc 2: iResult = " + iResult);

        // Calculate  ( iA + iB ) / dX  and assign to dResult
        dResult = (iA + iB) / dX;
        System.out.println("   calc 3: dResult = " + dResult);

        // Calculate the square root of dY and assign to iResult using an explicit cast
        iResult = (int) Math.sqrt(dY);
        System.out.println("   calc 4: iResult = " + iResult);

        // Calculate the cube of dY, round to nearest integer and assign to iResult
        // Note: use Math.pow to raise dY to the 3rd power;
        // Note: Math.round returns a long, needs an explicit cast to assign to iResult
        iResult = (int) Math.round(Math.pow(dY, 3));
        System.out.println("   calc 5: iResult = " + iResult);

        // Calculate the max of iA and iB,  assign to iResult
        iResult = Math.max(iA, iB);
        System.out.println("   calc 6: iResult = " + iResult);

        // Calculate the min of dX and dY,  assign to dResult
        dResult = Math.min(dX, dY);
        System.out.println("   calc 7: dResult = " + dResult);

        // Calculate pow(cos(dX),2) + pow(sin(dX),2), assign to dResult
        dResult = Math.pow(Math.cos(dX), 2) + Math.pow(Math.sin(dX),2);
        System.out.println("   calc 8: dResult = " + dResult);
    } // end of public static void main
} // end of public class Lab1
