<A href="http://www.opengl.org"><IMG src='https://www.khronos.org/assets/images/api_logos/opengl.png' border=0 width="180" height="97"></A>

<H3>The <i>'Example-045 (Old Mode)'</i> Test</H3>

The <i>'Example-045 (Old Mode)'</i> Test draws the <i>'Hemisphere'</i> shape in an <A href="http://www.opengl.org"><i>OpenGL</i></A> window. Intuitively, the <i>'Hemisphere'</i> shape is basically any of <code><i>'2'</i></code> hemispheres of the <i>'Sphere'</i> shape. This latter describes a perfectly round geometrical object in the 3D space, that is the surface of a completely round ball. Like the <i>'Circle'</i> shape, which geometrically is an object in the 2D space, the <i>'Sphere'</i> shape is defined mathematically as the set of 3D points, that are all at the same distance <code><i>'R'</i></code> from a given point <code><i>'(xc,yc,zc)'</i></code>. The distance <code><i>'R'</i></code> is the <i>'radius'</i> of the <i>'Sphere'</i> shape, and the point <code><i>'(xc,yc,zc)'</i></code> is its <i>'center'</i></code>.<p>For the sake of the simplicity, we consider the <i>'Hemisphere'</i> shape as the superior hemisphere of the <i>'Sphere'</i> shape of radius <code><i>'R'</i></code> and center <code><i>'(xc,yc,zc)'</i></code>, and all its points are expressed as follows:<p><pre>x(r,s) = xc + R * cos(r) * cos(s), y(r,s) = yc + R * sin(r), z(r,s) = zc + R * cos(r) * sin(s)</pre><p>for any <code><i>'R>0'</i></code>, for any <code><i>'r'</i></code> in <code><i>'[ 0, pi/2 ]'</i></code>, and for any <code><i>'s'</i></code> in <code><i>'[ 0, 2*pi ]'</i></code>.<p>Here, the <i>'Hemisphere'</i> shape is approximated by a quad grid, formed by <code><i>'p'</i></code> <i>'slices'</i> around the <i>Z</i>-axis (similar to the longitudinal lines) and by <code><i>'q'</i></code>  <i>'stacks'</i> along the <i>Z</i>-axis (similar to the latitudinal lines). Specifically, the <i>'wireframe versions'</i> of the elements in the quad grid (in <i>'blue'</i>) are rendered by using the perspective projection.<p>Here, the user cannot modify the radius <code><i>'R'</i></code>, and the center <code><i>'(xc,yc,zc)'</i></code>, since they are fixed in advance. Instead, the user can modify the numbers <code><i>'p'</i></code> and <code><i>'q'</i></code> of the longitudinal and the latitudinal slices, respectively, as well as rotate the scene along the coordinate axes. In particular the user can:<p><ul>
<li>increase the number <code><i>'p'</i></code> of the longitudinal slices by pressing the <code><i>'P'</i></code> key;</li>
<li>decrease the number <code><i>'p'</i></code> of the longitudinal slices by pressing the <code><i>'p'</i></code> key;</li>
<li>increase the number <code><i>'q'</i></code> of the latitudinal slices by pressing the <code><i>'Q'</i></code> key;</li>
<li>decrease the number <code><i>'q'</i></code> of the latitudinal slices by pressing the <code><i>'q'</i></code> key;</li>
<li>increase the rotation angle <code><i>'Rx'</i></code> along the <code><i>'x'</i></code>-axis by pressing the <code><i>'X'</i></code> key;</li>
<li>decrease the rotation angle <code><i>'Rx'</i></code> along the <code><i>'x'</i></code>-axis by pressing the <code><i>'x'</i></code> key;</li>
<li>increase the rotation angle <code><i>'Ry'</i></code> along the <code><i>'y'</i></code>-axis by pressing the <code><i>'Y'</i></code> key;</li>
<li>decrease the rotation angle <code><i>'Ry'</i></code> along the <code><i>'y'</i></code>-axis by pressing the <code><i>'y'</i></code> key;</li>
<li>increase the rotation angle <code><i>'Rz'</i></code> along the <code><i>'z'</i></code>-axis by pressing the <code><i>'Z'</i></code> key;</li>
<li>decrease the rotation angle <code><i>'Rz'</i></code> along the <code><i>'z'</i></code>-axis by pressing the <code><i>'z'</i></code> key.</li></ul><p>Likewise, the window of interest can be closed by pressing the <code><i>'Esc'</i></code> key.<p>

