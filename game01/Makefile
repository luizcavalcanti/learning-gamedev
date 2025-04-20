.PHONY=compile

setup:
	meson setup build/macosx --prefix /tmp/myapp.app --bindir=Contents/MacOS --reconfigure
	meson setup build/windows --cross-file windows-cross.txt --reconfigure

compile:
	meson compile -C build/macosx

run: compile
	./build/macosx/game01

compile-all:
	meson compile -C build/macosx
	meson compile -C build/windows
