<A href="http://www.opengl.org"><IMG src='https://www.khronos.org/assets/images/api_logos/opengl.png' border=0 width="180" height="97"></A>

<H3>The <i>'Example-031 (Old Mode)'</i> Test</H3>

The <i>'Example-031 (Old Mode)'</i> Test draws <code>'3'</code> variants of the <i>'Circular Annulus'</i> shape with <i>'inner'</i> radius <code><i>'rI'</i></code>, <i>'outer'</i> radius <code><i>'rE'</i></code>, and center <code><i>'(xc,yc)'</i></code> in an <A href="http://www.opengl.org"><i>OpenGL</i></A> window. The <i>'Circular Annulus'</i> shape is defined as follows:<p><pre>| rI * cos(t) | <= | x(t) - xc | <= | rE * cos(t) |, | rI * sin(t) | <= | y(t) - yc | <= | rE * sin(t) |</pre><p>for every <code><i>'t'</i></code> in <code><i>'[-pi,pi]'</i></code>, and for any <code><i>'rI>0'</i></code> and <code><i>'rE>0'</i></code>, such that <code><i>'rI<rE'</i>.</code><p>In other words, it is formed by all points in the circular crown, bounded by <code>'2'</code> (concentric) <i>'Circle'</i> shapes (disks) of the same center <code><i>'(xc,yc)'</i></code> and of radius <code><i>'rI'</i></code> and <code><i>'rE'</i></code>, respectively. The disk of radius <code><i>'rE'</i></code> is the <i>'outer'</i> disk, and the disk of radius <code><i>'rI'</i></code> is the <i>'inner'</i> disk.<p>Specifically, this test draws the following variants of the <i>'Circular Annulus'</i> shape:<p><ol start='0'>
<li>the <i>'Variant #0'</i> of the <i>'Circular Annulus'</i> shape exploits <code><i>'2'</i></code> triangle fans, formed by <code><i>'n>4'</i></code> vertices (including their <i>'reference vertices'</i>). By construction, it is not possible to have <code><i>'n<5'</i></code>. Broadly speaking, <code><i>'2'</i></code> triangle fans describe, respectively, the <i>'inner'</i> disk (in <i>'blue'</i>) and the <i>'outer'</i> disk (in <i>'red'</i>) at different z-depth. These disks are described by the <i>'Circle'</i> shape, and are drawn by using the orthographic projection, such that their <i>'reference vertices'</i> are projected on the same point. Here, the user can choose to modify the rendering order of the <i>'inner'</i> and the <i>'outer'</i> disks by obtaining the following configurations:<p><ul>
<li>the <i>'Configuration #0'</i>, where the <i>'inner'</i> disk is rendered after the <i>'outer'</i> disk. Here, both the disks are visible.</li>
<li>The <i>'Configuration #1'</i>, where the <i>'inner'</i> disk is rendered before the <i>'outer'</i> disk. Here, only the <i>'outer'</i> disk is visible, and hides the other disk.</li></ul><p>It is clear that only the <i>'Configuration #0'</i> seems to coincide with the <i>'Circular Annulus'</i> shape. In any case, any of these configurations for the <i>'Variant #0'</i> are not <i>'real'</i> approximations of the <i>'Circular Annulus'</i> shape.<p></li>
<li>The <i>'Variant #1'</i> of the <i>'Circular Annulus'</i> shape is defined in the same spirit of the <i>'Variant #0'</i>, but the z-buffer (depth test) technique is exploited here for rendering <code><i>'2'</i></code> disks of interest. Also in this case, each of them is approximated by <code><i>'2'</i></code> triangle fans with <code><i>'n>4'</i></code> vertices, including their <i>'reference vertices'</i>, and it is not possible to have <code><i>'n<5'</i></code>. Thus, the resulting scene does not depend on the rendering order of <code><i>'2'</i></code> disks, and is only <i>'the same as'</i> the <i>'Configuration #0'</i> for the <i>'Variant #0'</i> of the <i>'Circular Annulus'</i> shape.<p></li>
<li>The <i>'Variant #2'</i> of the <i>'Circular Annulus'</i> shape is defined by only one triangle strip, formed by <code><i>'m=n-1'</i></code> pairs of the corresponding vertices (thus <code><i>'2*n-2'</i></code> vertices) in the <i>'inner'</i> and the <i>'outer'</i> circles, respectively. These curves approximate the boundary of the <i>'Circular Annulus'</i> shape. Broadly speaking, we consider the orthographic projections of all <code><i>'n>4'</i></code> vertices in the <i>'Variant #0'</i> (or also in the <i>'Variant #1'</i>) of the <i>'Circular Annulus'</i> shape, excepting their <i>'reference vertices'</i>. By construction, it is not possible to have <code><i>'n<5'</i></code>, thus to have <code><i>'m<4'.</i></code> In any case, note that the triangle strip of interest is planar, and is a <i>'real'</i> approximation of the <i>'Circular Annulus'</i> shape.<p></li></ol><p>Each variant of the <i>'Circular Annulus'</i> shape is accompanied by an explicative label. Thus, this test also shows how writing and rendering some text in an <A href="http://www.opengl.org"><i>OpenGL</i></A> window.<p>Here, the user cannot modify the radii and the centers for <code>'3'</code> variants of the <i>'Circular Annulus'</i> shape, since they are fixed in advance. Instead, the user can:<p><ul>
<li>choose to render either the <i>'wireframe'</i> or the <i>'filled versions'</i> for all triangles of interest by pressing cyclically the <code><i>' '</i></code> (space) key;</li>
<li>choose to exploit any of <code><i>'2'</i></code> rendering orders for the triangles fans of interest (disks) in the <i>'Variant #0'</i> of the <i>'Circular Annulus'</i> shape by pressing cyclically the <code><i>'o'</i></code> key;</li>
<li>increase the number <code><i>'n'</i></code> of the vertices in the triangle fans (including their <i>'reference vertices'</i>), thus also the number <code><i>'m=n-1'</i></code> of the vertices pairs in the triangle strip, by pressing the <code><i>'+'</i></code> key. By construction, it is not possible to have <code><i>'n<5'</i></code>, thus to have <code><i>'m<4'.</i></code></li>
<li>Decrease the number <code><i>'n'</i></code> of the vertices in the triangle fans (including their <i>'reference vertices'</i>), thus also the number <code><i>'m=n-1' </i></code> of the vertices cout<<"pairs in the triangle strip, by pressing the <code><i>'-'</i></code> key. By construction, it is not possible to have <code><i>'n<5'</i></code>, thus to have <code><i>'m<4'.</i></code></li></ul><p>Likewise, the window of interest can be closed by pressing any among the <code><i>'Q'</i></code>, the <code><i>'q'</i></code>, and the <code><i>'Esc'</i></code> keys.<p><table border=0 width=100%><tr>
<td width=50%><IMG style=float:middle src='http://davidcanino.github.io/img/shots_opengl/shot_example031_old_conf0.png' border='1' width="800" height="500"></td>
<td width=50%><IMG style=float:middle src='http://davidcanino.github.io/img/shots_opengl/shot_example031_old_conf1.png' border='1' width="800" height="500"></td></tr>
<tr><td>Here, the <i>'wireframe versions'</i> of all triangles in the triangle fans (with <code><i>'n=5'</i></code> vertices) and in the triangle strip (with <code><i>'m=4'</i></code> vertices pairs) of interest are drawn. The <i>'Configuration #0'</i> for the <i>'Variant #0'</i> is considered.</td>


