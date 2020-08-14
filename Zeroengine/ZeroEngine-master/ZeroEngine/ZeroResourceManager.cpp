#include "stdafx.h"
#include "ZeroResourceManager.h"
#include "ZeroResource.h"

ZeroResourceManager::ZeroResourceManager(void) {}

ZeroResourceManager::~ZeroResourceManager(void) {
	CleanUp();
}

ZeroResourceManager* ZeroResourceManager::GetInstance() {
	static ZeroResourceManager m_Instance;
	return &m_Instance;
}

void ZeroResourceManager::ReloadAllResource() {
	for (ResourceList::iterator iter = resourceList.begin(); iter != resourceList.end(); iter++)
		(*iter)->ReloadResource();
}

void ZeroResourceManager::OnPrevDeviceReset() {
	for (ResourceList::iterator iter = resourceList.begin(); iter != resourceList.end(); iter++)
		(*iter)->OnPrevDeviceReset();
}

void ZeroResourceManager::OnPostDeviceReset() {
	for (ResourceList::iterator iter = resourceList.begin(); iter != resourceList.end(); iter++)
		(*iter)->OnPostDeviceReset();
}

void ZeroResourceManager::RegisterResource(ZeroResource* _newResource) {
	resourceList.push_back(_newResource);
}

void ZeroResourceManager::UnRegisterResource(ZeroResource* _removeResource) {
	if (resourceList.size() == 0) return;

	for (ResourceList::iterator iter = resourceList.begin(); iter != resourceList.end(); iter++) {
		if ((*iter) == _removeResource) {
			resourceList.erase(iter);
			break;
		}
	}
}

void ZeroResourceManager::CleanUp() {
	resourceList.clear();
}
