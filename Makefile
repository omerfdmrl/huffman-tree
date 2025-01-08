RM = rm -rf
BUILD_DIR=build/
APP_NAME=HuffmanEncodingApp
SOURCE=main.cpp

all:
	@if [ ! -d $(BUILD_DIR) ]; then mkdir $(BUILD_DIR); fi
	
	cd $(BUILD_DIR) && cmake -DSOURCE:STRING=$(SOURCE) .. && make
	./$(BUILD_DIR)/$(APP_NAME)

.PHONE: all
.DEFAULT_GOAL = all