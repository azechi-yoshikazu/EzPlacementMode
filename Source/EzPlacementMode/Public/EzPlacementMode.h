// Copyright 2023 Yoshikazu Azechi All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FPlacementModeID;
class UEasyPlacementModeSettings;


class FEasyPlacementModeModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	void RegisterPlacementCategory(const UEasyPlacementModeSettings& Settings);
	void UnregisterPlacementCategory();
	
	void HandleSettingsChanged(UObject* Object, struct FPropertyChangedEvent& PropertyChangedEvent);

private:
	// For unregister process
	TArray<FName> RegisteredCategories;
};
