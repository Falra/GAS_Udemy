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
    virtual void StartTargeting(UGameplayAbility* Ability) override;
    virtual void ConfirmTargetingAndContinue() override;
    virtual void Tick(float DeltaSeconds) override;
    
    UFUNCTION(BlueprintCallable, Category = AbilitySystem)
    bool GetPlayerLookingPoint(FVector& OutViewPoint);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AbilitySystem)
    float Radius = 100.0f;
};
