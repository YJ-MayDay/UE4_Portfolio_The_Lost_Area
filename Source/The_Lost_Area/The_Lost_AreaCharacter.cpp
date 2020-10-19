// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "The_Lost_AreaCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"
#include "Runtime/Engine/Classes/Components/SceneComponent.h"
#include "PlayerCharacter/BulletProjectile.h"
#include "Runtime/Engine/Classes/Animation/AnimMontage.h"
#include "Runtime/Engine/Classes/Animation/AnimInstance.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "NPCCharacter/NPCCharacter.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include "Runtime/UMG/Public/Blueprint/WidgetBlueprintLibrary.h"
#include "Runtime/UMG/Public/Blueprint/WidgetLayoutLibrary.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "Engine.h"
#include "PlayerCharacter/StatusStruct.h"
#include "Widget/PlayerInfo.h"
#include "EnemyCharacter/EnemyCharacter.h"
#include "Widget/TB_ItemInfo.h"
#include "The_Lost_Area/Widget/Inventory.h"
#include "The_Lost_Area/PlayGameMode/PlayGameMode.h"
#include "Runtime/Engine/Classes/Components/AudioComponent.h"
#include "The_Lost_Area/EndGameMode/GameDataInstance.h"

AThe_Lost_AreaCharacter::AThe_Lost_AreaCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(30.f, 85.0f);

	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMesh"));
	GunMesh->SetupAttachment(GetMesh());

	GunMuzzle = CreateDefaultSubobject<USceneComponent>(TEXT("GunMuzzle"));
	GunMuzzle->SetupAttachment(GunMesh);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	InteractionRange = 200.0f;
}

void AThe_Lost_AreaCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	//Player Input binding

	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AThe_Lost_AreaCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AThe_Lost_AreaCharacter::MoveRight);

	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AThe_Lost_AreaCharacter::StartFire);
	PlayerInputComponent->BindAction("Attack", IE_Released, this, &AThe_Lost_AreaCharacter::StopFire);

	PlayerInputComponent->BindAction("Aiming",IE_Pressed, this, &AThe_Lost_AreaCharacter::TrueAiming);
	PlayerInputComponent->BindAction("Aiming", IE_Released, this, &AThe_Lost_AreaCharacter::FalseAiming);

	PlayerInputComponent->BindAction("Weapon0", IE_Pressed, this, &AThe_Lost_AreaCharacter::WeaponChange0);
	PlayerInputComponent->BindAction("Weapon1", IE_Pressed, this, &AThe_Lost_AreaCharacter::WeaponChange1);
	PlayerInputComponent->BindAction("Weapon2", IE_Pressed, this, &AThe_Lost_AreaCharacter::WeaponChange2);

	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &AThe_Lost_AreaCharacter::Reload);
	PlayerInputComponent->BindAction("Firing", IE_Pressed, this, &AThe_Lost_AreaCharacter::ToggleFiring);

	PlayerInputComponent->BindAction("Wheel", IE_Pressed, this, &AThe_Lost_AreaCharacter::ShowInventory);
	PlayerInputComponent->BindAction("ItemUse", IE_Pressed, this, &AThe_Lost_AreaCharacter::SelectItemUse);
	PlayerInputComponent->BindAction("Inventory", IE_Pressed, this, &AThe_Lost_AreaCharacter::InventoryToggle);

	PlayerInputComponent->BindAction("StageStart", IE_Pressed, this, &AThe_Lost_AreaCharacter::NowStageStart);
	PlayerInputComponent->BindAction("Interaction", IE_Pressed, this, &AThe_Lost_AreaCharacter::NPC_Interaction);

	PlayerInputComponent->BindAxis("Turn", this, &AThe_Lost_AreaCharacter::AddControllerYaw);
	PlayerInputComponent->BindAxis("TurnRate", this, &AThe_Lost_AreaCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &AThe_Lost_AreaCharacter::AddControllerPitch);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AThe_Lost_AreaCharacter::LookUpAtRate);
}

