// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"


struct FBullCowCount
{

	int32 Bulls =0;
	int32 Cows = 0; // both are public per def
};



UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

	public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString& Input) override;
	void InitGame();// we decalre in the header a function , because otherhwise we running the code and calling the function and  the fucntion declaration migth be later on down the code ,  we would have an error.
	//but declared in teh header the C++ code will go to the header and that header will go back to and look for the function 
	//because it reads top down
	void EndGame();

	bool IsIsogram(const FString& Word) const;
	void ProcessGuess(FString Guess);

	void GetBulledCows(const FString& Guess, int32& BullsCount,int32& CowCount) const;
	// out paramter are reference parameter no copied but are not CONST ! dangerous
 
	// Your declarations go below!
	private:
	
	FString Hiddenword;
	int32 Lives;
	bool bGameOver;

	//TArray<FString> Isograms; could do a valid list of Words
	
 // unreal engine uses int32 instead of int , same for FString , specific variables
};