<p><table border=0 width=100%>
<tr>
<td width=50%><IMG style=float:middle src='http://davidcanino.github.io/img/shots_opengl/shot_example045_old_conf0.png' border='0'></td>
<td width=50%><IMG style=float:middle src='http://davidcanino.github.io/img/shots_opengl/shot_example045_old_conf1.png' border='0'></td></tr>
<tr>
<td width=50%>Here, the <i>'Hemisphere'</i> shape is approximated by a quad strip with <code><i>'q=3'</i></code> longitudinal slices and <code><i>'p=3'</i></code> latitudinal slices, and a<code><i>'Rx=45'</i></code>, <code><i>'Ry=25'</i></code>, and <code><i>'Rz=0'</i></code>.</td>
<td width=50%>Here, the <i>'Hemisphere'</i> shape is approximated by a quad strip with <code><i>'q=6'</i></code> longitudinal slices and <code><i>'p=3'</i></code> latitudinal slices, and <code><i>'Rx=45'</i></code>, <code><i>'Ry=25'</i></code>, and <code><i>'Rz=0'</i></code>.</td>
</tr>

<tr>
<td width=50%><IMG style=float:middle src='http://davidcanino.github.io/img/shots_opengl/shot_example045_old_conf2.png' border='0'></td>
<td width=50%><IMG style=float:middle src='http://davidcanino.github.io/img/shots_opengl/shot_example045_old_conf3.png' border='0'></td></tr>
<tr>
<td width=50%>Here, the <i>'Hemisphere'</i> shape is approximated by a quad strip with <code><i>'q=6'</i></code> longitudinal slices and <code><i>'p=24'</i></code> latitudinal slices, and <code><i>'Rx=45'</i></code>, <code><i>'Ry=25'</i></code>, and <code><i>'Rz=0'</i></code>.</td>
<td width=50%>Here, the <i>'Hemisphere'</i> shape is approximated by a quad strip with <code><i>'q=20'</i></code> longitudinal slices and <code><i>'p=24'</i></code> latitudinal slices, and <code><i>'Rx=45'</i></code>, <code><i>'Ry=25'</i></code>, and <code><i>'Rz=0'</i></code>.</td>
</tr>

<tr>
<td width=50%><IMG style=float:middle src='http://davidcanino.github.io/img/shots_opengl/shot_example045_old_conf4.png' border='0'></td>
<td width=50%><IMG style=float:middle src='http://davidcanino.github.io/img/shots_opengl/shot_example045_old_conf5.png' border='0'></td></tr>
<tr>
<td width=50%>Here, the <i>'Hemisphere'</i> shape is approximated by a quad strip with <code><i>'q=3'</i></code> longitudinal slices and <code><i>'p=3'</i></code> latitudinal slices, and <code><i>'Rx=270'</i></code>, <code><i>'Ry=0'</i></code>, and <code><i>'Rz=0'</i></code>.</td>
<td width=50%>Here, the <i>'Hemisphere'</i> shape is approximated by a quad strip with <code><i>'q=10'</i></code> longitudinal slices and <code><i>'p=10'</i></code> latitudinal slices, and <code><i>'Rx=270'</i></code>, <code><i>'Ry=0'</i></code>, and <code><i>'Rz=0'</i></code>.</td>
</tr>

</table>

<p><hr><p><h4>Dependencies</h4>

The <i>'Example-045 (Old Mode)'</i> Test is based on the so-called <i>OpenGL old (direct drawing) mode</i>, and requires the following dependencies:<ul>

