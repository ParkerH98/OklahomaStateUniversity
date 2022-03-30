import java.io.*;
import java.util.*;
import org.apache.hadoop.io.*;
import org.apache.hadoop.fs.*;
import org.apache.hadoop.mapreduce.*;
import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;

//hdfs dfs -rm -r /user/phague/assn1/log1; rm *.class; rm part1.jar; clear && ls && javac --release 8 *.java -cp $(hadoop classpath ) && jar cf part1.jar *.class && hadoop jar part1.jar P1Driver

public class P1Driver
{
  static Configuration conf;
  static FileSystem fs;

  public static void main(String[] args) throws Exception
  {
    initializeConfig();
    ReadDirectory();
    // ReadFile("/user/phague/assn1/2022/03/04/23/FlumeData.1646456853318");
  }

  //initializes a couple of important variables for fs operations
  public static void initializeConfig() throws Exception
  {
    P1Driver.conf = new Configuration();
    P1Driver.fs = FileSystem.get(conf);
  }
  
  // prints input file
  public static void ReadFile(String filePath)
  {
    try
    {
      // Hadoop DFS Path - Input file
      Path inFile = new Path(filePath);

      // Check if input is valid
      if (!fs.exists(inFile))
      {
        System.out.println("Input file not found");
        throw new IOException("Input file not found");
      }

      // open and read from file
      FSDataInputStream in = fs.open(inFile);
      // system.out as output stream to display
      // file content on terminal
      OutputStream out = System.out;
      byte buffer[] = new byte[256];
      try
      {
        int bytesRead = 0;
        while ((bytesRead = in.read(buffer)) > 0)
        {
          out.write(buffer, 0, bytesRead);
        }
      } catch (IOException e)
      {
        System.out.println("Error while copying file");
      } finally
      {
        // Closing streams
        in.close();
        out.close();
      }
    } catch (IOException e)
    {
      e.printStackTrace();
    }
  }

  public static void ReadDirectory() throws IOException
  {
    Path input_dir = new Path("/user/phague/assn1");
    double size = 0;

    try
    {
      if (fs.exists(input_dir))
      {
        RemoteIterator<LocatedFileStatus> file_list = fs.listFiles(input_dir, true);

        System.out.println("\nContents of the directory: " + input_dir.toString());
        System.out.println("==========================================");

        while (file_list.hasNext())
        {
          LocatedFileStatus file = file_list.next();
          size = (int) file.getLen();
          System.out.println(file.getPath() + " | " + ((size / (1024)) / 1024) + "M | " + file.getPermission() + "\n");
        }

        System.out.println("==========================================\n\n\n");
      }
    }

    catch (Exception e)
    {
      e.printStackTrace();
    }
  }

  public static void getInputFileSumamry()
  {
    Path input_dir = new Path("/user/phague/assn1");

    double size = 0;

    try
    {
      if (fs.exists(input_dir))
      {
        RemoteIterator<LocatedFileStatus> file_list = fs.listFiles(input_dir, true);

        System.out.println("Input File Summary:");
        System.out.println("==========================================");

        while (file_list.hasNext())
        {
          LocatedFileStatus file = file_list.next();

          if (file.getPath().toString().contains("1646456853318")
              || file.getPath().toString().contains("1646457124988"))
          {
            System.out.println("Size of file: " + file.getPath().toString());
            size += (int) file.getLen();
          }
        }

        System.out.println("Bytes: " + size);
        System.out.println("KB: " + (size / (1024)));
        System.out.println("MB: " + ((size / (1024)) / 1024));

        System.out.println("==========================================\n\n");
      }
    } catch (Exception e)
    {
      e.printStackTrace();
    }
  }
}
