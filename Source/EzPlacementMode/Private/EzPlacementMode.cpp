// Copyright 2023 Yoshikazu Azechi All Rights Reserved.

#include "EzPlacementMode.h"

// Engine
#include "Editor.h"
#include "PlacementMode/Public/IPlacementModeModule.h"

// EzPlacementMode
#include "EzPlacementModeSettings.h"
#include "EzPlacementModeStyle.h"

#define LOCTEXT_NAMESPACE "FEzPlacementModeModule"

void FEzPlacementModeModule::StartupModule()
{
	StyleSet = MakeShared<FEzPlacementModeStyleSet>();

	UEzPlacementModeSettings* Settings = GetMutableDefault<UEzPlacementModeSettings>();
	if (Settings != nullptr)
	{
		RegisterPlacementCategory(*Settings);

		Settings->OnSettingChanged().AddRaw(this, &FEzPlacementModeModule::HandleSettingsChanged);
	}

}

void FEzPlacementModeModule::ShutdownModule()
{
	UnregisterPlacementCategory();
}

void FEzPlacementModeModule::RegisterPlacementCategory(const UEzPlacementModeSettings& Settings)
{
	IPlacementModeModule& PlacementModeModule = IPlacementModeModule::Get();

	for (const auto& Category : Settings.Categories)
	{
		if (Category.Name.IsEmpty())
		{
			continue;
		}

		const FName UniqueID = Category.GetHandle();

		const FPlacementCategoryInfo CategoryInfo(Category.Name, FSlateIcon(FEzPlacementModeStyleSet::NAME_StyleSetName, "Icons.Category"), UniqueID, TEXT("PMEzPlacementMode"), Category.Priority);
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

void FEzPlacementModeModule::UnregisterPlacementCategory()
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

void FEzPlacementModeModule::HandleSettingsChanged(UObject* Object, struct FPropertyChangedEvent& PropertyChangedEvent)
{
	UnregisterPlacementCategory();

	UEzPlacementModeSettings* Settings = GetMutableDefault<UEzPlacementModeSettings>();
	if (Settings != nullptr)
	{
		RegisterPlacementCategory(*Settings);
	}
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FEzPlacementModeModule, EzPlacementMode)
