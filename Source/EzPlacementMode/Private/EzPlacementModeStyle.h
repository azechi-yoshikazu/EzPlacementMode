// Copyright 2023 Yoshikazu Azechi All Rights Reserved.

#pragma once

#include "Styling/SlateStyle.h"

class FEzPlacementModeStyleSet : public FSlateStyleSet
{
public:
	static const FName NAME_StyleSetName;
	static const FName NAME_DefaultStyleName;

public:
	FEzPlacementModeStyleSet(const class UEzPlacementModeSettings* const InSettings);
	~FEzPlacementModeStyleSet();
};
