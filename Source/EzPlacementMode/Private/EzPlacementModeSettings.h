// Copyright 2023 Yoshikazu Azechi All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "EzPlacementModeSettings.generated.h"

/**
 * A struct represents user-defined category information
 */
USTRUCT()
struct FEzPlacementCategory
{
	GENERATED_BODY()
	// This category's display name
	UPROPERTY(EditDefaultsOnly)
	FText Name;
	// this category's priority (lowest first)
	UPROPERTY(EditDefaultsOnly)
	int32 Priority = 100;
	// A list of actors to display in this category
	UPROPERTY(EditDefaultsOnly, meta = (MetaClass = "Actor", OnlyPlaceable))
	TArray<FSoftClassPath> Actors;

	FName GetHandle() const
	{
		return FName(Name.ToString());
	}
};

/**
 * A class that provides customization settings for placing objects in Project Settings for a user
 */
UCLASS(config=Engine, defaultconfig, meta=(DisplayName="Ez Placement Mode"))
class UEzPlacementModeSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UEzPlacementModeSettings(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	UPROPERTY(config, EditDefaultsOnly)
	TArray<FEzPlacementCategory> Categories;
};