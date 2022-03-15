import java.io.*;
import org.apache.hadoop.io.*;
import org.apache.hadoop.mapreduce.*;

public class P3CReducer extends Reducer<Text, IntWritable, Text, IntWritable>
{
    int max = 1;
    @Override
    public void reduce(Text key, Iterable<IntWritable> values, Context context) throws IOException, InterruptedException
    {
        context.write(key, new IntWritable(max));
        max++;
    }
}