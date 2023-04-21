// Copyright 2023 Yoshikazu Azechi All Rights Reserved.

#include "EzPlacementModeStyle.h"

// Engine
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleRegistry.h"


const FName FEzPlacementModeStyleSet::NAME_StyleSetName = "EzPlacementModeStyleSet";


FEzPlacementModeStyleSet::FEzPlacementModeStyleSet()
	: FSlateStyleSet(NAME_StyleSetName)
{
	const FString BaseDir = IPluginManager::Get().FindPlugin("EzPlacementMode")->GetContentDir();

	SetContentRoot(BaseDir / TEXT("Editor/Slate"));

	Set("Icons.Category", new FSlateImageBrush(RootToContentDir("Icons/Category", TEXT(".png")), FVector2D(16.0f, 16.0f)));

	FSlateStyleRegistry::RegisterSlateStyle(*this);
}

FEzPlacementModeStyleSet::~FEzPlacementModeStyleSet()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*this);
}
