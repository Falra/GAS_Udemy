// Fill out your copyright notice in the Description page of Project Settings.


#include "GATargetActorGroundSelect.h"

#include "DrawDebugHelpers.h"
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
        const FGameplayAbilityTargetDataHandle TargetData = StartLocation.MakeTargetDataHandleFromActors(OverlappedActors);
        TargetDataReadyDelegate.Broadcast(TargetData);
    }
    else
    {
        TargetDataReadyDelegate.Broadcast(FGameplayAbilityTargetDataHandle());
    }
}

void AGATargetActorGroundSelect::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    FVector ViewLocation;
    GetPlayerLookingPoint(ViewLocation);
    DrawDebugSphere(GetWorld(), ViewLocation, Radius, 32, FColor::Red, true, -1, 0, 5.0f);
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

    bool TryTrace = GetWorld()->LineTraceSingleByChannel(HitResult, ViewPoint, ViewPoint + ViewRotation.Vector() * 10000.0f,
        ECC_Visibility, QueryParams);

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
