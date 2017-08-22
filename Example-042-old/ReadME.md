<A href="http://www.opengl.org"><IMG src='https://www.khronos.org/assets/images/api_logos/opengl.png' border=0 width="180" height="97"></A>

<H3>The <i>'Example-042 (Old Mode)'</i> Test</H3>

The <i>'Example-042 (Old Mode)'</i> Test draws several views of the <i>'Cone'</i> shape in an <A href="http://www.opengl.org"><i>OpenGL</i></A> window by using the rendering settings, chosen interactively by the user. Broadly speaking, the <i>'Cone'</i> shape tapers smoothly from a flat base (often, but not necessarily, described by a <i>'Circle'</i> shape) to a given point, called the <i>'apex'</i> or the <i>'vertex'</i>. In other words, the <i>'Cone'</i> shape is formed by a collection of lines, connecting the <i>'apex'</i> to all of the points on a base, which does not contain the <i>'apex'</i>. The <i>'axis'</i> of the <i>'Cone'</i> shape is the line, passing through the <i>'apex'</i>, about which the <i>'Cone'</i> shape has a circular symmetry.<p>Here, we limit our attention to a <i>'Cone'</i>, where the basis is described by a <i>'Circle'</i> shape of radius <code><i>'R=35'</i></code>, and the point <code><i>'(0,70,0)'</i></code> as the <i>'apex'</i> of the <i>'Cone'</i> shape. The <i>'Cone'</i> shape of interest is open, thus we consider only the boundary of the <i>'Circle'</i> shape, described by the <i>'Circle'</i> curve.<p>In this case, the <i>'Cone'</i> shape of interest is described by a triangle fan (in <i>'red'</i>) with <code><i>'n'</i></code> vertices (including the <i>'apex'</i>). Thanks to its symmetry properties, it is interesting to analyze (upon request) <code>'6'</code> views of the <i>'Cone'</i> shape, in particular:<p><ul>
<li>a view along the canonical plane <code><i>'xz'</i></code> and its upturned version (indicated as the <i>'View #0'</i> and the <i>'View #1'</i>);</li>
<li>a view along the canonical plane <code><i>'yz'</i></code> and its upturned version (indicated as the <i>'View #2'</i> and the <i>'View #3'</i>);</li>
<li>a view along the canonical plane <code><i>'xy'</i></code> and its upturned version (indicated as the <i>'View #4'</i> and the <i>'View #5'</i>);</li></ul><p>in order to give a more complete overview of its properties.<p>Meanwhile, it is also possible to apply (upon request) any between the orthographic and the perspective projection, since some portions of the shape may overlap and not be visible in a specific view. Finally, it also possible to render (upon request) the <i>'wireframe'</i> and the 'filled versions'</i> of all triangles in the current approximation of the <i>'Cone'</i> shape. These aspects are orthogonal, and can be combined together in several ways.<p>Here, the user cannot modify the radius <code><i>'R=35'</i></code> and the center for the basis of the <i>'Cone'</i> shape, since they are fixed in advance. Instead, the user can:<p><ul>
<li>choose to render a specific view of the <i>'Cone'</i> shape by pressing cyclically the <code><i>'c'</i></code> key;</li>
<li>choose to apply the orthographic or the perspective projection to the current view of the <i>'Cone'</i> shape by pressing cyclically the <code><i>' '</i></code> (space) key;</li>
<li>choose to render the <i>'wireframe'</i> or the <i>'filled versions'</i> of all triangles in the current approximation of the <i>'Cone'</i> shape by pressing cyclically the <code><i>'r'</i></code> key;</li>
<li>increase the number <code><i>'n'</i></code> of all vertices (including the <i>'apex'</i>) in the triangle fans of interest by pressing the <code><i>'+'</i></code> key;</li>
<li>decrease the number <code><i>'n'</i></code> of all vertices (including the <i>'apex'</i>) in the triangle fans of interest by pressing the <code><i>'-'</i></code> key.</li></ul><p>Likewise, the window of interest can be closed by pressing any among the <code><i>'Q'</i></code>, the <code><i>'q'</i></code>, and the <code><i>'Esc'</i></code> keys.

