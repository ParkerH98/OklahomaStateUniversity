import java.io.*;
import java.util.*;
import org.apache.hadoop.io.*;
import org.apache.hadoop.fs.*;
import org.apache.hadoop.mapreduce.*;
import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;

//hdfs dfs -rm -r /user/phague/assn1/log2; rm *.class; rm part2.jar; clear && ls && javac --release 8 *.java -cp $(hadoop classpath ) && jar cf part2.jar *.class && hadoop jar part2.jar Code_2_1 && hdfs dfs -cat /user/phague/assn1/log2/part-r-00000

public class Code_2_1 
{
  static Configuration conf;
  static FileSystem fs;

  public static void main(String[] args) throws Exception {

    initializeConfig();

    //this is just for local use
    // getInputFileSumamry();

    Job job = new Job();
    job.setJarByClass(Code_2_1.class);
    job.setJobName("Parker Job");

    // io files for running under user phague
    // FileInputFormat.addInputPath(job, new Path("/user/phague/assn1/2022/03/04/23/FlumeData.1646456853318"));
    // FileInputFormat.addInputPath(job, new Path("/user/phague/assn1/2022/03/04/23/FlumeData.1646457124988"));
    // FileOutputFormat.setOutputPath(job, new Path("/user/phague/assn1/log2"));

    FileInputFormat.addInputPath(job, new Path(args[0]));
    FileOutputFormat.setOutputPath(job, new Path(args[1]));

    // finds and sets relevant .class files
    job.setMapperClass(Code_2_2.class);
    job.setReducerClass(Code_2_3.class);
    job.setOutputKeyClass(Text.class);
    job.setOutputValueClass(IntWritable.class);

    System.exit(job.waitForCompletion(true) ? 0 : 1);
  }

  public static void initializeConfig() throws Exception {
    try {
      Code_2_1.conf = new Configuration();
      Code_2_1.fs = FileSystem.get(conf);
    } catch (IOException e) {
    }
  }

  // prints a file summary of the inputs for this assignment
  public static void getInputFileSumamry() {
    Path input_dir = new Path("/user/phague/assn1");

    double size = 0;

    try {
      // iterates through whole directory
      if (fs.exists(input_dir)) {
        RemoteIterator<LocatedFileStatus> file_list = fs.listFiles(input_dir, true);

        System.out.println("Input File Summary:");
        System.out.println("==========================================");

        while (file_list.hasNext()) {
          LocatedFileStatus file = file_list.next();

          // finds specific files
          if (file.getPath().toString().contains("1646456853318")
              || file.getPath().toString().contains("1646457124988")) {
            // prints some relevant info
            System.out.println("Size of file: " + file.getPath().toString());
            size += (int) file.getLen();
          }
        }

        // calculates size
        System.out.println("Bytes: " + size);
        System.out.println("KB: " + (size / (1024)));
        System.out.println("MB: " + ((size / (1024)) / 1024));

        System.out.println("==========================================\n\n");
      }
    } catch (Exception e) {
      e.printStackTrace();
    }
  }

  public static void RunJob(String inFile, String outFile) throws IOException, InterruptedException, ClassNotFoundException {
    
 
  }
}
