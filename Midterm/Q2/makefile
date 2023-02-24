CC = g++

TARGET = q2

FLAGS = -std=c++2b -fsanitize=leak -g

$(TARGET): CST211MidtermBST.cpp Exception.h TreeNode.h BinarySearchTree.h
	$(CC) $(FLAGS) -o $(TARGET) CST211MidtermBST.cpp Exception.h TreeNode.h BinarySearchTree.h

clean:
	$(RM) $(TARGET)
