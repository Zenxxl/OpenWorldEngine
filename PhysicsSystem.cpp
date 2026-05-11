// PhysicsSystem.cpp
#include "PhysicsSystem.h"
using namespace physx;

PhysicsSystem::PhysicsSystem() {}
PhysicsSystem::~PhysicsSystem() { Shutdown(); }

bool PhysicsSystem::Initialize() {
    mFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, mAllocator, mErrorCallback);
    if (!mFoundation) return false;
    mPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *mFoundation, PxTolerancesScale(), true);
    if (!mPhysics) return false;
    mDispatcher = PxDefaultCpuDispatcherCreate(2);
    PxSceneDesc sceneDesc(mPhysics->getTolerancesScale());
    sceneDesc.gravity = PxVec3(0.0f, -9.81f, 0.0f);
    sceneDesc.cpuDispatcher = mDispatcher;
    sceneDesc.filterShader = PxDefaultSimulationFilterShader;
    mScene = mPhysics->createScene(sceneDesc);
    return mScene != nullptr;
}

void PhysicsSystem::Shutdown() {
    if (mScene) { mScene->release(); mScene = nullptr; }
    if (mDispatcher) { mDispatcher->release(); mDispatcher = nullptr; }
    if (mPhysics) { mPhysics->release(); mPhysics = nullptr; }
    if (mFoundation) { mFoundation->release(); mFoundation = nullptr; }
}
