CC = g++

TARGET = sorts

FLAGS = -std=c++2b -fsanitize=leak

$(TARGET): JacobKCST211Lab7Sorts.cpp Array.h Exception.h Sorts.h
	$(CC) $(FLAGS) -o $(TARGET) JacobKCST211Lab7Sorts.cpp Array.h Exception.h Sorts.h

clean:
	$(RM) $(TARGET)
