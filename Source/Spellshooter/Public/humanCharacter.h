// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
//#include "AbilitySystemInterface.h"
#include "HumanCharacter.generated.h"


UCLASS(config = Game)
class AHumanCharacter : public ACharacter
{
	GENERATED_BODY()

		/** Camera boom positioning the camera behind the character */
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

		/** Follow camera */
		UPROPERTY(EditAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
			class UCameraComponent* FollowCamera;
public:
	AHumanCharacter();

	UPROPERTY(BlueprintReadWrite, Category = "Shop")
	AActor* playerWeapon = nullptr;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		float BaseLookUpRate;

	UPROPERTY(EditAnywhere, Category = "shooting")
		TSubclassOf<class Abullet> BPbullet;

	// Player health
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "health")
		float maxPlayerHP;

	UPROPERTY(ReplicatedUsing = onRep_currentPlayerHP, EditAnywhere, BlueprintReadWrite, Category = "health") //-------->
		float currentPlayerHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "health")
		float tempPlayerHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "health")
		float playerHPpercent;

	UFUNCTION(BlueprintPure, Category = "health")
		float getPlayerHP();

	UFUNCTION(BlueprintCallable, Category = "health")
		void updatePlayerHP(float HP);


	UFUNCTION(BlueprintCallable, Category = "health")
		void playerTakeDamage(float damage);

	// Gun muzzle offset from the camera location.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector MuzzleOffset;

	UPROPERTY(ReplicatedUsing = onRep_Kill, BlueprintReadOnly, Category = Gameplay)
		AHumanCharacter* killer;

	UFUNCTION()
		void onRep_kill();

	UFUNCTION(BlueprintImplementableEvent)
		void displayDeathScreen();

	UFUNCTION()
		void onRep_currentPlayerHP();
	
protected:
	void BeginPlay();
	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	void shoot();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(Server, Reliable)//, WithValidation)
	void serverOnShoot();

protected:
	/** Equipped Items */
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Abilities, meta = (AllowPrivateAccess = "true"))
	//	TMap<0, FGameplayAbilitySpecHandle> EquipmentAbilities{};
	
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

