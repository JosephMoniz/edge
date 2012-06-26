CC?=g++

UVDIR=deps/libuv
HTTPDIR=deps/http-parser
YAJLDIR=deps/yajl
BUILDDIR=build
SRCDIR=src

CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -Werror
CFLAGS += -Wno-unused-parameter
CFLAGS += DEV_MULTIPLICITY=1

CFLAGS_FAST = $(CFLAGS) -O3
CFLAGS_DEBUG = $(CFLAGS) -O0 -g

INCLUDES = -I$(UVDIR)/include   \
           -I$(HTTPDIR)         \
           -I$(YAJLDIR)/src/api \
           -I$(SRCDIR)

OBJ = $(BUILDDIR)/main.o

DEPS = $(UVDIR)/uv.a            \
       $(YAJLDIR)/yajl.a        \
       $(HTTPDIR)/http_parser.o

$($BUILDDIR)/node: $(DEPS) $(OBJ)
	$(CC) $(CFLAGS_FAST) -o $@ $^

$(UVDIR)/Makefile:
	git submodule update --init $(BASEDIR)/$(UVDIR)

$(UVDIR)/uv.a: $(UVDIR)/Makefile
	$(MAKE) -C $(UVDIR) uv.a

$(YAJLDIR)/CMakeLists.txt:
	git submodule update --init $(BASEDIR)/$(YAJLDIR)

$(YAJLDIR)/Makefile: deps/Makefile.yajl $(YAJLDIR)/CMakeLists.txt
	cp deps/Makefile.yajl $(YAJLDIR)/Makefile

$(YAJLDIR)/yajl.a: $(YAJLDIR)/Makefile
	rm -rf $(YAJLDIR)/src/yajl
	cp -r $(YAJLDIR)/src/api $(YAJLDIR)/$(SRCDIR)/yajl
	$(MAKE) -C $(YAJLDIR)

$(HTTPDIR)/Makefile:
	git submodule update --init $(BASEDIR)/$(HTTPDIR)

$(HTTPDDIR)/http_parser.o: $(HTTPDIR)/Makefile
	$(MAKE) -C $(HTTPDIR) http_parser.o

tag:
	etags $(SRCDIR)/*.cc

deps:
	$(CC) -MM $(SRCDIR)/*.cc $(INCLUDES)

clean:
	rm -rf build
	$(MAKE) -C $(UVDIR) clean
	$(MAKE) -C $(HTTPDIR) clean
	$(MAKE) -C $(YAJLDIR) clean

$(BUILDDIR)/%.o: $(SRCDIR)/%.cc
	mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS_FAST) $(INCLUDES) -c $< -o $@

.PHONY: tag deps clean
