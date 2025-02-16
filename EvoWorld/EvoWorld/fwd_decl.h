#pragma once
class CompoundShape;
template <typename T>
struct Vector2;
class PhysicsDisk;
class PhysicsStaticRectangle;
template <typename TDisk, typename TRectangle>
    requires std::derived_from<TDisk, PhysicsDisk> && std::derived_from<TRectangle, PhysicsStaticRectangle>
class NewtonianPhysics;
