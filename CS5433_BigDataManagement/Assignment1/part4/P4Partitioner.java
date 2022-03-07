import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Partitioner;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.IntWritable;



public class P4Partitioner extends Partitioner<Text, IntWritable>
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