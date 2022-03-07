import java.io.*;
import java.util.*;
import org.apache.hadoop.io.*;
import org.apache.hadoop.fs.*;
import org.apache.hadoop.mapreduce.*;
import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;

//hdfs dfs -rm -r /user/phague/assn1/log2; rm *.class; rm part2.jar; clear && ls && javac --release 8 *.java -cp $(hadoop classpath ) && jar cf part2.jar *.class && hadoop jar part2.jar P2Driver && hdfs dfs -cat /user/phague/assn1/log2/part-r-00000

public class P2Driver
{
  static Configuration conf;
  static FileSystem fs;

  public static void main(String[] args) throws Exception
  {
    initializeConfig();
    getInputFileSumamry();
    RunJob();
  }

  public static void initializeConfig() throws Exception
  {
    try
    {
      P2Driver.conf = new Configuration();
      P2Driver.fs = FileSystem.get(conf);
    } catch (IOException e)
    {
    }
  }


  public static void getInputFileSumamry()
  {
    Path input_dir = new Path("/user/phague/assn1");

    double size = 0;

    try
    {
      if (fs.exists(input_dir))
      {
        RemoteIterator<LocatedFileStatus> file_list = fs.listFiles(input_dir, true);

        System.out.println("Input File Summary:");
        System.out.println("==========================================");

        while (file_list.hasNext())
        {
          LocatedFileStatus file = file_list.next();

          if (file.getPath().toString().contains("1646456853318")
              || file.getPath().toString().contains("1646457124988"))
          {
            System.out.println("Size of file: " + file.getPath().toString());
            size += (int) file.getLen();
          }
        }

        System.out.println("Bytes: " + size);
        System.out.println("KB: " + (size / (1024)));
        System.out.println("MB: " + ((size / (1024)) / 1024));

        System.out.println("==========================================\n\n");
      }
    } catch (Exception e)
    {
      e.printStackTrace();
    }
  }


  public static void RunJob() throws IOException, InterruptedException, ClassNotFoundException
  {
    Job job = new Job();
    job.setJarByClass(P2Driver.class);
    job.setJobName("Parker Job");

    FileInputFormat.addInputPath(job, new Path("/user/phague/assn1/2022/03/04/23/FlumeData.1646456853318"));
    FileInputFormat.addInputPath(job, new Path("/user/phague/assn1/2022/03/04/23/FlumeData.1646457124988"));
    FileOutputFormat.setOutputPath(job, new Path("/user/phague/assn1/log2"));

    job.setMapperClass(P2Mapper.class);
    job.setReducerClass(P2Reducer.class);
    job.setOutputKeyClass(Text.class);
    job.setOutputValueClass(IntWritable.class);

    System.exit(job.waitForCompletion(true) ? 0 : 1);
  }
}
