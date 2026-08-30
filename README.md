# GeometryFPS

A small 2D physics / collision learning project built with [raylib](https://www.raylib.com/) in C++17.
It is structured around a component-based architecture: a `GameObject` composes a transform, a
drawable, a collider, a rigidbody and an optional custom behaviour, while two systems —
`CollisionSystem` and `PhysicsSystem` — drive detection and simulation.

The project exercises, in a deliberately small way: Minimum Translation Vector (MTV) collision
detection between circles and rectangles, collision events via the Observer pattern, and
perfectly inelastic momentum resolution.

## Build and run

Requirements: a C++17 compiler (`g++`) and the raylib development libraries.

```sh
./build
```

The script compiles every `.cpp` under `src/`, `components/`, `factory/`, `customBehaviours/`
and `lib/`, links raylib, produces the `run` binary and launches it (it has separate link
flags for Linux and macOS).

## Architecture

### GameObject: the composition root

`GameObject` (`components/gameObject/`) owns **at most one component of each kind**, exclusively
(`unique_ptr`), and exposes them through `GetComponent<T>()`:

| Slot | Interface | Concrete implementations | Purpose |
|------|-----------|--------------------------|---------|
| Transform (required) | `IGameTransform` | `GameTransform` | Position, rotation (as `Vector2`), uniform scale |
| Drawable (required) | `IDrawable` | `CircleRenderer`, `RectangleRenderer` | Renders itself each frame; color exposed through the interface |
| Collider (optional) | `ICollider` | `CircleCollider`, `RectangleCollider` | Collision shape; also the Subject of collision events |
| Rigidbody (optional) | — | `Rigidbody` | Mass, velocity, gravity multiplier, `RigidbodyType` |
| Custom behaviour (optional) | `ICustomBehaviour` | `RectangleBehaviour` (sample) | Arbitrary per-object logic |

`GameObjectFactory` (`factory/`) builds ready-to-use objects by wiring these components together.

### Systems

Systems live in `lib/` and hold only non-owning `GameObject*` pointers:

- **`CollisionSystem`** — detects overlaps between every pair of colliders each frame, pushes
  overlapping shapes apart with the MTV, and fires collision enter/exit events.
- **`PhysicsSystem`** — integrates motion (gravity + velocity) for Dynamic bodies each frame,
  and listens for collision events to resolve momentum.

### Folder layout

```
components/        component interfaces and concrete components, one subfolder per component
customBehaviours/  user-defined behaviours (samples of ICustomBehaviour)
factory/           GameObjectFactory and helpers that assemble objects
lib/               systems: CollisionSystem, PhysicsSystem
src/               main.cpp — the sample application
build              build script
```

## Key design decisions

### Components hold narrow references — except ICustomBehaviour

Renderers and colliders only keep the specific reference they need: an `IGameTransform*`,
never a `GameObject*`. A component that only needs the position shouldn't see the whole object.

`ICustomBehaviour` is the deliberate exception: custom logic usually needs to fetch arbitrary
components (`GetComponent<T>()`) or register as a collision listener, so a behaviour holds a
`GameObject*`. The owner is delivered via `Start(GameObject*)` rather than the constructor
because of a chicken-and-egg problem: the `GameObject` creates and owns the behaviour, so the
behaviour exists *before* the `GameObject` does and cannot receive `this` at construction time.
`Start()` is called by the `GameObject` constructor once every component is in place — which
is also exactly the moment component lookups and listener registration become possible.

### Collision flow: detection, MTV correction, Observer events

Each frame `CollisionSystem::CollisionHandler()` tests every unordered pair of colliders once
and dispatches to the resolver matching the pair's shapes (`CircleCircleCollision`,
`CircleRectangleCollision`, `RectangleRectangleCollision`), selected via each collider's
`ShapeType`.

The response to an overlap is:

1. **MTV position correction** — the returned vector is added to one collider of the pair
   (the *mover*), pushing the two shapes apart. Only one side is ever moved.
2. **Events** — the pair is recorded in an internal `activeCollisions` set, and
   `OnCollisionEnter` is fired on both colliders every frame the overlap persists.
   When a previously colliding pair no longer overlaps, `OnCollisionExit` fires **exactly
   once** — the set's erase returns nonzero only the first time, so exit events are one-shot
   per contact and never fire for pairs that never collided.

Events follow the Observer pattern: `ICollider` is the Subject (via `AddListener`) and
`ICollisionListener` the Observer. Two very different reactions are listeners:

- **`PhysicsSystem`** — on enter, resolves momentum.
- **`RectangleBehaviour`** — on enter, turns the object's drawable red; on exit, white again.

Why `ShapeType` dispatch instead of each collider implementing `CollideWith()` against every
other shape? It keeps all collision math in one place: adding a new shape means adding one
resolver to `CollisionSystem`, and existing collider classes stay untouched.

### Why resolvers return `optional<Vector2>` instead of applying corrections

The resolver functions are pure detectors: they return the Minimum Translation Vector (or
`nullopt` when there is no overlap, or when either collider is disabled) without touching
anything. Detection is separated from response — the system decides *whether* and *how* to
respond (which collider moves, what events fire), and the collision math stays side-effect-free
and easy to reason about in isolation. `ResolveCollision()` is the single place that turns a
detection result into world changes.

### RigidbodyType: Static / Dynamic / Kinematic

`PhysicsSystem` treats each type differently during integration and collision response:

- **Static** — immovable world geometry. Never integrated, and its velocity is never rewritten
  by collisions.
- **Kinematic** — moved by gameplay code (`SetPosition`/`SetVelocity`) rather than by the
  simulation. Excluded from integration and momentum rewrites, but still fully collidable
  (the sample application's rectangle uses this).
- **Dynamic** — fully simulated: gravity and velocity integration every frame, and its
  velocity is rewritten on collision by the momentum resolution.

Note that the integration currently treats Static and Kinematic identically — both are skipped
by `PhysicsHandler()`. The distinction is one of *intent*: Static objects are not meant to move
at all, Kinematic objects are moved deliberately by game code instead of by physics.

### Collision momentum resolution

On a collision enter, `PhysicsSystem` computes the shared post-collision velocity of a
**perfectly inelastic** collision per axis:

```
v' = (m1·v1 + m2·v2) / (m1 + m2)
```

Momentum is conserved while both bodies end up moving together along that axis. The result is
applied only to bodies of type Dynamic — Static and Kinematic bodies keep their velocity, so
they act as immovable for the exchange. Collision exit needs no physics handling, which is why
`PhysicsSystem::OnCollisionExit()` is a no-op.

### Gravity model

Gravity is not a per-object acceleration constant: `PhysicsSystem` holds a system-wide
`gravityAcceleration`, and each `Rigidbody` carries a **gravity multiplier** (0 = no gravity).
Each frame, Dynamic bodies get their vertical velocity set to
`gravityAcceleration × multiplier × frame time`, then position is integrated by velocity.

### Colliders double as their own debug drawable

Colliders implement `IDrawable` themselves (returned by `GetDrawable()`), so
`GameObject::Draw()` can render their outline without a separate debug-draw component. The
outline only appears when the collider is created with its `show` flag set — an opt-in visual
debugging aid.

## The sample scene

`src/main.cpp` builds a circle and a rectangle through `GameObjectFactory`, sets the
rectangle's rigidbody to `Kinematic`, and gives the rectangle a `RectangleBehaviour` that
flashes it red while it is colliding — a compact tour of the factory, the collision events
and the behaviour system.
