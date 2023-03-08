# Makefile to build and install the SDL_mixer library.

top_builddir = .
srcdir  = .
objects = build
prefix = /info/etu/l2info/s2100723/SDL2
exec_prefix = ${prefix}
bindir	= $(DESTDIR)${exec_prefix}/bin
libdir  = $(DESTDIR)${exec_prefix}/lib
includedir = $(DESTDIR)${prefix}/include
datarootdir = $(DESTDIR)${prefix}/share
datadir	= ${datarootdir}
mandir	= ${datarootdir}/man
auxdir	= ./build-scripts/
distpath = $(srcdir)/..
distdir = SDL2_mixer-2.6.3
distfile = $(distdir).tar.gz


EXE	= 
SHELL	= /bin/bash
CC      = gcc
CXX     = g++
CFLAGS  = -g -O2  -I./include -I./src -I./src/codecs
EXTRA_CFLAGS =  -D_GNU_SOURCE=1 -D_REENTRANT -I/usr/include/SDL2 -DSDL_BUILD_MAJOR_VERSION=2 -DSDL_BUILD_MINOR_VERSION=6 -DSDL_BUILD_MICRO_VERSION=3 -Wall -fvisibility=hidden -DHAVE_SIGNAL_H -DHAVE_SETBUF -DHAVE_FORK -DMUSIC_CMD -DMUSIC_WAV -DMUSIC_MID -DMUSIC_MID_TIMIDITY -I$(srcdir)/src/codecs/timidity -DMUSIC_OGG -DOGG_USE_STB -DMUSIC_FLAC_DRFLAC -DMUSIC_MP3_DRMP3
LDFLAGS =  -Wl,--no-undefined
EXTRA_LDFLAGS = 
MIXER_LIBS =  -lm
LIBTOOL = $(SHELL) $(top_builddir)/libtool
INSTALL = /usr/bin/install -c
AR	= ar
RANLIB	= ranlib
RC	= 
SDL_CFLAGS = -D_REENTRANT -I/usr/include/SDL2
SDL_LIBS = -lSDL2

TARGET  = libSDL2_mixer.la
OBJECTS = $(objects)/load_aiff.lo $(objects)/load_voc.lo $(objects)/mp3utils.lo $(objects)/music_cmd.lo $(objects)/music_drflac.lo $(objects)/music_drmp3.lo $(objects)/music_flac.lo $(objects)/music_fluidsynth.lo $(objects)/music_modplug.lo $(objects)/music_mpg123.lo $(objects)/music_nativemidi.lo $(objects)/music_ogg.lo $(objects)/music_ogg_stb.lo $(objects)/music_opus.lo $(objects)/music_timidity.lo $(objects)/music_wav.lo $(objects)/music_xmp.lo $(objects)/effect_position.lo $(objects)/effect_stereoreverse.lo $(objects)/effects_internal.lo $(objects)/mixer.lo $(objects)/music.lo $(objects)/utils.lo $(objects)/common.lo $(objects)/instrum.lo $(objects)/mix.lo $(objects)/output.lo $(objects)/playmidi.lo $(objects)/readmidi.lo $(objects)/resample.lo $(objects)/tables.lo $(objects)/timidity.lo 
VERSION_OBJECTS = 
PLAYWAVE_OBJECTS = $(objects)/playwave.lo
PLAYMUS_OBJECTS = $(objects)/playmus.lo

SRC_DIST =			\
	.gitmodules		\
	Android.mk		\
	CHANGES.txt		\
	CMakeLists.txt		\
	LICENSE.txt		\
	Makefile.in		\
	Makefile.os2		\
	README.txt		\
	SDL2_mixer.pc.in	\
	SDL2_mixer.spec.in	\
	SDL2_mixerConfig.cmake.in \
	VisualC			\
	VisualC-WinRT		\
	Xcode			\
	acinclude		\
	autogen.sh		\
	build-scripts		\
	cmake			\
	configure		\
	configure.ac		\
	external/download.sh	\
	include/SDL_mixer.h	\
	mingw			\
	playmus.c		\
	playwave.c		\
	sdl2_mixer-config-version.cmake.in \
	sdl2_mixer-config.cmake.in \
	src			\
	version.rc

GEN_DIST = SDL2_mixer.spec

LT_AGE      = 600
LT_CURRENT  = 600
LT_RELEASE  = 2.0
LT_REVISION = 3
LT_EXTRA    = 
LT_LDFLAGS  = -no-undefined -rpath $(libdir) -release $(LT_RELEASE) -version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE) $(LT_EXTRA)

