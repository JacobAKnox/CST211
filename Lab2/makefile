CC = g++

TARGET = llist

FLAGS = -std=c++2b -fsanitize=leak

$(TARGET): JacobKCST211Lab2LinkedListShell.cpp Node.h List.h Exception.h
	$(CC) $(FLAGS) -o $(TARGET) JacobKCST211Lab2LinkedListShell.cpp Node.h List.h Exception.h

clean:
	$(RM) $(TARGET)