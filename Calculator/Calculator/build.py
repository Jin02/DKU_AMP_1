import os

os.system("g++ -std=c++11 -I ./inc -c ./src/*.cpp")
os.system("g++ -std=c++11 -I ./inc main.cpp *.o -o OutputFile")
os.system("rm *.o")