
#include <proto/ECS/Registry.h>

using namespace mud;
using namespace toy;

struct Position;
struct Velocity;

namespace mud
{
	template <> Type& type<Position>() { static Type ty("Position"); return ty; }
	template <> Type& type<Velocity>() { static Type ty("Velocity"); return ty; }
}

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

class MyBufferRegistry : public BufferRegistry<MyBufferRegistry,
	//ComponentBufferSparse<Position>,
	//ComponentBufferSparse<Velocity>
	ComponentBufferDense<Position>,
	ComponentBufferDense<Velocity>
>
{
public:
	MyBufferRegistry() { m_buffers = { { type<Position>(), 0 }, { type<Velocity>(), 1 } }; }
	template <class T> static constexpr size_t buffer_index() {}
	template <> static constexpr size_t buffer_index<Position>() { return 0; }
	template <> static constexpr size_t buffer_index<Velocity>() { return 1; }
};

void test_ecs()
{
	int preallocShift = 14;
	static EntityRegistry<MyBufferRegistry> registry_ = { 1 << preallocShift };

    //create registry
    //Print("Creating Registry");

//        PrintRegistryDebug();

    //create and register some component buffers
//        Print("Creating Component Buffers");

    //registry_.RegisterComponent<Position>(BufferType::Dense, 1<<preallocShift);
   // registry_.RegisterComponent<Velocity>(BufferType::Dense, 1<<preallocShift);
        
//        PrintRegistryDebug();
//        PrintCompBufsDebug();




        
    auto e = registry_.CreateEntity();
    registry_.AddComponent(e, Position());
    registry_.AddComponent(e, Velocity{ 0, 3 });

    auto e1 = registry_.CreateEntity();
    registry_.AddComponent(e1, Position());
    //registry_.AddComponent(e1, Velocity { x = 0, y = 1 });

    auto e2 = registry_.CreateEntity();
    registry_.AddComponent(e2, Position());
    registry_.AddComponent(e2, Velocity { 0, 5 });

    auto e3 = registry_.CreateEntity();
    registry_.AddComponent(e3, Position());
    //registry_.AddComponent(e3, Velocity { x = 0, y = 1 });

    registry_.Loop<Position, Velocity>([](EntIdx entIdx, Position& pos, Velocity& vel)
    {
		UNUSED(entIdx);
        pos.m_y += vel.m_y;
    });


    //Console.ReadKey();
    /*




    ////create entities and components
    //Print("Creating 4 Entities");

    //auto entA = registry_.CreateEntity();
    //registry_.AddComponent(entA, new Position());
    //registry_.AddComponent(entA, new Velocity());

    //PrintEntityDebug(entA);

    //auto entB = registry_.CreateEntity();
    //registry_.AddComponent(entB, new Position());

    //PrintEntityDebug(entB);

    //auto entC = registry_.CreateEntity();
    //registry_.AddComponent(entC, new Velocity());

    //PrintEntityDebug(entC);

    //auto entD = registry_.CreateEntity();

    //PrintEntityDebug(entD);

    //PrintRegistryDebug();
    //PrintCompBufsDebug(true);

    //Print("Removing component");

    //registry_.RemoveComponent<Velocity>(entA);

    //PrintCompBufsDebug(true);

    //Print("Readding component");

    //registry_.AddComponent(entA, new Velocity());

    //PrintCompBufsDebug(true);

    //Print("Removing other");

    //registry_.RemoveComponent<Position>(entA);

    //PrintCompBufsDebug(true);

    //Print("Readding other");

    //registry_.AddComponent(entA, new Position());

    //PrintCompBufsDebug(true);

    //Print("Adding new to 2nd entity");

    //registry_.AddComponent(entB, new Velocity());

    //PrintEntityDebug(entB);
    //PrintCompBufsDebug(true);

    //Print("Removing all from 2nd entity");

    //registry_.RemoveAllComponents(entB);

    //PrintEntityDebug(entB);
    //PrintCompBufsDebug(true);

    //Print("Removing 3rd entity");

    //registry_.DeleteEntity(entC);
    //PrintRegistryDebug(true);
    //PrintCompBufsDebug(true);

    //Print("Removing 1st entity");

    //registry_.DeleteEntity(entA);
    //PrintRegistryDebug(true);
    //PrintCompBufsDebug(true);

    //Print("Creating new with components");

    //auto entE = registry_.CreateEntity();
    //registry_.AddComponent(entE, new Position());
    //registry_.AddComponent(entE, new Velocity{x=0,y=1});
    //PrintRegistryDebug(true);
    //PrintCompBufsDebug(true);

    //Print("Removing newly created entity");

    //registry_.DeleteEntity(entE);
    //PrintRegistryDebug(true);
    //PrintCompBufsDebug(true);

    //Print("Adding component to 4th entity");

    //registry_.AddComponent(entD, new Position());
    //PrintRegistryDebug(true);
    //PrintCompBufsDebug(true);

    //####################### LOOPS
    // add a tonne of stuff
    Print("Adding a ton of ents and comps");
    auto sw = Stopwatch.StartNew();
    for (int i = 0; i < 1<<16; i++)
    {
        auto id = registry_.CreateEntity();
        registry_.AddComponent(id, new Position());
        registry_.AddComponent(id, new Velocity { x = 0, y = 1 });
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
    //registry_.Loop((EntIdx entIdx, ref Position transform) =>
    //{
    //    transform.x = 10;
    //});
    //Print($"Took {sw.ElapsedMicroseconds()}");


    registry_.Loop((EntIdx entIdx, ref Velocity vel, ref Position pos) =>
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