<p><h5>Rendering the <i>'View #0'</i></h5>

<p><table border=0 width=100%>
<tr>
<td width=50%><IMG style=float:middle src='http://davidcanino.github.io/img/shots_opengl/shot_example042_old_view0_wireframe_orthographic_0.png' border='0'></td>
<td width=50%><IMG style=float:middle src='http://davidcanino.github.io/img/shots_opengl/shot_example042_old_view0_wireframe_orthographic_50.png' border='0'></td></tr>
<tr>
<td width=50%>The <code><i>'n=5'</i></code> vertices (including the <i>'apex'</i>) in the <i>'wireframe versions'</i> of the triangles (with the orthographic projection).</td>
<td width=50%>The <code><i>'n=50'</i></code> vertices (including the <i>'apex'</i>) in the <i>'wireframe versions'</i> of the triangles (with the orthographic projection).</td>
</tr>
<tr>
<td width=50%><IMG style=float:middle src='http://davidcanino.github.io/img/shots_opengl/shot_example042_old_view0_filled_orthographic_0.png' border='0'></td>
<td width=50%><IMG style=float:middle src='http://davidcanino.github.io/img/shots_opengl/shot_example042_old_view0_filled_orthographic_50.png' border='0'></td></tr>
<tr>
<td width=50%>The <code><i>'n=5'</i></code> vertices (including the <i>'apex'</i>) in the <i>'filled versions'</i> of the triangles (with the orthographic projection).</td>
<td width=50%>The <code><i>'n=50'</i></code> vertices (including the <i>'apex'</i>) in the <i>'filled versions'</i> of the triangles (with the orthographic projection).</td>
</tr>
<tr>
<td width=50%><IMG style=float:middle src='http://davidcanino.github.io/img/shots_opengl/shot_example042_old_view0_wireframe_perspective_0.png' border='0'></td>
<td width=50%><IMG style=float:middle src='http://davidcanino.github.io/img/shots_opengl/shot_example042_old_view0_wireframe_perspective_50.png' border='0'></td></tr>
<tr>
<td width=50%>The <code><i>'n=5'</i></code> vertices (including the <i>'apex'</i>) in the <i>'wireframe versions'</i> of the triangles (with the perspective projection).</td>
<td width=50%>The <code><i>'n=50'</i></code> vertices (including the <i>'apex'</i>) in the <i>'wireframe versions'</i> of the triangles (with the perspective projection).</td>
</tr>
<tr>
<td width=50%><IMG style=float:middle src='http://davidcanino.github.io/img/shots_opengl/shot_example042_old_view0_filled_perspective_0.png' border='0'></td>
<td width=50%><IMG style=float:middle src='http://davidcanino.github.io/img/shots_opengl/shot_example042_old_view0_filled_perspective_50.png' border='0'></td></tr>
<tr>
<td width=50%>The <code><i>'n=5'</i></code> vertices (including the <i>'apex'</i>) in the <i>'filled versions'</i> of the triangles (with the perspective projection).</td>
<td width=50%>The <code><i>'n=50'</i></code> vertices (including the <i>'apex'</i>) in the <i>'filled versions'</i> of the triangles (with the perspective projection).</td>
</tr></table>

<p><h5>Rendering the <i>'View #1'</i></h5>

