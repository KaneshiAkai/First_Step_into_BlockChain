CC = g++
CFLAGS = -std=c++11 -Wall
INCLUDEDIRS = -I"C:/msys64/mingw64/include" -Iinclude
LIBDIRS = -L"C:/msys64/mingw64/lib"
LIBS = -lssl -lcrypto

SRCDIR = src
INCDIR = include
TESTDIR = test
OBJDIR = obj

# Lấy riêng src files và test files
SRC_FILES = $(wildcard $(SRCDIR)/*.cpp)
TEST_FILES = $(wildcard $(TESTDIR)/*.cpp)

# Tạo object files tương ứng
SRC_OBJS = $(SRC_FILES:$(SRCDIR)/%.cpp=$(OBJDIR)/src_%.o)
TEST_OBJS = $(TEST_FILES:$(TESTDIR)/%.cpp=$(OBJDIR)/test_%.o)

OBJS = $(SRC_OBJS) $(TEST_OBJS)
EXEC = blockchain

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDEDIRS) $(LIBDIRS) -o $@ $^ $(LIBS)

# Compile src files với tên khác biệt
$(OBJDIR)/src_%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDEDIRS) -c $< -o $@

# Compile test files với tên khác biệt  
$(OBJDIR)/test_%.o: $(TESTDIR)/%.cpp | $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDEDIRS) -c $< -o $@

$(OBJDIR):
	if not exist $(OBJDIR) mkdir $(OBJDIR)

clean:
	if exist $(OBJDIR) rmdir /s /q $(OBJDIR)
	if exist $(EXEC).exe del $(EXEC).exe

debug:
	@echo "SRC_FILES: $(SRC_FILES)"
	@echo "TEST_FILES: $(TEST_FILES)" 
	@echo "SRC_OBJS: $(SRC_OBJS)"
	@echo "TEST_OBJS: $(TEST_OBJS)"
	@echo "All OBJS: $(OBJS)"

run: all
	.\$(EXEC).exe

.PHONY: all clean run debug