<A href="http://www.opengl.org"><IMG src='https://www.khronos.org/assets/images/api_logos/opengl.png' border=0 width="180" height="97"></A>

<H3>The <i>'Example-050 (Old Mode)'</i> Test</H3>

The <i>'Example-050 (Old Mode)'</i> Test draws the <i>'Playground Slide'</i> shape in an <A href="http://www.opengl.org"><i>OpenGL</i></A> window. Intuitively, this shape describes the classical playground slides, that can be found in parks, schools, playgrounds, and backyards. A slide may be flat or (more often) half cylindrical, in order to prevent falls. Slides are usually constructed of plastic or metal, and they have a smooth surface, which is either straight or wavy. The user, typically a child, climbs to the top of the slide via a ladder or stairs, sits down on the top of the slide, and slides down the chute.<p>In this case, we try to model this physical object by considering a parabolic profile to be extruded. A parabolic profile is a portion of the <i>'Parabola'</i> curve, defined as follows:<p><pre>x(t) = t, y(t) = a * t ^ 2 + b * t + c</pre><p>for any not null <code><i>'a'</i></code>, and for every <code><i>'t'</i></code>. The parameters <code><i>'a'</i>, <i>'b'</i></code>, and <code><i>'c'</i></code> determine the properties of the <i>'Parabola'</i> curve.<p>Here, we limit our attention to every <code><i>'t'</i></code> in a given range in order to obtain a parabolic profile, which is extruded along the <code><i>'z'</i></code>-axis in order to obtain the slide of interest (specifically a curvilinear <code><i>'2D'</i></code> shape). In order to obtain a <code><i>'3D'</i></code> solid, we also consider <code><i>'2'</i></code> lateral surfaces, bounded by the parabolic profiles and by the <code><i>'xz'</i></code> coordinate plane, as well as <code><i>'2'</i></code> quadrilaterals, that are the frontward and the backward sides of the solid, plus another quadrilateral, which is the bottom basis in the <code><i>'xz'</i></code> coordinate plane. Broadly speaking, the <i>'Playground Slide'</i> shape is the <code><i>'2D'</i></code> shape, bounding this <code><i>'3D'</i></code> solid.<p>The parabolic profile of interest is approximated by a polyline with <code><i>'n'</i></code> vertices and edges. This implies that each lateral side as well as the bottom basis of the <i>'Playgrond Slide'</i> shape can be approximated by a quad strip. Instead, the frontward and the backward sides of the <i>'Playground Slide'</i> shape are simply quadrilaterals. By construction, it is possible to merge these grids into a unique quad grid. Specifically, the <i>'wireframe versions'</i> of the quadrilaterals in this quad grid (in <i>'blue'</i>) are rendered by using the perspective projection.<p>In this test, the user cannot modify the parameters of the parabolic profile to be extruded (like the parabola equation and the position), as well as the extrusion parameters for the <i>'Playground Slide'</i> shape of interest, since they are fixed in advance. Instead, the user can modify the number <code><i>'n'</i></code> of the samples in the parabolic profile, as well as rotate the scene along the coordinate axes. In particular the user can:<p><ul>
<li>increase the number <code><i>'n'</i></code> of the samples by pressing the <code><i>'+'</i></code> key;</li>
<li>decrease the number <code><i>'n'</i></code> of the samples by pressing the <code><i>'-'</i></code> key;</li>
<li>increase the rotation angle <code><i>'Rx'</i></code> along the <code><i>'x'</i></code>-axis by pressing the <code><i>'X'</i></code> key;</li>
<li>decrease the rotation angle <code><i>'Rx'</i></code> along the <code><i>'x'</i></code>-axis by pressing the <code><i>'x'</i></code> key;</li>
<li>increase the rotation angle <code><i>'Ry'</i></code> along the <code><i>'y'</i></code>-axis by pressing the <code><i>'Y'</i></code> key;</li>
<li>decrease the rotation angle <code><i>'Ry'</i></code> along the <code><i>'y'</i></code>-axis by pressing the <code><i>'y'</i></code> key;</li>
<li>increase the rotation angle <code><i>'Rz'</i></code> along the <code><i>'z'</i></code>-axis by pressing the <code><i>'Z'</i></code> key;</li>
<li>decrease the rotation angle <code><i>'Rz'</i></code> along the <code><i>'z'</i></code>-axis by pressing the <code><i>'z'</i></code> key.</li></ul><p>Likewise, the window of interest can be closed by pressing any among the <code><i>'Q'</i></code>, the <code><i>'q'</i></code>, and the <code><i>'Esc'</i></code> keys.
<p><table border=0 width=100%>

