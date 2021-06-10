#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ClosableWnd.generated.h"

DECLARE_MULTICAST_DELEGATE(FWndEventSignature)

UCLASS()
class UE4RPG_API UClosableWnd : 
	public UUserWidget
{
	GENERATED_BODY()

public :
	// â�� ���� �� �߻��ϴ� �̺�Ʈ
	FWndEventSignature OnWndClosed;

public :
	// Widget Controller
	class UWidgetController* WidgetController;

public :
	// â ũ�⸦ ��Ÿ���ϴ�.
	FVector2D WndSize;

	// ���� ó���� â���� ��Ÿ���ϴ�.
	bool bBeClose;

private :
	UPROPERTY(meta = (BindWidget))
	class UDraggableWndTitle * DraggableWndTitle;

protected :
	virtual void NativeConstruct() override;

public :
	// â�� ������ �����մϴ�.
	void SetTitleText(FText newTitleText);

	FORCEINLINE void SetTielText(FString newTitleText)
	{ SetTitleText(FText::FromString(newTitleText)); }

	// �� â�� �ݽ��ϴ�.
	UFUNCTION()
	void CloseThisWnd();

	// �� â�� CanvasPanelSlot �� ��ȯ�մϴ�.
	/// - �� �޼���� �׻� ȭ�鿡 �߰��� �� ���Ǿ�� �մϴ�.
	class UCanvasPanelSlot* GetCanvasPanelSlot() const;
	
};