void AThe_Lost_AreaCharacter::SetupStatus()
{
	//Player 스테이터스 셋팅

	status.MaxHealthPoint = 100;

	status.HealthPoint = 100;
	OpacityCount = status.HealthPoint;
	status.AttackDamage = 20;
	status.DefensePoint = 0;
	status.MoveSpeed = 300.f;
	status.RunSpeed = 600.f;
	status.Score = 500;
}

//Weapon 메시를 배열로 가진 상태에서 해당 번호를 입력하면 해당 무기로 교체 및 교체 사운드 재생
//애님 블루프린트에서 애니메이션 노티파이를 이용하여 제작
void AThe_Lost_AreaCharacter::SetWeapon(FWeapon Weapon)
{
	
	if (Weapon.GunMesh != NULL)
	{
		GunMesh->SetSkeletalMesh(Weapon.GunMesh);
		SetTransform(Weapon);
	}

	if (NowWeapon.ChangeSound->IsValidLowLevelFast())
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), NowWeapon.ChangeSound, this->GetActorLocation());
	}
}

//현재 그려주는 무기를 바꿔주는 함수
//각 1,2,3 번 키에 대응하며 배열로 가지고 있는 무기를 입력받은 무기로 교체하며 몽타주 애니메이션 재생
void AThe_Lost_AreaCharacter::WeaponChange0()
{
	if (isReloading == false)
	{
		isGunChange = true;

		for (int32 i = 0; i < weapon.Num(); i++)
		{
			if (NowWeapon.GunMesh == weapon[i].GunMesh)
				weapon[i] = NowWeapon;
		}
		NowWeapon = weapon[0];

		UAnimInstance* Anim = GetMesh()->GetAnimInstance();
		if (!Anim->Montage_IsPlaying(EquipMontage))
			Anim->Montage_Play(EquipMontage, 1.0f);
	}
}

void AThe_Lost_AreaCharacter::WeaponChange1()
{
	if (isReloading == false)
	{
		isGunChange = true;

		for (int32 i = 0; i < weapon.Num(); i++)
		{
			if (NowWeapon.GunMesh == weapon[i].GunMesh)
				weapon[i] = NowWeapon;

		}
		NowWeapon = weapon[1];

		UAnimInstance* Anim = GetMesh()->GetAnimInstance();
		if (!Anim->Montage_IsPlaying(EquipMontage))
			Anim->Montage_Play(EquipMontage, 1.0f);
	}
}

void AThe_Lost_AreaCharacter::WeaponChange2()
{
	if (isReloading == false)
	{
		isGunChange = true;

		for (int32 i = 0; i < weapon.Num(); i++)
		{
			if (NowWeapon.GunMesh == weapon[i].GunMesh)
				weapon[i] = NowWeapon;

		}
		NowWeapon = weapon[2];

		UAnimInstance* Anim = GetMesh()->GetAnimInstance();
		if (!Anim->Montage_IsPlaying(EquipMontage))
			Anim->Montage_Play(EquipMontage, 1.0f);
	}
}

//재장전 함수
//무기의 탄종에 따라 무기를 구분하여 재장전 몽타주 ,재장전 사운드를 재생하는 함수
void AThe_Lost_AreaCharacter::Reload()
{
	if (isGunChange == false)
	{
		isReloading = true;

		if (NowWeapon.CurrentBullet < CarryFullBullet)
		{
			switch (NowWeapon.BulletType)
			{
			case EBulletType::BT_556mm:
			{
				if (Total556Bullet != 0)
				{
					UAnimInstance* Anim = GetMesh()->GetAnimInstance();
					if (!Anim->Montage_IsPlaying(ReloadMontage))
					{
						if (NowWeapon.ReloadSound->IsValidLowLevelFast())
							UGameplayStatics::PlaySoundAtLocation(GetWorld(), NowWeapon.ReloadSound, this->GetActorLocation());
						Anim->Montage_Play(ReloadMontage, 1.0f);
					}
				}
			}
			break;
			case EBulletType::BT_762mm:
			{
				if (Total762Bullet != 0)
				{
					UAnimInstance* Anim = GetMesh()->GetAnimInstance();
					if (!Anim->Montage_IsPlaying(ReloadMontage))
					{
						if (NowWeapon.ReloadSound->IsValidLowLevelFast())
							UGameplayStatics::PlaySoundAtLocation(GetWorld(), NowWeapon.ReloadSound, this->GetActorLocation());
						Anim->Montage_Play(ReloadMontage, 1.0f);
					}
				}
			}
			break;
			}
		}
	}
}

