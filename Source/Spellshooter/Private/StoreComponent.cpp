// Fill out your copyright notice in the Description page of Project Settings.


#include "StoreComponent.h"
#include "humanCharacter.h"

// Sets default values for this component's properties
UStoreComponent::UStoreComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStoreComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UStoreComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

//	DOESNT WORK YET!
bool UStoreComponent::EquipItem(USpellshooterItem* Item)
{
	auto* Owner = GetOwner();
	UWorld* World = GetWorld();
	//auto* relevantPlayerCharacter = Cast<AHumanCharacter>(Cast<APlayerController>(Owner)->GetCharacter());
	//relevantPlayerCharacter->ServerGiveAbilityFromItem(Item);
	return false;
}
