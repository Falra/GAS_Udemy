// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "GATargetActorGroundSelect.generated.h"

/**
 * 
 */
UCLASS()
class GAS_API AGATargetActorGroundSelect : public AGameplayAbilityTargetActor
{
    GENERATED_BODY()

public:
    AGATargetActorGroundSelect();
    
    virtual void StartTargeting(UGameplayAbility* Ability) override;
    virtual void ConfirmTargetingAndContinue() override;
    virtual void Tick(float DeltaSeconds) override;
    
    UFUNCTION(BlueprintCallable, Category = AbilitySystem)
    bool GetPlayerLookingPoint(FVector& OutViewPoint);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AbilitySystem, meta = (ExposeOnSpawn = true))
    float Radius = 100.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AbilitySystem)
    UDecalComponent* Decal;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AbilitySystem)
    USceneComponent* RootComp;
};
