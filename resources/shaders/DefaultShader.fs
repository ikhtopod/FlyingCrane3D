#version 330 core

layout (location = 0) out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;

uniform vec3 cameraPos;

void main() {
	vec3 lightPos = vec3(1.2f, 1.0f, 2.0f);
	vec3 objectColor = vec3(.7f, .3f, .0f);
	vec3 lightColor = vec3( 1.0f );
	
	// ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
    
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
	
	// specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(cameraPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;  
	
	
	vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
}
