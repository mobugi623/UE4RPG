#pragma once

#include "CoreMinimal.h"
#include "NpcDialogInfo.generated.h"


USTRUCT(BluePrintType)
struct UE4RPG_API FNpcDialogInfo
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MultiLine = "true"))
	TArray<FText> DialogText; 

public :
	// ��ȭ ������ ����ִ��� Ȯ���մϴ�.
	bool IsEmpty() const;

public :
	// ������ ��ȭ �ε����� ��ȯ�մϴ�.
	FORCEINLINE int32 GetLastDialogIndex() const
	{ return DialogText.Num() - 1; }

};
