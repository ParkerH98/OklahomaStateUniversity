import java.io.*;
import java.util.*;
import org.apache.hadoop.io.*;
import org.apache.hadoop.mapreduce.*;


public class P2Mapper extends Mapper<LongWritable, Text, Text, IntWritable>
{
    @Override
    public void map(LongWritable key, Text value, Context context) throws IOException, InterruptedException
    {
        String line = value.toString();
        String[] tweets = line.split("created_at\":\"");

        ArrayList<Object> times = new ArrayList<>();

        for (int i = 0; i < tweets.length; i++)
        {
            int end = tweets[i].indexOf("\"");

            String subString;
            if (end != -1)
            {
                subString = tweets[i].substring(0, end);

                if (!times.contains(subString) && !subString.contains("{"))
                {
                    times.add(subString);
                }
            }
        }

        for (int i = 0; i < times.size(); i++)
        {
            context.write(new Text(times.get(i).toString()), new IntWritable(1));
        }
    }
}