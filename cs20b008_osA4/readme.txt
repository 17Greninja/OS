Steps to run the code:
-> open terminal
-> get into the corret directory
-> Compile the code : g++ q.cpp -o out
-> Execute : ./out
-> enter time quantum
-> enter number of processes
-> enter data related to processes
-> output will appear

Example testcase1: 

3
20
p1 0 3 sys 1
p2 0 2 ip 0
p3 0 2 iep 0
p4 0 3 bp 0
p5 0 1 sp 0
p6 1 2 iep 0
p7 2 4 sys 2
p8 2 3 ip 0
p9 3 2 bp 0
p10 3 3 sp 0
p11 3 2 iep 0
p12 4 3 sys 4
p13 4 2 sys 3
p14 5 3 ip 0
p15 6 5 ip 0
p16 6 3 bp 0
p17 6 2 bp 0
p18 7 5 sp 0
p19 9 2 ip 0
p20 10 2 sp 0

Example testcase2:

5
10
201 8 3 ip 0
202 15 2 ip 0
303 11 4 iep 0
304 37 3 iep 0
505 15 5 sp 0
506 21 2 sp 0
507 30 1 sp 0
108 0 4 sys 3
109 1 2 sys 1
110 15 3 sys 2