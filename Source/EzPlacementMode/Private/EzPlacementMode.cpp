// Copyright 2023 Yoshikazu Azechi All Rights Reserved.

#include "EzPlacementMode.h"

// Engine
#include "Editor.h"
#include "IPlacementModeModule.h"

// EzPlacementMode
#include "EzPlacementModeSettings.h"
#include "EzPlacementModeStyle.h"

#define LOCTEXT_NAMESPACE "FEzPlacementModeModule"

void FEzPlacementModeModule::StartupModule()
{
	UEzPlacementModeSettings* Settings = GetMutableDefault<UEzPlacementModeSettings>();

	StyleSet = MakeShared<FEzPlacementModeStyleSet>(Settings);

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
		const FName& StyleName = (Category.IconResource != nullptr) ? UniqueID : FEzPlacementModeStyleSet::NAME_DefaultStyleName;

		const FPlacementCategoryInfo CategoryInfo(Category.Name, FSlateIcon(FEzPlacementModeStyleSet::NAME_StyleSetName, StyleName), UniqueID, TEXT("PMEzPlacementMode"), Category.Priority);
		if (!PlacementModeModule.RegisterPlacementCategory(CategoryInfo))
		{
			continue;
		}

		RegisteredCategories.Add(UniqueID);

		for (int32 Index = 0; Index < Category.Actors.Num(); Index++)
		{
			if (UObject* ActorObject = Category.Actors[Index].TryLoad())
			{
				const FAssetData AssetData(ActorObject);

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
		StyleSet.Reset();
		StyleSet = MakeShared<FEzPlacementModeStyleSet>(Settings);
		RegisterPlacementCategory(*Settings);
	}
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FEzPlacementModeModule, EzPlacementMode)
