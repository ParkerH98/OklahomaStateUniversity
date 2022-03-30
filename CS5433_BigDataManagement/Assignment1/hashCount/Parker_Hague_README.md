# Author
Parker Hague
phague@okstate.edu

# About
This code uses MapReduce to count the total number of unique hashtags.

# Contents
- HashCountDriver.java - main program driver
- HashCountMapper.java - mapper
- HashCountReducer.java - reducer
  
  
# Usage Instructions

Must execute this command when inside of the relevant subdirectory. For example, this will only work when inside of the hashCount directory.

  hdfs dfs -rm -r /user/phague/assn1/log3c; rm *.class; rm part3c.jar; clear && ls && javac --release 8 *.java -cp $(hadoop classpath ) && jar cf part3c.jar *.class && hadoop jar part3c.jar HashCountDriver && hdfs dfs -cat /user/phague/assn1/log3c/part-r-00000


This command will delete old files, compile the .java files, create a jar file, run the hadoop command, and then list the results after.