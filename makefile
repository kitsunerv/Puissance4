CC := gcc
SRC_DIR ?= src
OBJ_DIR ?= obj
DEBUG ?= 1

ifeq '$(DEBUG)' '1'
CFLAGS ?= -Wall -MMD -g3
else
CFLAGS ?= -Wall -MMD -g3 -DNDEBUG
endif

CFLAGS += -I3rdParty/SDL2/Library/include/
LDFLAGS = -L3rdParty/SDL2/Library/lib/ -lSDL2

OBJS := $(shell find $(SRC_DIR) -name "*.c" |sed 's/.c$$/.o/g' | sed 's/$(SRC_DIR)/$(OBJ_DIR)/g')
DEPS := $(OBJS:.o=.d)
TARGET ?= 3rdParty/SDL2/Library/lib/libSDL2.so exec doc

all: $(TARGET) 

3rdParty/SDL2/Library/lib/libSDL2.so:
	./build_lib.sh

exec: $(OBJS)
	$(CC) -o Puissance4 $(OBJS) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

mrproper: clean
	rm -f $(TARGET)
	make -C 3rdParty/SDL2/ distclean

doc:
	doxygen ./documentation/Doxyfile

-include $(DEPS)