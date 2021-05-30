// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWorldList.h"



//FString Hiddenword= TEXT("cake") instead of decalring here ,we declare it in header file , lesson 23, this is bad , makes it global. Also it's bad practice
//HiddenWord varaible needs to be used across multiple functions in the BullCowCartridge
//BCC class creates an instance of BCC, but if we runn two instances of the bullcowgame , they will both change a shared global variable , bad

void UBullCowCartridge::BeginPlay() // When the game starts , run when game start
// control and left click to see where each variable is from , good for finding what is what
{
    Super::BeginPlay();
    //Super is to ahve inheritence of somtehing , an extension
    InitGame();

  

    PrintLine(FString::Printf(TEXT("The HiddenWord is : %s, \nIt is %i charcahter long"), *Hiddenword, Hiddenword.Len())); // see line 54 , this is a debug line
    // they redefiner Printline in cartridge.h so that it alreayd incluides the FString::Printf and we are not actually forced to use it every time

    // Setting up the game
    // we decalre in the header , because otherhwise we running this the fucntion would not be declared quite yet becasue it's at the bottom of the page, and we would have an error

    // see replace and seach for some words and repalce across all the files. lesson 30. go in the edit tool top left





}

void UBullCowCartridge::OnInput(const FString &Input) // When the player puts an input, see lecture 17 unreal has its own C++ type
// we are not copying what the player input , we refer to the address of the data ,constant reference 
//stdcout<<"welcome"; or std::string Word="Welcome" this is to declare the string ,it's all is C++ ,in unreal we need to use FString instead
{

    //FString a = "a";
    //FString b = "a";  wokrs for stringf to do a==b, becasue already implemented in stringf, but it doesnt work for everything

    //a.Equals(b); // for the rest it is  otherhwise a==b might be checking if same pointer and whatnot

    if (bGameOver)
    {
        ClearScreen();
        InitGame();
        return; // allows to remvoe teh else and such !
    }
    else
    {

        ClearScreen();
        /*FString Hiddenword= TEXT("cake")  ;//capital to begin with the variable , 
     we need to use text macro from so that engine can make it work on any platform , and should also be more efficient, TEXT is the macro
     so unreal can encode it corrrectly*/

        // c++ dot operator that is prebuilt for fstring , Hiddenword my variable fstring . Hiddenword.  gives us many option

        Hiddenword.Len(); // gives lengt as an integer

        PrintLine(("You typed " + Input)); /* input holds the string written by the player , becasue input is  a string you can do +, other way PrintLine(FString::Printf(Text("you typed! %s"), *Input))
    FString::Printf(Text("you typed! %s"), *Input) returns a new fstring , we go in fstring class and find static function Printf ,(it's a function that dont need to have an object initialised
     is the pointer *input gives the memory adress of object input, the adress is an array of 5 element for "cake" . one for each letter follwoed by a 0 to let compiler know it's the end of teh stirng
     for an int32 it has 4 byte , 32 bit */
        if (Input == Hiddenword)
        {
            PrintLine(TEXT("You won"));
            EndGame();
        }
        else
        {
            if (Input.Len() != Hiddenword.Len())
            {
                PrintLine(FString::Printf(TEXT("The length of the word is  %i "), Hiddenword.Len()));
                // we could use return to avoid to run Isisogram and what not
            }
            if(!IsIsogram(Input)){
            PrintLine(TEXT("You lost, no repeating letters try again"));
            //  FString is a TArray of TCHAR, array length start couting from  0
            }
            int32 Bulls,Cows;
            GetBulledCows(Input,Bulls,Cows);

           PrintLine(TEXT("You have %i Bulls and %i Cows"), Bulls,Cows);
            PrintLine(TEXT("You lost,try again"));
            --Lives;
            PrintLine(FString::Printf(TEXT("you got   %i  lives left"), Lives));
            if (Lives <= 0)
            {
                PrintLine(TEXT("You lost, and are out of lives"));
                EndGame();
            }
        }
    }
}

