#version 420 core                                                  
                                                                   
layout (location = 0) in vec4 position;                                                          
layout (location = 1) in vec3 normal;
layout (location = 2) in vec4 color; 
                                                                                                  
out VS_OUT                                                         
{                                                                  
    vec4 color;                                                    
} vs_out;                                                          
                                                                   
uniform mat4 mv_matrix;                                            
uniform mat4 proj_matrix;                                          

// Light and material properties
uniform vec3 light_pos = vec3(0.0, 60.0, -10.0);
uniform vec3 diffuse_albedo = vec3(0.9, 0.2, 0.7);
uniform vec3 specular_albedo = vec3(0.7);
uniform float specular_power = 128.0;
uniform vec4 ambient = vec4(0.3, 0.3, 0.3, 1.0);                                                                   
                                                                   
void main(void)                                                    
{                                                                  
    //gl_Position = proj_matrix * mv_matrix * position;              
    //vs_out.color = position * 2.0 + vec4(0.5, 0.5, 0.5, 0.0);					
    //vs_out.color = color;													    

	// Calculate view-space coordinate
    vec4 P = mv_matrix * position;

    // Calculate normal in view space
    vec3 N = mat3(mv_matrix) * normal;
    // Calculate view-space light vector
    vec3 L = light_pos - P.xyz;
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
	//vs_out.color = color;

    // Calculate the clip-space position of each vertex
    gl_Position = proj_matrix * P;
}                                                                  