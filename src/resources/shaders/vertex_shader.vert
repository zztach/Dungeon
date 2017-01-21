#version 420 core                                                  
                                         
// the incoming vertex                          
layout (location = 0) in vec4 position;                                                          
layout (location = 1) in vec3 normal;
layout (location = 2) in vec4 color;       
layout (location = 3) in vec2 vertTexCoord;
                                                                                            
out VS_OUT                                                         
{                                                                  
    vec4 color;                            
    vec2 fragTexCoord;                        
} vs_out;                                                          

uniform mat4 camera_matrix;                                                                   
uniform mat4 mv_matrix;                                            
uniform mat4 proj_matrix;                                          
uniform vec4 light_pos;

// Light and material properties
uniform vec3 diffuse_albedo = vec3(0.6, 0.6, 0.6);
uniform vec3 specular_albedo = vec3(0.95);
uniform float specular_power = 188.0;
uniform vec4 ambient = vec4(0.4, 0.4, 0.4, 1.0);                                                                   
                                                                   
void main(void)                                                    
{                                                                      
    // Calculate coordinate in view-space
    vec4 P = camera_matrix * mv_matrix * position;

    // Calculate normal in view-space. For further explanation check
    // http://tomdalling.com/blog/modern-opengl/06-diffuse-point-lighting/ and
    // http://en.wikibooks.org/wiki/GLSL_Programming/Applying_Matrix_Transformations	
    vec3 N = transpose(inverse(mat3(mv_matrix))) * normal;

    // Calculate light vector in view-space
    vec3 L;
    if (light_pos.w == 0.0f)
            L = light_pos.xyz;
    else 
        L = light_pos.xyz - P.xyz;    
            // this ones moves the light along with the camera
            //L = mat3(mv_matrix)*light_pos.xyz - P.xyz;

    // Calculate view vector (simply the negative of the view-space position)
    vec3 V = -P.xyz;

    // Normalize all three vectors
    N = normalize(N);
    L = normalize(L);
    V = normalize(V);

    // Calculate R by reflecting -L around the plane defined by N
    vec3 R = reflect(-L, N);

    // Calculate the diffuse and specular contributions
    vec3 diffuse = max(dot(N, L), 0.0) * diffuse_albedo;
    vec3 specular = pow(max(dot(R, V), 0.0), specular_power) * specular_albedo;

    // Send the color output to the fragment shader
    vs_out.color = color * (ambient + vec4(diffuse, 1.0f) + vec4(specular, 1.0f));		

    // Pass the texture coordinate to the fragment shader
    vs_out.fragTexCoord = vertTexCoord;

    // Calculate the clip-space position of each vertex
    // adding here the transformations we get steady light    
    gl_Position = proj_matrix * P;
}                                                                  