import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;

public class Parker {
  public static void main(String[] args) throws Exception {

    Job job = new Job();
   job.setJarByClass(Parker.class);
   job.setJobName("Max temperature");
   FileInputFormat.addInputPath(job, new Path("phague/assn1"));
   FileOutputFormat.setOutputPath(job, new Path("/phague");
  //  job.setMapperClass(ParkerMapper.class);
  //  job.setReducerClass(ParkerReducer.class);
   job.setOutputKeyClass(Text.class);
   job.setOutputValueClass(IntWritable.class);
   System.exit(job.waitForCompletion(true) ? 0 : 1);
}