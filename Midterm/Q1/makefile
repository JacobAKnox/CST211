CC = g++

TARGET = q1

FLAGS = -std=c++2b -fsanitize=leak -g

$(TARGET): CST211MidtermQ1Errors.cpp Exception.h array2d.h
	$(CC) $(FLAGS) -o $(TARGET) CST211MidtermQ1Errors.cpp Exception.h array2d.h  

clean:
	$(RM) $(TARGET)