//현재 무기를 구분하여 각 무기별 맞는 탄환을 세팅
//재장전 함수 후 애님 블루프린트에서 애니메이션 노티파이로 접근
//현재 보유하고 있는 탄환의 개수가 마이너스가 되지 않도록 제작
void AThe_Lost_AreaCharacter::SetBullet()
{
	switch (NowWeapon.BulletType)
	{
	case EBulletType::BT_556mm:
		{
			if (Total556Bullet < CarryFullBullet)
			{
				NowWeapon.CurrentBullet += Total556Bullet;
				Total556Bullet = 0;

				if (NowWeapon.CurrentBullet >= CarryFullBullet)
				{
					int32 temp = NowWeapon.CurrentBullet - CarryFullBullet;
					NowWeapon.CurrentBullet = CarryFullBullet;
					Total556Bullet += temp;
					isReloading = false;
				}
			}
			else
			{
				int32 temp = CarryFullBullet - NowWeapon.CurrentBullet;

				Total556Bullet -= temp;

				NowWeapon.CurrentBullet += temp;
				isReloading = false;
			}
		}
	break;
	
	case EBulletType::BT_762mm:
		{
		if (Total762Bullet < CarryFullBullet)
		{
			NowWeapon.CurrentBullet += Total762Bullet;
			Total762Bullet = 0;

			if (NowWeapon.CurrentBullet >= CarryFullBullet)
			{
				int32 temp = NowWeapon.CurrentBullet - CarryFullBullet;
				NowWeapon.CurrentBullet = CarryFullBullet;
				Total762Bullet += temp;
				isReloading = false;
			}
		}
		else
		{
			int32 temp = CarryFullBullet - NowWeapon.CurrentBullet;
			Total762Bullet -= temp;
			NowWeapon.CurrentBullet += temp;
			isReloading = false;
		}
		}
	break;
	}
}

//Q 토글키로 연발/단발 설정
void AThe_Lost_AreaCharacter::ToggleFiring()
{
	if (isShooting)
		isShooting = false;
	else
		isShooting = true;
}

//F 아이템 사용 키를 누를 시 현재 선택되어 있는 아이템을 구분, 
//각 아이템별로 효과가 다르기 때문에 switch문으로 각기 다른 효과 적용
void AThe_Lost_AreaCharacter::SelectItemUse()
{
	if (Inventory[InventoryNum].ItemCount > 0)
	{
		switch (Inventory[InventoryNum].Kinds)
		{
		case EItemKinds::Consumeable:
			if (status.HealthPoint < status.MaxHealthPoint)
			{
				status.HealthPoint += Inventory[InventoryNum].BufferValue;
				OpacityCount += Inventory[InventoryNum].BufferValue;
				if (status.HealthPoint >= status.MaxHealthPoint)
				{
					status.HealthPoint = status.MaxHealthPoint;
				}
				Inventory[InventoryNum].ItemCount--;
			}
			break;

		case EItemKinds::Ammo:

			if (!isItemUse)
			{
				FString ItemName1(TEXT("소이탄")), ItemName2(TEXT("폭발탄"));

				if (Inventory[InventoryNum].Name.EqualTo(FText::FromString(ItemName1)))
				{
					TempAttackDamage = status.AttackDamage;
					Inventory[InventoryNum].ItemCount--;
					isItemUse = true;

				}
				else if (Inventory[InventoryNum].Name.EqualTo(FText::FromString(ItemName2)))
				{
					TempAttackDamage = status.AttackDamage;
					status.AttackDamage = status.AttackDamage * 1.5f;
					Inventory[InventoryNum].ItemCount--;

					isItemUse = true;
				}
			}
			break;
		}
	}
}

