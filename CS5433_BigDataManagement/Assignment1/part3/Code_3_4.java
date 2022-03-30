import java.io.*;
import org.apache.hadoop.io.*;
import org.apache.hadoop.mapreduce.*;

public class Code_3_4 extends Reducer<Text, IntWritable, Text, IntWritable>
{
    @Override
    public void reduce(Text key, Iterable<IntWritable> values, Context context) throws IOException, InterruptedException
    {
        // counts the number of times this specific hashtag appeared
        int count = 1;
        for (IntWritable value : values)
        {
            count++;
        }

        // writes the reducer computation to the output file with the occurrence as the value
        String toWrite = "#" + key.toString() + ", crypto, " + count + ", osrs, " + 0;
        context.write(new Text(toWrite), new IntWritable(count));
    }
}