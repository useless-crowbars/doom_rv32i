################################################################
#
# $Id:$
#
# $Log:$
#

HOSTGCC?=gcc

CC?=gcc  # gcc or g++
CC_HOST?=gcc
# 

# for E1M1 Only, 
#  make clean && cp support/stripchoice-E1M1ONLY.txt support/stripchoice.txt && cp support/stripchoice-E1M1ONLY.txt support/stripchoicebegin.txt && EXTRA_CFLAGS="-DE1M1ONLY=1" make && ls -l emdoom
# 

EXTRA_CFLAGS="-DE1M1ONLY=1"
IGNORE_WARNINGS=-Wno-int-conversion -Wno-incompatible-pointer-types -Wno-implicit-int -Wno-implicit-function-declaration
CFLAGS?=-m32 -Os -g -w $(IGNORE_WARNINGS) -flto -DMAXPLAYERS=1 -DRANGECHECK -DDISABLE_NETWORK -fdata-sections -ffunction-sections $(EXTRA_CFLAGS) # -DUSEASM
LDFLAGS?=-L/usr/X11R6/lib -Wl,--gc-sections $(CFLAGS)
LIBS?=-lglfw -lGL
CFLAGS_HOST?=-m32 $(IGNORE_WARNINGS) $(EXTRA_CFLAGS)
LDFLAGS_HOST?=-L/usr/X11R6/lib
LIBS_HOST?=-lglfw -lGL
CS?=i_video_pajseri.c ../../emu_rv32i/stdlib/*.c


# If you want to reduce printf junk
CFLAGS+=-DSET_MEMORY_DEBUG=0


#CFLAGS_FINAL:=$(CFLAGS)
#CFLAGS_FINAL+=-DFIXED_HEAP=262144
#CS:=i_video.c

# if you need to do low-level memory debugging.  This will help find things like out-of-array writing.
#CFLAGS_HOST+=-fsanitize=address -static-libasan -g

# For RISC-V
CFLAGS:=-Os -D__STDC_HOSTED__=0 -w $(IGNORE_WARNINGS) -march=rv32im -mabi=ilp32 -nostdlib -ffreestanding -DMAXPLAYERS=1 -DDISABLE_NETWORK -fdata-sections -ffunction-sections $(EXTRA_CFLAGS)
LDFLAGS:= -T linker.ld $(CFLAGS)
LIBS:=
SUPPORT_FILES:=startup.S
CC:=riscv64-elf-gcc

# Tricky - if removing maps, also be careful to add/remove maps from stripchoice.txt
#STRIKEMAP:=-strikemap 3 4 5 6 7 8 9 

BAKED:=support/baked_texture_data.o support/baked_map_data.o
# subdirectory for objects
O=linux

# not too sophisticated dependency
CS+=				\
		doomdef.c \
		doomstat.c \
		dstrings.c \
		i_system.c		\
		tables.c			\
		f_finale.c		\
		f_wipe.c 		\
		d_main.c			\
		d_items.c		\
		g_game.c			\
		m_menu.c			\
		m_misc.c			\
		m_bbox.c			\
		m_fixed.c		\
		m_swap.c			\
		m_cheat.c		\
		m_random.c		\
		am_map.c			\
		p_ceilng.c		\
		p_doors.c		\
		p_enemy.c		\
		p_floor.c		\
		p_inter.c		\
		p_lights.c		\
		p_map.c			\
		p_maputl.c		\
		p_plats.c		\
		p_pspr.c			\
		p_setup.c		\
		p_sight.c		\
		p_spec.c			\
		p_switch.c		\
		p_mobj.c			\
		p_telept.c		\
		p_tick.c			\
		p_saveg.c		\
		p_user.c			\
		r_bsp.c			\
		r_data.c			\
		r_draw.c			\
		r_main.c			\
		r_plane.c		\
		r_segs.c			\
		r_sky.c			\
		r_things.c		\
		w_wad.c			\
		wi_stuff.c		\
		v_video.c		\
		st_lib.c			\
		st_stuff.c		\
		hu_stuff.c		\
		hu_lib.c			\
		z_zone.c			\
		info.c				\
		i_net.c			\
		d_net.c			\
		stubs.c

all:	 emdoom

emdoom:	$(CS) i_main.c $(BAKED) $(SUPPORT_FILES) support/rawwad_use.o
	$(CC) $(CFLAGS_FINAL)  $^ -o emdoom $(LDFLAGS) $(LIBS)
	riscv64-elf-objcopy -O binary emdoom emdoom.bin

support/baked_texture_data.c support/baked_map_data.c support/bakedoutput.txt : emdoom.gentables.initial
	./emdoom.gentables.initial $(STRIKEMAP) > support/bakedoutput.txt

support/add_sprites.txt : support/bakedoutput.txt support/augment_sprites.txt
	cat support/bakedoutput.txt | grep ADD_SPRITE > support/add_sprites.txt
	cat support/augment_sprites.txt >> support/add_sprites.txt

#support/baked_map_data.c support/baked_texture_data.c : emdoom.gentables
#	./emdoom.gentables $(STRIKEMAP)

support/baked_map_data.o : support/baked_map_data.c
	$(CC) $(CFLAGS) -c -o $@ $^

support/baked_texture_data.o : support/baked_texture_data.c
	$(CC) $(CFLAGS) -c -o $@ $^

support/wadder : support/wadder.c
	$(HOSTGCC) -o $@ $^

# Don't normally need to do this, so it's hidden from the steps.
support/rawwad.c : support/wadder
	(cd support;./wadder;cd ..)

support/rawwad_use.o : support/rawwad_use.c
	$(CC) $(CFLAGS) -c -o $@ $^


support/rawwad_use_host.o : support/rawwad_use.c
	$(CC_HOST) $(CFLAGS_HOST) -c -o $@ $^

support/rawwad_host.o : support/rawwad.c
	$(CC_HOST) $(CFLAGS_HOST) -c -o $@ $^

support/rawwad_host_begin.o : support/rawwad_begin.c
	$(CC_HOST) $(CFLAGS_HOST) -c -o $@ $^


emdoom.size : emdoom
	nm --print-size --size-sort --radix=d emdoom  | grep -v " r " | grep -v " R "
	size emdoom -A

emdoom.gentables : i_main.c $(CS) support/rawwad_host_begin.o $(BAKED)
	$(CC_HOST) $(CFLAGS_HOST) $(LDFLAGS_HOST) $^ -o emdoom.gentables -g -DGENERATE_BAKED $(LIBS_HOST)

emdoom.gentables.initial : i_main.c $(CS) support/rawwad_host_begin.o
	$(CC_HOST) $(CFLAGS_HOST) $(LDFLAGS_HOST) $^ -o emdoom.gentables.initial -g -DGENERATE_BAKED -DGENERATE_BAKED_INITIAL $(LIBS_HOST)


clean:
	rm -f *.o *~ *.flc
	rm -f emdoom emdoom.bin emdoom.gentables emdoom.gentables.initial $(BAKED) support/wadder support/rawwad_host.o support/rawwad_host_use.o support/rawwad_host_begin.o support/shrinkwad
	rm -rf support/baked_map_data.c  support/baked_texture_data.c
	rm -rf support/rawwad_begin.c support/rawwad_begin.o support/rawwad_use.c support/rawwad_use.o support/bakedoutput.txt
	rm -rf support/add_sprites.txt support/rawwad_begin.h support/rawwad_use.h

### Extra features

support/shrinkwad : support/shrinkwad.c
	$(CC_HOST) $(CFLAGS_HOST) $(LDFLAGS_HOST) -o $@ $^ $(LIBS_HOST) 

support/rawwad_use.c : support/shrinkwad support/stripchoice.txt support/add_sprites.txt
	cd support && ./shrinkwad stripchoice.txt add_sprites.txt rawwad_use.c rawwad_use.h

support/rawwad_begin.c : support/shrinkwad support/stripchoicebegin.txt
	#cat gentableslog.txt | grep -a ACCESS_LUMP > lumpaccess.txt
	cd support && ./shrinkwad stripchoicebegin.txt 0 rawwad_begin.c rawwad_begin.h

#############################################################
#
#############################################################