<p><table border=0 width=100%>
<tr>
<td width=50%><IMG style=float:middle src='http://davidcanino.github.io/img/shots_opengl/shot_example042_old_view1_wireframe_orthographic_0.png' border='0'></td>
<td width=50%><IMG style=float:middle src='http://davidcanino.github.io/img/shots_opengl/shot_example042_old_view1_wireframe_orthographic_50.png' border='0'></td></tr>
<tr>
<td width=50%>The <code><i>'n=5'</i></code> vertices (including the <i>'apex'</i>) in the <i>'wireframe versions'</i> of the triangles (with the orthographic projection).</td>
<td width=50%>The <code><i>'n=50'</i></code> vertices (including the <i>'apex'</i>) in the <i>'wireframe versions'</i> of the triangles (with the orthographic projection).</td>
</tr>
<tr>
<td width=50%><IMG style=float:middle src='http://davidcanino.github.io/img/shots_opengl/shot_example042_old_view1_filled_orthographic_0.png' border='0'></td>
<td width=50%><IMG style=float:middle src='http://davidcanino.github.io/img/shots_opengl/shot_example042_old_view1_filled_orthographic_50.png' border='0'></td></tr>
<tr>
<td width=50%>The <code><i>'n=5'</i></code> vertices (including the <i>'apex'</i>) in the <i>'filled versions'</i> of the triangles (with the orthographic projection).</td>
<td width=50%>The <code><i>'n=50'</i></code> vertices (including the <i>'apex'</i>) in the <i>'filled versions'</i> of the triangles (with the orthographic projection).</td>
</tr>
<tr>
<td width=50%><IMG style=float:middle src='http://davidcanino.github.io/img/shots_opengl/shot_example042_old_view1_wireframe_perspective_0.png' border='0'></td>
<td width=50%><IMG style=float:middle src='http://davidcanino.github.io/img/shots_opengl/shot_example042_old_view1_wireframe_perspective_50.png' border='0'></td></tr>
<tr>
<td width=50%>The <code><i>'n=5'</i></code> vertices (including the <i>'apex'</i>) in the <i>'wireframe versions'</i> of the triangles (with the perspective projection).</td>
<td width=50%>The <code><i>'n=50'</i></code> vertices (including the <i>'apex'</i>) in the <i>'wireframe versions'</i> of the triangles (with the perspective projection).</td>
</tr>
<tr>
<td width=50%><IMG style=float:middle src='http://davidcanino.github.io/img/shots_opengl/shot_example042_old_view1_filled_perspective_0.png' border='0'></td>
<td width=50%><IMG style=float:middle src='http://davidcanino.github.io/img/shots_opengl/shot_example042_old_view1_filled_perspective_50.png' border='0'></td></tr>
<tr>
<td width=50%>The <code><i>'n=5'</i></code> vertices (including the <i>'apex'</i>) in the <i>'filled versions'</i> of the triangles (with the perspective projection).</td>
<td width=50%>The <code><i>'n=50'</i></code> vertices (including the <i>'apex'</i>) in the <i>'filled versions'</i> of the triangles (with the perspective projection).</td>
</tr></table>

<p><h5>Rendering the <i>'View #2'</i></h5>