</tr><tr>
<td width=50%><IMG style=float:middle src='http://davidcanino.github.io/img/shots_opengl/shot_example031_old_conf2.png' border='1' width="800" height="500"></td>
<td width=50%><IMG style=float:middle src='http://davidcanino.github.io/img/shots_opengl/shot_example031_old_conf3.png' border='1' width="800" height="500"></td></tr>
<tr><td> 

</td>

<td>

</td></tr>
<tr>
<td width=50%><IMG style=float:middle src='http://davidcanino.github.io/img/shots_opengl/shot_example031_old_conf4.png' border='1' width="800" height="500"></td>
<td width=50%><IMG style=float:middle src='http://davidcanino.github.io/img/shots_opengl/shot_example031_old_conf5.png' border='1' width="800" height="500"></td></tr>
<tr><td>

</td><td>

</td></tr><tr>
<tr>
<td width=50%><IMG style=float:middle src='http://davidcanino.github.io/img/shots_opengl/shot_example031_old_conf6.png' border='1' width="800" height="500"></td>
<td width=50%><IMG style=float:middle src='http://davidcanino.github.io/img/shots_opengl/shot_example031_old_conf7.png' border='1' width="800" height="500"></td></tr>
<tr><td>

</td><td>

</td></tr><tr></table><p><hr><p>

