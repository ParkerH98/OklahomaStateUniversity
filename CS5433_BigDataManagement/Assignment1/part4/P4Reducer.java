import java.io.IOException;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Reducer;

public class P4Reducer extends Reducer<Text, IntWritable, Text, IntWritable>
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
                context.write(key, new IntWritable(max));
                max++;
            }
            count++;
        }
    }
}