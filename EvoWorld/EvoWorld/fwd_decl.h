#pragma once
class CompoundShape;
template <typename T>
struct Vector2;
class PhysicsDisk;
template<typename TDisk>
requires std::derived_from<TDisk, PhysicsDisk>
class NewtonianPhysics;