
#include <proto/ECS/Registry.h>

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

template <> struct TypedBuffer<Position> { using type = ComponentBufferDense<Position>; static size_t index() { return 0; } };
template <> struct TypedBuffer<Velocity> { using type = ComponentBufferDense<Velocity>; static size_t index() { return 1; } };

void test_ecs()
{
	int preallocShift = 14;
	//static EntityRegistry<MyBufferRegistry> s_registry = { 1 << preallocShift };

    //create registry
    //Print("Creating Registry");

//        PrintRegistryDebug();

    //create and register some component buffers
//        Print("Creating Component Buffers");

	s_registry.AddBuffer<Position>(); // 1 << preallocShift;
	s_registry.AddBuffer<Velocity>(); // 1 << preallocShift;
        
//        PrintRegistryDebug();
//        PrintCompBufsDebug();


	Entity entity = {};
	Component<Position> position = { entity };
	Component<Velocity> velocity = { entity };

    auto e = s_registry.CreateEntity();
	s_registry.AddComponent(e, Position());
	s_registry.AddComponent(e, Velocity{ 0, 3 });

    auto e1 = s_registry.CreateEntity();
	s_registry.AddComponent(e1, Position());
    //s_registry.AddComponent(e1, Velocity { x = 0, y = 1 });

    auto e2 = s_registry.CreateEntity();
	s_registry.AddComponent(e2, Position());
	s_registry.AddComponent(e2, Velocity { 0, 5 });

    auto e3 = s_registry.CreateEntity();
	s_registry.AddComponent(e3, Position());
    //s_registry.AddComponent(e3, Velocity { x = 0, y = 1 });

    s_registry.Loop<Position, Velocity>([](uint32_t handle, Position& pos, Velocity& vel)
    {
		UNUSED(handle);
        pos.m_y += vel.m_y;
    });


    //Console.ReadKey();
    /*




    ////create entities and components
    //Print("Creating 4 Entities");

    //auto entA = s_registry.CreateEntity();
    //s_registry.AddComponent(entA, new Position());
    //s_registry.AddComponent(entA, new Velocity());

    //PrintEntityDebug(entA);

    //auto entB = s_registry.CreateEntity();
    //s_registry.AddComponent(entB, new Position());

    //PrintEntityDebug(entB);

    //auto entC = s_registry.CreateEntity();
    //s_registry.AddComponent(entC, new Velocity());

    //PrintEntityDebug(entC);

    //auto entD = s_registry.CreateEntity();

    //PrintEntityDebug(entD);

    //PrintRegistryDebug();
    //PrintCompBufsDebug(true);

    //Print("Removing component");

    //s_registry.RemoveComponent<Velocity>(entA);

    //PrintCompBufsDebug(true);

    //Print("Readding component");

    //s_registry.AddComponent(entA, new Velocity());

    //PrintCompBufsDebug(true);

    //Print("Removing other");

    //s_registry.RemoveComponent<Position>(entA);

    //PrintCompBufsDebug(true);

    //Print("Readding other");

    //s_registry.AddComponent(entA, new Position());

    //PrintCompBufsDebug(true);

    //Print("Adding new to 2nd entity");

    //s_registry.AddComponent(entB, new Velocity());

    //PrintEntityDebug(entB);
    //PrintCompBufsDebug(true);

    //Print("Removing all from 2nd entity");

    //s_registry.RemoveAllComponents(entB);

    //PrintEntityDebug(entB);
    //PrintCompBufsDebug(true);

    //Print("Removing 3rd entity");

    //s_registry.DeleteEntity(entC);
    //PrintRegistryDebug(true);
    //PrintCompBufsDebug(true);

    //Print("Removing 1st entity");

    //s_registry.DeleteEntity(entA);
    //PrintRegistryDebug(true);
    //PrintCompBufsDebug(true);

    //Print("Creating new with components");

    //auto entE = s_registry.CreateEntity();
    //s_registry.AddComponent(entE, new Position());
    //s_registry.AddComponent(entE, new Velocity{x=0,y=1});
    //PrintRegistryDebug(true);
    //PrintCompBufsDebug(true);

    //Print("Removing newly created entity");

    //s_registry.DeleteEntity(entE);
    //PrintRegistryDebug(true);
    //PrintCompBufsDebug(true);

    //Print("Adding component to 4th entity");

    //s_registry.AddComponent(entD, new Position());
    //PrintRegistryDebug(true);
    //PrintCompBufsDebug(true);

    //####################### LOOPS
    // add a tonne of stuff
    Print("Adding a ton of ents and comps");
    auto sw = Stopwatch.StartNew();
    for (int i = 0; i < 1<<16; i++)
    {
        auto id = s_registry.CreateEntity();
        s_registry.AddComponent(id, new Position());
        s_registry.AddComponent(id, new Velocity { x = 0, y = 1 });
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
    //s_registry.Loop((uint32_t handle, ref Position transform) =>
    //{
    //    transform.x = 10;
    //});
    //Print($"Took {sw.ElapsedMicroseconds()}");


    s_registry.Loop((uint32_t handle, ref Velocity vel, ref Position pos) =>
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