<li>the <A href="http://www.opengl.org"><i>OpenGL</i></A> package, distributed with the platform of interest (see the <i><A href="https://www.khronos.org/opengl/wiki/Getting_Started">Official Documentation</A></i>);</li>
<li>the <i><A href="https://www.opengl.org/resources/libraries/glut/">OpenGL Utility Toolkit (GLUT)</A></i> package (or the <A href="http://freeglut.sourceforge.net/"><i>FreeGLUT</i></A> package);</li>
<li>the <A href="http://glew.sourceforge.net/"><i>OpenGL Extension Wrangler Library (GLEW)</i></A> package.</li></ul><p>In particular, this test consists of the <i>'Example-045-old'</i> executable file (directly in the <i><code>'bin'</code></i> folder, or in a specific subfolder of the <i><code>'bin'</code></i> folder), starting uniquely from the <i>'main.cpp'</i> C++ source file (in the <i><code>'src'</code></i> folder).<p>Several methods for building this test are provided, and their building infrastructure is saved in the following folders:<p><ul>
<li>the <i><code>'cmake'</code></i> folder contains the project file for the <i><A href="http://cmake.org">CMake Building Tool</A></i>;</li>
<li>the <i><code>'vstudio'</code></i> folder contains the solution file for the <i><A href="http://www.visualstudio.com/">Microsoft Visual Studio (Community Edition 2015)</A></i>;</li>
<li>the <i><code>'xcode'</code></i> folder contains the project file for the <i><A href="http://developer.apple.com/xcode/">Apple XCode</A></i>.</li></ul><br><table border=1><tr><td><p><b>ATTENTION:</b><p>The majority of the dependencies for this test are stable, but are currently deprecated, and several warning messages may appear during the building process.<p></td></tr></table><p><hr><p>

<h4>Instructions for building this test with the <i><A href="http://cmake.org">CMake Building Tool</A></i></h4>

This test is built by using the <i>classic</i> instructions for building a program with the <i><A href="http://cmake.org">CMake Building Tool</A></i> from the <i><code>'cmake\'</code></i> folder:
<pre>mkdir build
cd build
cmake ..
make
</pre><p>As mentioned above, the <i>'Example-045-old'</i> executable file is saved in (a specific subfolder of) the <i><code>'bin'</code></i> folder. For instance, this test is executed by running:<pre>./bin/Example-045-old</pre><p>This building method is tested with the <A href="http://gcc.gnu.org/"><i>GCC</i></A> under the Ubuntu Linux 16.0.4 (LTS), as well as with the <A href="http://clang.llvm.org/"><i>CLANG</i></A> compiler under the MacOsX 11.* El-Capitan (and higher), and the <A href="http://www.visualstudio.com/"><i>Microsoft Visual Studio (Community Edition 2015)</i></A> under the Microsoft Windows 10.<p>In this latter case, three custom projects are automatically generated, and ready to be open in the <A href="http://www.visualstudio.com/"><i>Microsoft Visual Studio (Community Edition 2015)</i></A>. The solution file of interest is the <i>'Example-045-old.sln'</i> solution file, which can be exploited without being modified. This test is built by clicking on the <i>'Build'</i> command. The resulting <i>'Example-045-old.exe'</i> executable file is stored in the <i><code>'bin\Debug'</code></i> folder, if the debugging symbols are included, or in the <i><code>'bin\Release'</code></i> folder, otherwise.<p>

All dependencies of the <i>'Example-045 (Old Mode)'</i> Test are supported automatically by the <i><A href="http://cmake.org">CMake Building Tool</A></i> through a built-in manifest file. In particular, they are often pre-installed in a generic GNU/Linux distribution, and distributed in conjunction with the <A href="http://developer.apple.com/xcode/"><i>Apple XCode</i></A>. Thus, they should be found by the script of interest without problems in these platforms.<p>Instead, these libraries are not standard in the Microsoft Windows, and must be installed properly. For the sake of simplicity, the Win32 versions for the auxiliary libraries of interest in the <i><code>'depends'</code></i> folder are exploited, if the <i><A href="http://cmake.org">CMake Building Tool</A></i> fails while performing their automatic identification. This means that the resulting solution file creates automatically the Win32 version of the <i>'Example-045-old.exe'</i> executable file.<p>An interested user finds more details about other possible customization options in the Official Documentation of the <i><A href="http://cmake.org">CMake Building Tool</A></i>.<p><hr><p>