<p><table border=0 width=100%>
<tr>
<td width=50%><IMG style=float:middle src='http://davidcanino.github.io/img/shots_opengl/shot_example042_old_view2_wireframe_orthographic_0.png' border='0'></td>
<td width=50%><IMG style=float:middle src='http://davidcanino.github.io/img/shots_opengl/shot_example042_old_view2_wireframe_orthographic_50.png' border='0'></td></tr>
<tr>
<td width=50%>The <code><i>'n=5'</i></code> vertices (including the <i>'apex'</i>) in the <i>'wireframe versions'</i> of the triangles (with the orthographic projection).</td>
<td width=50%>The <code><i>'n=50'</i></code> vertices (including the <i>'apex'</i>) in the <i>'wireframe versions'</i> of the triangles (with the orthographic projection).</td>
</tr>
<tr>
<td width=50%><IMG style=float:middle src='http://davidcanino.github.io/img/shots_opengl/shot_example042_old_view2_filled_orthographic_0.png' border='0'></td>
<td width=50%><IMG style=float:middle src='http://davidcanino.github.io/img/shots_opengl/shot_example042_old_view2_filled_orthographic_50.png' border='0'></td></tr>
<tr>
<td width=50%>The <code><i>'n=5'</i></code> vertices (including the <i>'apex'</i>) in the <i>'filled versions'</i> of the triangles (with the orthographic projection).</td>
<td width=50%>The <code><i>'n=50'</i></code> vertices (including the <i>'apex'</i>) in the <i>'filled versions'</i> of the triangles (with the orthographic projection).</td>
</tr>
<tr>
<td width=50%><IMG style=float:middle src='http://davidcanino.github.io/img/shots_opengl/shot_example042_old_view2_wireframe_perspective_0.png' border='0'></td>
<td width=50%><IMG style=float:middle src='http://davidcanino.github.io/img/shots_opengl/shot_example042_old_view2_wireframe_perspective_50.png' border='0'></td></tr>
<tr>
<td width=50%>The <code><i>'n=5'</i></code> vertices (including the <i>'apex'</i>) in the <i>'wireframe versions'</i> of the triangles (with the perspective projection).</td>
<td width=50%>The <code><i>'n=50'</i></code> vertices (including the <i>'apex'</i>) in the <i>'wireframe versions'</i> of the triangles (with the perspective projection).</td>
</tr>
<tr>
<td width=50%><IMG style=float:middle src='http://davidcanino.github.io/img/shots_opengl/shot_example042_old_view2_filled_perspective_0.png' border='0'></td>
<td width=50%><IMG style=float:middle src='http://davidcanino.github.io/img/shots_opengl/shot_example042_old_view2_filled_perspective_50.png' border='0'></td></tr>
<tr>
<td width=50%>The <code><i>'n=5'</i></code> vertices (including the <i>'apex'</i>) in the <i>'filled versions'</i> of the triangles (with the perspective projection).</td>
<td width=50%>The <code><i>'n=50'</i></code> vertices (including the <i>'apex'</i>) in the <i>'filled versions'</i> of the triangles (with the perspective projection).</td>
</tr></table>

<p><h5>Rendering the <i>'View #3'</i></h5>

<p><table border=0 width=100%>
<tr>
<td width=50%><IMG style=float:middle src='http://davidcanino.github.io/img/shots_opengl/shot_example042_old_view3_wireframe_orthographic_0.png' border='0'></td>
<td width=50%><IMG style=float:middle src='http://davidcanino.github.io/img/shots_opengl/shot_example042_old_view3_wireframe_orthographic_50.png' border='0'></td></tr>
<tr>
<td width=50%>The <code><i>'n=5'</i></code> vertices (including the <i>'apex'</i>) in the <i>'wireframe versions'</i> of the triangles (with the orthographic projection).</td>
<td width=50%>The <code><i>'n=50'</i></code> vertices (including the <i>'apex'</i>) in the <i>'wireframe versions'</i> of the triangles (with the orthographic projection).</td>
</tr>
<tr>
<td width=50%><IMG style=float:middle src='http://davidcanino.github.io/img/shots_opengl/shot_example042_old_view3_filled_orthographic_0.png' border='0'></td>
<td width=50%><IMG style=float:middle src='http://davidcanino.github.io/img/shots_opengl/shot_example042_old_view3_filled_orthographic_50.png' border='0'></td></tr>
<tr>
<td width=50%>The <code><i>'n=5'</i></code> vertices (including the <i>'apex'</i>) in the <i>'filled versions'</i> of the triangles (with the orthographic projection).</td>
<td width=50%>The <code><i>'n=50'</i></code> vertices (including the <i>'apex'</i>) in the <i>'filled versions'</i> of the triangles (with the orthographic projection).</td>
</tr>
<tr>
<td width=50%><IMG style=float:middle src='http://davidcanino.github.io/img/shots_opengl/shot_example042_old_view3_wireframe_perspective_0.png' border='0'></td>
<td width=50%><IMG style=float:middle src='http://davidcanino.github.io/img/shots_opengl/shot_example042_old_view3_wireframe_perspective_50.png' border='0'></td></tr>
<tr>
<td width=50%>The <code><i>'n=5'</i></code> vertices (including the <i>'apex'</i>) in the <i>'wireframe versions'</i> of the triangles (with the perspective projection).</td>
<td width=50%>The <code><i>'n=50'</i></code> vertices (including the <i>'apex'</i>) in the <i>'wireframe versions'</i> of the triangles (with the perspective projection).</td>
</tr>
<tr>
<td width=50%><IMG style=float:middle src='http://davidcanino.github.io/img/shots_opengl/shot_example042_old_view3_filled_perspective_0.png' border='0'></td>
<td width=50%><IMG style=float:middle src='http://davidcanino.github.io/img/shots_opengl/shot_example042_old_view3_filled_perspective_50.png' border='0'></td></tr>
<tr>
<td width=50%>The <code><i>'n=5'</i></code> vertices (including the <i>'apex'</i>) in the <i>'filled versions'</i> of the triangles (with the perspective projection).</td>
<td width=50%>The <code><i>'n=50'</i></code> vertices (including the <i>'apex'</i>) in the <i>'filled versions'</i> of the triangles (with the perspective projection).</td>
</tr></table>

