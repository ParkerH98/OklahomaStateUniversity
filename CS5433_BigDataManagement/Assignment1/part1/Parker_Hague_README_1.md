# Author
Parker Hague
phague@okstate.edu

# About
This code lists the files and directories in the phague directory of the HDFS. I also included a function to print a file.

# Contents
- P1Driver.java - main program driver

# Usage Instructions

Must execute this command when inside of the relevant subdirectory. For example, this will only work when inside of the part1 directory.

    hdfs dfs -rm -r /user/phague/assn1/log1; rm *.class; rm part1.jar; clear && ls && javac --release 8 *.java -cp $(hadoop classpath ) && jar cf part1.jar *.class && hadoop jar part1.jar P1Driver

This command will delete old files, compile the .java files, create a jar file, run the hadoop command, and then list the results after.