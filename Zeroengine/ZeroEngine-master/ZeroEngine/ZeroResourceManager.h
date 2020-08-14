#pragma once

class ZeroResource;

#define ZeroResourceMgr ZeroResourceManager::GetInstance()

class ZeroResourceManager {
private:
	ZeroResourceManager(void);
	~ZeroResourceManager(void);

	typedef std::vector<ZeroResource*> ResourceList;
	ResourceList resourceList;

public:
	static ZeroResourceManager* GetInstance();

	void ReloadAllResource();
	void OnPrevDeviceReset();
	void OnPostDeviceReset();
	void RegisterResource(ZeroResource* _newResource);
	void UnRegisterResource(ZeroResource* _removeResource);
	void CleanUp();
};
