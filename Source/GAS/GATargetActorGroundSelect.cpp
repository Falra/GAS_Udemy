// Fill out your copyright notice in the Description page of Project Settings.


#include "GATargetActorGroundSelect.h"
#include "Abilities/GameplayAbility.h"
#include "Components/DecalComponent.h"

AGATargetActorGroundSelect::AGATargetActorGroundSelect()
{
    PrimaryActorTick.bCanEverTick = true;
    
    Decal = CreateDefaultSubobject<UDecalComponent>("Decal");
    RootComp = CreateDefaultSubobject<USceneComponent>("Root");
    SetRootComponent(RootComp);
    Decal->SetupAttachment(RootComp);
    Radius = 200.0f;
    Decal->DecalSize = FVector(Radius);
}

void AGATargetActorGroundSelect::StartTargeting(UGameplayAbility* Ability)
{
    Super::StartTargeting(Ability);
    Decal->DecalSize = FVector(Radius);
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

    FGameplayAbilityTargetData_LocationInfo* CenterLocation = new FGameplayAbilityTargetData_LocationInfo();
    CenterLocation->TargetLocation.LiteralTransform = Decal->GetComponentTransform();
    CenterLocation->TargetLocation.LocationType = EGameplayAbilityTargetingLocationType::LiteralTransform;
    
    if (OverlappedActors.Num() > 0)
    {
        FGameplayAbilityTargetDataHandle TargetData = StartLocation.MakeTargetDataHandleFromActors(OverlappedActors);
        TargetData.Add(CenterLocation);
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
    Decal->SetWorldLocation(ViewLocation);
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
