TARGET=LtM

all : clean $(TARGET) 

$(TARGET) : $(TARGET).c
	gcc -Wall -o $(TARGET) $(TARGET).c -lwiringPi

clean:
	rm -f $(TARGET)

release : clean $(TARGET)
	rm /home/pi/prod/$(TARGET)
	cp $(TARGET) /home/pi/prod/

