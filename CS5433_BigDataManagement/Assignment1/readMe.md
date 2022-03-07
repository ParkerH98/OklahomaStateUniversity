


hdfs dfs -ls -h /user/phague/assn1

hdfs dfs -du -s -h /user/phague/assn1

hdfs dfs -rm -R /user/phague/assn1/log




hdfs dfs -rm -r /user/phague/assn1/log2; rm *.class; rm part2.jar; clear && ls && javac --release 8 *.java -cp $(hadoop classpath ) && jar cf part2.jar *.class && hadoop jar part2.jar P2Driver && hdfs dfs -cat /user/phague/assn1/log2/part-r-00000







hdfs dfs -rm -r /user/phague/assn1/log3; rm *.class; rm part3.jar; clear && ls && javac --release 8 *.java -cp $(hadoop classpath ) && jar cf part3.jar *.class && hadoop jar part3.jar P3Driver && hdfs dfs -cat /user/phague/assn1/log3/part-r-00000
