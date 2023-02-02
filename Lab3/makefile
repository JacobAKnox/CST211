CC = g++

TARGET = stack

FLAGS = -std=c++2b -fsanitize=leak

$(TARGET): JacobKCST211Lab3Stack.cpp Stack.h Node.h List.h Exception.h
	$(CC) $(FLAGS) -o $(TARGET) JacobKCST211Lab3Stack.cpp Stack.h Node.h List.h Exception.h
clean:
	$(RM) $(TARGET)