<p><h5>Rendering the <i>'View #4'</i></h5>

<p><table border=0 width=100%>
<tr>
<td width=50%><IMG style=float:middle src='http://davidcanino.github.io/img/shots_opengl/shot_example042_old_view4_wireframe_orthographic_0.png' border='0'></td>
<td width=50%><IMG style=float:middle src='http://davidcanino.github.io/img/shots_opengl/shot_example042_old_view4_wireframe_orthographic_50.png' border='0'></td></tr>
<tr>
<td width=50%>The <code><i>'n=5'</i></code> vertices (including the <i>'apex'</i>) in the <i>'wireframe versions'</i> of the triangles (with the orthographic projection).</td>
<td width=50%>The <code><i>'n=50'</i></code> vertices (including the <i>'apex'</i>) in the <i>'wireframe versions'</i> of the triangles (with the orthographic projection).</td>
</tr>
<tr>
<td width=50%><IMG style=float:middle src='http://davidcanino.github.io/img/shots_opengl/shot_example042_old_view4_filled_orthographic_0.png' border='0'></td>
<td width=50%><IMG style=float:middle src='http://davidcanino.github.io/img/shots_opengl/shot_example042_old_view4_filled_orthographic_50.png' border='0'></td></tr>
<tr>
<td width=50%>The <code><i>'n=5'</i></code> vertices (including the <i>'apex'</i>) in the <i>'filled versions'</i> of the triangles (with the orthographic projection).</td>
<td width=50%>The <code><i>'n=50'</i></code> vertices (including the <i>'apex'</i>) in the <i>'filled versions'</i> of the triangles (with the orthographic projection).</td>
</tr>
<tr>
<td width=50%><IMG style=float:middle src='http://davidcanino.github.io/img/shots_opengl/shot_example042_old_view4_wireframe_perspective_0.png' border='0'></td>
<td width=50%><IMG style=float:middle src='http://davidcanino.github.io/img/shots_opengl/shot_example042_old_view4_wireframe_perspective_50.png' border='0'></td></tr>
<tr>
<td width=50%>The <code><i>'n=5'</i></code> vertices (including the <i>'apex'</i>) in the <i>'wireframe versions'</i> of the triangles (with the perspective projection).</td>
<td width=50%>The <code><i>'n=50'</i></code> vertices (including the <i>'apex'</i>) in the <i>'wireframe versions'</i> of the triangles (with the perspective projection).</td>
</tr>
<tr>
<td width=50%><IMG style=float:middle src='http://davidcanino.github.io/img/shots_opengl/shot_example042_old_view4_filled_perspective_0.png' border='0'></td>
<td width=50%><IMG style=float:middle src='http://davidcanino.github.io/img/shots_opengl/shot_example042_old_view4_filled_perspective_50.png' border='0'></td></tr>
<tr>
<td width=50%>The <code><i>'n=5'</i></code> vertices (including the <i>'apex'</i>) in the <i>'filled versions'</i> of the triangles (with the perspective projection).</td>
<td width=50%>The <code><i>'n=50'</i></code> vertices (including the <i>'apex'</i>) in the <i>'filled versions'</i> of the triangles (with the perspective projection).</td>
</tr></table>

