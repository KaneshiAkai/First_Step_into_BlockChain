CC = g++
CFLAGS = -std=c++11 -Wall
INCLUDEDIRS = -I"C:/msys64/mingw64/include"
LIBDIRS = -L"C:/msys64/mingw64/lib"
LIBS = -lssl -lcrypto
SRCS = test.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = test

# Để buộc biên dịch lại toàn bộ:
# 1. Lưu tệp nguồn của bạn (ví dụ: test.cpp).
# 2. Chạy 'mingw32-make clean' trong terminal.
# 3. Chạy 'mingw32-make run' (hoặc 'mingw32-make' sau đó là '.\test.exe').
# Điều này đảm bảo tất cả các tệp đã biên dịch cũ bị xóa và mọi thứ được xây dựng lại từ các nguồn mới nhất.

# mingw32-make run
all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDEDIRS) $(LIBDIRS) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDEDIRS) -c $< -o $@

clean:
	del $(OBJS) $(EXEC).exe 2>nul || rem

run: all
	.\$(EXEC).exe

.PHONY: all clean run