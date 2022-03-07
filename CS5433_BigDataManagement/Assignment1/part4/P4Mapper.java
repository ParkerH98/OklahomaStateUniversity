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

public class P4Mapper extends Mapper<LongWritable, Text, Text, IntWritable>
{
    @Override
    public void map(LongWritable key, Text value, Context context) throws IOException, InterruptedException
    {
        String line = value.toString();
        String[] tweets = line.split("full_text\":\"");

        // ArrayList<Object> hashTags = new ArrayList<>();

        for (int i = 0; i < tweets.length; i++)
        {
            int end = tweets[i].indexOf("\"");
            String tweet;

            if (end != -1)
            {
                tweet = tweets[i].substring(0, end);

                String[] words = tweet.split(" ");
                ArrayList<String> hashTags = new ArrayList<>();

                for (String word : words)
                {

                    if (word.contains("#"))
                    {
                        String toClean = cleanTextContent(word);

                        word = toClean;

                        if (!hashTags.contains(word) && !word.contains("http") && (tweet.contains("crypto")
                                || tweet.contains("CRYPTO") || tweet.contains("osrs") || tweet.contains("OSRS")))
                        {
                            hashTags.add(word);
                        }
                    }
                }

                // if (tweet.contains(" ")) {
                // end = tweets[i].indexOf(" ");
                // tweet = tweets[i].tweet(0, end);
                // }

                for (int j = 0; j < hashTags.size(); j++)
                {
                    context.write(new Text(hashTags.get(j).toString()), new IntWritable(1));
                }

                // if (!hashTags.contains(tweet) && !tweet.contains("{") &&
                // !tweet.contains("http") && (tweet.contains("crypto") ||
                // tweet.contains("OSRS"))) {
                // hashTags.add(tweet);
                // }
            }
        }

        // for (int i = 0; i < hashTags.size(); i++) {
        // context.write(new Text(hashTags.get(i).toString()), new IntWritable(1));
        // }

        // for (int i = 0; i < tweets.length; i++) {
        // context.write(new Text(tweets[i].toString()), new IntWritable(1));
        // }
    }

    private static String cleanTextContent(String text)
    {
        // strips off all non-ASCII characters
        text = text.replaceAll("[^\\x00-\\x7F]", "");
        // text = text.replaceAll(",", "");
        // text = text.replaceAll("\\.", "");
        // text = text.replaceAll(":", "");
        // text = text.replaceAll("\n", "");

        // erases all the ASCII control characters
        // text = text.replaceAll("[\\p{Cntrl}&&[^\r\n\t]]", "");

        // // removes non-printable characters from Unicode
        // text = text.replaceAll("\\p{C}", "");

        // text = text.replaceAll("[^ -~]","");

        // text = text.replaceAll("[^\\p{ASCII}]", "");

        // text = text.replaceAll("\\\\x\\p{XDigit}{2}", "");

        // text = text.replaceAll("\\n","");

        // text = text.replaceAll("[^\\x20-\\x7e]", "");
        return text.trim();
    }
}