<p><h5>Rendering the <i>'View #5'</i></h5>

<p><table border=0 width=100%>
<tr>
<td width=50%><IMG style=float:middle src='http://davidcanino.github.io/img/shots_opengl/shot_example042_old_view5_wireframe_orthographic_0.png' border='0'></td>
<td width=50%><IMG style=float:middle src='http://davidcanino.github.io/img/shots_opengl/shot_example042_old_view5_wireframe_orthographic_50.png' border='0'></td></tr>
<tr>
<td width=50%>The <code><i>'n=5'</i></code> vertices (including the <i>'apex'</i>) in the <i>'wireframe versions'</i> of the triangles (with the orthographic projection).</td>
<td width=50%>The <code><i>'n=50'</i></code> vertices (including the <i>'apex'</i>) in the <i>'wireframe versions'</i> of the triangles (with the orthographic projection).</td>
</tr>
<tr>
<td width=50%><IMG style=float:middle src='http://davidcanino.github.io/img/shots_opengl/shot_example042_old_view5_filled_orthographic_0.png' border='0'></td>
<td width=50%><IMG style=float:middle src='http://davidcanino.github.io/img/shots_opengl/shot_example042_old_view5_filled_orthographic_50.png' border='0'></td></tr>
<tr>
<td width=50%>The <code><i>'n=5'</i></code> vertices (including the <i>'apex'</i>) in the <i>'filled versions'</i> of the triangles (with the orthographic projection).</td>
<td width=50%>The <code><i>'n=50'</i></code> vertices (including the <i>'apex'</i>) in the <i>'filled versions'</i> of the triangles (with the orthographic projection).</td>
</tr>
<tr>
<td width=50%><IMG style=float:middle src='http://davidcanino.github.io/img/shots_opengl/shot_example042_old_view5_wireframe_perspective_0.png' border='0'></td>
<td width=50%><IMG style=float:middle src='http://davidcanino.github.io/img/shots_opengl/shot_example042_old_view5_wireframe_perspective_50.png' border='0'></td></tr>
<tr>
<td width=50%>The <code><i>'n=5'</i></code> vertices (including the <i>'apex'</i>) in the <i>'wireframe versions'</i> of the triangles (with the perspective projection).</td>
<td width=50%>The <code><i>'n=50'</i></code> vertices (including the <i>'apex'</i>) in the <i>'wireframe versions'</i> of the triangles (with the perspective projection).</td>
</tr>
<tr>
<td width=50%><IMG style=float:middle src='http://davidcanino.github.io/img/shots_opengl/shot_example042_old_view5_filled_perspective_0.png' border='0'></td>
<td width=50%><IMG style=float:middle src='http://davidcanino.github.io/img/shots_opengl/shot_example042_old_view5_filled_perspective_50.png' border='0'></td></tr>
<tr>
<td width=50%>The <code><i>'n=5'</i></code> vertices (including the <i>'apex'</i>) in the <i>'filled versions'</i> of the triangles (with the perspective projection).</td>
<td width=50%>The <code><i>'n=50'</i></code> vertices (including the <i>'apex'</i>) in the <i>'filled versions'</i> of the triangles (with the perspective projection).</td>
</tr></table>

<p><hr><p><h4>Dependencies</h4>

The <i>'Example-42 (Old Mode)'</i> Test is based on the so-called <i>OpenGL old (direct drawing) mode</i>, and requires the following dependencies:<ul>

