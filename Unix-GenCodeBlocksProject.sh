BUILT_TARGET="Debug"

#First parameter, if any, is used as build target.
#If no parameter is given, then default to Debug
if [ "$#" == 0 ]; then
	BUILD_TARGET="Debug"
else
	BUILD_TARGET="$1"
fi

cd build
cmake -DCMAKE_BUILD_TYPE="$BUILD_TARGET" -G "CodeBlocks - Unix Makefiles" ../

mv ../res/ ./
