// Copyright 2023 Yoshikazu Azechi All Rights Reserved.

#include "EasyPlacementMode.h"

// Engine
#include "Editor.h"
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
	UnregisterPlacementCategory();
}

void FEasyPlacementModeModule::RegisterPlacementCategory(const UEasyPlacementModeSettings& Settings)
{
	IPlacementModeModule& PlacementModeModule = IPlacementModeModule::Get();

	for (const auto& Category : Settings.Categories)
	{
		if (Category.Name.IsEmpty())
		{
			continue;
		}

		const FName UniqueID = Category.GetHandle();

		const FPlacementCategoryInfo CategoryInfo(Category.Name, FSlateIcon(FAppStyle::GetAppStyleSetName(), "PlacementBrowser.Icons.Basic"), UniqueID, TEXT("PMEzPlacementMode"), Category.Priority);
		if (!PlacementModeModule.RegisterPlacementCategory(CategoryInfo))
		{
			continue;
		}

		RegisteredCategories.Add(UniqueID);

		for (int32 Index = 0; Index < Category.Classes.Num(); Index++)
		{
			if (UObject* Object = Category.Classes[Index].TryLoad())
			{
				const FAssetData AssetData(Object);

				UActorFactory* ActorFactory = GEditor ? GEditor->FindActorFactoryForActorClass(AssetData.GetClass()) : nullptr;

				const TSharedRef<FPlaceableItem> Placeable = MakeShared<FPlaceableItem>(ActorFactory, AssetData, Index);
				PlacementModeModule.RegisterPlaceableItem(UniqueID, Placeable);
			}
		}
	}
}

void FEasyPlacementModeModule::UnregisterPlacementCategory()
{
	if (IPlacementModeModule::IsAvailable())
	{
		for (const FName& Category : RegisteredCategories)
		{
			IPlacementModeModule::Get().UnregisterPlacementCategory(Category);
		}
	}

	RegisteredCategories.Empty();
}

void FEasyPlacementModeModule::HandleSettingsChanged(UObject* Object, struct FPropertyChangedEvent& PropertyChangedEvent)
{
	UnregisterPlacementCategory();

	UEasyPlacementModeSettings* Settings = GetMutableDefault<UEasyPlacementModeSettings>();
	if (Settings != nullptr)
	{
		RegisterPlacementCategory(*Settings);
	}
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FEasyPlacementModeModule, EasyPlacementMode)
