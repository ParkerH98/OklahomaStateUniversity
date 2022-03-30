import java.io.*;
import org.apache.hadoop.io.*;
import org.apache.hadoop.mapreduce.*;

public class Code_2_3 extends Reducer<Text, IntWritable, Text, IntWritable>
{
    int max = 1;

    // counts only the first occurrance of each hashtag so we canm only count the unique ones. the 
    // value is the count of the current tweet
    @Override
    public void reduce(Text key, Iterable<IntWritable> values, Context context) throws IOException, InterruptedException
    {
        int count = 1;
        for (IntWritable value : values)
        {
            // only writes first one
            if (count == 1)
            {
                String toWrite = "Created Date: " + key + " ----- Tweet Count: ";
                context.write(new Text(toWrite), new IntWritable(max));
                max++;
            }
            count++;
        }
    }
}