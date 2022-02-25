#pragma once

/// <summary>
/// An Enum which denotes cardnal directions.
/// </summary>
/// Given a top down view (Looking down the z-axis in Unreal):
/// +X is due North, -X is due South
/// +Y is due East, -Y is due West

UENUM(BlueprintType)
enum class EDirection : uint8 {
	North UMETA(DisplayName = "North"),
	East UMETA(DisplayName = "East"),
	South UMETA(DisplayName = "South"),
	West UMETA(DisplayName = "West")
};