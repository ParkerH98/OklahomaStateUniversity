import java.io.*;
import org.apache.hadoop.io.*;
import org.apache.hadoop.mapreduce.*;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;

//hdfs dfs -rm -r /user/phague/assn1/log3; rm *.class; rm part3.jar; clear && ls && javac --release 8 *.java -cp $(hadoop classpath ) && jar cf part3.jar *.class && hadoop jar part3.jar Code_3_1 && hdfs dfs -cat /user/phague/assn1/log3/part-r-00000

public class Code_3_1
{
  public static void main(String[] args) throws Exception
  {
    Job job = new Job();
    job.setJarByClass(Code_3_1.class);
    job.setJobName("Parker Job");

    // io files
    // FileInputFormat.addInputPath(job, new Path("/user/phague/assn1/2022/03/04/23/FlumeData.1646456853318"));
    // FileInputFormat.addInputPath(job, new Path("/user/phague/assn1/2022/03/04/23/FlumeData.1646457124988"));
    // FileOutputFormat.setOutputPath(job, new Path("/user/phague/assn1/log3"));

    FileInputFormat.addInputPath(job, new Path(args[0]));
    FileOutputFormat.setOutputPath(job, new Path(args[1]));

    // looks for respective .class files 
    job.setMapperClass(Code_3_2.class);
    job.setNumReduceTasks(100);
    job.setPartitionerClass(Code_3_3.class);
    job.setReducerClass(Code_3_4.class);
    job.setOutputKeyClass(Text.class);
    job.setOutputValueClass(IntWritable.class);

    System.exit(job.waitForCompletion(true) ? 0 : 1);
  }

  public static void RunJob() throws IOException, InterruptedException, ClassNotFoundException
  {

  }
}
