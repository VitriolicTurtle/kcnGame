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

bool UStoreComponent::getItemFromStore(USpellshooterItem* Item){
	
	OnItemAdded.Broadcast(GetOwner(), this, Item);
	return true;
}

bool UStoreComponent::removeItemFromPlayer(USpellshooterItem* Item)
{
	OnItemRemoved.Broadcast(GetOwner(), this, Item);
	return true;
}

void UStoreComponent::getStoreList(TArray<USpellshooterItem*>& SendStoreItems){

	for (const auto& item : storeItems) {
		SendStoreItems.Add(item);
	}

}
