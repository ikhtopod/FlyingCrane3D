#version 330 core

layout (location = 0) out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;

uniform vec3 bgColor;
uniform vec3 lightColor;
uniform vec3 objectColor;

uniform vec3 cameraPos;

void main() {
	vec3 norm = normalize(Normal);
	
	// ambient
    float ambientStrength = 1.0f;
    vec3 ambient = ambientStrength * bgColor * lightColor;
    
    // diffuse 
	vec3 lightDir = normalize(cameraPos);
    vec3 diffuse = lightColor * max(dot(norm, lightDir), 0.0);
	
	// specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(cameraPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;  
	
	vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
}
