SRC:=$(wildcard *.c)
BIN:=IoT_Memory_Reporter
OBJ:=$(SRC:.c=.o)

LDFLAGS:=-llink_core -lmiddleware_implementation -lplatform_port -lutils_modules -lblobmsg_json -lubus -lubox

.PHONY: all clean

all: $(BIN)

$(BIN): $(SRC)
	$(CC) -o $(BIN) $^ $(LDFLAGS)

clean:
	$(RM) $(OBJ) $(BIN)

