# Synthesys-Practical-Work-Ensea-in-the-Shell
TP 1 Major Computer science

For every questions, we used the VM given by ENSEA, in order to work on a Linux environnement. 
We used Geany to work on a clean IDE, not on a simple file like we started, with no colors. 
We created the folder Synthesys-Practical-Work-Ensea-in-the-shell, where we stored every file for every question, and the makefile.

On a terminal, we typed 'ls' to see all the directory, and by typing 'cd Synthesys-Practical-Work-Ensea-in-the-shell', we now are in the right folder. 

For every question, once the code seems right, we have to type 'make'. Then we have to compile the file we want by typing : 
'gcc -o enseash_Qx enseash_Qx.c' (with Qx the number of the question)

Then we need to call the file by typing its name : 'enseash_Qx'
The tiny shell appears.


Question 4: test of stop signal
![image](https://github.com/user-attachments/assets/7cb94167-d679-4617-8d71-d68ee502774f)

Here we launch the 'yes' function that write infinite 'y'. Then on another terminal, we type the line :
'ps aux | grep yes' which allows us to know the IP adress of the child. 
We can now send a signal with the command kill, here 'kill -9 1949' with the IP adress 1949. When executed, the infinite y on the other terminal is stopped, and the number of the signal is displayed, here 9.
