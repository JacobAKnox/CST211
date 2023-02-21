CC = g++

TARGET = hash

FLAGS = -std=c++2b -fsanitize=leak -g

$(TARGET): JacobKCST211Lab6Hash.cpp Hash.h
	$(CC) $(FLAGS) -o $(TARGET) JacobKCST211Lab6Hash.cpp Hash.h

clean:
	$(RM) $(TARGET)
