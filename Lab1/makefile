CC = g++

TARGET = array

FLAGS = -std=c++2b -fsanitize=leak

$(TARGET): JacobKLab1.cpp Array.h Exception.h
	$(CC) $(FLAGS) -o $(TARGET) JacobKLab1.cpp Array.h Exception.h

clean:
	$(RM) $(TARGET)