<li>the <A href="http://www.opengl.org"><i>OpenGL</i></A> package, distributed with the platform of interest (see the <i><A href="https://www.khronos.org/opengl/wiki/Getting_Started">Official Documentation</A></i>);</li>
<li>the <i><A href="https://www.opengl.org/resources/libraries/glut/">OpenGL Utility Toolkit (GLUT)</A></i> package (or the <A href="http://freeglut.sourceforge.net/"><i>FreeGLUT</i></A> package);</li>
<li>the <A href="http://glew.sourceforge.net/"><i>OpenGL Extension Wrangler Library (GLEW)</i></A> package.</li></ul><p>In particular, this test consists of the <i>'Example-042-old'</i> executable file (directly in the <i><code>'bin'</code></i> folder, or in a specific subfolder of the <i><code>'bin'</code></i> folder), starting uniquely from the <i>'main.cpp'</i> C++ source file (in the <i><code>'src'</code></i> folder).<p>Several methods for building this test are provided, and their building infrastructure is saved in the following folders:<p><ul>
<li>the <i><code>'cmake'</code></i> folder contains the project file for the <i><A href="http://cmake.org">CMake Building Tool</A></i>;</li>
<li>the <i><code>'vstudio'</code></i> folder contains the solution file for the <i><A href="http://www.visualstudio.com/">Microsoft Visual Studio (Community Edition 2015)</A></i>;</li>
<li>the <i><code>'xcode'</code></i> folder contains the project file for the <i><A href="http://developer.apple.com/xcode/">Apple XCode</A></i>.</li></ul><br><table border=1><tr><td><p><b>ATTENTION:</b><p>The majority of the dependencies for this test are stable, but are currently deprecated, and several warning messages may appear during the building process.<p></td></tr></table><p><hr><p>

<h4>Instructions for building this test with the <i><A href="http://cmake.org">CMake Building Tool</A></i></h4>

This test is built by using the <i>classic</i> instructions for building a program with the <i><A href="http://cmake.org">CMake Building Tool</A></i> from the <i><code>'cmake\'</code></i> folder:
<pre>mkdir build
cd build
cmake ..
make
</pre><p>As mentioned above, the <i>'Example-042-old'</i> executable file is saved in (a specific subfolder of) the <i><code>'bin'</code></i> folder. For instance, this test is executed by running:<pre>./bin/Example-042-old</pre><p>This building method is tested with the <A href="http://gcc.gnu.org/"><i>GCC</i></A> under the Ubuntu Linux 16.0.4 (LTS), as well as with the <A href="http://clang.llvm.org/"><i>CLANG</i></A> compiler under the MacOsX 11.* El-Capitan (and higher), and the <A href="http://www.visualstudio.com/"><i>Microsoft Visual Studio (Community Edition 2015)</i></A> under the Microsoft Windows 10.<p>In this latter case, three custom projects are automatically generated, and ready to be open in the <A href="http://www.visualstudio.com/"><i>Microsoft Visual Studio (Community Edition 2015)</i></A>. The solution file of interest is the <i>'Example-042-old.sln'</i> solution file, which can be exploited without being modified. This test is built by clicking on the <i>'Build'</i> command. The resulting <i>'Example-042-old.exe'</i> executable file is stored in the <i><code>'bin\Debug'</code></i> folder, if the debugging symbols are included, or in the <i><code>'bin\Release'</code></i> folder, otherwise.<p>

All dependencies of the <i>'Example-042 (Old Mode)'</i> Test are supported automatically by the <i><A href="http://cmake.org">CMake Building Tool</A></i> through a built-in manifest file. In particular, they are often pre-installed in a generic GNU/Linux distribution, and distributed in conjunction with the <A href="http://developer.apple.com/xcode/"><i>Apple XCode</i></A>. Thus, they should be found by the script of interest without problems in these platforms.<p>Instead, these libraries are not standard in the Microsoft Windows, and must be installed properly. For the sake of simplicity, the Win32 versions for the auxiliary libraries of interest in the <i><code>'depends'</code></i> folder are exploited, if the <i><A href="http://cmake.org">CMake Building Tool</A></i> fails while performing their automatic identification. This means that the resulting solution file creates automatically the Win32 version of the <i>'Example-042-old.exe'</i> executable file.<p>An interested user finds more details about other possible customization options in the Official Documentation of the <i><A href="http://cmake.org">CMake Building Tool</A></i>.<p><hr><p>

