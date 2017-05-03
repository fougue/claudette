Claudette v0.1 by Fougue Ltd, fork of

ColDet - 3D Collision Detection Library  
Copyright (C) 2000  Amir Geva


Description
===========================================

ColDet is a 3D collision detection library, intended for games.  
It supports generic polyhedra, and even polygon soups.

As ColDet is no longer actively maintained, Fougue decided to fork the project
to keep it up to date :
  * ensure source code builds with recent C/C++ compilers
  * use GitHub as main project infrastructure


Requirements
===========================================

It is written in standard C++ and can be compiled on Windows or GNU/Linux systems

Other systems that have g++ will probably compile with no modification.  
The code is portable to any system with a standard C++ compliant compiler
(as compliant as they get)


Installation
===========================================

Claudette can be built with CMake, by default a shared library is generated.
1. For an out-of-source build, create a directory where the build will take place (say `build`)
2. Call cmake, passing as argument the directory where is located `CMakeLists.txt`
3. `(n)make`
4. `(n)make install`

Read `CMakeLists.txt` to figure out how to build debug and release libraries.


License
===========================================

It is distributed under the Library GNU Lesser Public License (see the file: COPYING)  
Any redistribution of the files in this package must include the entire package.


Contact Information
===========================================

   Fougue:  
     Web Site: http://www.fougue.pro  
     email:    contact@fougue.pro

   Original author of ColDet:  
     Web Site: http://photoneffect.com/coldet/  
     email:    photon@photoneffect.com


Hwow to report a bug
===========================================

If you think you have found a bug in Claudette, we would like to hear
about it so that we can fix it.  
The Claudette bug tracking system is open to the public at https://github.com/fougue/claudette/issues.

Before reporting a bug, please use the bug-tracker's search functions
to see if the issue is already known.

Always include the following information in your bug report:  
  * the name and version number of your compiler;  
  * the name and version number of your operating system;  
  * the version of Claudette you are using, and what options it was compiled with.

If the problem you are reporting is only visible at run-time, try to
create a small test program that shows the problem when run.

