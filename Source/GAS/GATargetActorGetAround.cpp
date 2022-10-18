// Fill out your copyright notice in the Description page of Project Settings.


#include "GATargetActorGetAround.h"
#include "Abilities/GameplayAbility.h"
#include "GameFramework/PlayerController.h"

void AGATargetActorGetAround::StartTargeting(UGameplayAbility* Ability)
{
    Super::StartTargeting(Ability);
    MasterPC = Cast<APlayerController>(Ability->GetOwningActorFromActorInfo()->GetInstigatorController());
}

void AGATargetActorGetAround::ConfirmTargetingAndContinue()
{
    APawn* OwningPawn = MasterPC->GetPawn();
    if (!OwningPawn)
    {
        TargetDataReadyDelegate.Broadcast(FGameplayAbilityTargetDataHandle());
        return;
    }
    FVector ViewLocation = OwningPawn->GetActorLocation();

    TArray<FOverlapResult> Overlapped;
    TArray<TWeakObjectPtr<AActor>> OverlappedActors;
    const bool TraceComplex = false;

    FCollisionQueryParams QueryParams;
    QueryParams.bTraceComplex = TraceComplex;
    QueryParams.bReturnPhysicalMaterial = false;
    QueryParams.AddIgnoredActor(MasterPC->GetPawn());
    const bool TryOverlap = GetWorld()->OverlapMultiByObjectType(Overlapped, ViewLocation, FQuat::Identity,
        FCollisionObjectQueryParams(ECC_Pawn), FCollisionShape::MakeSphere(Radius), QueryParams);

    if (TryOverlap)
    {
        for (auto OverlapResult : Overlapped)
        {
            auto PawnOverlap = Cast<APawn>(OverlapResult.GetActor());
            if (PawnOverlap && !OverlappedActors.Contains(PawnOverlap))
            {
                OverlappedActors.Add(PawnOverlap);
            }
        }
    }

    if (OverlappedActors.Num() > 0)
    {
        FGameplayAbilityTargetDataHandle TargetData = StartLocation.MakeTargetDataHandleFromActors(OverlappedActors);
        TargetDataReadyDelegate.Broadcast(TargetData);
    }
    else
    {
        TargetDataReadyDelegate.Broadcast(FGameplayAbilityTargetDataHandle());
    }
}
