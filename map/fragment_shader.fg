#version 420 core                                                  
                 
layout (binding = 0) uniform sampler2D tex;                                                  
out vec4 color;                                                    
                                                                   
in VS_OUT                                                          
{                                                                  
   vec4 color;
   vec2 fragTexCoord;                                                    
} fs_in;                                                          
                                                                  
void main(void)                                                   
{  
// Write incoming color to the framebuffer   
//   if (tex == 0)                                                            
//     color = fs_in.color;                                              
//   else
     color = texture(tex, fs_in.fragTexCoord) * fs_in.color; 
   //color = texelFetch(tex, ivec2(fs_in.fragTexCoord), 0); 
   //color = texture(tex, gl_FragCoord.xy / textureSize(tex, 0));  
   //color = texture(tex, gl_FragCoord.xy / 256);
}                    