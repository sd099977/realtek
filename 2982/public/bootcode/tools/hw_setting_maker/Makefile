
RM = rm -f
SRC = generate_config.c
TARGET = generate_config 

#OPTION += -static

all: $(TARGET)

$(TARGET): $(SRC)
#	$(CC) $(OPTION) $^ -o $(OUTPUT)
	$(CC) $^ -o $(TARGET)


.PHONY: clean
clean:
	$(RM) *.o $(TARGET)

