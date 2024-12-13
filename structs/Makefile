CC = clang
CC_FLAGS = -Wall -Wextra -Wvla -pedantic
CC_DEBUG = -g -fsanitize=address

objects = src/vec src/linked_list

build: $(objects)

debug: CC_FLAGS += $(CC_DEBUG)
debug: $(objects)

$(objects): %: %.c
	$(CC) $(CC_FLAGS) -o $@ $<

clean:
	rm $(objects)

.PHONY: build debug clean
