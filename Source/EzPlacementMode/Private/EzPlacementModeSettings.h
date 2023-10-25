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
    UPROPERTY(EditDefaultsOnly, Category = "Ez Placement Mode")
    FText Name;
    // This category's priority (lowest first)
    UPROPERTY(EditDefaultsOnly, Category = "Ez Placement Mode")
    int32 Priority = 100;
    // A list of actors to display in this category
    UPROPERTY(EditDefaultsOnly, Category = "Ez Placement Mode", meta = (MetaClass = "Actor", OnlyPlaceable))
    TArray<FSoftClassPath> Actors;
    // This category's icon
    UPROPERTY(EditDefaultsOnly, Category = "Ez Placement Mode", meta = (AllowPrivateAccess = "true", DisplayThumbnail = "true", DisplayName = "Icon", AllowedClasses = "/Script/Engine.Texture,/Script/Engine.MaterialInterface,/Script/Engine.SlateTextureAtlasInterface", DisallowedClasses = "/Script/MediaAssets.MediaTexture"))
    TObjectPtr<UObject> IconResource;
    // This category's thumbnail color
    UPROPERTY(EditDefaultsOnly, Category = "Ez Placement Mode", meta = (EditCondition = "IconResource != nullptr"))
    FLinearColor IconColor = DefaultIconColor;

    FName GetHandle() const
    {
        return FName(Name.ToString());
    }

    static const FLinearColor DefaultIconColor;
};

/**
 * A class that provides customization settings for placing objects in Project Settings for a user
 */
UCLASS(config = Engine, defaultconfig, meta = (DisplayName = "Ez Placement Mode"))
class UEzPlacementModeSettings : public UDeveloperSettings
{
    GENERATED_BODY()

public:
    UEzPlacementModeSettings(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
    UPROPERTY(config, EditDefaultsOnly, Category = "Ez Placement Mode")
    TArray<FEzPlacementCategory> Categories;
};
