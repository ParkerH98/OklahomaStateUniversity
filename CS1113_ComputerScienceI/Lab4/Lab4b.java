package CS1113.Lab4;

// CS 1113 Lab 4b
// Parker Hague
// 60863
// 10/4/18

public class Lab4b {
    public static void main(String [] args){
        StdOut.printf("Lab %2s for %12s, Lab CRN %5s\n","4b",
                      "Parker Hague", "60863");
        if (args.length < 1) {
           StdOut.println("usage: java Lab4b mode < musicfile");
           System.exit(-1);
        }
        // mode selects the processing to apply to the music
            // chorus ... greater than 5 ms but less than 30 ms
            final double CHORUS_TIME = 0.0075; // 7.5 ms
            // echo or reverb ... 35 ms and greater
            final double ECHOA_TIME = 0.050; // 50 ms
            final double ECHOB_TIME = 0.075; // 75 ms
            double[] chorusLag = new double[(int)(StdAudio.SAMPLE_RATE*CHORUS_TIME)];
            double[] echoLagA = new double[(int)(StdAudio.SAMPLE_RATE*ECHOA_TIME)];
            double[] echoLagB = new double[(int)(StdAudio.SAMPLE_RATE*ECHOB_TIME)];

        int mode = Integer.parseInt(args[0]); 
        while (!StdIn.isEmpty()) {
            int pitch = StdIn.readInt();
            double duration = StdIn.readDouble();
            double[] a = PlayThatTuneDeluxe.note(pitch, duration);

            if (mode == 0) { // don't modify the audio
               StdAudio.play(a);
            } else if (mode == 1) { 
                StdAudio.play(Lab4a.overdrive(a,0.6));
            } else if (mode == 2) { 
                StdAudio.play(Lab4a.echo(a,chorusLag));
            } else if (mode == 3) { 
                StdAudio.play(Lab4a.echo(a,echoLagA));
            } else if (mode == 4 ) { 
                StdAudio.play(Lab4a.echo(a,echoLagB));
            } else {
                StdOut.printf("Unknown mode %d",mode);
            }
        }
        System.exit(0); // in case MS Windows needs it for StdAudio
    }
}