//We want to create new function   void UBullCiwCartridge::InitGame() , UBullCowCartridge it the class where we wanna tale the function initgame from , to avoid anem calsh between fucntiond
void UBullCowCartridge::InitGame()
{
    
    int32 ListLength=Words.Num();
// Words.Emplace() , .Remove() remove matching eleement , .RemoveAt()  etc etc see unreal engienr documentation, can be used to pick any member of the list 
//for (type TempVar: Data)  , so for us   for(FString Hiddenword: Words){}
    //{ will parse every element of the collection}

    
// there are plenty of specific functions like rangerandom that are specific to unreal engine , using regualr C++ function might not work all the time for every game 

    Hiddenword = Words[FMath::RandRange(0,5)]; // set the hidden word
    Lives = Hiddenword.Len();  //set lives

/*
    const TCHAR ArrayOfChars[] = TEXT("cake")  ;// Hiddenword is a FString we cannot use it directly , need to have a string array of cahr like "cake";
*/
    const TCHAR ArrayOfChars[] = {TEXT('c'),TEXT('a'),TEXT('k'),TEXT('e'),TEXT('\0')}; //that's how it is , it's the same
    PrintLine(TEXT("Character 1 of the hidden word is %c"), Hiddenword[0] ); //print c


    bGameOver = false;
    PrintLine(TEXT("Hi there, welcome to bull cows \n"));
    PrintLine(FString::Printf(TEXT("Guess the %i letter word"), Hiddenword.Len())); // Magic number to be removed
    // FString::Printf().   doesnt require instance of FString but doesnt acutally print anything ti format and allows to put data in text , like integer or string
    PrintLine(FString::Printf(TEXT("you got   %i  lives left"), Lives));
    PrintLine(TEXT("Type your guess.\n press enter to continue"));
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("That's the end, let's restart,press enter"));
}

// norn on boolean , good aractice call them with prefix b  , exempel bool bwongame

// you can do ++Lives pre increment  , but also Lives++ post increment , takes a copy , increment the value of Lives but return the copy , so Lives will be incremeneted after that line is done



void UBullCowCartridge::ProcessGuess(FString Guess) // just for practice
{
   return  ; 
}


bool UBullCowCartridge::IsIsogram(const FString&  Word) const
{
    // do { code is executed}
    //while (condition) , so at least the code is exectued once
    int32 Index = 0 ;
    int32 length = Word.Len() ;
    
    for (int32 Index=0; Index<length; Index++)
    {   
        for(int32 Comparison = Index + 1; Comparison < length; Comparison++)
        {
            if(Word[Index]== Word[Comparison])
            {
                return false;
            }

        }
        

    }

    // can also write for( int32 Index=0, comparison =Index+1; comparison etc)

    return true;
}


//const function are static function , they cannot change the value that you pass it as argumetn or any other varaibvle actually, and cosnt functionc an only call const function themselves
//

//LESSON 51 and 52 DISCUSSION OF MEMORY !

// every time  we pass a value we create a copy of the value , this called passing by value
// we can do some passing by reference !  pointers and reference 
// & is an anddress in memory, you cannot reasign a reference 

//REALLY IMPORTANT 

/*
int32 a=0;
int32 b=5;

int32& refa=a; 
refa is given the value of a refa=a

refa =b;
no , that will change the value of a ! it prints a=b and refa=b  , thats why we use const

we should do const int32& refa=a;

it's better to use pass by const reference than per value , passing per value makes copies and new variable for function call etc .. not optimized
*/

// there are plenty of specific functions like rangerandom that are specific to unreal engine , using regualr C++ function might not work all the time for every game 


void UBullCowCartridge::GetBulledCows(const FString& Guess, int32& BullCount, int32& CowCount) const

{// so here we on purpose use the "unwanted " behaviour of reference when changing its value to change the value of Cows and Bull !!!! 
    BullCount=0;
    CowCount=0;

    for (int32 GuessIndex=0 ; GuessIndex< Guess.Len(); GuessIndex++)
    {
        if( Guess [GuessIndex] == Hiddenword[GuessIndex])
        {
           BullCount++ ;
           continue ; //  jump the rest of teh code and jump back to the for loop ligne 205    
        }
        for (int32 HiddenIndex= 0 ; HiddenIndex < Hiddenword.Len(); HiddenIndex++)
        {
            if(Guess[GuessIndex] == Hiddenword[HiddenIndex])
            {
                CowCount++;
                break; // becasue words are isogram , its wasted time
            }

        }

    }

}
//see lesson 57 for break and continue

//lesson 58 , Structs, our own DATA TYPES , by default their data is public , in classes data is private , quite similar to classes but one is private teht other one is not. Both are type
// FString is a class , so FString Word, tho i can use Word.Len() that is a function , but couldnt do Word.Bulls that is one of the data

/*

struct FStructurName{
    type StructureMember1;
    type StructMember2;

};
struct FBullCowCount{

	int32 Bulls =0;
	int32 Cows = 0; // both are public per def
};
FBullCowCount Count ={2,3};
Count.Bull=9 , i can do that bc struct and not class
could make it that getbulledcows reutrn such object 
*/