all: $(srcdir)/configure Makefile $(objects)/$(TARGET) $(objects)/playwave$(EXE) $(objects)/playmus$(EXE)

$(srcdir)/configure: $(srcdir)/configure.ac
	@echo "Warning, configure is out of date, please re-run autogen.sh"

Makefile: $(srcdir)/Makefile.in
	$(SHELL) config.status $@

$(objects)/.created:
	$(SHELL) $(auxdir)/mkinstalldirs $(objects)
	touch $@

.PHONY: all install install-hdrs install-lib install-bin uninstall uninstall-hdrs uninstall-lib uninstall-bin clean distclean dist

$(objects)/$(TARGET): $(OBJECTS) $(VERSION_OBJECTS)
	$(LIBTOOL) --mode=link $(CC) -o $@ $(OBJECTS) $(VERSION_OBJECTS) $(LDFLAGS) $(EXTRA_LDFLAGS) $(LT_LDFLAGS) $(SDL_LIBS) $(MIXER_LIBS)

$(objects)/playwave$(EXE): $(objects)/playwave.lo $(objects)/$(TARGET)
	$(LIBTOOL) --mode=link $(CC) -o $@ $(objects)/playwave.lo $(SDL_CFLAGS) $(objects)/$(TARGET) $(SDL_LIBS) $(LDFLAGS)

$(objects)/playmus$(EXE): $(objects)/playmus.lo $(objects)/$(TARGET)
	$(LIBTOOL) --mode=link $(CC) -o $@ $(objects)/playmus.lo $(SDL_CFLAGS) $(objects)/$(TARGET) $(SDL_LIBS) $(LDFLAGS)

install: all install-hdrs install-lib #install-bin
install-hdrs:
	$(SHELL) $(auxdir)/mkinstalldirs $(includedir)/SDL2
	for src in $(srcdir)/include/SDL_mixer.h; do \
	    file=`echo $$src | sed -e 's|^.*/||'`; \
	    $(INSTALL) -m 644 $$src $(includedir)/SDL2/$$file; \
	done
	$(SHELL) $(auxdir)/mkinstalldirs $(libdir)/pkgconfig
	$(INSTALL) -m 644 SDL2_mixer.pc $(libdir)/pkgconfig/
	$(SHELL) $(auxdir)/mkinstalldirs $(libdir)/cmake/SDL2_mixer/
	$(INSTALL) -m 644 sdl2_mixer-config.cmake $(libdir)/cmake/SDL2_mixer
	$(INSTALL) -m 644 sdl2_mixer-config-version.cmake $(libdir)/cmake/SDL2_mixer
install-lib: $(objects)/$(TARGET)
	$(SHELL) $(auxdir)/mkinstalldirs $(libdir)
	$(LIBTOOL) --mode=install $(INSTALL) $(objects)/$(TARGET) $(libdir)/$(TARGET)
install-bin:
	$(SHELL) $(auxdir)/mkinstalldirs $(bindir)
	$(LIBTOOL) --mode=install $(INSTALL) -m 755 $(objects)/playwave$(EXE) $(bindir)/playwave$(EXE)
	$(LIBTOOL) --mode=install $(INSTALL) -m 755 $(objects)/playmus$(EXE) $(bindir)/playmus$(EXE)

uninstall: uninstall-hdrs uninstall-lib uninstall-bin
uninstall-hdrs:
	for src in $(srcdir)/include/SDL_mixer.h; do \
	    file=`echo $$src | sed -e 's|^.*/||'`; \
	    rm -f $(includedir)/SDL2/$$file; \
	done
	-rmdir $(includedir)/SDL2
	rm -f $(libdir)/pkgconfig/SDL2_mixer.pc
	-rmdir $(libdir)/pkgconfig
	rm -f $(libdir)/cmake/SDL2_mixer/sdl2_mixer-config.cmake
	rm -f $(libdir)/cmake/SDL2_mixer/sdl2_mixer-config-version.cmake
	-rmdir $(libdir)/cmake/SDL2_mixer
	-rmdir $(libdir)/cmake
uninstall-lib:
	$(LIBTOOL) --mode=uninstall rm -f $(libdir)/$(TARGET)
uninstall-bin:
	rm -f $(bindir)/playwave$(EXE)
	rm -f $(bindir)/playmus$(EXE)

