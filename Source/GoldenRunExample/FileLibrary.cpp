// Fill out your copyright notice in the Description page of Project Settings.


#include "FileLibrary.h"
#include "string"

PRAGMA_DISABLE_OPTIMIZATION

void UFileLibrary::SaveFromFile(FSaveInformation Info)
{
	FString ConfigPath = FPaths::ProjectDir() / TEXT("Data") / TEXT("Saved.json");
	
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
	
	TSharedPtr<FJsonObject> BaseObject = MakeShareable(new FJsonObject);
		BaseObject->SetStringField("Location", Info.ActorLocation.ToString());
		BaseObject->SetStringField("CurrentDig", std::to_string(Info.CurrentDig).c_str());
		BaseObject->SetStringField("CurrentGold", std::to_string(Info.CurrentGold).c_str());

	JsonObject->SetObjectField("BaseParams", BaseObject);

	TSharedPtr<FJsonObject> ActorArrayObject = MakeShareable(new FJsonObject);
	for (int Index = 0; Index < Info.ArrayInfo.Num(); Index++)
	{
		ActorArrayObject->SetStringField(std::to_string(Index).c_str(), Info.ArrayInfo[Index].ClassLocation.ToString());
	}

	JsonObject->SetObjectField("Mapping", ActorArrayObject);

	TSharedPtr<FJsonObject> ImageArrayObject = MakeShareable(new FJsonObject);
	for (int Index = 0; Index < Info.GoldArrayTexture2D.Num(); Index++)
	{
		ImageArrayObject->SetStringField("Image", std::to_string(1).c_str());
	}

	JsonObject->SetObjectField("ImageArray", ImageArrayObject);

	FString OutputString;
	TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);

	FFileHelper::SaveStringToFile(OutputString, *ConfigPath);
}

FSaveInformation UFileLibrary::LoadFromFile()
{
	FString ConfigPath = FPaths::ProjectDir() / TEXT("Data") / TEXT("Saved.json");

	FSaveInformation LoadInfo;
	
	FString JsonString;
	FFileHelper::LoadFileToString(JsonString, *ConfigPath);
	TSharedPtr<FJsonObject> JsonConfig = MakeShareable(new FJsonObject());
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);
	FJsonSerializer::Deserialize(JsonReader, JsonConfig);
	
	const TSharedPtr<FJsonObject>& ObjectConfig = JsonConfig->GetObjectField(TEXT("BaseParams"));

	FString TmpValue = ObjectConfig->GetStringField(TEXT("Location"));
	TArray<FString> Out;
	TmpValue.ParseIntoArray(Out,TEXT(" "),true);
	TArray<FString> X;
	TArray<FString> Y;
	TArray<FString> Z;
	Out[0].ParseIntoArray(X, TEXT("="), true);
	Out[1].ParseIntoArray(Y, TEXT("="), true);
	Out[2].ParseIntoArray(Z, TEXT("="), true);
	
	LoadInfo.ActorLocation = FVector(FCString::Atod(*X[1]), FCString::Atod(*Y[1]), FCString::Atod(*Z[1]));
	LoadInfo.CurrentDig = std::atoi(TCHAR_TO_UTF8(*ObjectConfig->GetStringField(TEXT("CurrentDig"))));
	LoadInfo.CurrentGold = std::atoi(TCHAR_TO_UTF8(*ObjectConfig->GetStringField(TEXT("CurrentGold"))));

	const TSharedPtr<FJsonObject>& ObjectConfig1 = JsonConfig->GetObjectField(TEXT("Mapping"));
	
	for(int Index = 0; Index < 100; Index++)
	{		
		TmpValue = ObjectConfig1->GetStringField(std::to_string(Index).c_str());
		TmpValue.ParseIntoArray(Out,TEXT(" "),true);
		Out[0].ParseIntoArray(X, TEXT("="), true);
		Out[1].ParseIntoArray(Y, TEXT("="), true);
		Out[2].ParseIntoArray(Z, TEXT("="), true);
		
		LoadInfo.ArrayInfo.Add(FSaveArrayElementInfo() = { nullptr, FVector(FCString::Atod(*X[1]), FCString::Atod(*Y[1]), FCString::Atod(*Z[1])) });
	}
	
	return LoadInfo;
}

