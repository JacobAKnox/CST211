CC = g++

TARGET = bst

FLAGS = -std=c++2b -fsanitize=leak -g

$(TARGET): JacobKCST211Lab6BST.cpp Node.h BST.h Exception.h
	$(CC) $(FLAGS) -o $(TARGET) JacobKCST211Lab6BST.cpp Node.h BST.h Exception.h

clean:
	$(RM) $(TARGET)
