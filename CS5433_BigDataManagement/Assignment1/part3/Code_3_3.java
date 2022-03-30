import java.util.*;
import org.apache.hadoop.io.*;
import org.apache.hadoop.mapreduce.*;


public class Code_3_3 extends Partitioner<Text, IntWritable>
{
    int count = 0;

    @Override
    public int getPartition(Text key, IntWritable value, int numReduceTasks)
    {

        // if the count hits the max, reset it back to 0
        if (count == 100)
        {
            count = 0;
        }

        // round robin returns a different index for each hashtag that appears
        int index = count;
        count++;

        return index;
    }
}