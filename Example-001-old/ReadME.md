<A href="http://www.opengl.org"><IMG src='https://www.khronos.org/assets/images/api_logos/opengl.png' border=0 width="180" 
height="97"></A>

<H3>The <i>'Example-001 (Old Mode)'</i> Test</H3>

The <i>'Example-001 (Old Mode)'</i> Test is similar to the classic <i>'Hello World'</i> program for testing the correctness of the building infrastructure. Broadly speaking, it creates a basic <A href="http://www.opengl.org"><i>OpenGL</i></A> window by providing no interaction with the user. This window must be stopped through an enforced closure.

<p>In particular, this test consists of the <i>'Example-001-old'</i> executable file (in the <i>'bin'</i> folder), starting uniquely from the <i>'main.cpp'</i> C++ source file (in the <i>'src'</i> folder).<p><hr><p>

<h4>Dependencies</h4>

The <i>'Example-001 (Old Mode)'</i> Test is based on the so-called <i>OpenGL old (direct drawing) mode</i>, and requires the following dependencies:<ul>

<li>the <i>OpenGL</i> package, distributed with the platform of interest (see the <i><A href="https://www.khronos.org/opengl/wiki/Getting_Started">Official Documentation</A></i>);</li>
<li>the <i><A href="https://www.opengl.org/resources/libraries/glut/">OpenGL Utility Toolkit (GLUT)</A></i> package (or the <A href="http://freeglut.sourceforge.net/"><i>FreeGLUT</i></A> package);</li>
<li>the <A href="http://glew.sourceforge.net/"><i>GLEW</i></A> package.</li></ul><p>Several methods for building this test are provided.<p><table border=1><tr><td><p><b>ATTENTION:</b><p>The majority of the dependencies for this test are stable, but are currently deprecated, and several warning messages may appear during the building process.<p></td></tr></table><p><hr><p>

<h4>Instructions for building this test with the <i><A href="http://cmake.org">CMake Building Tool</A></i></h4>

This test is built by using the <i>classic</i> instructions for building a program with the <i><A href="http://cmake.org">CMake Building Tool</A></i> from the <i>'cmake'</i> folder:
<pre>mkdir build
cd build
cmake ..
make
</pre><p>As mentioned above, the <i>'Example-001-old'</i> executable file is created in the <i>'bin'</i> folder. For instance, this test is executed by running:<pre>./bin/Example-001-old</pre><p>This building method is tested with the <A href="http://gcc.gnu.org/"><i>GCC</i></A> under the Ubuntu Linux 16.0.4 (LTS), as well as with the <A href="http://clang.llvm.org/"><i>CLANG</i></A> compiler under the MacOsX 11.* El-Capitan (and higher), and the <A href="http://www.visualstudio.com/"><i>Microsoft Visual Studio (Community Edition 2015)</i></A> under the Microsoft Windows 10.<p>In this latter case, three custom projects are automatically generated, and ready to be open in the <A href="http://www.visualstudio.com/"><i>Microsoft Visual Studio (Community Edition 2015)</i></A>. The solution file of interest is the <i>'Example-001-old.sln'</i> solution file, which can be open and built in the program without being modified.<p>

All dependencies of the <i>'Example-001 (Old Mode)'</i> Test are supported automatically by the <i><A href="http://cmake.org">CMake Building Tool</A></i> through a built-in manifest file. In particular, they are often pre-installed in a generic GNU/Linux distribution, and distributed in conjunction with the <A href="http://developer.apple.com/xcode/"><i>Apple XCode</i></A>. Thus, they should be found by the script of interest without problems in these platforms.<p>Instead, these libraries are not standard in the Microsoft Windows, and must be installed properly. For the sake of simplicity, the Win32 versions for the auxiliary libraries of interest in the <i>'../../depends'</i> folder are exploited, if the <i><A href="http://cmake.org">CMake Building Tool</A></i> fails while performing their automatic identification. This means that the resulting solution file creates automatically the <i>'Example-001-old.exe'</i> Win32 executable file.<p><hr><p>
