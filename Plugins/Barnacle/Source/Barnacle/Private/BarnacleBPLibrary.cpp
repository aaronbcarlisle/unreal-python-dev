// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "BarnacleBPLibrary.h"
#include "Barnacle.h"

UBarnacleBPLibrary::UBarnacleBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

FVector UBarnacleBPLibrary::Barnacle(int32 Vertex, USkeletalMeshComponent * MeshComp)
{

	// get vertex position
	FVector VertexPosition = MeshComp->GetSkinnedVertexPosition(Vertex);

	// if a vector is found, return that
	if (VertexPosition.Size())
	{
		return VertexPosition;
	}

	// else, return an empty vector
	UE_LOG(LogTemp, Warning, TEXT("No vector found for given vertex, defaulting to (0, 0, 0)."));
	return FVector(0,0,0);
}
