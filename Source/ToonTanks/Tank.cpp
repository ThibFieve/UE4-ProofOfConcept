// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

ATank::ATank() //constructor , the :: is scope operator , it is necessary so it's not jsut makking a new function , but making the constructor !
{
    

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Arm"));
	SpringArm->SetupAttachment(RootComponent); //BasePawn::BaseMesh

     Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm); //BasePawn::BaseMesh
}




// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	TankPlayerController = Cast<APlayerController>(GetController()); // if you go to definition , GetController returns Acontroler , belong to Pawn class , A player controller is a child of Acontroller
    // i cannot have a pointer of type player controller poiting to the adress of a parent Acontroller
    // plot twist the object behind the pointer of Acontroller is actually an AplayerController object !
    //  WE NEED TO CAST ! //
}



// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);//Super takes the parent class implementation 
    PlayerInputComponent->BindAxis(TEXT("MoveForward"),this, &ATank::Move); // address of function Move of Atank, a way to pass function to other functions
  // will be called every frame   it is an access maping , so it means that the function is called every frame and fed the value of the input
  // Action mapping means it is only called when the key is pressed.
 
    PlayerInputComponent->BindAxis(TEXT("Turn"),this, &ATank::Turn);
 // Access Mapping is called every frqme and call the function and feed it the vqlue of the key input ,  use bindaxis
//whereas action mapping is only calling the function  when the chosen key is pressed.  use bindaction

PlayerInputComponent->BindAction(TEXT("Fire"),IE_Pressed,this, &ATank::Fire); // &Super::Fire doesnt work 
//A derived class may access it's own protected members, but it cannot access the protected members of another class, even if that class is the parent type.

}

void ATank::Move(float Value)
{ 
    UE_LOG(LogTemp,Warning, TEXT("Value: %f"),Value);

    FVector DeltaLocation(0.f); // see definition of FVectorS , could also write         Fvector Delatalocation = Fvector::ZeroVector
    //X = Value * DeltaTime* Speed
    
	DeltaLocation.X = Value*SpeedTank *UGameplayStatics::GetWorldDeltaSeconds(this); // static function means we dont need an acutal instance of Ugameplays static class to accesss that function !

	AddActorLocalOffset(DeltaLocation,true); // first parameter is optional 

}

void ATank::Turn(float Value)
{
    FRotator DeltaRotation(0.f, RotationTank*Value *UGameplayStatics::GetWorldDeltaSeconds(this) , 0.f);
    AddActorLocalRotation(DeltaRotation,true);
}


// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



	// EXPERIMENTAL CODE //////////////////////////////////////////

	//FVector DeltaLocation(0.f); // see definition of FVectorS
	//DeltaLocation.X = 2.f;

	//AddActorLocalOffset(DeltaLocation); // first parameter is optional 

	// EXPERIMENTAL CODE //////////////////////////////////////////




    if (TankPlayerController)
    {
        FHitResult HitResult;//local variable
        TankPlayerController-> GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility,false, HitResult);// hit result will be changed in there and filled with dataù

        //  void func(int & parameter); means that the paramater object will be changed  pass by reference, void func(int parameter); means that the paramater will be copied in the function scope and orginial will not be changed


        /////////////////////////////////////////////////////////////////////////////////////////////////DEBUG SPHERE ////////////////////////////////////////


      //  DrawDebugSphere(GetWorld(), 
       // HitResult.ImpactPoint,
       // 25.f,
       // 12,
       // FColor::Red,
        //false,
        //-1.f);


        /////////////////////////////////////////////////////////////////////////////////////////////////DEBUG SPHERE ////////////////////////////////////////
        
        Super::RotateTurret(HitResult.ImpactPoint); // from parent class


        

    }
 


}


void ATank::HandleDestruction()
{
    Super::HandleDestruction();
    SetActorHiddenInGame(true); // the camera will remain but the actor will disapear visually
    SetActorTickEnabled(false); // will stop the tick function from this class
    bAlive =false;
}