<tr>
<td width=50%><IMG style=float:middle src='http://davidcanino.github.io/img/shots_opengl/shot_example050_old_conf0.png' border='0'></td>
<td width=50%><IMG style=float:middle src='http://davidcanino.github.io/img/shots_opengl/shot_example050_old_conf1.png' border='0'></td></tr>
<tr>
<td width=50%>The <i>'wireframe'</i> version for the <i>'Playground Slide'</i> shape of interest is approximated by extruding a parabolic profile with <code><i>'n=3'</i></code> samples, and rotation angles <code><i>'Rx=10'</i></code>, <code><i>'Ry=0'</i></code>, and <code><i>'Rz=0'</i></code>.</td>
<td width=50%>The <i>'wireframe'</i> version for the <i>'Playground Slide'</i> shape of interest is approximated by extruding a parabolic profile with <code><i>'n=3'</i></code> samples, and rotation angles <code><i>'Rx=10'</i></code>, <code><i>'Ry=335'</i></code>, and <code><i>'Rz=0'</i></code>.</td>
</tr>

<tr>
<td width=50%><IMG style=float:middle src='http://davidcanino.github.io/img/shots_opengl/shot_example050_old_conf2.png' border='0'></td>
<td width=50%><IMG style=float:middle src='http://davidcanino.github.io/img/shots_opengl/shot_example050_old_conf3.png' border='0'></td></tr>
<tr>
<td width=50%>The <i>'wireframe'</i> version for the <i>'Playground Slide'</i> shape of interest is approximated by extruding a parabolic profile with <code><i>'n=8'</i></code> samples, and rotation angles <code><i>'Rx=10'</i></code>, <code><i>'Ry=355'</i></code>, and <code><i>'Rz=0'</i></code>.</td>
<td width=50%>The <i>'wireframe'</i> version for the <i>'Playground Slide'</i> shape of interest is approximated by extruding a parabolic profile with <code><i>'n=8'</i></code> samples, and rotation angles <code><i>'Rx=10'</i></code>, <code><i>'Ry=20'</i></code>, and <code><i>'Rz=0'</i></code>.</td>
</tr>

<tr>
<td width=50%><IMG style=float:middle src='http://davidcanino.github.io/img/shots_opengl/shot_example050_old_conf4.png' border='0'></td>
<td width=50%><IMG style=float:middle src='http://davidcanino.github.io/img/shots_opengl/shot_example050_old_conf5.png' border='0'></td></tr>
<tr>
<td width=50%>The <i>'wireframe'</i> version for the <i>'Playground Slide'</i> shape of interest is approximated by extruding a parabolic profile with <code><i>'n=15'</i></code> samples, and rotation angles <code><i>'Rx=25'</i></code>, <code><i>'Ry=325'</i></code>, and <code><i>'Rz=355'</i></code>.</td>
<td width=50%>The <i>'wireframe'</i> version for the <i>'Playground Slide'</i> shape of interest is approximated by extruding a parabolic profile with <code><i>'n=15'</i></code> samples, and rotation angles <code><i>'Rx=335'</i></code>, <code><i>'Ry=180'</i></code>, and <code><i>'Rz=0'</i></code>.</td>
</tr>

<tr>
<td width=50%><IMG style=float:middle src='http://davidcanino.github.io/img/shots_opengl/shot_example050_old_conf6.png' border='0'></td>
<td width=50%><IMG style=float:middle src='http://davidcanino.github.io/img/shots_opengl/shot_example050_old_conf7.png' border='0'></td></tr>
<tr>
<td width=50%>The <i>'wireframe'</i> version for the <i>'Playground Slide'</i> shape of interest is approximated by extruding a parabolic profile with <code><i>'n=15'</i></code> samples, and rotation angles <code><i>'Rx=350'</i></code>, <code><i>'Ry=175'</i></code>, and <code><i>'Rz=165'</i></code>.</td>
<td width=50%>The <i>'wireframe'</i> version for the <i>'Playground Slide'</i> shape of interest is approximated by extruding a parabolic profile with <code><i>'n=8'</i></code> samples, and rotation angles <code><i>'Rx=290'</i></code>, <code><i>'Ry=180'</i></code>, and <code><i>'Rz=0'</i></code>.</td>
</tr>

