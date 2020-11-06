// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellshooterItem.h"

FString USpellshooterItem::GetIdentifierString() const {
	return GetPrimaryAssetId().ToString();
}

FPrimaryAssetId USpellshooterItem::GetPrimaryAssetId() const {
	return FPrimaryAssetId(itemType, GetFName());
}