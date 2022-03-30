# Author
Parker Hague
phague@okstate.edu

# About
This code uses MapReduce to count the the occurrence of keywords based on their hashtags. It then uses a partitioner to split up the work for the reduce jobs.

# Contents
- P3Driver.java - main program driver
- P3Mapper.java - mapper
- P3Reducer.java - reducer
- P3Partitioner.java - partitioner
  
  
# Usage Instructions

Must execute this command when inside of the relevant subdirectory. For example, this will only work when inside of the part3 directory.

  javac --release 8 *.java -cp $(hadoop classpath ) && jar cf part3.jar *.class && hadoop jar part3.jar Code_3_1 <in file path> <outfile path>

