// Fill out your copyright notice in the Description page of Project Settings.


#include "GATargetActorGroundSelect.h"

#include "Abilities/GameplayAbility.h"

void AGATargetActorGroundSelect::StartTargeting(UGameplayAbility* Ability)
{
    Super::StartTargeting(Ability);

    MasterPC = Cast<APlayerController>(Ability->GetOwningActorFromActorInfo()->GetInstigatorController());
}

void AGATargetActorGroundSelect::ConfirmTargetingAndContinue()
{
    FVector ViewLocation;
    GetPlayerLookingPoint(ViewLocation);
}

bool AGATargetActorGroundSelect::GetPlayerLookingPoint(FVector& OutViewPoint)
{
    FVector ViewPoint;
    FRotator ViewRotation;
    MasterPC->GetPlayerViewPoint(ViewPoint, ViewRotation);

    FHitResult HitResult;
    FCollisionQueryParams QueryParams;
    QueryParams.bTraceComplex = true;
    APawn* MyPawn = MasterPC->GetPawn();
    if (MyPawn)
    {
        QueryParams.AddIgnoredActor(MyPawn);
    }

    bool TryTrace = GetWorld()->LineTraceSingleByChannel(HitResult, ViewPoint, ViewPoint + ViewRotation.Vector() * 10000.0f, ECC_Visibility, QueryParams);
    if (TryTrace)
    {
        OutViewPoint = HitResult.ImpactPoint;
    }
    else
    {
        OutViewPoint = FVector();
    }
    return TryTrace;
}
