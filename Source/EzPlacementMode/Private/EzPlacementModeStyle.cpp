// Copyright 2023 Yoshikazu Azechi All Rights Reserved.

#include "EzPlacementModeStyle.h"

// Engine
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleRegistry.h"

// EzPlacementMode
#include "EzPlacementModeSettings.h"


const FName FEzPlacementModeStyleSet::NAME_StyleSetName = "EzPlacementModeStyleSet";
const FName FEzPlacementModeStyleSet::NAME_DefaultStyleName = "Icons.DefaultCategory";


FEzPlacementModeStyleSet::FEzPlacementModeStyleSet(const class UEzPlacementModeSettings* const InSettings)
	: FSlateStyleSet(NAME_StyleSetName)
{
	const FString BaseDir = IPluginManager::Get().FindPlugin("EzPlacementMode")->GetContentDir();

	SetContentRoot(BaseDir / TEXT("Editor/Slate"));

	Set(NAME_DefaultStyleName, new FSlateImageBrush(RootToContentDir("Icons/Category", TEXT(".png")), FVector2D(16.0f, 16.0f), FEzPlacementCategory::DefaultThumbnailColor));

	if (InSettings)
	{
		for (const auto& Category : InSettings->Categories)
		{
			if (Category.ThumbnailResource)
			{
				Set(Category.GetHandle(), new FSlateImageBrush(Category.ThumbnailResource, FVector2D(16.0f, 16.0f), Category.ThumbnailColor));
			}
		}
	}

	FSlateStyleRegistry::RegisterSlateStyle(*this);
}

FEzPlacementModeStyleSet::~FEzPlacementModeStyleSet()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*this);
}
