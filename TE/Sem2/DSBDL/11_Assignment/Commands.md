##Terminal Commands to upload hadoop 

hadoop fs -mkdir /user1

hadoop fs -mkdir /user1/input

hadoop fs -put pathToinput.txt /user1/input

hadoop jar pathTojarfile packageName.classname /user1/input  /user1/output
