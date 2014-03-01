3DEngineCpp
===========

It's like the 3D Game Engine, except in C++

##Build Instructions##

###Windows###
- Open 3DGameEngineCpp.sln in Microsoft Visual Studio 2012 or newer.
- Select build target (Debug or Release), and either click "Build" or hit 'F7'
- Click "Run" or hit 'Ctrl-F5'.
- Everything should work from that. If not, see section on reporting a build error.

###Mac###
I do not have a Mac, and therefore cannot write effective step by step instructions for building on a Mac. However, there are a few things that must be considered:
- Make sure you are building with C++11. If you are not, the OS dependent code in time.cpp will fall back on an inefficient default timer. While technically working, it does not produce smooth results.

####HELP WANTED:####
- If anyone can provide an XCode project that's set up to build, that'd be great!
- If anyone can provide high resolution timing code for Mac, that would make Mac build considerations significantly simpler! (See time.cpp for reference)

###Linux###
- Open a Terminal and install the build dependencies (GLEW, SDL2). Syntax on Ubuntu Linux: sudo apt-get install libglew-dev libsdl2-dev
  
    - NOTE: The syntax for this depends on both your package manager and your Linux distribution. If you're not sure how to install the dependencies, check with your distribution and package manager for details.

- For building/running, there are two possible options:

    A) Through Code::Blocks:
    - Go to the "3DGameEngineCpp" folder and open 3DGameEngine.cbp with Code::Blocks.
     
    - Select build target (Debug or Release), and either click "Build" or hit 'Ctrl-F9'
    
    - Click "Run" or hit 'F9'.
        
    B) Through Terminal:
    - Open a Terminal and navigate to the "3DGameEngineCpp" folder.
    
    - Type "make" (NOTE: You can add "debug" or "release" as an argument to specify a desired build target)
        
    - Copy the "res" folder to "bin/Debug" or "bin/Release" depending on the desired build target
        
    - Navigate to "bin/Debug" or "bin/Release" depending on the desired build target, and type "./3DGameEngine"
      
- Everything should work after completing either option. If not, see section on reporting a build error.
