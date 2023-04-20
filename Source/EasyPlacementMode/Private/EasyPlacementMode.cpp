// Copyright 2023 Yoshikazu Azechi All Rights Reserved.

#include "EasyPlacementMode.h"

// Engine
#include "PlacementMode/Public/IPlacementModeModule.h"

#include "EasyPlacementModeSettings.h"

#define LOCTEXT_NAMESPACE "FEasyPlacementModeModule"

void FEasyPlacementModeModule::StartupModule()
{
	UEasyPlacementModeSettings* Settings = GetMutableDefault<UEasyPlacementModeSettings>();
	if (Settings != nullptr)
	{
		RegisterPlacementCategory(*Settings);

		Settings->OnSettingChanged().AddRaw(this, &FEasyPlacementModeModule::HandleSettingsChanged);
	}

}

void FEasyPlacementModeModule::ShutdownModule()
{
	UEasyPlacementModeSettings* Settings = GetMutableDefault<UEasyPlacementModeSettings>();
	if (Settings != nullptr)
	{
		UnregisterPlacementCategory(*Settings);
	}
}

void FEasyPlacementModeModule::RegisterPlacementCategory(const UEasyPlacementModeSettings& Settings)
{
	for (const auto& Category : Settings.Categories)
	{
		if (Category.Name.IsEmpty())
		{
			continue;
		}

		const FPlacementCategoryInfo CategoryInfo(Category.Name, Category.GetHandle(), TEXT("EzPlacementMode"), Category.Priority);
		IPlacementModeModule::Get().RegisterPlacementCategory(CategoryInfo);
	}
}

void FEasyPlacementModeModule::UnregisterPlacementCategory(const UEasyPlacementModeSettings& Settings)
{
	if (IPlacementModeModule::IsAvailable())
	{
		for (const auto& Category : Settings.Categories)
		{
			IPlacementModeModule::Get().UnregisterPlacementCategory(Category.GetHandle());
		}
	}
}

void FEasyPlacementModeModule::HandleSettingsChanged(UObject* Object, struct FPropertyChangedEvent& PropertyChangedEvent)
{
	UEasyPlacementModeSettings* Settings = GetMutableDefault<UEasyPlacementModeSettings>();
	if (Settings != nullptr)
	{
		UnregisterPlacementCategory(*Settings);

		RegisterPlacementCategory(*Settings);
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FEasyPlacementModeModule, EasyPlacementMode)