clean:
	rm -rf $(objects)

distclean: clean
	rm -f Makefile
	rm -f config.status config.cache config.log libtool
	rm -f SDL2_mixer.pc
	rm -rf $(srcdir)/autom4te*
	find $(srcdir) \( \
	    -name '*~' -o \
	    -name '*.bak' -o \
	    -name '*.old' -o \
	    -name '*.rej' -o \
	    -name '*.orig' -o \
	    -name '.#*' \) \
	    -exec rm -f {} \;

dist $(distfile):
	$(SHELL) $(auxdir)/mkinstalldirs $(distdir)
	(cd $(srcdir); tar cf - $(SRC_DIST)) | (cd $(distdir); tar xf -)
	tar cf - $(GEN_DIST) | (cd $(distdir); tar xf -)
	-rm -rf `find $(distdir)/external -name '.git*'`
	-rm -rf `find $(distdir)/external -name '.ci*'`
	-rm -rf `find $(distdir)/external -name '*.yml'`
	-rm -rf `find $(distdir)/external -name ci`
	-rm -f `find $(distdir) -name '.#*'`
	tar cf - $(distdir) | gzip --best >$(distfile)
	rm -rf $(distdir)

rpm: $(distfile)
	rpmbuild -ta $?

# Build rules for objects
-include $(OBJECTS:.lo=.d)

$(objects)/load_aiff.lo: ./src/codecs/load_aiff.c $(objects)/.created
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/load_voc.lo: ./src/codecs/load_voc.c $(objects)/.created
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/mp3utils.lo: ./src/codecs/mp3utils.c $(objects)/.created
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/music_cmd.lo: ./src/codecs/music_cmd.c $(objects)/.created
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/music_drflac.lo: ./src/codecs/music_drflac.c $(objects)/.created
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/music_drmp3.lo: ./src/codecs/music_drmp3.c $(objects)/.created
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/music_flac.lo: ./src/codecs/music_flac.c $(objects)/.created
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/music_fluidsynth.lo: ./src/codecs/music_fluidsynth.c $(objects)/.created
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/music_modplug.lo: ./src/codecs/music_modplug.c $(objects)/.created
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/music_mpg123.lo: ./src/codecs/music_mpg123.c $(objects)/.created
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/music_nativemidi.lo: ./src/codecs/music_nativemidi.c $(objects)/.created
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/music_ogg.lo: ./src/codecs/music_ogg.c $(objects)/.created
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/music_ogg_stb.lo: ./src/codecs/music_ogg_stb.c $(objects)/.created
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/music_opus.lo: ./src/codecs/music_opus.c $(objects)/.created
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/music_timidity.lo: ./src/codecs/music_timidity.c $(objects)/.created
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/music_wav.lo: ./src/codecs/music_wav.c $(objects)/.created
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/music_xmp.lo: ./src/codecs/music_xmp.c $(objects)/.created
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/effect_position.lo: ./src/effect_position.c $(objects)/.created
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/effect_stereoreverse.lo: ./src/effect_stereoreverse.c $(objects)/.created
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/effects_internal.lo: ./src/effects_internal.c $(objects)/.created
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/mixer.lo: ./src/mixer.c $(objects)/.created
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/music.lo: ./src/music.c $(objects)/.created
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/utils.lo: ./src/utils.c $(objects)/.created
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/common.lo: ./src/codecs/timidity/common.c $(objects)/.created
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/instrum.lo: ./src/codecs/timidity/instrum.c $(objects)/.created
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/mix.lo: ./src/codecs/timidity/mix.c $(objects)/.created
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/output.lo: ./src/codecs/timidity/output.c $(objects)/.created
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/playmidi.lo: ./src/codecs/timidity/playmidi.c $(objects)/.created
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/readmidi.lo: ./src/codecs/timidity/readmidi.c $(objects)/.created
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/resample.lo: ./src/codecs/timidity/resample.c $(objects)/.created
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/tables.lo: ./src/codecs/timidity/tables.c $(objects)/.created
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/timidity.lo: ./src/codecs/timidity/timidity.c $(objects)/.created
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 


-include $(PLAYWAVE_OBJECTS:.lo=.d)

$(objects)/playwave.lo: ./playwave.c $(objects)/.created
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@

-include $(PLAYMUS_OBJECTS:.lo=.d)

$(objects)/playmus.lo: ./playmus.c $(objects)/.created
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@