<h4>Instructions for building this test with the <i><A href="http://www.visualstudio.com/">Microsoft Visual Studio (Community Edition 2015)</A></i></h4>

This test is also built by using the <A href="http://www.visualstudio.com/"><i>Microsoft Visual Studio (Community Edition 2015)</i></A>. In particular, the <i><code>'vstudio\'</code></i> folder contains the <i>'Example-045-old.sln'</i> solution file, which can be exploited without being modified. This test is built by clicking on the <i>'Build'</i> command. The resulting <i>'Example-045-old.exe'</i> executable file is stored in the <i><code>'Debug'</code></i> folder, if the debugging symbols are included, or in the <i><code>'Release'</code></i> folder, otherwise.

Note that this solution file is independently created from scratch, and is different from the solution file, which may be generated automatically by the <i><A href="http://cmake.org">CMake Building Tool</A></i>.

Specifically, the Win32 versions for the auxiliary libraries of interest in the <i><code>'depends\'</code></i> folder are exploited for building the <i>'Example-045 (Old Mode)'</i> Test. This implies that the <i>'Example-045-old.sln'</i> solution file is set up for including these auxiliary libraries, and it should not be modified, unless you are an expert. Furthermore, it is mandatory to enable the building for a generic Win32 platform for creating correctly the Win32 version of the <i>'Example-045-old.exe'</i> executable file.<p>An interested user finds more details in the Official Documentation of the <i><A href="http://www.visualstudio.com/">Microsoft Visual Studio (Community Edition 2015)</A></i>.<p><hr><p>

<h4>Instructions for building this test with the <i><A href="http://developer.apple.com/xcode/">Apple XCode</A></i></h4>

This test is also built by using the <A href="http://developer.apple.com/xcode/"><i>Apple XCode</i></A> (based on the <A href="http://clang.llvm.org/"><i>CLANG</i> compiler</A>) under the MacOsX 11.* El-Capitan (and higher). In particular, the <i><code>'xcode'</code></i> folder contains the <i>'Example-045-old.xcodeproj'</i> project file, which can be exploited without being modified. This test is built by clicking on the <i>'Build & Run'</i> command. The resulting <i>'Example-045-old'</i> executable file is stored in the <i><code>'Build/Products/Debug/'</code></i> folder, if the debugging symbols are included, or in the <i><code>'Build/Products/Release/'</code></i> folder, otherwise.<p>

Note that this project file is independently created from scratch, and is different from the project file, which may be generated automatically by the <i><A href="http://cmake.org">CMake Building Tool</A></i>.<p>

Specifically, this project file includes the versions (frameworks) of the <A href="http://www.opengl.org"><i>OpenGL</i></A> and of the <i><A href="https://www.opengl.org/resources/libraries/glut/">OpenGL Utility Toolkit (GLUT)</A></i> packages, that are distributed in conjunction with the <A href="http://developer.apple.com/xcode/"><i>Apple XCode</i></A>. Instead, the headers and the library files of the <A href="http://glew.sourceforge.net/"><i>OpenGL Extension Wrangler Library (GLEW)</i></A> are assumed to be stored in the <i><code>'/usr/local/include/'</code></i> and the <i><code>'/usr/local/lib/'</code></i> folders, respectively. This implies that the <i>'Example-045-old.xcodeproj'</i> project file is set up for including these auxiliary libraries, and it should not be modified, unless you are an expert.<p>An interested user finds more details in the Official Documentation of the <A href="http://developer.apple.com/xcode/"><i>Apple XCode</i></A>.<p><hr><p><table border=1><tr><td><p><b>ATTENTION:</b><p>This test is not related officially to the <i><A href="https://www.khronos.org/">Khronos Group</A></i>. All trademarks or registered trademarks are the property of their respective owners.</td></tr></table>