<h4>Instructions for building this test with the <i><A href="http://www.visualstudio.com/">Microsoft Visual Studio (Community Edition 2015)</A></i></h4>

This test is also built by using the <A href="http://www.visualstudio.com/"><i>Microsoft Visual Studio (Community Edition 2015)</i></A>. In particular, the <i><code>'vstudio\'</code></i> folder contains the <i>'Example-042-old.sln'</i> solution file, which can be exploited without being modified. This test is built by clicking on the <i>'Build'</i> command. The resulting <i>'Example-042-old.exe'</i> executable file is stored in the <i><code>'Debug'</code></i> folder, if the debugging symbols are included, or in the <i><code>'Release'</code></i> folder, otherwise.

Note that this solution file is independently created from scratch, and is different from the solution file, which may be generated automatically by the <i><A href="http://cmake.org">CMake Building Tool</A></i>.

Specifically, the Win32 versions for the auxiliary libraries of interest in the <i><code>'depends\'</code></i> folder are exploited for building the <i>'Example-042 (Old Mode)'</i> Test. This implies that the <i>'Example-042-old.sln'</i> solution file is set up for including these auxiliary libraries, and it should not be modified, unless you are an expert. Furthermore, it is mandatory to enable the building for a generic Win32 platform for creating correctly the Win32 version of the <i>'Example-042-old.exe'</i> executable file.<p>An interested user finds more details in the Official Documentation of the <i><A href="http://www.visualstudio.com/">Microsoft Visual Studio (Community Edition 2015)</A></i>.<p><hr><p>

<h4>Instructions for building this test with the <i><A href="http://developer.apple.com/xcode/">Apple XCode</A></i></h4>

This test is also built by using the <A href="http://developer.apple.com/xcode/"><i>Apple XCode</i></A> (based on the <A href="http://clang.llvm.org/"><i>CLANG</i> compiler</A>) under the MacOsX 11.* El-Capitan (and higher). In particular, the <i><code>'xcode'</code></i> folder contains the <i>'Example-042-old.xcodeproj'</i> project file, which can be exploited without being modified. This test is built by clicking on the <i>'Build & Run'</i> command. The resulting <i>'Example-042-old'</i> executable file is stored in the <i><code>'Build/Products/Debug/'</code></i> folder, if the debugging symbols are included, or in the <i><code>'Build/Products/Release/'</code></i> folder, otherwise.<p>

Note that this project file is independently created from scratch, and is different from the project file, which may be generated automatically by the <i><A href="http://cmake.org">CMake Building Tool</A></i>.<p>

Specifically, this project file includes the versions (frameworks) of the <A href="http://www.opengl.org"><i>OpenGL</i></A> and of the <i><A href="https://www.opengl.org/resources/libraries/glut/">OpenGL Utility Toolkit (GLUT)</A></i> packages, that are distributed in conjunction with the <A href="http://developer.apple.com/xcode/"><i>Apple XCode</i></A>. Instead, the headers and the library files of the <A href="http://glew.sourceforge.net/"><i>OpenGL Extension Wrangler Library (GLEW)</i></A> are assumed to be stored in the <i><code>'/usr/local/include/'</code></i> and the <i><code>'/usr/local/lib/'</code></i> folders, respectively. This implies that the <i>'Example-042-old.xcodeproj'</i> project file is set up for including these auxiliary libraries, and it should not be modified, unless you are an expert.<p>An interested user finds more details in the Official Documentation of the <A href="http://developer.apple.com/xcode/"><i>Apple XCode</i></A>.<p><hr><p><table border=1><tr><td><p><b>ATTENTION:</b><p>This test is not related officially to the <i><A href="https://www.khronos.org/">Khronos Group</A></i>. All trademarks or registered trademarks are the property of their respective owners.</td></tr></table>
