// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpellshooterItem.h"
#include "StoreComponent.generated.h"

class UStoreComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FItemPurchase, AActor*, Owner, UStoreComponent*, Store, USpellshooterItem*, Item);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPELLSHOOTER_API UStoreComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStoreComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/*
	*	Item purchasing and equipping
	*/
	UPROPERTY(BlueprintAssignable, Category = Inventory)
		FItemPurchase OnItemPurchased{};
	
	UFUNCTION(BlueprintCallable, Category = "Store")
		bool EquipItem(USpellshooterItem* Item);

};
