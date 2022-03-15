import java.io.*;
import org.apache.hadoop.io.*;
import org.apache.hadoop.mapreduce.*;

public class P3Reducer extends Reducer<Text, IntWritable, Text, IntWritable>
{
    @Override
    public void reduce(Text key, Iterable<IntWritable> values, Context context) throws IOException, InterruptedException
    {
        int count = 1;
        for (IntWritable value : values)
        {
            count++;
        }

        String toWrite = "#" + key.toString() + ", crypto, " + count + ", osrs, " + 0;
        context.write(new Text(toWrite), new IntWritable(count));
    }
}