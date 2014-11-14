#
# This makefile places the object files and executable into a
# subdirectory named ./build.
#

# Let's use gcc as our compiler.  Define flags here.
CC := gcc
CFLAGS += -std=gnu99
LDFLAGS +=

# This macro finds the local dir of the make file
GET_LOCAL_DIR    = $(patsubst %/,%,$(dir $(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST))))

# This macro makes sure the target dir exists
MKDIR = if [ ! -d $@ ]; then echo "Making $@"; mkdir -p $@; fi

LOCAL_DIR := $(GET_LOCAL_DIR)
BUILD_DIR := $(LOCAL_DIR)/build

# List the source files here.
DIVIDE_TEST_SRCS=divide_test.c divide.c

DIVIDE_TEST_OBJS=$(DIVIDE_TEST_SRCS:%.c=$(BUILD_DIR)/%.o)
DIVIDE_TEST := $(BUILD_DIR)/divide_test

# The 'all' target must be .PHONY because the 'divide_test' target is
# also .PHONY.  If 'all' were not .PHONY, then make will not consider
# 'divide_test' to be .PHONY because .PHONY targets cannot be
# prerequisites of real files.  In this case, if 'all' is not .PHONY,
# then 'all' is considered a 'real file' and so implicity,
# 'divide_test' cannot be a .PHONY target because it is a prerequisite
# of 'all'.
.PHONY: all
all: divide_test

.PHONY: run
run:  divide_test
	$(DIVIDE_TEST)

.PHONY: divide_test
divide_test: $(DIVIDE_TEST)

$(DIVIDE_TEST): $(DIVIDE_TEST_OBJS)
	$(CC) $(LDFLAGS) $(DIVIDE_TEST_OBJS) -o $@

# The BUILD_DIR is an order-only prerequisite (which is why it is
# after the '|'), which means that it is made only if it doesn't exist
# and that the tiemstamp of BUILD_DIR is not considered when
# it is a prerequisite of other files.
$(DIVIDE_TEST_OBJS): | $(BUILD_DIR)

$(BUILD_DIR)/%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/:
	mkdir -p $@

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

