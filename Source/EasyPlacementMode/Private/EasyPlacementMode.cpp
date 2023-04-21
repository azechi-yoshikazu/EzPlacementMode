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
	UEasyPlacementModeSettings* Settings = GetMutableDefault<UEasyPlacementModeSettings>();
	if (Settings != nullptr)
	{
		UnregisterPlacementCategory(*Settings);
	}
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

		const FPlacementCategoryInfo CategoryInfo(Category.Name, UniqueID, TEXT("EzPlacementMode"), Category.Priority);
		if (PlacementModeModule.RegisterPlacementCategory(CategoryInfo))
		{
			RegisteredCategories.Add(UniqueID);

			for (int32 Index = 0; Index < Category.Classes.Num(); Index++)
			{
				if (UObject* Object = Category.Classes[Index].TryLoad())
				{
					FAssetData AssetData(Object);
					UActorFactory* UseActorFactory = nullptr;

					if (GEditor)
					{
						for (auto ActorFactory : GEditor->ActorFactories)
						{
							FText ErrorMessage;
							if (ActorFactory->CanCreateActorFrom(AssetData, ErrorMessage))
							{
								UseActorFactory = ActorFactory.Get();
								break;
							}
							UE_LOG(LogTemp, Log, TEXT("%s: %s"), *ActorFactory->GetName(), *ErrorMessage.ToString());
						}
					}

					//UActorFactory* ActorFactory = GEditor ? GEditor->FindActorFactoryForActorClass(Class) : nullptr;

					const TSharedRef<FPlaceableItem> Placeable = MakeShared<FPlaceableItem>(UseActorFactory, AssetData, Index);
					PlacementModeModule.RegisterPlaceableItem(UniqueID, Placeable);
				}
			}
		}
	}
}

void FEasyPlacementModeModule::UnregisterPlacementCategory(const UEasyPlacementModeSettings& Settings)
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
	UEasyPlacementModeSettings* Settings = GetMutableDefault<UEasyPlacementModeSettings>();
	if (Settings != nullptr)
	{
		UnregisterPlacementCategory(*Settings);

		RegisterPlacementCategory(*Settings);
	}
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FEasyPlacementModeModule, EasyPlacementMode)
