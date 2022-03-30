import java.io.*;
import org.apache.hadoop.io.*;
import org.apache.hadoop.mapreduce.*;


public class Code_3_2 extends Mapper<LongWritable, Text, Text, IntWritable>
{
    @Override
    public void map(LongWritable key, Text value, Context context) throws IOException, InterruptedException
    {
        // grabs tweets by their text
        String line = value.toString();
        String[] tweets = line.split("full_text\":\"");

        for (int i = 0; i < tweets.length; i++)
        {
            // gets location of end of tweet
            int end = tweets[i].indexOf("\"");
            String tweet;

            if (end != -1)
            {
                // captures substring tweet
                tweet = tweets[i].substring(0, end);

                // separates words in tweet
                String[] words = tweet.split(" ");
                for (String word : words)
                {
                    // finds each # in the separated words
                    if (word.contains("#"))
                    {
                        // removes unwanted characters
                        String toClean = cleanTextContent(word);
                        word = toClean;

                        // done bc sometimes a word has many hashtags
                        String[] hashTagSplit = word.split("#");

                        for (String splitHash : hashTagSplit)
                        {
                            // adds tweet if it is relevant to crypto
                            if (!splitHash.contains("0") && !splitHash.contains("@") && !splitHash.contains("http")
                                    && (tweet.contains("crypto") || tweet.contains("CRYPTO")))
                            {
                                context.write(new Text(splitHash), new IntWritable(1));
                            }
                            // adds tweet if it is relevant to OSRS
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

        // used to print the whole tweet
        // for (int i = 0; i < tweets.length; i++) {
        // context.write(new Text(tweets[i].toString()), new IntWritable(1));
        // }
    }

    // removes a bunch of unwanted characters like punctuation and emojis
    private static String cleanTextContent(String text)
    {
        // strips off all non-ASCII characters
        text = text.replaceAll("[^\\x00-\\x7F]", "");
        text = text.replaceAll(",", "");
        text = text.replaceAll("[].]", "");
        text = text.replaceAll(":", "");
        text = text.replaceAll("\\\\n", "");
        text = text.replaceAll("\\\\", "");
        text = text.replaceAll("!", "");
        return text.trim();
    }
}