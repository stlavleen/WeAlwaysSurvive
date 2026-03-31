// Fill out your copyright notice in the Description page of Project Settings.


#include "DirectoryVisitor.h"

DirectoryVisitor::DirectoryVisitor(TArray<FString>& output) : output(output)
{
}

bool DirectoryVisitor::Visit(const TCHAR* FilenameOrDirectory, bool bIsDirectory)
{
	if (!bIsDirectory)
		output.Add(FilenameOrDirectory);

	return true;
}