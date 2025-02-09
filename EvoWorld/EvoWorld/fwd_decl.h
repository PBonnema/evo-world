#pragma once
class Arena;
class CompoundShape;
class SumoGame;
template <typename T>
struct Vector2;
class Glider;
class RushGlider;
class PlayerGlider;
class CenteringGlider;
class TrajectoryGlider;
struct TrajectoryPoint;
class EvoGlider;
class PhysicsDisk;
template<typename TDisk>
requires std::derived_from<TDisk, PhysicsDisk>
class NewtonianDiskPhysics;