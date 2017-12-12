// Copyright Aaron Carlisle 2016

#include "OpenDoor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	// get owner
	AActor* Owner = GetOwner();

	// new rotation value
	FRotator NewRotation = FRotator(0.0f, 30.0f, 0.0f);

	// set door rotation
	Owner->SetActorRotation(NewRotation);
	
	// UE_LOG(LogTemp, Warning, TEXT("Owner Rotation is %s"), *sOwnerRotation);
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