//Enter 키 입력시 스테이지를 시작하는 함수
//Gamemodefmf 얻어 IsEnemySpawn을 true로 만들어 스폰을 시작.
void AThe_Lost_AreaCharacter::NowStageStart()
{
	APlayGameMode* GameMode = Cast<APlayGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode != nullptr)
	{
		IsEnemySpawn = true;
		GameMode->SpawnEnemy();
	}
}

//I 토글키로 플레이어의 인벤토리를 보여주는 함수.
void AThe_Lost_AreaCharacter::InventoryToggle()
{
	if (Inventory2->Visibility == ESlateVisibility::Collapsed)
	{
		Inventory2->SetInventoryList();
		Inventory2->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		Inventory2->SetVisibility(ESlateVisibility::Collapsed);
	}
}

//PlayerInfo UI에 표시되는 아이템을 보여주는 함수.
//InventoryNum은 PlayerInfo 블루프린트에서 휠을 굴렸을 때의 값을 받아 적용되게 제작 
void AThe_Lost_AreaCharacter::ShowInventory()
{
	Info->SetShowItemCount(Inventory[InventoryNum]);
}

void AThe_Lost_AreaCharacter::SetTransform(FWeapon weapon)
{
	//마켓플레이스에서 메시를 구매해 사용하다보니 위치/회전값이 맞지 않아
	//각 값을 구해 맞는 위치를 잡아줌
	//정확도를 위해 검지 본에 붙여주고 디테일한 위지값을 설정

	GunMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), "index_03_r");

	GunMesh->SetRelativeLocation(weapon.Location);
	GunMesh->SetRelativeRotation(weapon.Rotator);

	SetMuzzleTransform(GunMuzzle, weapon);
}

void AThe_Lost_AreaCharacter::SetMuzzleTransform(USceneComponent* GunMuzzle, FWeapon weapon)
{
	GunMuzzle->SetRelativeLocation(weapon.Muzzle_Location);
	GunMuzzle->SetRelativeRotation(weapon.Muzzle_Rotation);
}

bool AThe_Lost_AreaCharacter::SetIsEnemySpawn(bool bValue)
{
	return IsEnemySpawn = bValue;
}