</table>
<p><hr><p><h4>Dependencies</h4>

The <i>'Example-050 (Old Mode)'</i> Test is based on the so-called <i>OpenGL old (direct drawing) mode</i>, and requires the following dependencies:<ul>

<li>the <A href="http://www.opengl.org"><i>OpenGL</i></A> package, distributed with the platform of interest (see the <i><A href="https://www.khronos.org/opengl/wiki/Getting_Started">Official Documentation</A></i>);</li>
<li>the <i><A href="https://www.opengl.org/resources/libraries/glut/">OpenGL Utility Toolkit (GLUT)</A></i> package (or the <A href="http://freeglut.sourceforge.net/"><i>FreeGLUT</i></A> package);</li>
<li>the <A href="http://glew.sourceforge.net/"><i>OpenGL Extension Wrangler Library (GLEW)</i></A> package.</li></ul><p>In particular, this test consists of the <i>'Example-050-old'</i> executable file (directly in the <i><code>'bin'</code></i> folder, or in a specific subfolder of the <i><code>'bin'</code></i> folder), starting uniquely from the <i>'main.cpp'</i> C++ source file (in the <i><code>'src'</code></i> folder).<p>Several methods for building this test are provided, and their building infrastructure is saved in the following folders:<p><ul>
<li>the <i><code>'cmake'</code></i> folder contains the project file for the <i><A href="http://cmake.org">CMake Building Tool</A></i>;</li>
<li>the <i><code>'vstudio'</code></i> folder contains the solution file for the <i><A href="http://www.visualstudio.com/">Microsoft Visual Studio (Community Edition 2015)</A></i>;</li>
<li>the <i><code>'xcode'</code></i> folder contains the project file for the <i><A href="http://developer.apple.com/xcode/">Apple XCode</A></i>.</li></ul><br><table border=1><tr><td><p><b>ATTENTION:</b><p>The majority of the dependencies for this test are stable, but are currently deprecated, and several warning messages may appear during the building process.<p></td></tr></table><p><hr><p>

<h4>Instructions for building this test with the <i><A href="http://cmake.org">CMake Building Tool</A></i></h4>

This test is built by using the <i>classic</i> instructions for building a program with the <i><A href="http://cmake.org">CMake Building Tool</A></i> from the <i><code>'cmake\'</code></i> folder:
<pre>mkdir build
cd build
cmake ..
make
</pre><p>As mentioned above, the <i>'Example-050-old'</i> executable file is saved in (a specific subfolder of) the <i><code>'bin'</code></i> folder. For instance, this test is executed by running:<pre>./bin/Example-050-old</pre><p>This building method is tested with the <A href="http://gcc.gnu.org/"><i>GCC</i></A> under the Ubuntu Linux 16.0.4 (LTS), as well as with the <A href="http://clang.llvm.org/"><i>CLANG</i></A> compiler under the MacOsX 11.* El-Capitan (and higher), and the <A href="http://www.visualstudio.com/"><i>Microsoft Visual Studio (Community Edition 2015)</i></A> under the Microsoft Windows 10.<p>In this latter case, three custom projects are automatically generated, and ready to be open in the <A href="http://www.visualstudio.com/"><i>Microsoft Visual Studio (Community Edition 2015)</i></A>. The solution file of interest is the <i>'Example-050-old.sln'</i> solution file, which can be exploited without being modified. This test is built by clicking on the <i>'Build'</i> command. The resulting <i>'Example-050-old.exe'</i> executable file is stored in the <i><code>'bin\Debug'</code></i> folder, if the debugging symbols are included, or in the <i><code>'bin\Release'</code></i> folder, otherwise.<p>

