<A href="http://www.opengl.org"><IMG src='https://www.khronos.org/assets/images/api_logos/opengl.png' border=0 width="180" 
height="97"></A>

<H3>The <i>'Example-005 (Old Mode)'</i> Test</H3>

The <i>'Example-005 (Old Mode)'</i> Test draws the <i>'filled version'</i> of a polygon (in <i>'red'</i>) in an <A href="http://www.opengl.org"><i>OpenGL</i></A> window by providing a basic interaction mechanism with the user. The polygon of interest is the intersection of the following elements:<p><ul>
<li>the orthographic projection viewing box, defined by <i>[0,100] x [0,100] x [-1,1]</i>.</li>
<li>the triangle of 3D vertices <i>(x,20,0)</i>, <i>(80,20,0)</i>, and <i>(80,80,0)</i>.</li></ul><p>Here, the viewing box is not modified. Instead, the <i>'x'</i> coordinate of the triangle can be moved by the user along the x-axis. Specifically, the user can:<p><ul>
<li>increase the <i>'x'</i> coordinate by 1.0 by pressing the <i>'+'</i> key;</li>
<li>decrease the <i>'x'</i> coordinate by 1.0 by pressing the <i>'-'</i> key;</li>
<li>reset the <i>'x'</i> coordinate to its initial value <i>'20'</i> by pressing the <i>'='</i> key.</li></ul><p>Likewise, the window of interest can be closed by pressing any among the <i>'Q'</i>, the <i>'q'</i>, and the <i>'Esc'</i> keys.<p>In particular, this test consists of the <i>'Example-005-old'</i> executable file (in the <i>'bin'</i> folder), starting uniquely from the <i>'main.cpp'</i> C++ source file (in the <i>'src'</i> folder).<p><hr><p>