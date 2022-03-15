import org.apache.hadoop.io.*;
import org.apache.hadoop.mapreduce.*;

public class P3Partitioner extends Partitioner<Text, IntWritable>
{

int count = 0;

    @Override
    public int getPartition(Text key, IntWritable value, int numReduceTasks) {

        if (numReduceTasks == 0) {
            return 0;
        }

        if (count == 29)
        {
            count = 0;

        }
  
        int index = count;
        count++;

        return index;
    }
}