<h4>Dependencies</h4>

The <i>'Example-031 (Old Mode)'</i> Test is based on the so-called <i>OpenGL old (direct drawing) mode</i>, and requires the following dependencies:<ul>

<li>the <A href="http://www.opengl.org"><i>OpenGL</i></A> package, distributed with the platform of interest (see the <i><A href="https://www.khronos.org/opengl/wiki/Getting_Started">Official Documentation</A></i>);</li>
<li>the <i><A href="https://www.opengl.org/resources/libraries/glut/">OpenGL Utility Toolkit (GLUT)</A></i> package (or the <A href="http://freeglut.sourceforge.net/"><i>FreeGLUT</i></A> package);</li>
<li>the <A href="http://glew.sourceforge.net/"><i>OpenGL Extension Wrangler Library (GLEW)</i></A> package.</li></ul><p>In particular, this test consists of the <i>'Example-031-old'</i> executable file (directly in the <i><code>'bin'</code></i> folder, or in a specific subfolder of the <i><code>'bin'</code></i> folder), starting uniquely from the <i>'main.cpp'</i> C++ source file (in the <i><code>'src'</code></i> folder).<p>Several methods for building this test are provided, and their building infrastructure is saved in the following folders:<p><ul>
<li>the <i><code>'cmake'</code></i> folder contains the project file for the <i><A href="http://cmake.org">CMake Building Tool</A></i>;</li>
<li>the <i><code>'vstudio'</code></i> folder contains the solution file for the <i><A href="http://www.visualstudio.com/">Microsoft Visual Studio (Community Edition 2015)</A></i>;</li>
<li>the <i><code>'xcode'</code></i> folder contains the project file for the <i><A href="http://developer.apple.com/xcode/">Apple XCode</A></i>.</li></ul><br><table border=1><tr><td><p><b>ATTENTION:</b><p>The majority of the dependencies for this test are stable, but are currently deprecated, and several warning messages may appear during the building process.<p></td></tr></table><p><hr><p>

<h4>Instructions for building this test with the <i><A href="http://cmake.org">CMake Building Tool</A></i></h4>

This test is built by using the <i>classic</i> instructions for building a program with the <i><A href="http://cmake.org">CMake Building Tool</A></i> from the <i><code>'cmake\'</code></i> folder:
<pre>mkdir build
cd build
cmake ..
make
</pre><p>As mentioned above, the <i>'Example-031-old'</i> executable file is saved in (a specific subfolder of) the <i><code>'bin'</code></i> folder. For instance, this test is executed by running:<pre>./bin/Example-031-old</pre><p>This building method is tested with the <A href="http://gcc.gnu.org/"><i>GCC</i></A> under the Ubuntu Linux 16.0.4 (LTS), as well as with the <A href="http://clang.llvm.org/"><i>CLANG</i></A> compiler under the MacOsX 11.* El-Capitan (and higher), and the <A href="http://www.visualstudio.com/"><i>Microsoft Visual Studio (Community Edition 2015)</i></A> under the Microsoft Windows 10.<p>In this latter case, three custom projects are automatically generated, and ready to be open in the <A href="http://www.visualstudio.com/"><i>Microsoft Visual Studio (Community Edition 2015)</i></A>. The solution file of interest is the <i>'Example-031-old.sln'</i> solution file, which can be exploited without being modified. This test is built by clicking on the <i>'Build'</i> command. The resulting <i>'Example-031-old.exe'</i> executable file is stored in the <i><code>'bin\Debug'</code></i> folder, if the debugging symbols are included, or in the <i><code>'bin\Release'</code></i> folder, otherwise.<p>

