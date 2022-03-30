# Author
Parker Hague
phague@okstate.edu

# About
This code uses MapReduce to count the number of tweets in the two input files.

# Contents
- P2Driver.java - main program driver
- P2Mapper.java - mapper
- P2Reducer.java - reducer
  
# Usage Instructions

Must execute this command when inside of the relevant subdirectory. For example, this will only work when inside of the part2 directory.

  javac --release 8 *.java -cp $(hadoop classpath ) && jar cf part2.jar *.class && hadoop jar part2.jar Code_2_1 <in file path> <outfile path>

