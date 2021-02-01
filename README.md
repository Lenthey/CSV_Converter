# CSV_Converter
A C program switch CSV file from input to output with minimal memory usage
Sample Examples :
Example #1
Given an input file with 4 columns containing the following 3 records of data:
10,20,30,40
a,b,c,d
this is input,more input,3,last input
Calling the program as:
./cnvtr -c 4 4 3 2 1 < input_file > output_file
It says to read an input CSV file where each record has 4 columns. The output specification is to
write a CSV file where each output record has a column order of 4,3,2,1 from each input record.
The columns above are in order 1,2,3,4. For e.g.: in the case of 10,20,30,40 – 10 (column 1) is
entry 0 in the array.
The output will contain three records that look like:
40,30,20,10
d,c,b,a
last input,3,more input,this is input
You do not need to parse "<" and ">" from the command line in your program. These
are redirection operators and are parsed by the shell before the arguments even arrive in
your program.
Example #2
Calling the program, cnvtr with the same input but as: 
./cnvtr -c 4 3 < input_file > output_file
