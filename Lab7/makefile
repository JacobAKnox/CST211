CC = g++

TARGET = sorts

FLAGS = -std=c++2b -fsanitize=leak

$(TARGET): JacobKCST211Lab7Sorts.cpp Array.h Exception.h
	$(CC) $(FLAGS) -o $(TARGET) JacobKCST211Lab7Sorts.cpp Array.h Exception.h

clean:
	$(RM) $(TARGET)
