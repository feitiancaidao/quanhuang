#ifdef GL_ES 
precision lowp float; 
#endif 
varying vec4 v_fragmentColor;
 varying vec2 v_texCoord; 
 uniform sampler2D my_Texture0;
void main() { 
vec4 color =  texture2D(my_Texture0, v_texCoord);
float grey=dot(color.rgb, vec3(0.3,0.6,0.1));
gl_FragColor=vec4(grey,grey,grey,color.a);
//gl_FragColor=vec4(1.0,0.0,0.0,1.0);
}