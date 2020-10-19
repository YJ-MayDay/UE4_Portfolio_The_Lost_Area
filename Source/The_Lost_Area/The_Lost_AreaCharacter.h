// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter/StatusStruct.h"
#include "The_Lost_Area/Widget/TB_ItemInfo.h"
#include "The_Lost_AreaCharacter.generated.h"

UENUM()
enum class EBulletType
{
	BT_556mm,
	BT_762mm
};

USTRUCT(BlueprintType)
struct FWeapon
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
		class USkeletalMesh* GunMesh;

	UPROPERTY(EditAnywhere)
		int32 WeaponDamage;

	UPROPERTY(EditAnywhere)
		EBulletType BulletType;

	UPROPERTY(EditAnywhere)
		int32 CurrentBullet;

	UPROPERTY(EditAnywhere)
		int32 TotalCarryBullet;

	UPROPERTY(EditAnywhere)	FVector Location;
	UPROPERTY(EditAnywhere)	FRotator Rotator;

	UPROPERTY(EditAnywhere)	FVector Muzzle_Location;
	UPROPERTY(EditAnywhere)	FRotator Muzzle_Rotation;

	UPROPERTY(EditAnywhere) 
		class USoundCue* ReloadSound;

	UPROPERTY(EditAnywhere)
		class USoundCue* FireSound;

	UPROPERTY(EditAnywhere)
		class USoundCue* ChangeSound;
};

USTRUCT(Atomic, BlueprintType)
struct FInventoryList
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
		FText Name;

	UPROPERTY(EditAnywhere)
		int32 ItemCount;

	UPROPERTY(EditAnywhere)
		EItemKinds Kinds;

	UPROPERTY(EditAnywhere)
		int32 BufferValue;

	UPROPERTY(EditDefaultsOnly) 
		TSoftObjectPtr<class UTexture2D> Icon;
};

UCLASS(config=Game)
class AThe_Lost_AreaCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	AThe_Lost_AreaCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;


protected:

	void MoveForward(float Value);
	void MoveRight(float Value);
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);

protected:
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		void SetupStatus();

	UFUNCTION(BlueprintCallable)
		void SetWeapon(FWeapon Weapon);

	UFUNCTION()	void WeaponChange0();
	UFUNCTION()	void WeaponChange1();
	UFUNCTION()	void WeaponChange2();

	UFUNCTION()
		void Reload();
	UFUNCTION(BlueprintCallable)
		void SetBullet();

	UFUNCTION()
		void ToggleFiring();

	UFUNCTION()
		void SelectItemUse();

	UFUNCTION()
		void NowStageStart();

	int32 EnemyCount = 5;

	UFUNCTION()	void InventoryToggle();
	UFUNCTION()	void ShowInventory();

	UPROPERTY(BlueprintReadWrite)
		int32 InventoryNum = 0;

	UFUNCTION()
		void SetTransform(FWeapon weapon);

	UFUNCTION()
		void SetMuzzleTransform(USceneComponent* GunMuzzle, FWeapon weapon);

public:
	bool GetIsEnemySpawn() { return IsEnemySpawn; }
	bool SetIsEnemySpawn(bool bValue);
	bool IsEnemySpawn = false;

	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Gameplay)
		class UAnimMontage* FireAnimation;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Gameplay)
		class UAnimMontage* IronAnimation;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = ChangeWeapon)
		class UAnimMontage* EquipMontage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Reload)
		class UAnimMontage* ReloadMontage;

	UPROPERTY(BlueprintReadOnly)
	int32 WeaponNum;

	FCharacterStatusStruct GetPlayerStatus() { return status; }

	UFUNCTION()
		int32 GetEnemyCount() { return EnemyCount; }
	UFUNCTION()
	void SetHealthPoint(int32 Value);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		struct FCharacterStatusStruct status;
	UPROPERTY(EditAnywhere)
		TArray<FInventoryList> Inventory;

	UPROPERTY()
		class UInventory* Inventory2;

	UPROPERTY()
		class UPlayerInfo* Info;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		bool isAiming = false;

	UPROPERTY(BlueprintReadOnly)
		float InteractionRange;

	UPROPERTY(BlueprintReadOnly)
		FWeapon NowWeapon;

	UPROPERTY(EditAnywhere)
		int32 Total556Bullet;

	UPROPERTY(EditAnywhere)
		int32 Total762Bullet;

	int32 CarryFullBullet = 30;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Particle)
	class UParticleSystem* AmmoParticle;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Particle)
	class UParticleSystem* BombParticle;
	
	virtual void Tick(float DeltaSecends) override;

	void AddControllerYaw(float Val);

	void AddControllerPitch(float Val);

	UFUNCTION() void OnFire();

	UFUNCTION()	void StartFire();
	UFUNCTION()	void StopFire();

	UPROPERTY()
		bool isFiring = false;

	UPROPERTY()
		bool isShooting = false;

	UPROPERTY()
		FTimerHandle timer;

	UPROPERTY(EditDefaultsOnly)
		FName EndLevelName;

	UFUNCTION()
		void NPC_Interaction();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USkeletalMeshComponent* CurrentWeapon;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	class USkeletalMeshComponent* GunMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USceneComponent* GunMuzzle;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		TArray<FWeapon> weapon;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class ABulletProjectile> Bullet556_Class;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class ABulletProjectile> Bullet762_Class;

	UPROPERTY(BlueprintReadOnly)
		bool isUIPopup = false;

	bool NPC_IsPopup;

	UFUNCTION()	void TrueAiming();
	UFUNCTION()	void FalseAiming();

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UUserWidget> Infoclass;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UUserWidget> CrossHairclass;

	UUserWidget* CrossHair;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UUserWidget> InventoryClass;

	UPROPERTY()
		bool isGunChange = false;
	UPROPERTY()
		bool isReloading = false;

	UPROPERTY(EditDefaultsOnly)
		class UDataTable* ItemTable;

	UPROPERTY()
		int32 ItemListCount;

	bool isItemUse = false;

	float UseTime = 5.0f;
	int32 TempAttackDamage;

	class UGameDataInstance* Instance;

	int32 Instance_Kills;
	int32 Instance_Score;
	int32 Instance_UsedBullet;

	float OpacityCount = 0.0f;
	bool IsDeath = false;

	void ScoreLevelOpen();
};
