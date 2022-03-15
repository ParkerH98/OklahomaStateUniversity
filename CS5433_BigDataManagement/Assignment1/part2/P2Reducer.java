import java.io.*;
import org.apache.hadoop.io.*;
import org.apache.hadoop.mapreduce.*;

public class P2Reducer extends Reducer<Text, IntWritable, Text, IntWritable>
{
    int max = 1;
    @Override
    public void reduce(Text key, Iterable<IntWritable> values, Context context) throws IOException, InterruptedException
    {
        int count = 1;
        for (IntWritable value : values)
        {
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