.PHONY: all payload patch clean

all: payload patch

payload:
	cd payload && $(MAKE)
	clear

patch:
	mkdir -p build
	python scripts/patch_lk.py lk/lk.img payload/build/payload.bin build/lk-patched.img
	clear

clean:
	$(MAKE) -C payload clean
	rm -rf build
	clear