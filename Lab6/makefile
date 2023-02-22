CC = g++

TARGET = hash

FLAGS = -std=c++2b -fsanitize=leak -g

$(TARGET): JacobKCST211Lab6Hash.cpp Hash.h Exception.h
	$(CC) $(FLAGS) -o $(TARGET) JacobKCST211Lab6Hash.cpp Hash.h Exception.h

clean:
	$(RM) $(TARGET)
