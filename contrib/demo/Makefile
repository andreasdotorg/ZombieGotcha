

all: stagethree
install: stagethree
	cd sprites && make install
stagethree: stagetwo
	cp src/zombie.hex ./
stagetwo: stageone
	cd src && make clean all
stageone:
	cd sprites && ./build.zsh
clean:
	#Clean up yourself!
