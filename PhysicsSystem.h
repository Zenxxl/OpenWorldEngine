// PhysicsSystem.h
#pragma once
#include <PxPhysicsAPI.h>

class PhysicsSystem {
public:
    PhysicsSystem();
    ~PhysicsSystem();
    bool Initialize();
    void Shutdown();
private:
    physx::PxDefaultAllocator      mAllocator;
    physx::PxDefaultErrorCallback  mErrorCallback;
    physx::PxFoundation*           mFoundation = nullptr;
    physx::PxPhysics*              mPhysics = nullptr;
    physx::PxDefaultCpuDispatcher* mDispatcher = nullptr;
    physx::PxScene*                mScene = nullptr;
};
