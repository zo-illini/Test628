#include "NewEditorTool.h"
#include "UObject/ConstructorHelpers.h"

UNewEditorTool::UNewEditorTool(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void UNewEditorTool::ExecuteThis()
{
	FillBoneTransform();
	FillCurveVector();
}

void UNewEditorTool::EraseCurve() 
{
	
}

void UNewEditorTool::FillBoneTransform() 
{
	BoneTransform.Empty();
	float DeltaTime = sequence->GetPlayLength() / sequence->GetNumberOfFrames();
	for (int i = 0; i < sequence->GetNumberOfFrames(); i++)
	{
		FTransform out;
		sequence->GetBoneTransform(out, TrackIdx, i * DeltaTime, true);
		BoneTransform.Add(out);
	}
}

void UNewEditorTool::FillCurveVector() 
{
	FString PackageName = TEXT("/Game/") + PackagePath + TEXT("/");
	FString BoneID = FString::FromInt(TrackIdx);
	PackageName += BoneID;
	UPackage* Package = CreatePackage(*PackageName);
	Package->FullyLoad();

	UCurveVector* CurveVectorTrans = NewObject<UCurveVector>(Package, *(BoneID + TEXT("_Trans")), RF_Public | RF_Standalone | RF_MarkAsRootSet);
	UCurveVector* CurveVectorRot = NewObject<UCurveVector>(Package, *(BoneID + TEXT("_Rot")), RF_Public | RF_Standalone | RF_MarkAsRootSet);
	UCurveVector* CurveVectorScale = NewObject<UCurveVector>(Package, *(BoneID + TEXT("_Scale")), RF_Public | RF_Standalone | RF_MarkAsRootSet);

	//Package->AddToRoot();
	//CurveVectorTrans->AddToRoot();
	//CurveVectorRot->AddToRoot();
	//CurveVectorScale->AddToRoot();


	float DeltaTime = sequence->GetPlayLength() / sequence->GetNumberOfFrames();
	FVector Val;
	for (int i = 0; i < BoneTransform.Num(); i++)
	{
		Val = BoneTransform[i].GetLocation();
		CurveVectorTrans->FloatCurves[0].AddKey(i * DeltaTime, Val[0]);
		CurveVectorTrans->FloatCurves[1].AddKey(i * DeltaTime, Val[1]);
		CurveVectorTrans->FloatCurves[2].AddKey(i * DeltaTime, Val[2]);

		Val = BoneTransform[i].GetRotation().Euler();
		CurveVectorRot->FloatCurves[0].AddKey(i * DeltaTime, Val[0]);
		CurveVectorRot->FloatCurves[1].AddKey(i * DeltaTime, Val[1]);
		CurveVectorRot->FloatCurves[2].AddKey(i * DeltaTime, Val[2]);

		Val = BoneTransform[i].GetScale3D();
		CurveVectorScale->FloatCurves[0].AddKey(i * DeltaTime, Val[0]);
		CurveVectorScale->FloatCurves[1].AddKey(i * DeltaTime, Val[1]);
		CurveVectorScale->FloatCurves[2].AddKey(i * DeltaTime, Val[2]);
	}

	FAssetRegistryModule::AssetCreated(CurveVectorTrans);
	FAssetRegistryModule::AssetCreated(CurveVectorRot);
	FAssetRegistryModule::AssetCreated(CurveVectorScale);

	Package->MarkPackageDirty();
	FString PackageFileName = FPackageName::LongPackageNameToFilename(PackageName, FPackageName::GetAssetPackageExtension());
	UPackage::SavePackage(Package, CurveVectorTrans, EObjectFlags::RF_Public | EObjectFlags::RF_Standalone, *PackageFileName);
	UPackage::SavePackage(Package, CurveVectorRot, EObjectFlags::RF_Public | EObjectFlags::RF_Standalone, *PackageFileName);
	UPackage::SavePackage(Package, CurveVectorScale, EObjectFlags::RF_Public | EObjectFlags::RF_Standalone, *PackageFileName);

	
}