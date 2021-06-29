#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "UObject/Object.h"
#include "NewEdMode.h"
#include "Curves/CurveVector.h"
#include "UObject/Package.h"
#include "AssetRegistryModule.h"
#include "NewEditorTool.generated.h"

class FNewEdMode;

UCLASS()
class UNewEditorTool : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	FNewEdMode* ParentMode;
	
	UPROPERTY(EditAnywhere)
		UAnimSequence* sequence;

	UPROPERTY(VisibleAnywhere)
		TArray<FTransform> BoneTransform;

	UPROPERTY(EditAnywhere)
		int TrackIdx;

	UPROPERTY(EditAnywhere)
		FString PackagePath;

	//UCurveVector * CurveVector;

	UFUNCTION(Exec)
	void ExecuteThis();

	UFUNCTION(Exec)
	void EraseCurve();

	void FillBoneTransform();
	void FillCurveVector();

	void SetParent(FNewEdMode* NewParent)
	{
		ParentMode = NewParent;
	}
};