All dependencies of the <i>'Example-031 (Old Mode)'</i> Test are supported automatically by the <i><A href="http://cmake.org">CMake Building Tool</A></i> through a built-in manifest file. In particular, they are often pre-installed in a generic GNU/Linux distribution, and distributed in conjunction with the <A href="http://developer.apple.com/xcode/"><i>Apple XCode</i></A>. Thus, they should be found by the script of interest without problems in these platforms.<p>Instead, these libraries are not standard in the Microsoft Windows, and must be installed properly. For the sake of simplicity, the Win32 versions for the auxiliary libraries of interest in the <i><code>'depends'</code></i> folder are exploited, if the <i><A href="http://cmake.org">CMake Building Tool</A></i> fails while performing their automatic identification. This means that the resulting solution file creates automatically the Win32 version of the <i>'Example-031-old.exe'</i> executable file.<p>An interested user finds more details about other possible customization options in the Official Documentation of the <i><A href="http://cmake.org">CMake Building Tool</A></i>.<p><hr><p>

<h4>Instructions for building this test with the <i><A href="http://www.visualstudio.com/">Microsoft Visual Studio (Community Edition 2015)</A></i></h4>

This test is also built by using the <A href="http://www.visualstudio.com/"><i>Microsoft Visual Studio (Community Edition 2015)</i></A>. In particular, the <i><code>'vstudio\'</code></i> folder contains the <i>'Example-031-old.sln'</i> solution file, which can be exploited without being modified. This test is built by clicking on the <i>'Build'</i> command. The resulting <i>'Example-031-old.exe'</i> executable file is stored in the <i><code>'Debug'</code></i> folder, if the debugging symbols are included, or in the <i><code>'Release'</code></i> folder, otherwise.

Note that this solution file is independently created from scratch, and is different from the solution file, which may be generated automatically by the <i><A href="http://cmake.org">CMake Building Tool</A></i>.

Specifically, the Win32 versions for the auxiliary libraries of interest in the <i><code>'depends\'</code></i> folder are exploited for building the <i>'Example-031 (Old Mode)'</i> Test. This implies that the <i>'Example-031-old.sln'</i> solution file is set up for including these auxiliary libraries, and it should not be modified, unless you are an expert. Furthermore, it is mandatory to enable the building for a generic Win32 platform for creating correctly the Win32 version of the <i>'Example-031-old.exe'</i> executable file.<p>An interested user finds more details in the Official Documentation of the <i><A href="http://www.visualstudio.com/">Microsoft Visual Studio (Community Edition 2015)</A></i>.<p><hr><p>

<h4>Instructions for building this test with the <i><A href="http://developer.apple.com/xcode/">Apple XCode</A></i></h4>

This test is also built by using the <A href="http://developer.apple.com/xcode/"><i>Apple XCode</i></A> (based on the <A href="http://clang.llvm.org/"><i>CLANG</i> compiler</A>) under the MacOsX 11.* El-Capitan (and higher). In particular, the <i><code>'xcode'</code></i> folder contains the <i>'Example-031-old.xcodeproj'</i> project file, which can be exploited without being modified. This test is built by clicking on the <i>'Build & Run'</i> command. The resulting <i>'Example-031-old'</i> executable file is stored in the <i><code>'Build/Products/Debug/'</code></i> folder, if the debugging symbols are included, or in the <i><code>'Build/Products/Release/'</code></i> folder, otherwise.<p>

Note that this project file is independently created from scratch, and is different from the project file, which may be generated automatically by the <i><A href="http://cmake.org">CMake Building Tool</A></i>.<p>

Specifically, this project file includes the versions (frameworks) of the <A href="http://www.opengl.org"><i>OpenGL</i></A> and of the <i><A href="https://www.opengl.org/resources/libraries/glut/">OpenGL Utility Toolkit (GLUT)</A></i> packages, that are distributed in conjunction with the <A href="http://developer.apple.com/xcode/"><i>Apple XCode</i></A>. Instead, the headers and the library files of the <A href="http://glew.sourceforge.net/"><i>OpenGL Extension Wrangler Library (GLEW)</i></A> are assumed to be stored in the <i><code>'/usr/local/include/'</code></i> and the <i><code>'/usr/local/lib/'</code></i> folders, respectively. This implies that the <i>'Example-031-old.xcodeproj'</i> project file is set up for including these auxiliary libraries, and it should not be modified, unless you are an expert.<p>An interested user finds more details in the Official Documentation of the <A href="http://developer.apple.com/xcode/"><i>Apple XCode</i></A>.<p><hr><p><table border=1><tr><td><p><b>ATTENTION:</b><p>This test is not related officially to the <i><A href="https://www.khronos.org/">Khronos Group</A></i>. All trademarks or registered trademarks are the property of their respective owners.</td></tr></table>
