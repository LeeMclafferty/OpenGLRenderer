#include "Material.h"

Material::Material()
	:ambient(glm::vec4(.5f)), diffuse(glm::vec4(1.f)), specular(glm::vec4(1.f)),
	shininess(1.f)
{

}
