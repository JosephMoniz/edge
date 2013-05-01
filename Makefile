CC=g++

UVDIR=dep/libuv
HTTPDIR=dep/http-parser
YAJLDIR=dep/yajl
BUILDDIR=build
SRCDIR=src

CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -Werror
CFLAGS += -Wno-unused-parameter
CFLAGS += -DEV_MULTIPLICITY=1
CFLAGS += --std=c++11

# unconditionally link against core services right now
# eventually wrap this in a OS checking conditional
# for now though this works because im working on a mac
CFLAGS += -framework CoreServices

CFLAGS_FAST = $(CFLAGS) -O3
CFLAGS_DEBUG = $(CFLAGS) -O0 -g

INCLUDES = -I$(UVDIR)/include   \
           -I$(HTTPDIR)         \
           -I$(YAJLDIR)/src/api \
           -I$(SRCDIR)

OBJ = $(BUILDDIR)/path.o               \
      $(BUILDDIR)/querystring.o        \
      $(BUILDDIR)/url.o                \
      $(BUILDDIR)/error.o              \
      $(BUILDDIR)/loop.o               \
      $(BUILDDIR)/timers.o             \
      $(BUILDDIR)/dns.o                \
      $(BUILDDIR)/net.o                \
      $(BUILDDIR)/net/socket.o         \
      $(BUILDDIR)/net/server.o         \
      $(BUILDDIR)/http/server.o        \
      $(BUILDDIR)/http/client_stream.o \
      $(BUILDDIR)/process/stdin.o      \
      $(BUILDDIR)/process/stdout.o     \
      $(BUILDDIR)/main.o

DEP = $(UVDIR)/uv.a            \
      $(YAJLDIR)/yajl.a        \
      $(HTTPDIR)/http_parser.o

$(BUILDDIR)/edge: $(DEP) $(OBJ)
	$(CC) $(CFLAGS_FAST) -o $@ $^

$(UVDIR)/Makefile:
	git submodule update --init $(UVDIR)

$(UVDIR)/uv.a: $(UVDIR)/Makefile
	$(MAKE) -C $(UVDIR) uv.a

$(YAJLDIR)/CMakeLists.txt:
	git submodule update --init $(YAJLDIR)

$(YAJLDIR)/Makefile: dep/Makefile.yajl $(YAJLDIR)/CMakeLists.txt
	cp dep/Makefile.yajl $(YAJLDIR)/Makefile

$(YAJLDIR)/yajl.a: $(YAJLDIR)/Makefile
	rm -rf $(YAJLDIR)/yajl
	cp -r $(YAJLDIR)/src/api $(YAJLDIR)/$(SRCDIR)/yajl
	$(MAKE) -C $(YAJLDIR)

$(HTTPDIR)/Makefile:
	git submodule update --init $(HTTPDIR)

$(HTTPDIR)/http_parser.o: $(HTTPDIR)/Makefile
	$(MAKE) -C $(HTTPDIR) http_parser.o

tag:
	etags $(SRCDIR)/*.cc

dep:
	$(CC) -MM $(SRCDIR)/*.cc $(INCLUDES)

clean:
	rm -rf build
	$(MAKE) -C $(UVDIR) clean
	$(MAKE) -C $(HTTPDIR) clean
	$(MAKE) -C $(YAJLDIR) clean

$(BUILDDIR)/%.o: $(SRCDIR)/%.cc
	mkdir -p `dirname $@`
	$(CC) $(CFLAGS_FAST) $(INCLUDES) -c $< -o $@

.PHONY: tag dep clean
