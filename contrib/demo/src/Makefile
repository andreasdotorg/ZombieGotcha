CC=sdcc
CFLAGS = -Iinc --debug  --no-pack-iram
LFLAGS = --xram-loc 0xF000

#apps = randtest.rel timer.rel
#libs = times.rel io.rel font.rel string.rel keys.rel power.rel menu.rel $(apps)

apps = main.rel  io.rel  keys.rel  font.rel times.rel 
sys =  zombie.rel fbuffer.rel zsprites.rel ztug.rel zgame.rel

bins = $(sys) $(apps)
srcs = $(libs,.rel=.c) 

all: zombie.hex

%.rel : %.c
	$(CC) $(CFLAGS) -c $<

zombie.hex:  $(bins)
	sdcc $(LFLAGS) $(bins)
	packihx <zombie.ihx >zombie.hex

install: zombie.hex
	goodfet.cc erase
	goodfet.cc flash zombie.hex
	#goodfet.cc verify zombie.hex
clean:
	rm -f *.ihx *.rel *.hex *.sym *.asm *.lst *.lnk *.map *.mem *.rst *.adb
