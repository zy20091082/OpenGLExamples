<A href="http://www.opengl.org"><IMG src='https://www.khronos.org/assets/images/api_logos/opengl.png' border=0 width="180" height="97"></A>

<H3>The <i>'Example-057 (Old Mode)'</i> Test</H3>

The <i>'Example-057 (Old Mode)'</i> Test draws several approximations of the <i>'Circle'</i> shape with radius <code><i>'R'</i></code> and center <code><i>'(xc,yc)'</i></code> in an <A href="http://www.opengl.org"><i>OpenGL</i></A> window. The approximations of interest are activated upon request, and are formed by an arbitrary number <code><i>'n-1'</i></code> of the samples. The <i>'Circle'</i> shape is defined as follows:<p><pre>| x(t) - xc | <= R * cos(t), | y(t) - yc | <= R * sin(t)</pre><p>for any <code><i>'R>0'</i></code>, and for every <code><i>'t'</i></code> in <code><i>'[-pi,pi]'</i>.</code><p>Here, the <i>'Circle'</i> shape is approximated by <code><i>'n-1'</i></code> triangles in a triangle fan. All triangles (in <i>'white'</i>) are incident at the center <code><i>'(xc,yc)'</i></code>. Thus, the <i>'Circle'</i> shape is approximated by <code><i>'n'</i></code> samples, including the center.





In this test, it is not possible to modify the radius <code><i>'R'</i></code> and the center <code><i>'(xc,yc)'</i></code> for the <i>'Circle'</i> shape, since they are fixed in advance. Instead, the user can:<p><ul>
<li>increase the number <code><i>'n'</i></code> of the samples in the triangle fan by pressing the <code><i>'+'</i></code> key;<p></li>
<li>decrease the number <code><i>'n'</i></code> of the samples in the triangle fan by pressing the <code><i>'-'</i></code> key;<p></li>
</ul><p>and can press cyclically the <code><i>' '</i></code> (space) key for choosing to render:<p><ul>
<li>only the points for all triangles in the triangle strip of interest;</li>
<li>the <i>'wireframe versions'</i> for the triangle and the desired polygons in the quad strip of interest;</li>
<li>the <i>'filled versions'</i> for the triangle and the desired polygons in the quad strip of interest.</li></ul><p>Likewise, the window of interest can be closed by pressing any among the <code><i>'Q'</i></code>, the <code><i>'q'</i></code>, and the <code><i>'Esc'</i></code> keys.<p>
