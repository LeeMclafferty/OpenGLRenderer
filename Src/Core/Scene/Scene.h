#pragma once

#include <unordered_map>
#include <memory>
#include <string>
#include "Object/Object3D.h"

class Scene
{
public:
	Scene();

	std::unordered_map<std::string, std::shared_ptr<Object3D>> GetObjects() { return objects; }
	std::shared_ptr<Object3D> GetObject(std::string key);

	void addObject(const std::string& key, const std::shared_ptr<Object3D> obj);
	void removeObject(const std::string& key);
	

private:
	std::unordered_map<std::string, std::shared_ptr<Object3D>> objects;
};

