
#include <ecs/Registry.h>

using namespace mud;

struct Position;
struct Velocity;

struct Position
{
    long m_x;
    long m_y;
};

struct Velocity
{
    long m_x;
    long m_y;
};

namespace mud
{
	template <> struct TypedBuffer<Position> { static size_t index() { return 0; } };
	template <> struct TypedBuffer<Velocity> { static size_t index() { return 1; } };

	template <> Type& type<Position>() { static Type ty("Position"); return ty; }
	template <> Type& type<Velocity>() { static Type ty("Velocity"); return ty; }
}

void test_ecs()
{
	ECS ecs;
	s_ecs[0] = &ecs;

//        PrintRegistryDebug();

    //create and register some component buffers
//        Print("Creating Component Buffers");

	ecs.AddBuffers<Position>("Position"); // 1 << preallocShift;
	ecs.AddBuffers<Position, Velocity>("PositionVelocity"); // 1 << preallocShift;
        
//        PrintRegistryDebug();
//        PrintCompBufsDebug();


	Entity entity = { ecs.CreateEntity<Position, Velocity>(), 0 };
	ComponentHandle<Position> position = { entity };
	ComponentHandle<Velocity> velocity = { entity };
	UNUSED(position);
	UNUSED(velocity);

    uint32_t e = ecs.CreateEntity<Position, Velocity>();
	ecs.SetComponent(e, Position());
	ecs.SetComponent(e, Velocity{ 0, 3 });

    auto e1 = ecs.CreateEntity<Position>();
	ecs.SetComponent(e1, Position());
    //ecs.SetComponent(e1, Velocity { x = 0, y = 1 });

    auto e2 = ecs.CreateEntity<Position, Velocity>();
	ecs.SetComponent(e2, Position());
	ecs.SetComponent(e2, Velocity { 0, 5 });

    auto e3 = ecs.CreateEntity<Position>();
	ecs.SetComponent(e3, Position());
    //ecs.SetComponent(e3, Velocity { x = 0, y = 1 });

    ecs.Loop<Position, Velocity>([](uint32_t handle, Position& pos, Velocity& vel)
    {
		UNUSED(handle);
        pos.m_y += vel.m_y;
    });


    //Console.ReadKey();
    /*




    ////create entities and components
    //Print("Creating 4 Entities");

    //auto entA = ecs.CreateEntity();
    //ecs.AddComponent(entA, new Position());
    //ecs.AddComponent(entA, new Velocity());

    //PrintEntityDebug(entA);

    //auto entB = ecs.CreateEntity();
    //ecs.AddComponent(entB, new Position());

    //PrintEntityDebug(entB);

    //auto entC = ecs.CreateEntity();
    //ecs.AddComponent(entC, new Velocity());

    //PrintEntityDebug(entC);

    //auto entD = ecs.CreateEntity();

    //PrintEntityDebug(entD);

    //PrintRegistryDebug();
    //PrintCompBufsDebug(true);

    //Print("Removing component");

    //ecs.RemoveComponent<Velocity>(entA);

    //PrintCompBufsDebug(true);

    //Print("Readding component");

    //ecs.AddComponent(entA, new Velocity());

    //PrintCompBufsDebug(true);

    //Print("Removing other");

    //ecs.RemoveComponent<Position>(entA);

    //PrintCompBufsDebug(true);

    //Print("Readding other");

    //ecs.AddComponent(entA, new Position());

    //PrintCompBufsDebug(true);

    //Print("Adding new to 2nd entity");

    //ecs.AddComponent(entB, new Velocity());

    //PrintEntityDebug(entB);
    //PrintCompBufsDebug(true);

    //Print("Removing all from 2nd entity");

    //ecs.RemoveAllComponents(entB);

    //PrintEntityDebug(entB);
    //PrintCompBufsDebug(true);

    //Print("Removing 3rd entity");

    //ecs.DeleteEntity(entC);
    //PrintRegistryDebug(true);
    //PrintCompBufsDebug(true);

    //Print("Removing 1st entity");

    //ecs.DeleteEntity(entA);
    //PrintRegistryDebug(true);
    //PrintCompBufsDebug(true);

    //Print("Creating new with components");

    //auto entE = ecs.CreateEntity();
    //ecs.AddComponent(entE, new Position());
    //ecs.AddComponent(entE, new Velocity{x=0,y=1});
    //PrintRegistryDebug(true);
    //PrintCompBufsDebug(true);

    //Print("Removing newly created entity");

    //ecs.DeleteEntity(entE);
    //PrintRegistryDebug(true);
    //PrintCompBufsDebug(true);

    //Print("Adding component to 4th entity");

    //ecs.AddComponent(entD, new Position());
    //PrintRegistryDebug(true);
    //PrintCompBufsDebug(true);

    //####################### LOOPS
    // add a tonne of stuff
    Print("Adding a ton of ents and comps");
    auto sw = Stopwatch.StartNew();
    for (int i = 0; i < 1<<16; i++)
    {
        auto id = ecs.CreateEntity();
        ecs.AddComponent(id, new Position());
        ecs.AddComponent(id, new Velocity { x = 0, y = 1 });
    }
    Print($"Took {sw.ElapsedMicroseconds()}");
//        Console.ReadKey();
    PrintRegistryDebug();
    PrintCompBufsDebug();

    //Console.ReadKey();
    for (int i = 0; i < 10; i++)
    {
    Console.WriteLine("Looping a ton of ents and 2 comps");
    sw = Stopwatch.StartNew();

    //Print("Looping a ton of ents and comp");
    //sw = Stopwatch.StartNew();
    //ecs.Loop((uint32_t handle, ref Position transform) =>
    //{
    //    transform.x = 10;
    //});
    //Print($"Took {sw.ElapsedMicroseconds()}");


    ecs.Loop((uint32_t handle, ref Velocity vel, ref Position pos) =>
    {
        pos.y += vel.y;
    });
    Console.WriteLine($"Took {sw.ElapsedMicroseconds()}");

    }
        
    //TODO loop components exclusion matchers
    //TODO sort components (based on EntIdxs)


    Console.ReadKey();

    */
}

/*

TODO use this?
struct EntityID : IEquatable<EntityID>, IComparable<EntityID>
{
    private int index_;

    public EntityID(int index)
    {
        index_ = index;
    }

    public static implicit operator EntityID(int index)
    {
        return new EntityID(index);
    }

    public static implicit operator int(EntityID id)
    {
        return id.index_;
    }

    public bool Equals(EntityID other)
    {
        return index_ == other.index_;
    }

    public override bool Equals(object boxed)
    {
        if (boxed == null) return false;
        return boxed is EntityID id && Equals(id);
    }

    public override int GetHashCode()
    {
        return index_;
    }

    public int CompareTo(EntityID other)
    {
        return index_.CompareTo(other.index_);
    }
}
 */
