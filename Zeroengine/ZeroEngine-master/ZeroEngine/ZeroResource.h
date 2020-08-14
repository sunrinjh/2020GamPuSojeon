#pragma once

class ZeroResource {
public:
	ZeroResource();
	~ZeroResource();

public:
	virtual void ReloadResource();
	virtual void OnPrevDeviceReset();
	virtual void OnPostDeviceReset();
};
