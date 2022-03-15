import java.io.*;
import org.apache.hadoop.io.*;
import org.apache.hadoop.mapreduce.*;

public class P3CMapper extends Mapper<LongWritable, Text, Text, IntWritable>
{
    @Override
    public void map(LongWritable key, Text value, Context context) throws IOException, InterruptedException
    {
        String line = value.toString();
        String[] tweets = line.split("full_text\":\"");

        for (int i = 0; i < tweets.length; i++)
        {
            int end = tweets[i].indexOf("\"");
            String tweet;

            if (end != -1)
            {
                tweet = tweets[i].substring(0, end);

                String[] words = tweet.split(" ");
                for (String word : words)
                {
                    if (word.contains("#"))
                    {
                        String toClean = cleanTextContent(word);
                        word = toClean;

                        String[] hashTagSplit = word.split("#");

                        for (String splitHash : hashTagSplit)
                        {
                            if (!splitHash.contains("0") && !splitHash.contains("@") && !splitHash.contains("http")
                                    && (tweet.contains("crypto") || tweet.contains("CRYPTO")))
                            {
                                context.write(new Text(splitHash), new IntWritable(1));
                            }
                            if (!splitHash.contains("@") && !splitHash.contains("http")
                                    && (tweet.contains("osrs") || tweet.contains("OSRS")))
                            {
                                context.write(new Text(splitHash), new IntWritable(1));
                            }
                        }
                    }
                }
            }
        }
    }
    

    private static String cleanTextContent(String text)
    {
        // strips off all non-ASCII characters
        text = text.replaceAll("[^\\x00-\\x7F]", "");
        text = text.replaceAll(",", "");
        text = text.replaceAll("[].]", "");
        text = text.replaceAll(":", "");
        text = text.replaceAll("\\\\n", "");
        text = text.replaceAll("\\\\", "");
        return text.trim();
    }
}