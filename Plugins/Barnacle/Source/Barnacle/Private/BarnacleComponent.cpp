// Fill out your copyright notice in the Description page of Project Settings.

#include "BarnacleComponent.h"
#include <DrawDebugHelpers.h>
#include <Map.h>


// Seta default values for this component's properties
UBarnacleComponent::UBarnacleComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}



// Called when the game starts
void UBarnacleComponent::BeginPlay()
{

	Super::BeginPlay();

	// get owner
	AActor* Owner = GetOwner();

	// empty skinned positions
	VertexSkinnedPos.Empty();

	// get skeletal mesh component for vertex position and error check.
	TArray<USkinnedMeshComponent*> SkinMeshComps;
	Owner->GetComponents<USkinnedMeshComponent>(SkinMeshComps);
	if (SkinMeshComps.Num() == 0 || Bones.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not find any SkinnedMeshComponents!"));
		return;
	}

	// get skeletal mesh and component and error check.
	SkinComp = SkinMeshComps[0];
	USkeletalMesh* SkelMesh = SkinComp->SkeletalMesh;
	if (!SkelMesh)
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not find an associated SkeletalMesh!"));
		return;
	}

	// gathered skinned vertex positions and error check.
	SkinComp->ComputeSkinnedPositions(VertexSkinnedPos);
	if (VertexSkinnedPos.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not find any skinned verts!"));
		return;
	}

	// TODO: convert to BoneNames and log if they input more than one
	BoneNames = GetBoneNames();
	if (BoneNames.Num() > 0)
	{
		for (int32 bindex = 0; bindex < BoneNames.Num(); bindex++)
		{
			FName BoneName = BoneNames[bindex];
			BonePosition = GetBonePosition(BoneName);
			TMap<int32, int32> DistanceMap = GetDistanceMap(BoneName, BonePosition);
			Report(BoneName, DistanceMap);
		}
	}
}


void UBarnacleComponent::Report(FName BoneName, TMap <int32, int32> DistanceMap)
{
	// sort map to find closest points
	DistanceMap.ValueSort([](float A, float B) { return A < B; });

	// Report the bone name
	UE_LOG(LogTemp, Warning, TEXT("Bone: %s"), *BoneName.ToString());

	// iter through map based on tolerance set and provide visuals and output
	int32 count = 0;
	int32 ClosestPoint = 0;
	for (auto It = DistanceMap.CreateConstIterator(); It; ++It)
	{
		// break if tolerance is reached
		if (count >= Tolerance)
		{
			break;
		}
		
		// current closeset point and closest position
		FRotationTranslationMatrix mat = GetVertexMatrix();
		ClosestPoint = It.Key();
		ClosestPointPos = mat.TransformPosition(VertexSkinnedPos[ClosestPoint]);

		// debug line to see where verts are
		DrawDebugLine(
			GetWorld(), 
			BonePosition, 
			ClosestPointPos, 
			FColor(255,0,0), 
			true, -1.f, 0, 
			1.0
			);

		UE_LOG(LogTemp, Warning, TEXT("Closest Point %d: %d"), count, ClosestPoint);

		// iter
		count++;
	}
}

TArray <FName> UBarnacleComponent::GetBoneNames() const
{
	return Bones;
}

FVector UBarnacleComponent::GetBonePosition(FName BoneName) const
{
	// get world space of bone location
	// TODO: Ensure I handle cases where the bone does not exist
	return SkinComp->GetBoneLocation(BoneName, EBoneSpaces::WorldSpace);
}

FRotationTranslationMatrix UBarnacleComponent::GetVertexMatrix() const
{
	// get world space location of vertex components
	FVector location = SkinComp->GetComponentLocation();
	FRotator rotation = SkinComp->GetComponentRotation();
	FRotationTranslationMatrix mat(rotation, location);
	return mat;
}

TMap <int32, int32> UBarnacleComponent::GetDistanceMap(FName BoneName, FVector BonePosition) const
{
	TMap<int32, int32> DistanceMap;

	// loop through skinned vertexes and store the distance from the desired joint
	for (int32 i = 0; i < VertexSkinnedPos.Num(); i++)
	{
		// gets world space position of verts
		FRotationTranslationMatrix mat = GetVertexMatrix();
		FVector VertexPos = mat.TransformPosition(VertexSkinnedPos[i]);

		if (VertexPos != FVector(0, 0, 0))
		{
			// Get vector distance and store in map
			float VectorDistance = FVector::DistSquared(VertexPos, BonePosition);
			DistanceMap.Add(i, VectorDistance);
		 }
	}

	return DistanceMap;
}


// Called every frame
void UBarnacleComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
}


