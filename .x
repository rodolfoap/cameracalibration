BINARY=calib
execute(){
	./${BINARY} data/ 0.025 5 7
}
build(){
	mkdir -p build;
	pushd build &> /dev/null;
	[ -f Makefile ] || cmake .. -Wdev;
	make -j$(nproc); STATUS=$?
	popd &> /dev/null;
}
case "$1" in
	"")
		[ -f ${BINARY} ] || build
		execute
	;;
	b)
		build
	;;
	e)
		vi -p calib.cpp CMakeLists.txt
		rm -f ${BINARY}
		build;
		execute;
	;;
esac
