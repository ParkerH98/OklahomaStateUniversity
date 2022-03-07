import java.io.IOException;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Mapper;

import java.io.FileReader;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.Map;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.*;
import org.json.*;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

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