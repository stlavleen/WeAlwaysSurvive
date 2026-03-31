// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericPlatform/GenericPlatformFile.h"

/**
 * 
 */
class WEALWAYSSURVIVE_API DirectoryVisitor : public IPlatformFile::FDirectoryVisitor
{
private:
	TArray<FString>& output;
public:
	DirectoryVisitor(TArray<FString>& output);
	virtual bool Visit(const TCHAR* FilenameOrDirectory, bool bIsDirectory) override;
};
