CC = g++

TARGET = queue

FLAGS = -std=c++2b -fsanitize=leak -g

$(TARGET): JacobKCST211Lab4Queue.cpp Array.h Exception.h Queue.h
	$(CC) $(FLAGS) -o $(TARGET) JacobKCST211Lab4Queue.cpp Array.h Exception.h Queue.h
clean:
	$(RM) $(TARGET)
