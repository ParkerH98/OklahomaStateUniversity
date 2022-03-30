import java.io.*;
import org.apache.hadoop.io.*;
import org.apache.hadoop.mapreduce.*;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;

//hdfs dfs -rm -r /user/phague/assn1/log3c; rm *.class; rm part3c.jar; clear && ls && javac --release 8 *.java -cp $(hadoop classpath ) && jar cf part3c.jar *.class && hadoop jar part3c.jar HashCountDriver && hdfs dfs -cat /user/phague/assn1/log3c/part-r-00000

public class HashCountDriver
{
  public static void main(String[] args) throws Exception
  {
    RunJob();
  }

  public static void RunJob() throws IOException, InterruptedException, ClassNotFoundException
  {
    Job job = new Job();
    job.setJarByClass(HashCountDriver.class);
    job.setJobName("Parker Job");

    FileInputFormat.addInputPath(job, new Path("/user/phague/assn1/2022/03/04/23/FlumeData.1646456853318"));
    FileInputFormat.addInputPath(job, new Path("/user/phague/assn1/2022/03/04/23/FlumeData.1646457124988"));
    FileOutputFormat.setOutputPath(job, new Path("/user/phague/assn1/log3c"));

    job.setMapperClass(HashCountMapper.class);
    job.setNumReduceTasks(35);
    job.setPartitionerClass(HashCountPartitioner.class);
    job.setReducerClass(HashCountReducer.class);
    job.setOutputKeyClass(Text.class);
    job.setOutputValueClass(IntWritable.class);

    System.exit(job.waitForCompletion(true) ? 0 : 1);
  }
}
