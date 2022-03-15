import java.io.*;
import org.apache.hadoop.io.*;
import org.apache.hadoop.mapreduce.*;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;

//hdfs dfs -rm -r /user/phague/assn1/log3; rm *.class; rm part3.jar; clear && ls && javac --release 8 *.java -cp $(hadoop classpath ) && jar cf part3.jar *.class && hadoop jar part3.jar P3Driver && hdfs dfs -cat /user/phague/assn1/log3/part-r-00000


public class P3Driver
{
  public static void main(String[] args) throws Exception
  {
    RunJob();
  }

  public static void RunJob() throws IOException, InterruptedException, ClassNotFoundException
  {
    Job job = new Job();
    job.setJarByClass(P3Driver.class);
    job.setJobName("Parker Job");

    FileInputFormat.addInputPath(job, new Path("/user/phague/assn1/2022/03/04/23/FlumeData.1646456853318"));
    FileInputFormat.addInputPath(job, new Path("/user/phague/assn1/2022/03/04/23/FlumeData.1646457124988"));
    FileOutputFormat.setOutputPath(job, new Path("/user/phague/assn1/log3"));

    job.setMapperClass(P3Mapper.class);
    // job.setNumReduceTasks(29);
    // job.setPartitionerClass(P4Partitioner.class);
    job.setReducerClass(P3Reducer.class);
    job.setOutputKeyClass(Text.class);
    job.setOutputValueClass(IntWritable.class);

    System.exit(job.waitForCompletion(true) ? 0 : 1);
  }
}