void AThe_Lost_AreaCharacter::BeginPlay()
{
	Super::BeginPlay();

	NowWeapon = weapon[0];

	SetTransform(NowWeapon);

	SetupStatus();

	//HIScoreBoard에 필요한 데이터를 받기 위해 GameInstance 선언 및 할당
	Instance = Cast<UGameDataInstance>(GetWorld()->GetGameInstance());
	if (Instance == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Instance is nullptr"));
		return;
	}

	//미리 만들어 놓은 CSV 아이템 리스트 파일을 로드, PlayerInfo UI에 띄워주기 위한 리스트 제작
	FString Context;
	TArray<FTB_ItemInfo*> ItemList;
	ItemTable->GetAllRows<FTB_ItemInfo>(Context, ItemList);

	for (FTB_ItemInfo* ItemCount : ItemList)
	{
		if (ItemCount->Kinds != EItemKinds::Equipment)
		{
			FInventoryList TempInventory;
			TempInventory.Icon = ItemCount->TextureIcon;
			TempInventory.Name = ItemCount->Name;
			TempInventory.Kinds = ItemCount->Kinds;
			TempInventory.BufferValue = ItemCount->StatusValue;
			TempInventory.ItemCount = 0;
			Inventory.Add(TempInventory);
		}
	}

	//플레이어 인벤토 UI를 만들고 채워주는 함수
	if (InventoryClass != nullptr)
	{
		UUserWidget* Inven = CreateWidget<UUserWidget>(GetWorld(), InventoryClass);

		Inventory2 = Cast<UInventory>(Inven);
		Inventory2->SetInventoryList();
		Inventory2->AddToViewport();
		Inventory2->SetVisibility(ESlateVisibility::Collapsed);
	}

	//게임 플레이에 필요한 UI들을 PlayerInfo UI에 모아 하나의 블루프린트로 만들고
	//플레이어의 BeginPlay에서 화면의 띄워주는 부분
	if (Infoclass != nullptr)
	{
		UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), Infoclass);

		Info = Cast<UPlayerInfo>(Widget);
		Info->SetAmmoCount(NowWeapon.CurrentBullet);
		Info->SetTotalAmmoCount(NowWeapon.TotalCarryBullet);

		Widget->AddToViewport();
	}

	//크로스헤어 위젯을 받아 화면 중앙으로 셋팅
	if (CrossHairclass != nullptr)
	{
		CrossHair = CreateWidget<UUserWidget>(GetWorld(), CrossHairclass);
		CrossHair->AddToViewport();
	}

	UWidgetBlueprintLibrary::SetInputMode_GameOnly(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

//플레이어의 방어력이 있으면 방어력을 먼저 감소,
//방어력이 없으면 체력을 줄이면서 화면의 불투명도를 증가, 화면을 붉게 만듭니다.
void AThe_Lost_AreaCharacter::SetHealthPoint(int32 Value)
{
	if (status.DefensePoint > 0)
	{
		status.DefensePoint -= Value;
		if (status.DefensePoint < 0)
			status.DefensePoint = 0;
	}
	else
	{
		status.HealthPoint -= Value;
		if (status.HealthPoint <= 0)
			status.HealthPoint = 0;
		OpacityCount -= Value;
	}
}

void AThe_Lost_AreaCharacter::Tick(float DeltaSecends)
{
	Super::Tick(DeltaSecends);

	//PlayerInfo UI에서 항상 표시되어야 할 정보 표시
	switch (NowWeapon.BulletType)
	{
	case EBulletType::BT_556mm:
		Info->SetAmmoCount(NowWeapon.CurrentBullet);
		Info->SetTotalAmmoCount(Total556Bullet);
		break;

	case EBulletType::BT_762mm:
		Info->SetAmmoCount(NowWeapon.CurrentBullet);
		Info->SetTotalAmmoCount(Total762Bullet);
		break;
	}

	Info->SetScore(status.Score);
	Info->SetDefenseCount(status.DefensePoint);
	Info->SetOpacity(OpacityCount);

	//무기 교체 중에 다른 행동을 하지 못하도록 IsGunChange 변수를 사용, true로 설정
	//GunChange 몽타주 재생이 종료되면 IsGunChange 변수를 false로 변환 다른 행동이 가능해집니다.
	if (GetMesh()->HasValidAnimationInstance())
	{
		UAnimInstance* Anim = GetMesh()->GetAnimInstance();
		if (Anim->Montage_GetIsStopped(EquipMontage))
		{
			isGunChange = false;
		}
	}
	ShowInventory();

	//데미지 증가 아이템 사용시 효과 유지 시간 설정 및 효과 종료 후 원래 공격력으로 설정하는 부분입니다.
	if (isItemUse)
	{
		if (UseTime >= 0)
		{
			UseTime -= DeltaSecends;
		}
		else
		{
			isItemUse = false;
			UseTime = 5.0f;
			status.AttackDamage = TempAttackDamage;
		}
	}
	
	//플레이어 체력이 0이 되면 사망상태로 바꿔주며, 사망시 GameInstance에 HiScoreBoard에 필요한 데이터들을 넘겨줍니다.
	if (status.HealthPoint <= 0) IsDeath = true;

	if (IsDeath)
	{
		Instance_Score = status.Score;
		Instance->SetGameScore(Instance_Score);
		Instance->SetUsedBullet(Instance_UsedBullet);

		FTimerHandle TimerHandler;
		GetWorldTimerManager().SetTimer(TimerHandler, this, &AThe_Lost_AreaCharacter::ScoreLevelOpen, 3.0f, false);
	}
}

void AThe_Lost_AreaCharacter::ScoreLevelOpen()
{
	UGameplayStatics::OpenLevel(GetWorld(), EndLevelName);
}

//마우스 오른쪽 버튼 조준 토글키 입니다.
//마우스 오른쪽을 누를때만 조준이 되며 마우스를 떼면 false가 되며 원상태로 돌아옵니다.
void AThe_Lost_AreaCharacter::TrueAiming()
{
	isAiming = true;
}
void AThe_Lost_AreaCharacter::FalseAiming()
{
	isAiming = false;
}

void AThe_Lost_AreaCharacter::AddControllerYaw(float Val)
{
	if (NPC_IsPopup)
		return;

	if (Val != 0.f && Controller && Controller->IsLocalPlayerController())
	{
		APlayerController* const PC = CastChecked<APlayerController>(Controller);
		PC->AddYawInput(Val);
	}
}

void AThe_Lost_AreaCharacter::AddControllerPitch(float Val)
{
	if (NPC_IsPopup)
		return;


	if (Val != 0.f && Controller && Controller->IsLocalPlayerController())
	{
		APlayerController* const PC = CastChecked<APlayerController>(Controller);
		PC->AddPitchInput(Val);
	}
}

void AThe_Lost_AreaCharacter::OnFire()
{
	if (NPC_IsPopup || isGunChange)
		return;
	
	//현재 가지고 있는 탄환이 0일 경우 자동으로 재장전 할 수 있게 제작했습니다.
	if (NowWeapon.CurrentBullet == 0)
	{
		Reload();
		return;
	}

	if (NowWeapon.CurrentBullet != 0)
	{

		//Fire 함수에 성곡적으로 진입하면 파이어 사운드를 재생합니다.
		if (NowWeapon.FireSound->IsValidLowLevelFast())
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), NowWeapon.FireSound, this->GetActorLocation());
		
		//레이캐스팅을 하기 위한 부분입니다.
		FHitResult HitResult;
		FVector StartPoint = GunMuzzle->GetComponentLocation();
		FVector Forward = GetFollowCamera()->GetForwardVector();
		FVector EndPoint = StartPoint + (Forward * 3000.0f);
		EndPoint.Z = EndPoint.Z + 100.f;

		FCollisionQueryParams CollisionParams;

		//bool형 isHitdmfh 레이캐스팅 결과를 받아옵니다.
		bool isHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartPoint, EndPoint, ECollisionChannel::ECC_WorldDynamic, CollisionParams);

		FVector returnVector = UKismetMathLibrary::SelectVector(HitResult.ImpactPoint, HitResult.TraceEnd, isHit);
		FRotator FindRotate = UKismetMathLibrary::FindLookAtRotation(GunMuzzle->GetComponentLocation(), returnVector);
		FTransform finalTransform = UKismetMathLibrary::MakeTransform(GunMuzzle->GetComponentLocation(), FindRotate, FVector(1.0f, 1.0f, 1.0f));

		//앞에 isHit 이 true이고 Hit 대상이 적 캐릭터였을 때 적 체력을 감소시켜고,
		//아이템 사용 유무를 받아 효과를 적용해주고 투사체를 적을 향해 발사합니다.
		//적 캐릭터의 태그는 적 블루프린트에서 설정해 주었습니다.
		if (isHit && HitResult.GetActor()->ActorHasTag("Enemy"))
		{
			AEnemyCharacter* temp = Cast<AEnemyCharacter>(HitResult.GetActor());
			temp->SetDamage(status.AttackDamage);

			if (isItemUse)
			{
				//아이템 별로 파티클을 다르게 설정하여 피격시 불이 붙거나 폭발하는 파티클을 넣어주었습니다.
				FString ItemName1(TEXT("소이탄")), ItemName2(TEXT("폭발탄"));
				if (Inventory[InventoryNum].Name.EqualTo(FText::FromString(ItemName1)))
				{
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), AmmoParticle, temp->GetTransform());
					temp->SetIsFire(true);
					UE_LOG(LogTemp, Warning, TEXT("Use Item Name Is :: %s"), *ItemName1);
				}
				else if (Inventory[InventoryNum].Name.EqualTo(FText::FromString(ItemName2)))
				{
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BombParticle, temp->GetTransform());
					UE_LOG(LogTemp, Warning, TEXT("Use Item Name Is :: %s"), *ItemName2);
				}
			}
			switch (NowWeapon.BulletType)
			{
			case EBulletType::BT_556mm:
			{
				if (Bullet556_Class != nullptr && NowWeapon.CurrentBullet != 0)
				{
					NowWeapon.CurrentBullet -= 1;
					UWorld* const World = GetWorld();
					World->SpawnActor<ABulletProjectile>(Bullet556_Class, finalTransform);
				}
			}
			break;
			case EBulletType::BT_762mm:
			{
				if (Bullet762_Class != nullptr && NowWeapon.CurrentBullet != 0)
				{
					NowWeapon.CurrentBullet -= 1;
					UWorld* const World = GetWorld();
					World->SpawnActor<ABulletProjectile>(Bullet762_Class, finalTransform);
				}
			}
			break;
			}
		}
		else
		{
			switch (NowWeapon.BulletType)
			{
			case EBulletType::BT_556mm:
			{
				if (Bullet556_Class != nullptr && NowWeapon.CurrentBullet != 0)
				{
					NowWeapon.CurrentBullet -= 1;
					UWorld* const World = GetWorld();
					World->SpawnActor<ABulletProjectile>(Bullet556_Class, finalTransform);
				}
			}
			break;
			case EBulletType::BT_762mm:
			{
				if (Bullet762_Class != nullptr && NowWeapon.CurrentBullet != 0)
				{
					NowWeapon.CurrentBullet -= 1;
					UWorld* const World = GetWorld();
					World->SpawnActor<ABulletProjectile>(Bullet762_Class, finalTransform);
				}
			}
			break;
			}
		}


		//기본 자세와 조준 자세를 각각 다른 몽타주 애니메이션을 설정, 차이점을 주었습니다.
		UAnimInstance* Anim = GetMesh()->GetAnimInstance();

		if (Anim != nullptr && NowWeapon.CurrentBullet != 0)
		{
			if (!isAiming && FireAnimation != nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("Fire Montage Check"));
				Anim->Montage_Play(FireAnimation, 1.0f);
			}
			else if (isAiming && IronAnimation != nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("IronSight Montage Check"));
				Anim->Montage_Play(IronAnimation, 1.0f);
			}
		}

		Instance_UsedBullet++;

		//두개의 bool형으로 연사기능을 만들었습니다.
		//isShooting이 true일 경우 0.2초 간격으로 발사됩니다.
		if (isFiring && isShooting)
		{
			GetWorld()->GetTimerManager().SetTimer(timer, this, &AThe_Lost_AreaCharacter::OnFire, 0.2f, false);
		}
	}
}

