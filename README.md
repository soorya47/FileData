# file-movement-JNI
This class file is used to move files using c++ through java JNI.

preRequisite:
g++ compiler and JDk
commands needed:
1)to create .h file
javac -h . FileMovement.java
2)to create dll library file and link your .cpp file.
x86_64-w64-mingw32-g++ -I"%JAVA_HOME%\include" -I"%JAVA_HOME%\include\win32" -shared -o fileCopy.dll FileCopy.cpp
3)to run the class
java FileMovement

for running the class step 2 and 3 in enough

