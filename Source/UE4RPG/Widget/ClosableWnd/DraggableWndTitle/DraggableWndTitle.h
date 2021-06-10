#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DraggableWndTitle.generated.h"

UCLASS()
class UE4RPG_API UDraggableWndTitle final : 
	public UUserWidget
{
	GENERATED_BODY()

private :
	// �巡���� üũ�� ��ư
	UPROPERTY(meta = (BindWidget))
	class UButton * Button_Draggable;

	// �ݱ� ��ư
	UPROPERTY(meta = (BindWidget))
	class UButton * Button_Close;

	// â ����
	UPROPERTY(meta = (BindWidget))
	class UTextBlock * Text_Title;

	// �巡�� ������ ��Ÿ���ϴ�.
	bool bIsDragging;
	
	// �巡�� ��ų â ������ ��Ÿ���ϴ�.
	class UClosableWnd* TargetWnd;

	// �巡�� ���� ��ġ�� ��Ÿ���ϴ�.
	FVector2D DragStartPosition;

	// �巡�� ���� �Է� ���콺 ��ġ�� ��Ÿ���ϴ�.
	FVector2D DragInputPosition;
	
protected :
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Window Title")
	FText TitleText;

public :
	UDraggableWndTitle(const FObjectInitializer& ObjectInitializer);

protected :
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public :
	FORCEINLINE void SetDragTarget(class UClosableWnd* targetWnd)
	{ TargetWnd = targetWnd; }

	FORCEINLINE class UButton* GetCloseButton() const
	{ return Button_Close; }

private :
	void DragWidget();

	UFUNCTION()
	void OnWidgetDragStarted();

	UFUNCTION()
	void OnWidgetDragFinished();

public :
	FORCEINLINE FText GetTitleText() const
	{ return TitleText; }

	void SetTitleText(FText newTitleText);

};
