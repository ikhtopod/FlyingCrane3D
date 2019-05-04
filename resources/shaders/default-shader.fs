#version 330 core

in vec3 FragPos;
in vec3 Normal;

uniform vec3 bgColor;
uniform vec3 lightColor;
uniform vec3 objectColor;

uniform vec3 cameraPos;

uniform bool isSelectionProcess;
uniform bool isSelected;
uniform vec4 colorCode;


void drawSelectionProcess() {
	gl_FragColor = vec4(colorCode.r, colorCode.g, colorCode.b, colorCode.a) / 255.0;
}

void drawColorDefault() {
	vec3 norm = normalize(Normal);
	
	// ambient
    float ambientStrength = 1.0f;
    vec3 ambient = ambientStrength * bgColor * lightColor;
    
    // diffuse 
	vec3 lightDir = normalize(cameraPos);
    vec3 diffuse = lightColor * max(dot(norm, lightDir), 0.0f);
	
	// specular
    float specularStrength = 0.5f;
    vec3 viewDir = normalize(cameraPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32);
    vec3 specular = specularStrength * spec * lightColor;  
	
	vec3 result = (ambient + diffuse + specular) * objectColor;
    gl_FragColor = vec4(result, 1.0f);
}

void drawColorSelected() {
	drawColorDefault();
}

void main() {
	if (isSelectionProcess) {
		drawSelectionProcess();
	} else {
		if (isSelected) {
			drawColorSelected();
		} else {
			drawColorDefault();
		}//fi
	}//fi
}
