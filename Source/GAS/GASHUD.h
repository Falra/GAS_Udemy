// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GASHUD.generated.h"

UCLASS()
class AGASHUD : public AHUD
{
    GENERATED_BODY()

public:
    AGASHUD();

    /** Primary draw call for the HUD */
    virtual void DrawHUD() override;

private:
    /** Crosshair asset pointer */
    class UTexture2D* CrosshairTex;
};