void AThe_Lost_AreaCharacter::StartFire()
{
	isFiring = true;
	OnFire();
}

void AThe_Lost_AreaCharacter::StopFire()
{
	isFiring = false;
}

//E 토글키로 NPC와의 거리를 탐지하여 일정 거리안으로 들어왔을때 키를 입력하면 해당 NPC에 맞는 위젯을 띄워줍니다.
void AThe_Lost_AreaCharacter::NPC_Interaction()
{
	TArray<AActor*> NPCCharacters;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ANPCCharacter::StaticClass(), NPCCharacters);

	if (NPCCharacters.Num() != 0)
	{
		for (int32 i = 0; i < NPCCharacters.Num(); i++)
		{
			float NPCDistance = GetDistanceTo(NPCCharacters[i]);
			if (NPCDistance < InteractionRange)
			{
				ANPCCharacter* NPC = Cast<ANPCCharacter>(NPCCharacters[i]);
				switch (NPC->GetKinds())
				{
					case ENPCKinds::none:
						break;
					case ENPCKinds::weapon_merchant:
					{
						isUIPopup = true;
						NPC_IsPopup = NPC->GetIsPopup();
						NPC->SetAmmoBuyWidget();
					}
					break;
					case ENPCKinds::item_merchant:
					{
						isUIPopup = true;
						NPC_IsPopup = NPC->GetIsPopup();
						NPC->SetMarketWidget();
					}
					break;
				}
			}
			else
			{
				isUIPopup = false;
			}
		}
	}
}

void AThe_Lost_AreaCharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AThe_Lost_AreaCharacter::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AThe_Lost_AreaCharacter::MoveForward(float Value)
{
	if (NPC_IsPopup)
		return;

	if ((Controller != NULL) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AThe_Lost_AreaCharacter::MoveRight(float Value)
{
	if (NPC_IsPopup)
		return;

	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}
