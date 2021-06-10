#include "ItemSlot.h"

#include "Single/GameInstance/RPGGameInstance.h"

#include "Components/Image.h"



UItemSlot::UItemSlot(const FObjectInitializer& objInitializer) : 
	Super(objInitializer)
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ITEM_INFO(
		TEXT("DataTable'/Game/Resources/DataTable/DT_ItemInfo.DT_ItemInfo'"));
	if (DT_ITEM_INFO.Succeeded()) DT_ItemInfo = DT_ITEM_INFO.Object;

	static ConstructorHelpers::FObjectFinder<UTexture2D> T_NULL(
		TEXT("Texture2D'/Game/Resources/Image/Slot/T_Null.T_Null'"));
	if (T_NULL.Succeeded()) T_Null = T_NULL.Object;
}

void UItemSlot::InitializeSlot(ESlotType slotType, FName inCode)
{
	Super::InitializeSlot(slotType, inCode);

	SetItemInfo(inCode);
	
	UpdateItemImage();
}

void UItemSlot::UpdateItemImage()
{
	UTexture2D* itemImage = nullptr;


	// ������ ������ ����ִٸ� ������ �̹��� ���
	if (ItemInfo.IsEmpty()) itemImage = T_Null;

	// ������ ������ ������� �ʴٸ� ������ �̹��� �ε�
	else
	{
		// ������ �̹��� ��ΰ� ����ִٸ� ������ �̹��� ���
		if (ItemInfo.ItemImagePath.IsNull()) itemImage = T_Null;

		// ������ �̹��� ��ΰ� ������� �ʴٸ� ������ �̹����� �ε��Ͽ� ���
		else itemImage = Cast<UTexture2D>(
			GetManager(FStreamableManager)->LoadSynchronous(ItemInfo.ItemImagePath));
	}

	// ������ �̹��� ����
	if (itemImage) GetSlotImage()->SetBrushFromTexture(itemImage);
}

void UItemSlot::SetItemInfo(FName itemCode)
{
	// ������ ���� ����
	FString contextString;
	FItemInfo* findedItemInfo = nullptr;

	// ������ �ڵ尡 ����ִٸ�
	if (itemCode.IsNone())
	{
		// ������ ������ ���ϴ�.
		ItemInfo = FItemInfo();
		return;
	}

	// ������ �ڵ尡 ������� �ʴٸ� ������ �ڵ带 �̿��Ͽ� ������ ������ ����ϴ�.
	else findedItemInfo = DT_ItemInfo->FindRow<FItemInfo>(itemCode, contextString);

	if (findedItemInfo == nullptr) ItemInfo = FItemInfo();
	else ItemInfo = *findedItemInfo;
}
