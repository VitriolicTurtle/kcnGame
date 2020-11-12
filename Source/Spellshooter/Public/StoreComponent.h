// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpellshooterItem.h"
#include "StoreComponent.generated.h"

class UStoreComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FItemAdded, AActor*, Owner, UStoreComponent*, Store, USpellshooterItem*, Item);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FItemRemoved, AActor*, Owner, UStoreComponent*, Store, USpellshooterItem*, Item);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPELLSHOOTER_API UStoreComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UStoreComponent();

protected:
	virtual void BeginPlay() override;

	

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Store")
		TArray<class USpellshooterItem*> storeItems{};


public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Store")
		int32 weaponAmount = 0;

	UPROPERTY(BlueprintAssignable, Category = "Store")
		FItemAdded OnItemAdded {};

	UPROPERTY(BlueprintAssignable, Category = "Store")
		FItemRemoved OnItemRemoved {};
	
	UFUNCTION(BlueprintCallable, Category = "Store")
		bool getItemFromStore(USpellshooterItem* Item);

	UFUNCTION(BlueprintCallable, Category = "Store")
		bool removeItemFromPlayer(USpellshooterItem* Item);

	UFUNCTION(BlueprintCallable, Category = "Store")
		void getStoreList(TArray<USpellshooterItem*>& SendStoreItems);

};
