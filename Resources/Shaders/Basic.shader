#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 color;
layout (location = 3) in vec3 aTexCoord;
layout (location = 3) in vec3 aNormal;

uniform mat4 modelTransformMatrix; // Model to world
uniform mat4 viewMatrix; // World to view
uniform mat4 projectionMatrix; // View to projection
uniform mat3 normalMatrix;

out vec4 vertexColor;
out vec3 normal;
out vec3 fragPos;

void main()
{
    vec4 worldPos = modelTransformMatrix * vec4(aPos, 1.0);
    gl_Position = projectionMatrix * viewMatrix * worldPos;
    vertexColor = color;
    normal = normalMatrix * aNormal;
    fragPos = vec3(modelTransformMatrix * vec4(aPos, 1.0));
};

#shader fragment
#version 330 core

struct Material {
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    float shininess;
}; 

struct Light {
    vec3 position;
  
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
};
  
in vec4 vertexColor;
in vec3 normal;
in vec3 fragPos;

uniform vec4 lightingColor;
uniform vec3 lightPos;
uniform vec3 cameraPos;
uniform Material material;
uniform Light light;

out vec4 FragColor;

void main()
{
    vec4 ambient = light.ambient * lightingColor * material.ambient;

    vec3 norm = normalize(normal);

    vec3 lightDir = normalize(lightPos - fragPos);
    vec3 viewDir = normalize(cameraPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float diff = max(dot(norm, lightDir), 0.0);
    vec4 diffuse = light.diffuse * (diff * material.diffuse) * lightingColor;
    
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec4 specular = light.specular * (material.specular * spec) * lightingColor;

    FragColor = (ambient + diffuse + specular) * vertexColor;
}