import java.io.*;
import java.util.*;
import org.apache.hadoop.io.*;
import org.apache.hadoop.mapreduce.*;


public class Code_2_2 extends Mapper<LongWritable, Text, Text, IntWritable>
{
    @Override
    public void map(LongWritable key, Text value, Context context) throws IOException, InterruptedException
    {
        // collects tweets by created_at attr
        String line = value.toString();
        String[] tweets = line.split("created_at\":\"");

        ArrayList<Object> times = new ArrayList<>();

        for (int i = 0; i < tweets.length; i++)
        {
            // grabs tweet to quote mark
            int end = tweets[i].indexOf("\"");

            String subString;
            if (end != -1)
            {
                // grabs actual tweet substring
                subString = tweets[i].substring(0, end);

                // add it to the list if it doesnt already exist
                if (!times.contains(subString) && !subString.contains("{"))
                {
                    times.add(subString);
                }
            }
        }

        // write each tweet as a KV pair
        for (int i = 0; i < times.size(); i++)
        {
            context.write(new Text(times.get(i).toString()), new IntWritable(1));
        }
    }
}