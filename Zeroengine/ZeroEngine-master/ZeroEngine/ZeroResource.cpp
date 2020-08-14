#include "stdafx.h"
#include "ZeroResource.h"
#include "ZeroResourceManager.h"

ZeroResource::ZeroResource() {
	ZeroResourceMgr->RegisterResource(this);
}

ZeroResource::~ZeroResource() {
	ZeroResourceMgr->UnRegisterResource(this);
}

void ZeroResource::OnPrevDeviceReset() {}

void ZeroResource::OnPostDeviceReset() {}

void ZeroResource::ReloadResource() {}
