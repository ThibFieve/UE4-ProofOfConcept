// Copyright Epic Games, Inc. All Rights Reserved.

#include "Building_escape.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, Building_escape, "Building_escape" );



// pointer , its just like reference useful to avoid copy data , its the 
//memory adress of a type , ex: FType *NameOfPointer
// it is important that the type reflect the type of object ze pointing to 
// NameOfPoiter is a poitner
// AActor *SomeActor , Someactor is a pointer of an AActor
// if we type *SomeActor, it will de-references the pointer , we actually get the value of that adress
// exemple , AActor class has a method GetName(), so ze can write (*SomeActor).GetName()
// Howere you can follow and access in one using ->, arrow operator
// SomeActor->GetName(). To sum up , use qrrow operqtor when pojtner , qnd dot when its not
//



// inheritance , a ford is a car . is a . trqbsmits attributes
// components , a car has a driver . has a . good to share common behaviorus and features.  mesh , audio collision

// we gonna make WorldPosition Component


//