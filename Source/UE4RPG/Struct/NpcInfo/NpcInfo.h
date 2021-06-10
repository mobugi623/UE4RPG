#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Struct/NpcDialogInfo/NpcDialogInfo.h"
#include "NpcInfo.generated.h"

USTRUCT(BlueprintType)
struct UE4RPG_API FNpcInfo : 
	public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	// Npc �̸�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText NpcName;

	// �⺻ ��ȭ ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FNpcDialogInfo DefaultDialogInfo;

	// ���� �ڵ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ShopCode;


};
