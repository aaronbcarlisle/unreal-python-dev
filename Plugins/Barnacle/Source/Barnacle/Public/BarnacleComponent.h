// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BarnacleComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UBarnacleComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBarnacleComponent();

	TArray <FName> GetBoneNames() const;
	FRotationTranslationMatrix GetVertexMatrix() const;
	FVector GetBonePosition(FName) const;
	TMap<int32, int32> GetDistanceMap(FName, FVector) const;

	FRotationTranslationMatrix mat(FRotator, FVector);

	void Report(FName BoneName, TMap<int32, int32>);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	USkinnedMeshComponent* SkinComp;
	FVector BonePosition;
	FVector ClosestPointPos;

	TArray <FName> BoneNames;
	TArray<FVector> VertexSkinnedPos;

	// editor properties
	UPROPERTY(EditAnywhere, Category = SkeletalControl)
	TArray <FName> Bones;

	UPROPERTY(EditAnywhere)
	int32 Tolerance;
	 
};
