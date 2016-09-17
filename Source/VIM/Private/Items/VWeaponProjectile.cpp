// copyright The Perfect Game Company 2016

#include "VIM.h"
#include "VWeaponProjectile.h"
#include "VProjectileBase.h"

AVWeaponProjectile::AVWeaponProjectile(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

//////////////////////////////////////////////////////////////////////////
// Weapon usage

void AVWeaponProjectile::FireWeapon()
{
	FVector ShootDir = GetMuzzleDirection();
	FVector Origin = GetMuzzleLocation();

	//trace from camera to check what's in front of us
	const float ProjectileAdjustRange = 10000.0f;
	const FVector StartTrace = Origin;
	const FVector EndTrace = StartTrace * ProjectileAdjustRange;
	FHitResult Impact = WeaponTrace(StartTrace, EndTrace);
	
	// and adjust directions to hit that actor
	if (Impact.bBlockingHit)
	{
		const FVector AdjustedDir = (Impact.ImpactPoint - Origin).GetSafeNormal();
		bool bWeaponPenetration = false;
		const float DirectionDot = FVector::DotProduct(AdjustedDir, ShootDir);
		if (DirectionDot < 0.0f)
		{
			// shooting backwards = weapon is penetrating
			bWeaponPenetration = true;
		}
		else if (DirectionDot < 0.5f)
		{
			// check for weapon penetration if angle difference is big enough
			// raycast along weapon mesh to check if there's blocking hit

			FVector MuzzleStartTrace = Origin - GetMuzzleDirection() * 150.0f;
			FVector MuzzleEndTrace = EndTrace;
			FHitResult MuzzleImpact = WeaponTrace(MuzzleStartTrace, MuzzleEndTrace);

			if (MuzzleImpact.bBlockingHit)
			{
				bWeaponPenetration = true;
			}
		}

		if (bWeaponPenetration)
		{
			// spawn at crosshair position
			Origin = Impact.ImpactPoint - ShootDir * 10.0f;
		}
		else
		{
			// adjust direction to hit
			ShootDir = AdjustedDir;
		}
	}

	FireProjectile(Origin, ShootDir);
}
void AVWeaponProjectile::FireProjectile(FVector Origin, FVector_NetQuantizeNormal ShootDir)
{
	FTransform SpawnTM(ShootDir.Rotation(), Origin);
	auto Projectile = Cast<AVProjectileBase>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, ProjectileConfig.ProjectileClass,SpawnTM));
	if (Projectile)
	{
		Projectile->Instigator = Instigator;
		Projectile->SetOwner(this);
		Projectile->InitVelocity(ShootDir);
		UGameplayStatics::FinishSpawningActor(Projectile,SpawnTM);
	}
}

void AVWeaponProjectile::ApplyWeaponConfig(FProjectileWeaponData& Data)
{
	Data = ProjectileConfig;
}


