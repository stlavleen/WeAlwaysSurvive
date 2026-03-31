// Fill out your copyright notice in the Description page of Project Settings.


#include "FileSystemHelper.h"
#include "DirectoryVisitor.h"

TArray<FString> UFileSystemHelper::GetFilesNames(const FString folderName) const
{
	auto& platformFile = FPlatformFileManager::Get().GetPlatformFile();
	auto gameDir = GetGamePath();
	auto& dir = gameDir.Append(folderName);
	TArray<FString> filesNames;
	DirectoryVisitor visitor(filesNames);

	platformFile.IterateDirectory(*dir, visitor);

	return filesNames;
}

FString UFileSystemHelper::GetGamePath() const
{
	return FPaths::ConvertRelativePathToFull(FPaths::ProjectDir());
}