All dependencies of the <i>'Example-050 (Old Mode)'</i> Test are supported automatically by the <i><A href="http://cmake.org">CMake Building Tool</A></i> through a built-in manifest file. In particular, they are often pre-installed in a generic GNU/Linux distribution, and distributed in conjunction with the <A href="http://developer.apple.com/xcode/"><i>Apple XCode</i></A>. Thus, they should be found by the script of interest without problems in these platforms.<p>Instead, these libraries are not standard in the Microsoft Windows, and must be installed properly. For the sake of simplicity, the Win32 versions for the auxiliary libraries of interest in the <i><code>'depends'</code></i> folder are exploited, if the <i><A href="http://cmake.org">CMake Building Tool</A></i> fails while performing their automatic identification. This means that the resulting solution file creates automatically the Win32 version of the <i>'Example-050-old.exe'</i> executable file.<p>An interested user finds more details about other possible customization options in the Official Documentation of the <i><A href="http://cmake.org">CMake Building Tool</A></i>.<p><hr><p>

<h4>Instructions for building this test with the <i><A href="http://www.visualstudio.com/">Microsoft Visual Studio (Community Edition 2015)</A></i></h4>

This test is also built by using the <A href="http://www.visualstudio.com/"><i>Microsoft Visual Studio (Community Edition 2015)</i></A>. In particular, the <i><code>'vstudio\'</code></i> folder contains the <i>'Example-050-old.sln'</i> solution file, which can be exploited without being modified. This test is built by clicking on the <i>'Build'</i> command. The resulting <i>'Example-050-old.exe'</i> executable file is stored in the <i><code>'Debug'</code></i> folder, if the debugging symbols are included, or in the <i><code>'Release'</code></i> folder, otherwise.

Note that this solution file is independently created from scratch, and is different from the solution file, which may be generated automatically by the <i><A href="http://cmake.org">CMake Building Tool</A></i>.

Specifically, the Win32 versions for the auxiliary libraries of interest in the <i><code>'depends\'</code></i> folder are exploited for building the <i>'Example-050 (Old Mode)'</i> Test. This implies that the <i>'Example-050-old.sln'</i> solution file is set up for including these auxiliary libraries, and it should not be modified, unless you are an expert. Furthermore, it is mandatory to enable the building for a generic Win32 platform for creating correctly the Win32 version of the <i>'Example-050-old.exe'</i> executable file.<p>An interested user finds more details in the Official Documentation of the <i><A href="http://www.visualstudio.com/">Microsoft Visual Studio (Community Edition 2015)</A></i>.<p><hr><p>

<h4>Instructions for building this test with the <i><A href="http://developer.apple.com/xcode/">Apple XCode</A></i></h4>

This test is also built by using the <A href="http://developer.apple.com/xcode/"><i>Apple XCode</i></A> (based on the <A href="http://clang.llvm.org/"><i>CLANG</i> compiler</A>) under the MacOsX 11.* El-Capitan (and higher). In particular, the <i><code>'xcode'</code></i> folder contains the <i>'Example-050-old.xcodeproj'</i> project file, which can be exploited without being modified. This test is built by clicking on the <i>'Build & Run'</i> command. The resulting <i>'Example-050-old'</i> executable file is stored in the <i><code>'Build/Products/Debug/'</code></i> folder, if the debugging symbols are included, or in the <i><code>'Build/Products/Release/'</code></i> folder, otherwise.<p>

Note that this project file is independently created from scratch, and is different from the project file, which may be generated automatically by the <i><A href="http://cmake.org">CMake Building Tool</A></i>.<p>

Specifically, this project file includes the versions (frameworks) of the <A href="http://www.opengl.org"><i>OpenGL</i></A> and of the <i><A href="https://www.opengl.org/resources/libraries/glut/">OpenGL Utility Toolkit (GLUT)</A></i> packages, that are distributed in conjunction with the <A href="http://developer.apple.com/xcode/"><i>Apple XCode</i></A>. Instead, the headers and the library files of the <A href="http://glew.sourceforge.net/"><i>OpenGL Extension Wrangler Library (GLEW)</i></A> are assumed to be stored in the <i><code>'/usr/local/include/'</code></i> and the <i><code>'/usr/local/lib/'</code></i> folders, respectively. This implies that the <i>'Example-050-old.xcodeproj'</i> project file is set up for including these auxiliary libraries, and it should not be modified, unless you are an expert.<p>An interested user finds more details in the Official Documentation of the <A href="http://developer.apple.com/xcode/"><i>Apple XCode</i></A>.<p><hr><p><table border=1><tr><td><p><b>ATTENTION:</b><p>This test is not related officially to the <i><A href="https://www.khronos.org/">Khronos Group</A></i>. All trademarks or registered trademarks are the property of their respective owners.</td></tr></table>
