BUILT_TARGET="Debug"

#First parameter, if any, is used as build target.
#If no parameter is given, then default to Debug
if [ "$#" == 0 ]; then
	BUILD_TARGET="Debug"
else
	BUILD_TARGET="$1"
fi

#All remaining parameters are used as parameters to CMake

cd build
cmake -DCMAKE_BUILD_TYPE="$BUILD_TARGET" "${@:1}" ../
make -j 4
mv ../res/ ./
