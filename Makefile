CC=/opt/local/bin/g++-mp-4.8

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

CFLAGS_FAST = $(CFLAGS) -O3
CFLAGS_DEBUG = $(CFLAGS) -O0 -g

INCLUDES = -I$(UVDIR)/include   \
           -I$(HTTPDIR)         \
           -I$(YAJLDIR)/src/api \
           -I$(SRCDIR)

OBJ = $(BUILDDIR)/path.o         \
      $(BUILDDIR)/eventemitter.o \
      $(BUILDDIR)/querystring.o  \
      $(BUILDDIR)/main.o

DEP = $(UVDIR)/uv.a            \
       $(YAJLDIR)/yajl.a        \
       $(HTTPDIR)/http_parser.o

$(BUILDDIR)/node: $(DEP) $(OBJ)
	$(CC) $(CFLAGS_FAST) -o $@ $^

$(UVDIR)/Makefile:
	git submodule update --init $(BASEDIR)/$(UVDIR)

$(UVDIR)/uv.a: $(UVDIR)/Makefile
	$(MAKE) -C $(UVDIR) uv.a

$(YAJLDIR)/CMakeLists.txt:
	git submodule update --init $(BASEDIR)/$(YAJLDIR)

$(YAJLDIR)/Makefile: dep/Makefile.yajl $(YAJLDIR)/CMakeLists.txt
	cp dep/Makefile.yajl $(YAJLDIR)/Makefile

$(YAJLDIR)/yajl.a: $(YAJLDIR)/Makefile
	rm -rf $(YAJLDIR)/yajl
	cp -r $(YAJLDIR)/src/api $(YAJLDIR)/$(SRCDIR)/yajl
	$(MAKE) -C $(YAJLDIR)

$(HTTPDIR)/Makefile:
	git submodule update --init $(BASEDIR)/$(HTTPDIR)

$(HTTPDDIR)/http_parser.o: $(HTTPDIR)/Makefile
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
	mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS_FAST) $(INCLUDES) -c $< -o $@

.PHONY: tag dep clean
