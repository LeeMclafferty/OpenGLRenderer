#include "Scene.h"

Scene::Scene()
{

}

std::shared_ptr<Object3D> Scene::GetObject(std::string key)
{
	auto iter = objects.find(key);
	if (iter != objects.end())
	{
		return iter->second; 
	}
	
	return nullptr; 
}

void Scene::addObject(const std::string& key, const std::shared_ptr<Object3D> obj)
{
	objects[key] = obj;
}

void Scene::removeObject(const std::string& key)
{
	objects.erase(key);
}
