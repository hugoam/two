#pragma once

#include <mud/srlz.h>
#include <mud/refl.h>
#include <mud/infra.h>
#include <mud/type.h>





#ifndef MUD_MATH_EXPORT
#define MUD_MATH_EXPORT MUD_IMPORT
#endif

namespace mud
{
    enum Clockwise : unsigned int;
    enum class Axis : unsigned int;
    enum class Axes : unsigned int;
    enum class SignedAxis : unsigned int;
    enum class Side : unsigned int;
    enum class TrackMode : unsigned int;
    enum class Spectrum : short;
    
    template <class T> struct Range;
    template <class T> struct ValueCurve;
    template <class T> struct ValueTrack;
    template <class T> struct Grid;
    template <class T> struct array3d;
	template <class T> struct StatDef;
	template <class T> struct Stat;
    template <class T> struct AutoStat;
    
    struct Transform;
    struct Colour;
    class Lerp;
    class Grided3;
    struct Image;
    struct Palette;
    struct Image256;
    class ImageAtlas;
    class Sprite;
    class SpriteAtlas;
	class TextureAtlas;
    struct Ratio;
    struct Gauge;
    struct Time;
    struct TimeSpan;
    class Clock;
    struct Anim;
    class Animator;
}



namespace mud
{
	export_ enum class refl_ Axis : unsigned int
	{
		X = 0,
		Y = 1,
		Z = 2,
	};

	export_ enum class refl_ Axes : unsigned int
	{
		None = 0,
		X = 1 << 0,
		Y = 1 << 1,
		Z = 1 << 2,
	};

	export_ inline Axes to_axes(Axes x = Axes::None, Axes y = Axes::None, Axes z = Axes::None) { return Axes(uint(x) | uint(y) | uint(z)); }
	export_ inline bool check_axis(Axes axes, Axes axis) { return (uint(axes) & uint(axis)) != 0; }

	export_ enum class refl_ SignedAxis : unsigned int
	{
		PlusX  = 0,
		MinusX = 1,
		PlusY  = 2,
		MinusY = 3,
		PlusZ  = 4,
		MinusZ = 5,
	};

	export_ inline SignedAxis to_signed_axis(Axis axis, bool positive)
	{
		return SignedAxis(uint(axis) * 2 + (positive ? 0 : 1));
	}

	export_ enum class refl_ Side : unsigned int
	{
		Right = uint(SignedAxis::PlusX),
		Left  = uint(SignedAxis::MinusX),
		Up    = uint(SignedAxis::PlusY),
		Down  = uint(SignedAxis::MinusY),
		Back  = uint(SignedAxis::PlusZ),
		Front = uint(SignedAxis::MinusZ),
	};
}



#ifndef MUD_CPP_20
#include <stdint.h>
#endif

#ifdef MUD_META_GENERATOR
namespace mud
{
	struct refl_ array_ extern_ vec2  { constr_ vec2();   constr_ vec2(float a);     constr_ vec2(float x, float y);                                attr_ float x; attr_ float y; };
	struct refl_ array_ extern_ uvec2 { constr_ uvec2();  constr_ uvec2(uint32_t a); constr_ uvec2(uint32_t x, uint32_t y);						    attr_ uint32_t x; attr_ uint32_t y; };
	struct refl_ array_ extern_ vec3  { constr_ vec3();   constr_ vec3(float a);     constr_ vec3(float x, float y, float z);                       attr_ float x; attr_ float y; attr_ float z; };
	struct refl_ array_ extern_ uvec3 { constr_ uvec3();  constr_ uvec3(uint32_t a); constr_ uvec3(uint32_t x, uint32_t y, uint32_t z);             attr_ uint32_t x;   attr_ uint32_t y;   attr_ uint32_t z; };
	struct refl_ array_ extern_ ivec3 { constr_ ivec3();  constr_ ivec3(int a);      constr_ ivec3(int x, int y, int z);                            attr_ int x;   attr_ int y;   attr_ int z; };
	struct refl_ array_ extern_ vec4  { constr_ vec4();   constr_ vec4(float a);     constr_ vec4(float w, float x, float y, float z);              attr_ float x; attr_ float y; attr_ float z; attr_ float w; };
	struct refl_ array_ extern_ uvec4 { constr_ uvec4();  constr_ uvec4(uint32_t a); constr_ uvec4(uint32_t w, uint32_t x, uint32_t y, uint32_t z); attr_ uint32_t x; attr_ uint32_t y; attr_ uint32_t z; attr_ uint32_t w; };
	struct refl_ array_ extern_ quat  { constr_ quat();   constr_ quat(float w, float x, float y, float z);   constr_ quat(vec3 euler_angles);      attr_ float x; attr_ float y; attr_ float z; attr_ float w; };
	struct refl_ extern_ mat4 {};

	struct refl_ extern_ bvec3 {};
	struct refl_ extern_ bvec4 {};
	struct refl_ extern_ ivec2 {};
	struct refl_ extern_ ivec4 {};

	struct refl_ extern_ half3 {};
	struct refl_ extern_ half2 {};
}
#else
namespace mud
{
	template <class T>
	export_ struct refl_ struct_ array_ v2
	{
		typedef uint length_type;
		typedef T type;
		v2();
		explicit v2(T v);
		v2(T x, T y);
		template <class V>
		explicit v2(V v);
		T operator[](uint index) const;
		T& operator[](uint index);
		bool operator==(const v2& other) const;
		bool operator!=(const v2& other) const;
		explicit operator T();
		union {
			struct { attr_ T x; attr_ T y; };
			T f[2];
		};
	};

	template <class T>
	export_ struct refl_ struct_ array_ v3
	{
		typedef uint length_type;
		typedef T type;
		typedef v2<T> type2;
		v3();
		explicit v3(T v);
		v3(T x, T y, T z);
		v3(v2<T> a, T z);
		template <class V>
		explicit v3(V v);
		T operator[](uint index) const;
		T& operator[](uint index);
		bool operator==(const v3& other) const;
		bool operator!=(const v3& other) const;
		explicit operator T();
		explicit operator v2<T>();
		union {
			struct { attr_ T x; attr_ T y; attr_ T z; };
			struct { T r; T g; T b; };
			T f[3];
		};
	};

	template <class T>
	export_ struct refl_ struct_ array_ v4
	{
		typedef uint length_type;
		typedef T type;
		typedef v2<T> type2;
		typedef v3<T> type3;
		v4();
		explicit v4(T v);
		v4(T x, T y, T z, T w);
		v4(v3<T> a, T w);
		v4(T x, v3<T> b);
		v4(v2<T> a, v2<T> b);
		template <class V>
		explicit v4(V v);
		T operator[](uint index) const;
		T& operator[](uint index);
		bool operator==(const v4& other) const;
		bool operator!=(const v4& other) const;
		explicit operator v2<T>();
		explicit operator v3<T>();
		union {
			struct { attr_ T x; attr_ T y; attr_ T z; attr_ T w; };
			struct { T r; T g; T b; T a; };
			T f[4];
		};
	};

	export_ extern template struct refl_ v2<float>;
	export_ extern template struct refl_ v3<float>;
	export_ extern template struct refl_ v4<float>;

	export_ extern template struct refl_ v2<int>;
	export_ extern template struct refl_ v3<int>;
	export_ extern template struct refl_ v4<int>;

	export_ extern template struct refl_ v2<uint>;
	export_ extern template struct refl_ v3<uint>;
	export_ extern template struct refl_ v4<uint>;

	export_ extern template struct refl_ v2<bool>;
	export_ extern template struct refl_ v3<bool>;
	export_ extern template struct refl_ v4<bool>;

	export_ refl_ using half2 = v2<ushort>;
	export_ refl_ using half3 = v3<ushort>;

	export_ refl_ using float2 = v2<float>;
	export_ refl_ using float3 = v3<float>;
	export_ refl_ using float4 = v4<float>;

	export_ refl_ using int2 = v2<int>;
	export_ refl_ using int3 = v3<int>;
	export_ refl_ using int4 = v4<int>;

	export_ refl_ using uint2 = v2<uint>;
	export_ refl_ using uint3 = v3<uint>;
	export_ refl_ using uint4 = v4<uint>;

	export_ refl_ using bool2 = v2<bool>;
	export_ refl_ using bool3 = v3<bool>;
	export_ refl_ using bool4 = v4<bool>;

	export_ template <class T> inline typename T::type* value_ptr(T& v) { return &v[0]; }
	export_ template <class T> inline const typename T::type* value_ptr(const T& v) { return &v.f[0]; }

	export_ using vec2 = float2;
	export_ using vec3 = float3;
	export_ using vec4 = float4;
	export_ using uvec2 = uint2;
	export_ using uvec3 = uint3;
	export_ using uvec4 = uint4;
	export_ using ivec2 = int2;
	export_ using ivec3 = int3;
	export_ using ivec4 = int4;
	export_ using bvec3 = bool3;
	export_ using bvec4 = bool4;

	export_ struct refl_ struct_ array_ mat3
	{
		typedef float type;
		mat3();
		mat3(const float3& x, const float3& y, const float3& z);
		mat3(float f0, float f1, float f2, float f3, float f4, float f5, float f6, float f7, float f8);

		const float3& operator[](uint index) const { return *((float3*)f + index); }
		float3& operator[](uint index) { return *((float3*)f + index); }

		union
		{
			float m[3][3];
			attr_ float f[9];
		};
	};

	export_ struct refl_ struct_ array_ mat4
	{
		typedef float type;
		typedef uint length_type;
		mat4();
		mat4(const float4& x, const float4& y, const float4& z, const float4& w);
		mat4(float f0, float f1, float f2, float f3, float f4, float f5, float f6, float f7, float f8, float f9, float f10, float f11, float f12, float f13, float f14, float f15);

		const float4& operator[](uint index) const { return *((float4*)f + index); }
		float4& operator[](uint index) { return *((float4*)f + index); }

		bool operator==(const mat4& other) const;
		bool operator!=(const mat4& other) const { return !(*this == other); }

		union
		{
			float m[4][4];
			attr_ float f[16];
		};
	};

	export_ struct refl_ struct_ array_ quat : public float4
	{
		typedef float type;
		quat();
		quat(float v);
		quat(float x, float y, float z, float w);
		explicit quat(const float3& euler_angles);
	};

	export_ enum refl_ Clockwise : unsigned int
	{
		CLOCKWISE,
		ANTI_CLOCKWISE
	};
}
#endif

namespace mud
{
	export_ extern MUD_MATH_EXPORT const vec3 X3; // = { 1.f, 0.f, 0.f };
	export_ extern MUD_MATH_EXPORT const vec3 Y3; // = { 0.f, 1.f, 0.f };
	export_ extern MUD_MATH_EXPORT const vec3 Z3; // = { 0.f, 0.f, 1.f };

	export_ extern MUD_MATH_EXPORT const vec3 Zero3; // = { 0.f, 0.f, 0.f };
	export_ extern MUD_MATH_EXPORT const vec3 Unit3; // = { 1.f, 1.f, 1.f };

	export_ extern MUD_MATH_EXPORT const quat ZeroQuat; // = { 1.f, 0.f, 0.f, 0.f };

	export_ extern MUD_MATH_EXPORT const vec2 Zero2; // = { 0.f, 0.f };
	export_ extern MUD_MATH_EXPORT const vec2 Unit2; // = { 1.f, 1.f };

	export_ extern MUD_MATH_EXPORT const vec4 Zero4; // = { 0.f, 0.f, 0.f, 0.f };
	export_ extern MUD_MATH_EXPORT const vec4 Rect4; // = { 0.f, 0.f, 1.f, 1.f };

	export_ inline bool rect_intersects(const vec4& first, const vec4& second)
	{
		return !(second.x > first.x + first.z || second.y > first.y + first.w || second.x + second.z < first.x || second.y + second.w < first.y);
	}

	export_ struct refl_ MUD_MATH_EXPORT Transform
	{
		attr_ vec3 m_position = Zero3;
		attr_ quat m_rotation = ZeroQuat;
		attr_ vec3 m_scale = Unit3;
	};

	Transform average_transforms(array<Transform*> transforms);
}

#include <stl/stddef.h>

namespace mud
{
	// @todo replace with inline constexpr when moving to C++17
	export_ extern MUD_MATH_EXPORT const Side c_sides[6]; // = { Side::Right, Side::Left, Side::Up, Side::Down, Side::Back, Side::Front };

	export_ extern MUD_MATH_EXPORT const vec3 c_axes[3];			// = {  X3,  Y3,  Z3 };
	export_ extern MUD_MATH_EXPORT const vec3 c_tangents[6];		// = {  Y3, -Z3,  Y3 };
	export_ extern MUD_MATH_EXPORT const vec3 c_binormals[6];		// = { -Z3,  X3,  X3 };
	export_ extern MUD_MATH_EXPORT const vec3 c_dirs[6];			// = {  X3, -X3,  Y3, -Y3,  Z3, -Z3 };
	export_ extern MUD_MATH_EXPORT const vec3 c_dirs_tangents[6];	// = {  Y3, -Z3, -Z3,  X3,  Y3,  X3 };
	export_ extern MUD_MATH_EXPORT const vec3 c_dirs_normals[6];	// = { -Z3,  Y3,  X3, -Z3,  X3,  Y3 };

	export_ inline vec3 to_vec3(Axis axis) { return c_axes[size_t(axis)]; }
	export_ inline vec3 to_vec3(Side side) { return c_dirs[size_t(side)]; }
	export_ inline vec3 to_vec3(SignedAxis axis) { return c_dirs[size_t(axis)]; }
}



#ifndef MUD_CPP_20
#include <stl/stddef.h>
#include <stdint.h>
#endif

namespace mud
{
	export_ struct refl_ array_  MUD_MATH_EXPORT Colour
	{
		constr_ Colour();
		constr_ Colour(float v, float a = 1.f);
		constr_ Colour(float r, float g, float b, float a = 1.f);

		constr_ static Colour hsl(float h, float s, float l);

		Colour(const Colour& col) = default;
		Colour& operator=(const Colour&) = default;

		bool operator==(const Colour& other) const { return m_r == other.m_r && m_g == other.m_g && m_b == other.m_b && m_a == other.m_a; }

		union {
			struct {
				attr_ float m_r;
				attr_ float m_g;
				attr_ float m_b;
				attr_ float m_a;
			};
			struct { float m_h; float m_s; float m_l; float m__; };
			float m_floats[4];
		};

		float operator[](size_t i) const { return m_floats[i]; }
		float& operator[](size_t i) { return m_floats[i]; }

		Colour operator*(const float factor) const { return Colour(m_r*factor, m_g*factor, m_b*factor, m_a); }
		Colour operator*(const Colour& colour) const { return Colour(m_r*colour.m_r, m_g*colour.m_g, m_b*colour.m_b, m_a); }
		Colour operator+(const Colour& colour) const { return Colour(m_r+colour.m_r, m_g+colour.m_g, m_b+colour.m_b, m_a+colour.m_a); }
		Colour operator-(const Colour& colour) const { return Colour(m_r-colour.m_r, m_g-colour.m_g, m_b-colour.m_b, m_a-colour.m_a); }

		bool null() const { return m_a == 0.f; }

	public:
		attr_ static Colour Black;
		attr_ static Colour AlphaBlack;
		attr_ static Colour Red;
		attr_ static Colour Green;
		attr_ static Colour NeonGreen;
		attr_ static Colour Blue;
		attr_ static Colour Pink;
		attr_ static Colour Cyan;
		attr_ static Colour Yellow;
		attr_ static Colour White;
		attr_ static Colour AlphaWhite;
		attr_ static Colour LightGrey;
		attr_ static Colour MidGrey;
		attr_ static Colour DarkGrey;
		attr_ static Colour AlphaGrey;
		attr_ static Colour Transparent;
		attr_ static Colour Invisible;
		attr_ static Colour None;
	};

	export_ MUD_MATH_EXPORT func_ uint32_t to_rgba(const Colour& colour);
	export_ MUD_MATH_EXPORT func_ uint32_t to_abgr(const Colour& colour);
	export_ MUD_MATH_EXPORT func_ Colour from_rgba(uint32_t colour);
	export_ MUD_MATH_EXPORT func_ Colour from_abgr(uint32_t colour);
	export_ MUD_MATH_EXPORT func_ Colour to_linear(const Colour& colour);
	export_ MUD_MATH_EXPORT func_ Colour to_gamma(const Colour& colour);
	export_ MUD_MATH_EXPORT func_ Colour to_srgb(const Colour& colour);

	export_ MUD_MATH_EXPORT func_ Colour hsl_to_rgb(float h, float s, float l);
	export_ MUD_MATH_EXPORT func_ Colour rgb_to_hsl(float r, float g, float b);

	export_ MUD_MATH_EXPORT func_ Colour rgba_to_hsla(const Colour& colour);
	export_ MUD_MATH_EXPORT func_ Colour hsla_to_rgba(const Colour& colour);

	inline Colour saturation(const Colour& colour, float amount)
	{
		Colour result = rgb_to_hsl(colour.m_r, colour.m_g, colour.m_b);
		result.m_s *= amount;
		return hsl_to_rgb(result.m_h, result.m_s, result.m_l);
	}

	inline Colour offset_hsl(const Colour& colour, float h, float s, float l)
	{
		Colour result = rgb_to_hsl(colour.m_r, colour.m_g, colour.m_b);
		result.m_h *= h;
		result.m_s *= s;
		result.m_l *= l;
		return hsl_to_rgb(result.m_h, result.m_s, result.m_l);
	}

	export_ inline Colour to_colour(uint8_t r, uint8_t g, uint8_t b) { return Colour(float(r) / 255.f, float(g) / 255.f, float(b) / 255.f); }
	export_ inline Colour to_colour(uint8_t r, uint8_t g, uint8_t b, uint8_t a) { return Colour(float(r) / 255.f, float(g) / 255.f, float(b) / 255.f, float(a) / 255.f); }
}


#include <stl/vector.h>


#ifndef MUD_MODULES
#endif




#ifndef MUD_CPP_20
#include <stdint.h>
#include <cmath>
#endif

#ifdef MUD_META_GENERATOR
func_ float sinf(float a);
func_ float cosf(float a);
func_ double sin(double a);
func_ double cos(double a);
#endif

namespace mud
{
	export_ extern MUD_MATH_EXPORT const float c_pi;

	export_ using uchar = unsigned char;
	export_ using ushort = unsigned short;
	export_ using uint = unsigned int;

	export_ using u16 = uint16_t;
	export_ using u32 = uint32_t;
	export_ using i16 = int16_t;
	export_ using i32 = int32_t;

	export_ using std::abs;
	export_ using std::floor;
	export_ using std::ceil;
	export_ using std::sin;
	export_ using std::cos;
	export_ using std::pow;
	export_ using std::log2;
	export_ using std::isnan;
	export_ using std::isinf;

	export_ template <class T>
	inline T sign(T val) { return T(T(0) < val) - (val < T(0)); }

	export_ template <class T>
	inline T min(T a, T b) { return (b < a) ? b : a; }

	export_ template <class T>
	inline T max(T a, T b) { return (a < b) ? b : a; }

	export_ template <class T>
	inline T clamp(T v, T lo, T hi) { return min(max(v, lo), hi); }

	export_ template <class T>
	func_ T add(T a, T b) { return a + b; }

	export_ template <class T>
	func_ T subtract(T a, T b) { return a - b; }

	export_ template <class T>
	func_ T multiply(T a, T b) { return a * b; }

	export_ template <class T>
	func_ T divide(T a, T b) { return a / b; }

#ifndef MUD_META_GENERATOR
	template MUD_MATH_EXPORT func_ float add<float>(float a, float b);
	template MUD_MATH_EXPORT func_ float subtract<float>(float a, float b);
	template MUD_MATH_EXPORT func_ float multiply<float>(float a, float b);
	template MUD_MATH_EXPORT func_ float divide<float>(float a, float b);
#else
	template <> func_ float add<float>(float a, float b);
	template <> func_ float subtract<float>(float a, float b);
	template <> func_ float multiply<float>(float a, float b);
	template <> func_ float divide<float>(float a, float b);
#endif

	export_ MUD_MATH_EXPORT func_ float nsinf(float a); // { return a + 1.f / 2.f; } // @kludge can't be inline because we identify reflected functions through their pointer 
	export_ MUD_MATH_EXPORT func_ float ncosf(float a); // { return a + 1.f / 2.f; }

	export_ MUD_MATH_EXPORT func_ double nsin(double a); // { return a + 1.0 / 2.0; }
	export_ MUD_MATH_EXPORT func_ double ncos(double a); // { return a + 1.0 / 2.0; }

	inline float to_radians(float degrees)
	{
		return degrees / 180.f * c_pi;
	}

	export_ inline unsigned int pow2_round_up(unsigned int x)
	{
		--x;
		x |= x >> 1;
		x |= x >> 2;
		x |= x >> 4;
		x |= x >> 8;
		x |= x >> 16;
		return x + 1;
	}

	export_ inline float remap(float number, float from_low, float from_high, float low, float high)
	{
		float slope = (high - low) / (from_high - from_low);
		float result = low + slope * (number - from_low);
		return result;
	}

	export_ inline float remap_trig(float number, float low, float high)
	{
		return remap(number, -1.f, 1.f, low, high);
	}

	MUD_MATH_EXPORT void register_math_conversions();
}

#ifndef MUD_CPP_20
#include <stdint.h>
#include <cmath>
#endif

// These are binary-exact approximations of pi/e constants
// http://www.exploringbinary.com/pi-and-e-in-binary/

#define MATH_fPI 3.1415927410125732421875f
#define MATH_dPI 3.141592653589793115997963468544185161590576171875
#define MATH_fE 2.71828174591064453125f
#define MATH_dE 2.718281828459045090795598298427648842334747314453125

namespace mud
{
	template <class T>
	inline v2<T>::v2() { }
	template <class T>
	inline v2<T>::v2(T v) : x(v), y(v) {}
	template <class T>
	inline v2<T>::v2(T x, T y) : x(x), y(y) {}
	template <class T>
	template <class V>
	inline v2<T>::v2(V v) : x(T(v.x)), y(T(v.y)) {}
	template <class T>
	inline T v2<T>::operator[](uint index) const { return *((T*)&x + index); }
	template <class T>
	inline T& v2<T>::operator[](uint index) { return *((T*)&x + index); }
	template <class T>
	inline bool v2<T>::operator==(const v2& other) const { return x == other.x && y == other.y; }
	template <class T>
	inline bool v2<T>::operator!=(const v2& other) const { return x != other.x || y != other.y; }
	template <class T>
	inline v2<T>::operator T() { return T(x); }

	template <class T>
	inline v3<T>::v3() { }
	template <class T>
	inline v3<T>::v3(T v) : x(v), y(v), z(v) {}
	template <class T>
	inline v3<T>::v3(T x, T y, T z) : x(x), y(y), z(z) {}
	template <class T>
	inline v3<T>::v3(v2<T> a, T z) : x(a.x), y(a.y), z(z) {}
	template <class T>
	template <class V>
	inline v3<T>::v3(V v) : x(T(v.x)), y(T(v.y)), z(T(v.z)) {}
	template <class T>
	inline T v3<T>::operator[](uint index) const { return *((T*)&x + index); }
	template <class T>
	inline T& v3<T>::operator[](uint index) { return *((T*)&x + index); }
	template <class T>
	inline bool v3<T>::operator==(const v3& other) const { return x == other.x && y == other.y && z == other.z; }
	template <class T>
	inline bool v3<T>::operator!=(const v3& other) const { return x != other.x || y != other.y || z != other.z; }
	template <class T>
	inline v3<T>::operator T() { return T(x); }
	template <class T>
	inline v3<T>::operator v2<T>() { return v2<T>(x, y); }

	template <class T>
	inline v4<T>::v4() {}
	template <class T>
	inline v4<T>::v4(T v) : x(v), y(v), z(v), w(v) {}
	template <class T>
	inline v4<T>::v4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}
	template <class T>
	inline v4<T>::v4(v3<T> a, T w) : x(a.x), y(a.y), z(a.z), w(w) {}
	template <class T>
	inline v4<T>::v4(T x, v3<T> b) : x(x), y(b.x), z(b.y), w(b.z) {}
	template <class T>
	inline v4<T>::v4(v2<T> a, v2<T> b) : x(a.x), y(a.y), z(b.x), w(b.y) {}
	template <class T>
	template <class V>
	inline v4<T>::v4(V v) : x(T(v.x)), y(T(v.y)), z(T(v.z)), w(T(v.w)) {}
	template <class T>
	inline T v4<T>::operator[](uint index) const { return *((T*)&x + index); }
	template <class T>
	inline T& v4<T>::operator[](uint index) { return *((T*)&x + index); }
	template <class T>
	inline bool v4<T>::operator==(const v4& other) const { return x == other.x && y == other.y && z == other.z && w == other.w; }
	template <class T>
	inline bool v4<T>::operator!=(const v4& other) const { return x != other.x || y != other.y || z != other.z || w != other.w; }
	template <class T>
	inline v4<T>::operator v2<T>() { return v2<T>(x, y); }
	template <class T>
	inline v4<T>::operator v3<T>() { return v3<T>(x, y, z); }

	// Experimental swizzling
	export_ template <class T> inline typename T::type2 xy(const T& v)
	{
		return typename T::type2(v.x, v.y);
	}
	export_ template <class T> inline typename T::type2 xz(const T& v)
	{
		return typename T::type2(v.x, v.z);
	}
	// These alias instead of constructing another variable, allowing modification
	export_ template <class T> inline const typename T::type3& xyz(const T& v)
	{
		return (typename T::type3&)v;
	}
	export_ template <class T> inline typename T::type3& xyz(T& v)
	{
		return (typename T::type3&)v;
	}

	template <class T> inline v2<T> operator+(const v2<T>& a, const v2<T>& b) { return v2<T>(a.x + b.x, a.y + b.y); }
	template <class T> inline v3<T> operator+(const v3<T>& a, const v3<T>& b) { return v3<T>(a.x + b.x, a.y + b.y, a.z + b.z); }
	template <class T> inline v4<T> operator+(const v4<T>& a, const v4<T>& b) { return v4<T>(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w); }

	template <class T> inline v2<T> operator+(const v2<T>& a, T b) { return v2<T>(a.x + b, a.y + b); }
	template <class T> inline v3<T> operator+(const v3<T>& a, T b) { return v3<T>(a.x + b, a.y + b, a.z + b); }
	template <class T> inline v4<T> operator+(const v4<T>& a, T b) { return v4<T>(a.x + b, a.y + b, a.z + b, a.w + b); }

	template <class T> inline v2<T> operator-(const v2<T>& a, const v2<T>& b) { return v2<T>(a.x - b.x, a.y - b.y); }
	template <class T> inline v3<T> operator-(const v3<T>& a, const v3<T>& b) { return v3<T>(a.x - b.x, a.y - b.y, a.z - b.z); }
	template <class T> inline v4<T> operator-(const v4<T>& a, const v4<T>& b) { return v4<T>(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w); }

	template <class T> inline v2<T> operator-(const v2<T>& a, T b) { return v2<T>(a.x - b, a.y - b); }
	template <class T> inline v3<T> operator-(const v3<T>& a, T b) { return v3<T>(a.x - b, a.y - b, a.z - b); }
	template <class T> inline v4<T> operator-(const v4<T>& a, T b) { return v4<T>(a.x - b, a.y - b, a.z - b, a.w - b); }

	template <class T> inline v2<T> operator*(const v2<T>& a, const v2<T>& b) { return v2<T>(a.x * b.x, a.y * b.y); }
	template <class T> inline v3<T> operator*(const v3<T>& a, const v3<T>& b) { return v3<T>(a.x * b.x, a.y * b.y, a.z * b.z); }
	template <class T> inline v4<T> operator*(const v4<T>& a, const v4<T>& b) { return v4<T>(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w); }
	template <class T> inline v2<T> operator*(const v2<T>& a, T b) { return v2<T>(a.x * b, a.y * b); }
	template <class T> inline v3<T> operator*(const v3<T>& a, T b) { return v3<T>(a.x * b, a.y * b, a.z * b); }
	template <class T> inline v4<T> operator*(const v4<T>& a, T b) { return v4<T>(a.x * b, a.y * b, a.z * b, a.w * b); }
	template <class T> inline v2<T> operator*(T a, const v2<T>& b) { return v2<T>(a * b.x, a * b.y); }
	template <class T> inline v3<T> operator*(T a, const v3<T>& b) { return v3<T>(a * b.x, a * b.y, a * b.z); }
	template <class T> inline v4<T> operator*(T a, const v4<T>& b) { return v4<T>(a * b.x, a * b.y, a * b.z, a * b.w); }

	template <class T> inline v2<T> operator/(const v2<T>& a, const v2<T>& b) { return v2<T>(a.x / b.x, a.y / b.y); }
	template <class T> inline v3<T> operator/(const v3<T>& a, const v3<T>& b) { return v3<T>(a.x / b.x, a.y / b.y, a.z / b.z); }
	template <class T> inline v4<T> operator/(const v4<T>& a, const v4<T>& b) { return v4<T>(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w); }
	template <class T> inline v2<T> operator/(const v2<T>& a, T b) { return v2<T>(a.x / b, a.y / b); }
	template <class T> inline v3<T> operator/(const v3<T>& a, T b) { return v3<T>(a.x / b, a.y / b, a.z / b); }
	template <class T> inline v4<T> operator/(const v4<T>& a, T b) { return v4<T>(a.x / b, a.y / b, a.z / b, a.w / b); }
	template <class T> inline v2<T> operator/(T a, const v2<T>& b) { return v2<T>(a / b.x, a / b.y); }
	template <class T> inline v3<T> operator/(T a, const v3<T>& b) { return v3<T>(a / b.x, a / b.y, a / b.z); }
	template <class T> inline v4<T> operator/(T a, const v4<T>& b) { return v4<T>(a / b.x, a / b.y, a / b.z, a / b.w); }

	template <class T> inline v2<T> operator-(const v2<T>& a) { return v2<T>(-a.x, -a.y); }
	template <class T> inline v3<T> operator-(const v3<T>& a) { return v3<T>(-a.x, -a.y, -a.z); }
	template <class T> inline v4<T> operator-(const v4<T>& a) { return v4<T>(-a.x, -a.y, -a.z, -a.w); }

	template <class T> inline v2<T>& operator+=(v2<T>& a, const v2<T>& b) { a = a + b; return a; }
	template <class T> inline v3<T>& operator+=(v3<T>& a, const v3<T>& b) { a = a + b; return a; }
	template <class T> inline v4<T>& operator+=(v4<T>& a, const v4<T>& b) { a = a + b; return a; }

	template <class T> inline v2<T>& operator-=(v2<T>& a, const v2<T>& b) { a = a - b; return a; }
	template <class T> inline v3<T>& operator-=(v3<T>& a, const v3<T>& b) { a = a - b; return a; }
	template <class T> inline v4<T>& operator-=(v4<T>& a, const v4<T>& b) { a = a - b; return a; }

	template <class T> inline v2<T>& operator*=(v2<T>& a, const v2<T>& b) { a = a * b; return a; }
	template <class T> inline v3<T>& operator*=(v3<T>& a, const v3<T>& b) { a = a * b; return a; }
	template <class T> inline v4<T>& operator*=(v4<T>& a, const v4<T>& b) { a = a * b; return a; }
	template <class T> inline v2<T>& operator*=(v2<T>& a, T b) { a = a * b; return a; }
	template <class T> inline v3<T>& operator*=(v3<T>& a, T b) { a = a * b; return a; }
	template <class T> inline v4<T>& operator*=(v4<T>& a, T b) { a = a * b; return a; }

	template <class T> inline v2<T>& operator/=(v2<T>& a, const v2<T>& b) { a = a / b; return a; }
	template <class T> inline v3<T>& operator/=(v3<T>& a, const v3<T>& b) { a = a / b; return a; }
	template <class T> inline v4<T>& operator/=(v4<T>& a, const v4<T>& b) { a = a / b; return a; }
	template <class T> inline v2<T>& operator/=(v2<T>& a, T b) { a = a / b; return a; }
	template <class T> inline v3<T>& operator/=(v3<T>& a, T b) { a = a / b; return a; }
	template <class T> inline v4<T>& operator/=(v4<T>& a, T b) { a = a / b; return a; }

	template <class T> inline bool all(const v2<T>& v) { return v.x && v.y; }
	template <class T> inline bool all(const v3<T>& v) { return v.x && v.y && v.z; }
	template <class T> inline bool all(const v4<T>& v) { return v.x && v.y && v.z && v.w; }

	template <class T> inline bool any(const v2<T>& v) { return v.x || v.y; }
	template <class T> inline bool any(const v3<T>& v) { return v.x || v.y || v.z; }
	template <class T> inline bool any(const v4<T>& v) { return v.x || v.y || v.z || v.w; }

	template <class T> inline bool2 isinf(const v2<T>& v) { return bool2(isinf(v.x), isinf(v.y)); }
	template <class T> inline bool3 isinf(const v3<T>& v) { return bool3(isinf(v.x), isinf(v.y), isinf(v.z)); }
	template <class T> inline bool4 isinf(const v4<T>& v) { return bool4(isinf(v.x), isinf(v.y), isinf(v.z), isinf(v.w)); }

	template <class T> inline bool2 isnan(const v2<T>& v) { return bool2(isnan(v.x), isnan(v.y)); }
	template <class T> inline bool3 isnan(const v3<T>& v) { return bool3(isnan(v.x), isnan(v.y), isnan(v.z)); }
	template <class T> inline bool4 isnan(const v4<T>& v) { return bool4(isnan(v.x), isnan(v.y), isnan(v.z), isnan(v.w)); }

	template <class T> inline bool2 less(const v2<T>& a, const v2<T>& b) { return bool2(a.x < b.x, a.y < b.y); }
	template <class T> inline bool3 less(const v3<T>& a, const v3<T>& b) { return bool3(a.x < b.x, a.y < b.y, a.z < b.z); }
	template <class T> inline bool4 less(const v4<T>& a, const v4<T>& b) { return bool4(a.x < b.x, a.y < b.y, a.z < b.z, a.w < b.w); }

	template <class T> inline bool2 less_equal(const v2<T>& a, const v2<T>& b) { return bool2(a.x <= b.x, a.y <= b.y); }
	template <class T> inline bool3 less_equal(const v3<T>& a, const v3<T>& b) { return bool3(a.x <= b.x, a.y <= b.y, a.z <= b.z); }
	template <class T> inline bool4 less_equal(const v4<T>& a, const v4<T>& b) { return bool4(a.x <= b.x, a.y <= b.y, a.z <= b.z, a.w <= b.w); }

	template <class T> inline bool2 greater(const v2<T>& a, const v2<T>& b) { return bool2(a.x > b.x, a.y > b.y); }
	template <class T> inline bool3 greater(const v3<T>& a, const v3<T>& b) { return bool3(a.x > b.x, a.y > b.y, a.z > b.z); }
	template <class T> inline bool4 greater(const v4<T>& a, const v4<T>& b) { return bool4(a.x > b.x, a.y > b.y, a.z > b.z, a.w > b.w); }

	template <class T> inline bool2 greater_equal(const v2<T>& a, const v2<T>& b) { return bool2(a.x >= b.x, a.y >= b.y); }
	template <class T> inline bool3 greater_equal(const v3<T>& a, const v3<T>& b) { return bool3(a.x >= b.x, a.y >= b.y, a.z >= b.z); }
	template <class T> inline bool4 greater_equal(const v4<T>& a, const v4<T>& b) { return bool4(a.x >= b.x, a.y >= b.y, a.z >= b.z, a.w >= b.w); }

	template <class T> inline bool  equal(const T& a, const T& b, float eps) { return abs(b - a) < eps; }
	template <class T> inline bool2 equal(const v2<T>& a, const v2<T>& b, float eps) { return less(abs(b - a), v2<T>(eps)); }
	template <class T> inline bool3 equal(const v3<T>& a, const v3<T>& b, float eps) { return less(abs(b - a), v3<T>(eps)); }
	template <class T> inline bool4 equal(const v4<T>& a, const v4<T>& b, float eps) { return less(abs(b - a), v4<T>(eps)); }

	template <class T> inline bool2 equal(const v2<T>& a, const v2<T>& b) { return bool2(a.x == b.x, a.y == b.y); }
	template <class T> inline bool3 equal(const v3<T>& a, const v3<T>& b) { return bool3(a.x == b.x, a.y == b.y, a.z == b.z); }
	template <class T> inline bool4 equal(const v4<T>& a, const v4<T>& b) { return bool4(a.x == b.x, a.y == b.y, a.z == b.z, a.w == b.w); }

	template <class T> inline bool2 not_equal(const v2<T>& a, const v2<T>& b) { return bool2(a.x != b.x, a.y != b.y); }
	template <class T> inline bool3 not_equal(const v3<T>& a, const v3<T>& b) { return bool3(a.x != b.x, a.y != b.y, a.z != b.z); }
	template <class T> inline bool4 not_equal(const v4<T>& a, const v4<T>& b) { return bool4(a.x != b.x, a.y != b.y, a.z != b.z, a.w != b.w); }

	//template <class T> inline T     sign(T v) { return T(T(0) < v) - T(v < T(0)); }
	template <class T> inline v2<T> sign(const v2<T>& v) { return T2(less(v2<T>(T(0)), v)) - v2<T>(less(v, v2<T>(T(0)))); }
	template <class T> inline v3<T> sign(const v3<T>& v) { return T3(less(v3<T>(T(0)), v)) - v3<T>(less(v, v3<T>(T(0)))); }
	template <class T> inline v4<T> sign(const v4<T>& v) { return T4(less(v4<T>(T(0)), v)) - v4<T>(less(v, v4<T>(T(0)))); }

	template <class T> inline T dot(const v2<T>& a, const v2<T>& b) { v2<T> tmp = a * b; return tmp.x + tmp.y; }
	template <class T> inline T dot(const v3<T>& a, const v3<T>& b) { v3<T> tmp = a * b; return tmp.x + tmp.y + tmp.z; }
	template <class T> inline T dot(const v4<T>& a, const v4<T>& b) { v4<T> tmp = a * b; return tmp.x + tmp.y + tmp.z + tmp.w; }

	template <class T> v3<T> cross(const v3<T>& a, const v3<T>& b)
	{
		return v3<T>(
			a.y * b.z - b.y * a.z,
			a.z * b.x - b.z * a.x,
			a.x * b.y - b.x * a.y
		);
	}

	template <class T> inline T length(const v2<T>& v) { return T(sqrt(dot(v, v))); }
	template <class T> inline T length(const v3<T>& v) { return T(sqrt(dot(v, v))); }
	template <class T> inline T length(const v4<T>& v) { return T(sqrt(dot(v, v))); }

	template <class T> inline T length2(const v2<T>& v) { return dot(v, v); }
	template <class T> inline T length2(const v3<T>& v) { return dot(v, v); }
	template <class T> inline T length2(const v4<T>& v) { return dot(v, v); }

	template <class T> inline T distance(const v2<T>& a, const v2<T>& b) { return length(b - a); }
	template <class T> inline T distance(const v3<T>& a, const v3<T>& b) { return length(b - a); }
	template <class T> inline T distance(const v4<T>& a, const v4<T>& b) { return length(b - a); }

	template <class T> inline T distance2(const v2<T>& a, const v2<T>& b) { return length2(b - a); }
	template <class T> inline T distance2(const v3<T>& a, const v3<T>& b) { return length2(b - a); }
	template <class T> inline T distance2(const v4<T>& a, const v4<T>& b) { return length2(b - a); }

	template <class T> inline v2<T> normalize(const v2<T>& v) { return v * T(1) / T(sqrt(dot(v, v))); }
	template <class T> inline v3<T> normalize(const v3<T>& v) { return v * T(1) / T(sqrt(dot(v, v))); }
	template <class T> inline v4<T> normalize(const v4<T>& v) { return v * T(1) / T(sqrt(dot(v, v))); }

	template <class T> inline v2<T> abs(const v2<T>& v) { return v2<T>(abs(v.x), abs(v.y)); }
	template <class T> inline v3<T> abs(const v3<T>& v) { return v3<T>(abs(v.x), abs(v.y), abs(v.z)); }
	template <class T> inline v4<T> abs(const v4<T>& v) { return v4<T>(abs(v.x), abs(v.y), abs(v.z), abs(v.w)); }

	template <class T> inline v2<T> mod(const v2<T>& a, const v2<T>& b) { return v2<T>(fmod(a.x, b.x), fmod(a.y, b.y)); }
	template <class T> inline v3<T> mod(const v3<T>& a, const v3<T>& b) { return v3<T>(fmod(a.x, b.x), fmod(a.y, b.y), fmod(a.z, b.z)); }
	template <class T> inline v4<T> mod(const v4<T>& a, const v4<T>& b) { return v4<T>(fmod(a.x, b.x), fmod(a.y, b.y), fmod(a.z, b.z), fmod(a.w, b.w)); }

	template <class T> inline T     imod(const T& a, const T& b) { return a % b; }
	template <class T> inline v2<T> imod(const v2<T>& a, const v2<T>& b) { return v2<T>(a.x % b.x, a.y % b.y); }
	template <class T> inline v3<T> imod(const v3<T>& a, const v3<T>& b) { return v3<T>(a.x % b.x, a.y % b.y, a.z % b.z); }
	template <class T> inline v4<T> imod(const v4<T>& a, const v4<T>& b) { return v4<T>(a.x % b.x, a.y % b.y, a.z % b.z, a.w % b.w); }

	template <class T> inline v2<T> min(const v2<T>& a, const v2<T>& b) { return v2<T>(min(a.x, b.x), min(a.y, b.y)); }
	template <class T> inline v3<T> min(const v3<T>& a, const v3<T>& b) { return v3<T>(min(a.x, b.x), min(a.y, b.y), min(a.z, b.z)); }
	template <class T> inline v4<T> min(const v4<T>& a, const v4<T>& b) { return v4<T>(min(a.x, b.x), min(a.y, b.y), min(a.z, b.z), min(a.w, b.w)); }
	template <class T> inline v2<T> min(const v2<T>& a, T b) { return v2<T>(min(a.x, b), min(a.y, b)); }
	template <class T> inline v3<T> min(const v3<T>& a, T b) { return v3<T>(min(a.x, b), min(a.y, b), min(a.z, b)); }
	template <class T> inline v4<T> min(const v4<T>& a, T b) { return v4<T>(min(a.x, b), min(a.y, b), min(a.z, b), min(a.w, b)); }

	template <class T> inline v2<T> max(const v2<T>& a, const v2<T>& b) { return v2<T>(max(a.x, b.x), max(a.y, b.y)); }
	template <class T> inline v3<T> max(const v3<T>& a, const v3<T>& b) { return v3<T>(max(a.x, b.x), max(a.y, b.y), max(a.z, b.z)); }
	template <class T> inline v4<T> max(const v4<T>& a, const v4<T>& b) { return v4<T>(max(a.x, b.x), max(a.y, b.y), max(a.z, b.z), max(a.w, b.w)); }
	template <class T> inline v2<T> max(const v2<T>& a, T b) { return v2<T>(max(a.x, b), max(a.y, b)); }
	template <class T> inline v3<T> max(const v3<T>& a, T b) { return v3<T>(max(a.x, b), max(a.y, b), max(a.z, b)); }
	template <class T> inline v4<T> max(const v4<T>& a, T b) { return v4<T>(max(a.x, b), max(a.y, b), max(a.z, b), max(a.w, b)); }

	template <class T> inline v2<T> clamp(const v2<T>& v, T lo, T hi) { return min(max(v, lo), hi); }
	template <class T> inline v3<T> clamp(const v3<T>& v, T lo, T hi) { return min(max(v, lo), hi); }
	template <class T> inline v4<T> clamp(const v4<T>& v, T lo, T hi) { return min(max(v, lo), hi); }

	template <class T> inline v2<T> clamp(const v2<T>& v, const v2<T>& lo, const v2<T>& hi) { return min(max(v, lo), hi); }
	template <class T> inline v3<T> clamp(const v3<T>& v, const v3<T>& lo, const v3<T>& hi) { return min(max(v, lo), hi); }
	template <class T> inline v4<T> clamp(const v4<T>& v, const v4<T>& lo, const v4<T>& hi) { return min(max(v, lo), hi); }

	template <class T> inline T     saturate(T v) { return clamp(v, T(0), T(1)); }
	template <class T> inline v2<T> saturate(const v2<T>& v) { return clamp(v, T(0), T(1)); }
	template <class T> inline v3<T> saturate(const v3<T>& v) { return clamp(v, T(0), T(1)); }
	template <class T> inline v4<T> saturate(const v4<T>& v) { return clamp(v, T(0), T(1)); }

	template <class T> inline v2<T> floor(const v2<T>& v) { return v2<T>(floor(v.x), floor(v.y)); }
	template <class T> inline v3<T> floor(const v3<T>& v) { return v3<T>(floor(v.x), floor(v.y), floor(v.z)); }
	template <class T> inline v4<T> floor(const v4<T>& v) { return v4<T>(floor(v.x), floor(v.y), floor(v.z), floor(v.w)); }

	template <class T> inline v2<T> ceil(const v2<T>& v) { return v2<T>(ceil(v.x), ceil(v.y)); }
	template <class T> inline v3<T> ceil(const v3<T>& v) { return v3<T>(ceil(v.x), ceil(v.y), ceil(v.z)); }
	template <class T> inline v4<T> ceil(const v4<T>& v) { return v4<T>(ceil(v.x), ceil(v.y), ceil(v.z), ceil(v.w)); }

	template <class T> inline v2<T> cos(const v2<T>& v) { return v2<T>(cos(v.x), cos(v.y)); }
	template <class T> inline v3<T> cos(const v3<T>& v) { return v3<T>(cos(v.x), cos(v.y), cos(v.z)); }
	template <class T> inline v4<T> cos(const v4<T>& v) { return v4<T>(cos(v.x), cos(v.y), cos(v.z), cos(v.w)); }

	template <class T> inline v2<T> sin(const v2<T>& v) { return v2<T>(sin(v.x), sin(v.y)); }
	template <class T> inline v3<T> sin(const v3<T>& v) { return v3<T>(sin(v.x), sin(v.y), sin(v.z)); }
	template <class T> inline v4<T> sin(const v4<T>& v) { return v4<T>(sin(v.x), sin(v.y), sin(v.z), sin(v.w)); }

	// lerp
	template <class T> inline T     lerp(T a, T b, float t) { return T(a + t * (b - a)); }
	template <class T> inline v2<T> lerp(const v2<T>& a, const v2<T>& b, float t) { return v2<T>(a) + t * v2<T>(b - a); }
	template <class T> inline v3<T> lerp(const v3<T>& a, const v3<T>& b, float t) { return v3<T>(a) + t * v3<T>(b - a); }
	template <class T> inline v4<T> lerp(const v4<T>& a, const v4<T>& b, float t) { return v4<T>(a) + t * v4<T>(b - a); }

	template <class T> T     spline(T a, T b, T c, T d, T t);
	template <class T> v2<T> spline(const v2<T>& a, const v2<T>& b, const v2<T>& c, const v2<T>& d, T t);
	template <class T> v3<T> spline(const v3<T>& a, const v3<T>& b, const v3<T>& c, const v3<T>& d, T t);
	template <class T> v4<T> spline(const v4<T>& a, const v4<T>& b, const v4<T>& c, const v4<T>& d, T t);

	template <class T> inline T angle(T a, T b) { return acos(clamp(a * b, T(-1), T(1))); }
	template <class T> inline T angle(const v2<T>& a, const v2<T>& b) { return acos(clamp(dot(a, b), T(-1), T(1))); }
	template <class T> inline T angle(const v3<T>& a, const v3<T>& b) { return acos(clamp(dot(a, b), T(-1), T(1))); }
	template <class T> inline T angle(const v4<T>& a, const v4<T>& b) { return acos(clamp(dot(a, b), T(-1), T(1))); }

	inline mat3::mat3() {}
	inline mat3::mat3(const float3& x, const float3& y, const float3& z)
	{
		f[0] = x.x; f[1] = x.y; f[2] = x.z;
		f[3] = y.x; f[4] = y.y; f[5] = y.z;
		f[6] = z.x; f[7] = z.y; f[8] = z.z;
	}
	inline mat3::mat3(float f0, float f1, float f2, float f3, float f4, float f5, float f6, float f7, float f8)
	{
		f[0] = f0; f[1] = f1; f[2] = f2;
		f[3] = f3; f[4] = f4; f[5] = f5;
		f[6] = f6; f[7] = f7; f[8] = f8;
	}

	//inline const float3& mat3::operator[](uint index) const { return *((float3*)f + index); }
	//inline float3& mat3::operator[](uint index) { return *((float3*)f + index); }

	inline mat4::mat4() {}
	inline mat4::mat4(const float4& x, const float4& y, const float4& z, const float4& w)
	{
		f[0] = x.x; f[1] = x.y; f[2] = x.z; f[3] = x.w;
		f[4] = y.x; f[5] = y.y; f[6] = y.z; f[7] = y.w;
		f[8] = z.x; f[9] = z.y; f[10] = z.z; f[11] = z.w;
		f[12] = w.x; f[13] = w.y; f[14] = w.z; f[15] = w.w;
	}
	inline mat4::mat4(float f0, float f1, float f2, float f3, float f4, float f5, float f6, float f7, float f8, float f9, float f10, float f11, float f12, float f13, float f14, float f15)
	{
		f[0] = f0;  f[1] = f1;  f[2] = f2;  f[3] = f3;
		f[4] = f4;  f[5] = f5;  f[6] = f6;  f[7] = f7;
		f[8] = f8;  f[9] = f9;  f[10] = f10; f[11] = f11;
		f[12] = f12; f[13] = f13; f[14] = f14; f[15] = f15;
	}

	//inline const float4& mat4::operator[](uint index) const { return *((float4*)f + index); }
	//inline float4& mat4::operator[](uint index) { return *((float4*)f + index); }

	inline bool mat4::operator==(const mat4& other) const
	{
		return f[0] == other.f[0] && f[1] == other.f[1] && f[2] == other.f[2] && f[3] == other.f[3]
			&& f[4] == other.f[4] && f[5] == other.f[5] && f[6] == other.f[6] && f[7] == other.f[7]
			&& f[8] == other.f[8] && f[9] == other.f[9] && f[10] == other.f[10] && f[11] == other.f[11]
			&& f[12] == other.f[12] && f[13] == other.f[13] && f[14] == other.f[14] && f[15] == other.f[15];
	}

	//inline bool mat4::operator!=(const mat4& other) const { return !(*this == other); }

	inline quat::quat() { }
	inline quat::quat(float v) : float4(v) { }
	inline quat::quat(float x, float y, float z, float w) : float4(x, y, z, w) { }
	inline quat::quat(const float3& euler_angles)
	{
		float3 c = cos(euler_angles * float(0.5));
		float3 s = sin(euler_angles * float(0.5));

		this->x = s.x * c.y * c.z - c.x * s.y * s.z;
		this->y = c.x * s.y * c.z + s.x * c.y * s.z;
		this->z = c.x * c.y * s.z - s.x * s.y * c.z;
		this->w = c.x * c.y * c.z + s.x * s.y * s.z;
	}

	export_ template <> inline float* value_ptr(mat4& m) { return &m[0][0]; }
	export_ template <> inline const float* value_ptr(const mat4& m) { return &m.f[0]; }
	export_ template <> inline float* value_ptr(quat& q) { return &q[0]; }

	inline bool operator<(const uvec2& lhs, const uvec2& rhs) { return lhs.x < rhs.x || (lhs.x == rhs.x && lhs.y < rhs.y); }
	inline bool operator<(const ivec2& lhs, const ivec2& rhs) { return lhs.x < rhs.x || (lhs.x == rhs.x && lhs.y < rhs.y); }

	export_ inline vec3 to_xz(const vec2& vec) { return{ vec.x, 0.f, vec.y }; }
	export_ inline vec2 to_xz(const vec3& vec) { return{ vec.x, vec.z }; }
	export_ inline ivec3 to_xz(const ivec2& vec) { return{ vec.x, 0, vec.y }; }
	export_ inline ivec2 to_xz(const ivec3& vec) { return{ vec.x, vec.z }; }

	export_ inline float& rect_w(vec4& rect) { return rect.z; }
	export_ inline float& rect_h(vec4& rect) { return rect.w; }

	export_ inline float rect_w(const vec4& rect) { return rect.z; }
	export_ inline float rect_h(const vec4& rect) { return rect.w; }

	export_ inline unsigned int& rect_w(uvec4& rect) { return rect.z; }
	export_ inline unsigned int& rect_h(uvec4& rect) { return rect.w; }

	export_ inline vec2 rect_offset(const vec4& rect) { return{ rect.x, rect.y }; }
	export_ inline vec2 rect_size(const vec4& rect) { return{ rect.z, rect.w }; }
	export_ inline vec2 rect_sum(const vec4& rect) { return vec2{ rect.x, rect.y } + vec2{ rect.z, rect.w }; }
	export_ inline vec2 rect_center(const vec4& rect) { return rect_offset(rect) + rect_size(rect) * 0.5f; }

	export_ inline vec3 to_vec3(const Colour& colour) { return { colour.m_r, colour.m_g, colour.m_b }; }
	export_ inline vec4 to_vec4(const Colour& colour) { return { colour.m_r, colour.m_g, colour.m_b, colour.m_a }; }
	export_ inline Colour to_colour(const vec3& vec) { return { vec.x, vec.y, vec.z }; }
	export_ inline Colour to_colour(const vec4& vec) { return { vec.x, vec.y, vec.z, vec.w }; }

	export_ MUD_MATH_EXPORT uint32_t pack4(const vec4& vec);
	export_ MUD_MATH_EXPORT uint32_t pack3(const vec3& vec);
	export_ MUD_MATH_EXPORT vec3 unpack3(uint32_t vec);
	export_ MUD_MATH_EXPORT vec4 unpack4(uint32_t vec);

	export_ inline void flatten(vec3& vector)
	{
		for(vec3::length_type i = 0; i < 3; ++i)
			if(fabs(vector[i]) < 0.0000001f)
				vector[i] = 0.f;
	}

	export_ inline void flatten(float& f)
	{
		if(fabs(f) < 0.0000001)
			f = 0.f;
	}

#ifndef MUD_META_GENERATOR
	export_ template MUD_MATH_EXPORT func_ vec3 add<vec3>(vec3 a, vec3 b);
	export_ template MUD_MATH_EXPORT func_ vec3 subtract<vec3>(vec3 a, vec3 b);
	export_ template MUD_MATH_EXPORT func_ vec3 multiply<vec3>(vec3 a, vec3 b);
	export_ template MUD_MATH_EXPORT func_ vec3 divide<vec3>(vec3 a, vec3 b);
#else
	template <> func_ vec3 add<vec3>(vec3 a, vec3 b);
	template <> func_ vec3 subtract<vec3>(vec3 a, vec3 b);
	template <> func_ vec3 multiply<vec3>(vec3 a, vec3 b);
	template <> func_ vec3 divide<vec3>(vec3 a, vec3 b);
#endif

	export_ MUD_MATH_EXPORT quat operator*(const quat& a, const quat& b);
	//export_ MUD_MATH_EXPORT quat operator/(const quat& a, const quat& b);
	export_ MUD_MATH_EXPORT quat operator+(const quat& a, const quat& b);
	export_ MUD_MATH_EXPORT quat operator-(const quat& a, const quat& b);

	export_ MUD_MATH_EXPORT quat operator*(const quat& a, float s);
	export_ MUD_MATH_EXPORT quat operator/(const quat& a, float s);
	export_ MUD_MATH_EXPORT quat operator*(float s, const quat& a);
	export_ MUD_MATH_EXPORT quat operator/(float s, const quat& a);

	export_ MUD_MATH_EXPORT quat operator+(const quat& v);
	export_ MUD_MATH_EXPORT quat operator-(const quat& v);

	// transform position
	export_ MUD_MATH_EXPORT float3 operator*(const quat& q, const float3& v);
	export_ MUD_MATH_EXPORT float4 operator*(const quat& q, const float4& v);

	export_ MUD_MATH_EXPORT quat conjugate(const quat& q);
	export_ MUD_MATH_EXPORT quat inverse(const quat& q);
	export_ MUD_MATH_EXPORT quat negate(const quat& q);

	export_ MUD_MATH_EXPORT float dot(const quat& a, const quat& b);
	export_ MUD_MATH_EXPORT quat normalize(const quat& q);

	export_ MUD_MATH_EXPORT quat lerp(const quat& a, const quat& b, float t);
	export_ MUD_MATH_EXPORT quat slerp(const quat& a, const quat& b, float t);

	//quat qZero();
	//quat qIdentity();
	//float qNorm(const quat& q);
	//quat qScale(const quat& q, float scale);
	//quat qMultiply(const quat& a, const quat& b);
	//quat qMultiplyPure(const quat& a, const float3& b);
	//quat qRotationBetween(float3 v0, float3 v1);

	export_ inline float3 rotate(const quat& q, const float3& v) { return q * v; }

	export_ inline quat axis_angle(const float3& v, float a)
	{
		const float s = sin(a * float(0.5));
		return quat(v.x * s, v.y * s, v.z * s, cos(a * float(0.5)));
	}

	export_ inline quat angle_axis(float a, const float3& v) { return axis_angle(v, a); }
	export_ inline quat rotate(const quat& q, float a, const float3& v) { return q * angle_axis(a, v); }
	export_ inline quat rotate(const quat& q, const float3& v, float a) { return q * axis_angle(v, a); }

	export_ inline float2 rotate(const float2& v, float a)
	{
		const float c = cos(a);
		const float s = sin(a);
		return float2(v.x * c - v.y * s, v.x * s + v.y * c);
	}

	export_ MUD_MATH_EXPORT float oriented_angle(const float3& a, const float3& b, const float3& ref);
	export_ MUD_MATH_EXPORT float oriented_angle(const float2& a, const float2& b);
	export_ inline float oriented_angle_2d(const float2& a, const float2& b) { return oriented_angle(a, b); }

	export_ MUD_MATH_EXPORT mat4 inverse(const mat4& m);
	export_ MUD_MATH_EXPORT mat4 transpose(const mat4& m);
	export_ MUD_MATH_EXPORT mat4 operator*(const mat4& m0, const mat4& m1);
	export_ MUD_MATH_EXPORT float4 operator*(const mat4& m, const float4& v);

	export_ inline vec3 rotate(const vec3& v, float angle, const vec3& axis) { return angle_axis(angle, axis) * v; }
	export_ inline vec3 rotate(const vec3& v, const vec3& axis, float angle) { return angle_axis(angle, axis) * v; }

	export_ MUD_MATH_EXPORT func_ quat look_dir(const vec3& direction, const vec3& forward = -Z3);
	export_ MUD_MATH_EXPORT func_ quat look_at(const vec3& eye, const vec3& target, const vec3& forward = -Z3);

	export_ MUD_MATH_EXPORT Axis nearest_axis(const vec3& direction);

	export_ MUD_MATH_EXPORT float float_shortest_angle(float angle1, float angle2);
	export_ MUD_MATH_EXPORT float trigo_angle(const vec3& vec1, const vec3& vec2);
	export_ MUD_MATH_EXPORT float shortest_angle(const vec3& vec1, const vec3& vec2);

	export_ MUD_MATH_EXPORT void orthonormalize(const mat4& transform, vec3& x, vec3& y, vec3& z);
	export_ MUD_MATH_EXPORT mat4 orthonormalize(const mat4& transform);
	export_ MUD_MATH_EXPORT mat4 bias_mat();
	export_ MUD_MATH_EXPORT mat4 bias_mat_bgfx(bool origin_bottom_left, bool homogeneous_depth);
	export_ MUD_MATH_EXPORT mat4 rect_mat(vec4 rect);

	export_ MUD_MATH_EXPORT mat4 abs(const mat4& mat);

	export_ inline vec3 mulp(const mat4& mat, const vec3& p) { return vec3(mat * vec4(p, 1.f)); }
	export_ inline vec3 mult(const mat4& mat, const vec3& n) { return vec3(mat * vec4(n, 0.f)); }
	export_ inline vec3 muln(const mat4& mat, const vec3& n) { return normalize(vec3(mat * vec4(n, 0.f))); }
	//export_ inline vec3 muln(const mat4& mat, const vec3& n) { return vec3(normalize(mat * vec4(n, 0.f))); }
	export_ inline vec4 mult(const mat4& mat, const vec4& t) { return vec4(vec3(mat * vec4(vec3(t), 0.f)), t.w); }


#if 0 // not implemented
	// For float->float16 conversion
	half float_to_half(float f);
	float half_to_float(const half& h);

	// Uniform distribution mapping functions
	float3 UniformUVToSphere(const float2& uv, float r);
	float3 UniformUVToHemisphere(const float2& uv);
	float3 UniformUVToHemisphere(const float2& uv, float max_theta);
	float3 UniformUVToHemisphereCosine(const float2& uv);
	float3 UniformUVToHemisphereCosine(const float2& uv, float max_theta);

	// Signed distance functions
	// TODO: Move for use in HLSL
	float sdSphere(const float3& p, float r);
	float sdCylinder(const float3& p, const float2& h);
	float sdBox(const float3& p, const float3& b);
	float sdCapsule(const float3& p, const float3& a, const float3& b, float r);
	float sdEllipsoid(const float3& p, const float3& r);
	float sdUnion(float a, float b);
	float sdSubtract(float a, float b0);
	float sdIntersect(float a, float b);
	float sdSmoothUnion(float a, float b, float k);

//
// Vector conversion functions
//
float3 double3_to_float3(const double3& v);
double3 float3_to_double3(const float3& v);


/*$pycgen
	code = """
	T coserp_t(T t);
	T2 coserp_t(const T2& t);
	T3 coserp_t(const T3& t);
	T4 coserp_t(const T4& t);
	"""
	EmitRepl(code, "T:float")
*/
//$pycgen-begin
	float coserp_t(float t);
	float2 coserp_t(const float2& t);
	float3 coserp_t(const float3& t);
	float4 coserp_t(const float4& t);
//$pycgen-end


/*$pycgen
	code = """
	T cuberp_t(T t);
	T2 cuberp_t(const T2& t);
	T3 cuberp_t(const T3& t);
	T4 cuberp_t(const T4& t);
	"""
	EmitRepl(code, "T:float")
*/
//$pycgen-begin
	float cuberp_t(float t);
	float2 cuberp_t(const float2& t);
	float3 cuberp_t(const float3& t);
	float4 cuberp_t(const float4& t);
//$pycgen-end


/*$pycgen
	code = """
	T quinterp_t(T t);
	T2 quinterp_t(const T2& t);
	T3 quinterp_t(const T3& t);
	T4 quinterp_t(const T4& t);
	"""
	EmitRepl(code, "T:float")
*/
//$pycgen-begin
	float quinterp_t(float t);
	float2 quinterp_t(const float2& t);
	float3 quinterp_t(const float3& t);
	float4 quinterp_t(const float4& t);
//$pycgen-end


	//
	// Single precision dual quaternion
	//
	export_ struct refl_ struct_ array_ dualquat
	{
		quat r;
		quat d;
	};


	//
	// This is an affine frame with origin and basis as rotation operator
	//
	export_ struct refl_ struct_ array_ frame
	{
		quat rotation;
		float3 position;
	};
	export_ struct refl_ struct_ array_ framed
	{
		quat rotation;
		double3 position;
	};

	//
	// Scalar math
	//
	float2 SinCos(float angle);
	float DegreesToRadians(float degrees);
	double DegreesToRadians(double degrees);
	float RadiansToDegrees(float radians);
	double RadiansToDegrees(double radians);
	uint Factorial(uint v);


	//
	// Procedural operations on vectors
	//
	float3	vSlerp(const float3& a, const float3& b, float t);
	float3 	vPerpendicular(const float3& v);
	double3	vPerpendicular(const double3& v);
	bool 	vEquals(const int3& a, const int3& b, float epsilon = 0);
	float3	vProjectOnto(const float3& a, const float3& b);
	double3	vMapCubeToSphere(const double3& v);
	double3	vMapNonUnitCubeToSphere(const double3& v, double extents);
	float3	vFraction(const float3& v);
	double3	vFraction(const double3& v);
	void	vOrthogonalise(const float3& a, float3& b, float3& c);


	//
	// Matrix generation functions
	//
	mat3 m3Zero();
	mat4 m4Zero();
	mat3 m3Identity();
	mat4 m4Identity();
	mat3 m3RotateX(float angle);
	mat4 m4RotateX(float angle);
	mat3 m3RotateY(float angle);
	mat4 m4RotateY(float angle);
	mat3 m3RotateZ(float angle);
	mat4 m4RotateZ(float angle);
	mat3 m3Scale(float x, float y, float z);
	mat3 m3Scale(const float3& s);
	mat3 m3Direction(const float3& z);
	mat3 m3Direction(const float3& z, float3 y);
	mat4 m4Translate(float x, float y, float z);
	mat4 m4Translate(const float3& v);
	mat4 m4PerspectiveFovLH(float fov_y, float aspect_ratio, float near_z, float far_z);
	mat4 m4PerspectiveFovOffCenterLH(float fov_y, float aspect_ratio, const float4& rect, float near_z, float far_z);
	mat3 m3Up(const double3& y);
	mat3d m3dZero();
	mat3d m3dIdentity();


	//
	// Matrix conversion functions
	//
	mat3 mat4_to_mat3(const mat4& m4);
	mat4 mat3_to_mat4(const mat3& m3);
	mat3 mat3d_to_mat3(const mat3d& m3d);
	mat3d mat3_to_mat3d(const mat3& m3);


	//
	// Procedural operations on matrices
	// Disabled in HLSL for now as it's easy to mess up during porting
	//
	mat3 m3Multiply(const mat3& a, const mat3& b);
	mat4 m4Multiply(const mat4& a, const mat4& b);
	mat3d m3dMultiply(const mat3d& a, const mat3d& b);
	float m3Determinant(const mat3& m);
	float m4Determinant(const mat4& m);
	bool m3Inverse(const mat3& m, mat3& inv_m);
	bool m4Inverse(const mat4& m, mat4& inv_m);
	mat3 m3Transpose(const mat3& m);
	mat4 m4Transpose(const mat4& m);
	mat3 m3Orthogonalise(const mat3& m, int axis);
	mat3 m3Orthonormalise(const mat3& m, int axis);
	float3 m3Transform(const mat3& m, const float3& v);
	double3 m3Transform(const mat3& m, const double3& v);
	float4 m4Transform(const mat4& m, const float4& v);
	float3 m3TransformTransposed(const mat3& m, const float3& v);
	double3 m3TransformTransposed(const mat3& m, const double3& v);
	float3 m4TransformPos(const mat4& m, const float3& v);
	double3 m4TransformPos(const mat4& m, const double3& v);
	float3 m4TransformDir(const mat4& m, const float3& v);
	bool m3ToEulerXYZ(const mat3& m, float3& angles);
	bool m3ToEulerYXZ(const mat3& m, float3& angles);
	bool m3ToEulerZXY(const mat3& m, float3& angles);
	bool m3ToEulerZYX(const mat3& m, float3& angles);
	void m3dDiagonalise(const mat3d& m, mat3d& Q, mat3d& D);




	//
	// Quaternion conversion functions
	//
	mat3 quat_to_mat3(const quat& q);
	mat4 quat_to_mat4(const quat& q);
	quat mat3_to_quat(const mat3& m);


	//
	// Dual quaternion generation functions
	//
	dualquat dqIdentity();


	//
	// Frame functions
	//
	frame fIdentity();
	framed fdIdentity();
	frame fPosition(const float3& position);
	framed fdPosition(const double3& position);
	frame fPositionRotation(const float3& position, const quat& rotation);
	framed fdPositionRotation(const double3& position, const quat& rotation);
	frame fInverse(const frame& f);
	framed fInverse(const framed& f);
	frame fMultiply(const frame& a, const frame& b);
	framed fMultiply(const framed& a, const framed& b);
	frame fLerp(const frame& a, const frame& b, float t);
	float3 fTransformPos(const frame& f, const float3& v);
	double3 fTransformPos(const framed& f, const double3& v);


	//
	// Frame conversion functions
	//
	frame framed_to_frame(const framed& f);

	//
	// Rigid transform with position stored in double precision
	//
	export_ struct refl_ struct_ array_ transform
	{
		double3 position;
		mat3 rotation;
		float3 scale;
	};


	export_ struct refl_ struct_ array_ boxi
	{
		int3 min;
		int3 max;
	};


	//
	// A plane in 3 dimensions, composed of a normal and distance along the normal from the origin
	//
	export_ struct refl_ struct_ array_ planef
	{
		planef() { }
		planef(float x, float y, float z, float d)
			: n(x, y, z), d(d)
		{
		}
		planef(const float3& n, float d)
			: n(n), d(d)
		{
		}
		float3 n;
		float d;
	};
	export_ struct refl_ struct_ array_ planed
	{
		planed() { }
		planed(double x, double y, double z, double d)
			: n(x, y, z), d(d)
		{
		}
		planed(const double3& n, double d)
			: n(n), d(d)
		{
		}
		double3 n;
		double d;
	};


	//
	// A camera view volume bounded by 6 planes
	//
	export_ struct refl_ struct_ array_ frustumf
	{
		planef planes[6];
	};
	export_ struct refl_ struct_ array_ frustumd
	{
		planed planes[6];
	};


	
	//
	// Shared location for voxel type that all subsystems can reference
	// TODO: This is probably not the ideal place for this but it's better than in
	//       the VDB or Transvoxel libraries.
	//
	export_ struct refl_ struct_ array_ Voxel
	{
		// Fixed-point compressed distance to zero-surface
		i16 distance;

		// Material ID for this voxel
		u16 material_id;
	};


	//
	// Mutually exclusive flags for storing normal voxels in voxel grids
	//
	export_ enum refl_ struct_ array_ VoxelGridFlags
	{
		VoxelGridFlags_NoNormals = 0,
		VoxelGridFlags_StoreNormals = 1,
	};


	//
	// Describes the layout of a collection of voxels and cells constructed out of them.
	// There are equal number of cells/voxels on each axis.
	// The number of voxels is determined by the number of cells and whether an extra padding
	// layer of voxels is added round the outside for normal calculation.
	//
	export_ struct refl_ struct_ array_ VoxelGrid
	{
		VoxelGrid();
		VoxelGrid(i32 nb_cells_axis, VoxelGridFlags flags);

		// Cell count
		i32 nb_cells_axis;
		i32 nb_cells_axis_2;
		i32 nb_cells;
		i32 max_cell_index;

		// Flags about normal storage
		u32 stores_normals;

		// Voxel count - 1 extra voxel to cover last cell corner, 2 extra voxels for normal sampling either side
		i32 nb_voxels_axis;
		i32 nb_voxels_axis_2;
		i32 nb_voxels;
	};



	//
	// A unique node ID within a grid hierarchy stored as a 96-bit value.
	// Node x,y,z and level integer locations are bit-packed into this.
	//
	export_ struct refl_ struct_ array_ NodeID
	{
		NodeID();
		NodeID(const int3& node_index, int level_index);

		// Recalculate 3D index from the ID
		int3 Index() const;

		// Extract level index
		u32 Level() const;

		// Calculate a well-distributed hash from the ID
		u32 Hash() const;

		bool operator==(const NodeID& rhs) const;
		bool operator!=(const NodeID& rhs) const;

		u32 v[3];
	};


	struct BoxIterator
	{
		BoxIterator(const boxi& range)
			: range(range)
		{
			// Clamp any negative deltas to zero before calculating volume
			// Also add 1 to make the max inclusive
			delta = max(range.max - range.min + 1, 0);

			slice_size = delta.x * delta.y;
			size = slice_size * delta.z;
		}
		
		void GetPos(int i, int3& pos) const
		{
			// Calculate position within the range delta
			pos.z = i / slice_size;
			i -= pos.z * slice_size;
			pos.y = i / delta.x;
			pos.x = i - pos.y * delta.x;

			// Offset that to get the actual position
			pos.x += range.min.x;
			pos.y += range.min.y;
			pos.z += range.min.z;
		}

		const boxi& range;
		int3 delta;
		i32 slice_size;
		i32 size;
	};


	//
	// Transform functions
	//
	transform tZero();
	transform tIdentity();
	transform tPosition(const double3& position);
	transform tPositionRotation(const double3& position, const mat3& rotation);
	mat4 tToMat4(const transform& t);
	mat4 tToMat4Rigid(const transform& t);
	double3 tTransformPos(const transform& t, const double3& v);
	transform tMultiplyRigid(const transform& a, const transform& b);


	//
	// Box functions
	//
	boxi biScale(const boxi& box, i32 scale);
	boxi biInvScale(const boxi& box, i32 inv_scale);
	boxi biUnion(const boxi& a, const boxi& b);
	boxi biIntersection(const boxi& a, const boxi& b);
	bool biIntersects(const boxi& a, const boxi& b);
	i32 biVolume(const boxi& b);


	//
	// Plane generation functions
	//
	planef pPositionNormal(const float3& position, const float3& normal);
	planed pPositionNormal(const double3& position, const double3& normal);
	planef pTriangle(const float3& a, const float3& b, const float3& c);
	planed pTriangle(const double3& a, const double3& b, const double3& c);


	//
	// Procedural operations with planes
	//
	float pDistanceFrom(const planef& p, const float3& v);
	double pDistanceFrom(const planed& p, const double3& v);
	float pDistanceFrom(const planef& p, const float3& pos, const float3& extents);
	double pDistanceFrom(const planed& p, const double3& pos, const double3& extents);
	float3 pProjectVector(const planef& p, const float3& v);
	double3 pProjectVector(const planed& p, const double3& v);
	planef pNormalise(const planef& p);
	planed pNormalise(const planed& p);
	planef pTransform(const planef& p, const mat4& m);
	planed pTransform(const planed& p, const mat4& m);
	planef pTranslate(const planef& p, const float3& v);
	planed pTranslate(const planed& p, const double3& v);
	float3 pIntersectionPoint(const planef& a, const planef& b, const planef& c);
	double3 pIntersectionPoint(const planed& a, const planed& b, const planed& c);
	bool pIntersectionPoint(const planef& a, const planef& b, const planef& c, float3& Q);
	bool pIntersectionPoint(const planed& a, const planed& b, const planed& c, double3& Q);
	bool pIntersectionLine(const planef& a, const planef& b, float3& Q, float3& V);
	bool pIntersectionLine(const planed& a, const planed& b, double3& Q, double3& V);


	// Frustum functions
	frustumf frustumfMake(const mat4& m);
	frustumd frustumdMake(const mat4& m);
	frustumf frustumTransform(const frustumf& f, const mat4& m);
	frustumd frustumTransform(const frustumd& f, const mat4& m);
	frustumf frustumTranslate(const frustumf& f, const float3& v);
	frustumd frustumTranslate(const frustumd& f, const double3& v);
	bool frustumContains(const frustumf& f, const float3& pos, const float3& extents);
	bool frustumContains(const frustumd& f, const double3& pos, const double3& extents);
#endif
}

#if 0 // MUD_NOT_IMPLEMENTED
#include <stl/vector.h>

namespace mud
{
	//
	// Some utility functions
	//
	float QuadAreaApproximateSphereProjectionSize(const float3& pos, float radius, const mat4& w2c, const mat4& c2s, float near_z);
	double SphereAngularProjectionOntoPosition(const double3& sphere_pos, double radius, const double3& position);
	void MakeHammersleyPoints(u32 nb_points, vector<float4>& points);
	i16 Compress_DoubleToSigned16(double d, double extents);
	double Decompress_Signed16ToDouble(i16 d, double extents);
}
#endif

namespace mud
{
	inline quat lerp(const quat& a, const quat& b, float c)
	{
		return slerp(a, b, c);
	}

	export_ template <class T>
	inline T catmull_rom(const T& p0, const T& p1, const T& p2, const T& p3, float t)
	{
		float t2 = t * t;
		float t3 = t2 * t;

		return 0.5f * ((2.0f * p1) + (-p0 + p2) * t + (2.0f * p0 - 5.0f * p1 + 4.0f * p2 - p3) * t2 + (-p0 + 3.0f * p1 - 3.0f * p2 + p3) * t3);
	}

	export_ template <class T>
	inline T bezier(T start, T control_1, T control_2, T end, float t)
	{
		/* Formula from Wikipedia article on Bezier curves.*/
		float omt = (1.f - t);
		float omt2 = omt * omt;
		float omt3 = omt2 * omt;
		float t2 = t * t;
		float t3 = t2 * t;

		return start * omt3 + control_1 * omt2 * t * 3.f + control_2 * omt * t2 * 3.f + end * t3;
	}

	export_ template <class T>
	inline T cubic_interpolate(const T& a, const T& b, const T& pre_a, const T& post_b, float t)
	{
		float t2 = t * t;
		float t3 = t2 * t;

		return 0.5f * ((2.f * a) + (-pre_a + b) * t + (2.f * pre_a - 5.f* a + 4.f * b - post_b) * t2 + (-pre_a + 3.f * a - 3.f * b + post_b) * t3);
	}

	export_ template <>
	inline quat catmull_rom(const quat& p0, const quat& p1, const quat& p2, const quat& p3, float c)
	{
		UNUSED(p0); UNUSED(p3);
		return slerp(p1, p2, c);
	}

	export_ template <>
	inline quat bezier(quat start, quat control_1, quat control_2, quat end, float t)
	{
		UNUSED(control_1); UNUSED(control_2);
		return slerp(start, end, t);
	}

	inline Colour lerp(const Colour& a, const Colour& b, float c)
	{
		vec4 va = to_vec4(a);
		vec4 vb = to_vec4(b);
		return to_colour(va + (vb - va) * c);
	}

	export_ MUD_MATH_EXPORT void interpolate(Ref result, Ref a, Ref b, float t);
	export_ inline void interpolate_cubic(Ref result, Ref a, Ref b, Ref d, Ref e, float t) { UNUSED(e); UNUSED(d); return interpolate(result, a, b, t); }
	//export_ inline Var interpolate_cubic(Ref a, Ref b, Ref d, Ref e, float t) { UNUSED(e); UNUSED(d); return interpolate(a, b, t); }
}

namespace mud
{
	export_ enum class refl_ TrackMode : unsigned int
	{
		Constant,
		ConstantRandom,
		Curve,
		CurveRandom
	};

	export_ template <class T>
	struct refl_ struct_ ValueCurve
	{
		constr_ ValueCurve();
		constr_ ValueCurve(vector<T> keys);
		~ValueCurve();

		T sample_curve(float t);

		attr_ vector<T> m_keys;
	};

	export_ extern template struct refl_ ValueCurve<vec3>;
	export_ extern template struct refl_ ValueCurve<quat>;
	export_ extern template struct refl_ ValueCurve<float>;
	export_ extern template struct refl_ ValueCurve<uint32_t>;
	export_ extern template struct refl_ ValueCurve<Colour>;

	template <class T>
	struct One { static T value() { return T(1); } };

	template <> struct One<vec3> { static vec3 value() { return Unit3; } };
	template <> struct One<quat> { static quat value() { return ZeroQuat; } };
	template <> struct One<Colour> { static Colour value() { return Colour(1.f); } };

	export_ template <class T>
	struct refl_ struct_ ValueTrack
	{
		constr_ ValueTrack();
		constr_ ValueTrack(TrackMode mode, ValueCurve<T> curve, ValueCurve<T> min_curve, ValueCurve<T> max_curve);
		ValueTrack(T value);
		ValueTrack(T min, T max);
		ValueTrack(vector<T> values);
		ValueTrack(vector<T> min_values, vector<T> max_values);
		~ValueTrack();

		void set_mode(TrackMode mode);

		T sample(float t, float seed = 0.f);

		attr_ TrackMode m_mode;
		attr_ T m_value = One<T>::value();
		attr_ T m_min = One<T>::value();
		attr_ T m_max = One<T>::value();
		attr_ ValueCurve<T> m_curve;
		attr_ ValueCurve<T> m_min_curve;
		attr_ ValueCurve<T> m_max_curve;
	};

	export_ extern template struct refl_ ValueTrack<vec3>;
	export_ extern template struct refl_ ValueTrack<quat>;
	export_ extern template struct refl_ ValueTrack<float>;
	export_ extern template struct refl_ ValueTrack<uint32_t>;
	export_ extern template struct refl_ ValueTrack<Colour>;
}


#include <stl/vector.h>

#ifndef MUD_CPP_20
#include <stdint.h>
#endif

namespace mud
{
	export_ class Grided3
	{
	public:
		struct Dim
		{
		public:
			Dim() {}
			Dim(int period, size_t limit, int increment, size_t modulo, size_t divide)
				: m_period(period), m_limit(limit), m_increment(increment), m_modulo(modulo), m_divide(divide)
			{}

			size_t dim_index(size_t index) { return index % m_modulo / m_divide; }

			bool has_neighbour(size_t index) { return dim_index(index) != m_limit; }
			size_t neighbour_mod(size_t index) { return dim_index(index) == m_limit ? index + m_increment - m_period : index + m_increment; }
			size_t neighbour(size_t index) { return index + m_increment; }

		protected:
			int m_period;
			size_t m_limit;
			int m_increment;
			size_t m_modulo;
			size_t m_divide;
		};
	};

	export_ template <class T_Array>
	class Grided : public T_Array, public Grided3
	{
	public:
		using T = typename T_Array::value_type;

	public:
		Grided(size_t x, size_t y, size_t z)
			: T_Array(x*y*z), m_x(x), m_y(y), m_z(z), m_sq(x*y)
		{
			this->reset_dims();
		}

		Grided(size_t x, size_t y, size_t z, const T& val)
			: T_Array(x*y*z, val), m_x(x), m_y(y), m_z(z), m_sq(x*y)
		{
			this->reset_dims();
		}

		Grided(size_t s)
			: Grided(s, s, s)
		{}

		Grided()
			: Grided(0, 0, 0)
		{}

		Dim& dim(SignedAxis axis) { return m_dims[size_t(axis)]; }

		void reset_dims()
		{
			dim(SignedAxis::PlusX)  = {  int(m_x), m_x - 1, +1, m_x, 1 };
			dim(SignedAxis::MinusX) = { -int(m_x), 0, -1, m_x, 1 };
			dim(SignedAxis::PlusY)  = {  int(m_x*m_y), m_y - 1, +int(m_x), m_sq, m_x };
			dim(SignedAxis::MinusX) = { -int(m_x*m_y), 0, -int(m_x), m_sq, m_x };
			dim(SignedAxis::PlusZ)  = {  int(m_x*m_y*m_z), m_z - 1, +int(m_sq), SIZE_MAX, m_sq };
			dim(SignedAxis::MinusZ) = { -int(m_x*m_y*m_z), 0, -int(m_sq), SIZE_MAX, m_sq };
		}

		void clear(T val)
		{
			for(size_t i = 0; i < this->size(); ++i)
				(*this)[i] = val;
		}

		void reset(size_t x, size_t y, size_t z)
		{
			m_x = x; m_y = y; m_z = z; m_sq = x*y;
			this->reset_dims();
			this->resize(x*y*z);
		}
		
		void reset(size_t x, size_t y, size_t z, T val)
		{
			reset(x, y, z);
			clear(val);
		}

		inline T& at(size_t i) { return T_Array::operator[](i); }
		inline const T& at(size_t i) const { return T_Array::operator[](i); }

		inline T& at(size_t x, size_t y, size_t z = 0) { return at(x + y*m_x + z*m_sq); }
		inline const T& at(size_t x, size_t y, size_t z = 0) const { return at(x + y*m_x + z*m_sq); }

		inline T* safe_at(size_t x, size_t y, size_t z) { if(x > m_x || y > m_y || z > m_z) return nullptr; else return &at(x, y, z); }
		
		inline size_t index_at(size_t x, size_t y, size_t z) { return x + y*m_x + z*m_sq; }

		inline size_t x(size_t index) { return index % m_x; }
		inline size_t y(size_t index) { return index % (m_x*m_y) / m_x; }
		inline size_t z(size_t index) { return index / (m_x*m_y); }

		bool border(size_t index, Side direction) { return !m_dims[size_t(direction)].has_neighbour(index); }

		size_t neighbour_mod(size_t index, Side direction) { return m_dims[size_t(direction)].neighbour_mod(index); }
		size_t neighbour(size_t index, Side direction) { return m_dims[size_t(direction)].neighbour(index); }

		T& neighbour_item(size_t index, Side direction) { return at(neighbour(index, direction)); }

		T* safe_neighbour(size_t index, Side direction) { if(!border(index, direction)) return &neighbour_item(index, direction); return nullptr; }

		template <class T_Visitor>
		bool visit_near_dist(size_t x, size_t y, size_t z, size_t d, T_Visitor callback)
		{
			size_t xMin = x > d ? x - d : 0;
			size_t yMin = y > d ? y - d : 0;
			size_t xMax = x + d + 1 > m_x ? m_x : x + d + 1;
			size_t yMax = y + d + 1 > m_y ? m_y : y + d + 1;

			size_t dsquare = d * d;

			for(size_t i = xMin; i < xMax; ++i)
				for(size_t j = yMin; j < yMax; ++j)
					if(!(i == x && j == y))
						if((x - i)*(x - i) + (y - j)*(y - j) <= dsquare)
							if(!callback(this->at(i, j, z)))
								return false;
			return true;
		}

		template <class T_Visitor>
		bool visit_near_2d(size_t x, size_t y, size_t z, size_t d, T_Visitor callback)
		{
			size_t xMin = x > d ? x - d : 0;
			size_t yMin = y > d ? y - d : 0;
			size_t xMax = x + d + 1 > m_x ? m_x : x + d + 1;
			size_t yMax = y + d + 1 > m_y ? m_y : y + d + 1;

			//size_t dsquare = d*d;
			//if(sq(x - i) + sq(y - j) > dsquare)
			//	continue;

			for(size_t i = xMin; i < xMax; ++i)
				for(size_t j = yMin; j < yMax; ++j)
					if(!(i == x && j == y))
						if(!callback(this->at(i, j, z)))
							return false;
			return true;
		}

		template <class T_Visitor>
		bool visit_near(size_t x, size_t y, size_t z, size_t d, T_Visitor callback)
		{
			size_t xMin = x > d ? x - d : 0;
			size_t yMin = y > d ? y - d : 0;
			size_t zMin = z > d ? z - d : 0;
			size_t xMax = x + d + 1 > m_x ? m_x : x + d + 1;
			size_t yMax = y + d + 1 > m_y ? m_y : y + d + 1;
			size_t zMax = z + d + 1 > m_z ? m_z : z + d + 1;

			for(size_t i = xMin; i < xMax; ++i)
				for(size_t j = yMin; j < yMax; ++j)
					for(size_t k = zMin; k < zMax; ++k)
						if(!(i == x && j == y && k == z))
							if(!callback(this->at(i, j, k)))
								return false;
			return true;
		}

		template <class T_Visitor>
		bool visit_near_dist(size_t index, size_t dist, T_Visitor callback)
		{
			return this->visit_near_dist(this->x(index), this->y(index), this->z(index), dist, callback);
		}

		template <class T_Visitor>
		bool visit_near_2d(size_t index, size_t dist, T_Visitor callback)
		{
			return this->visit_near_2d(this->x(index), this->y(index), this->z(index), dist, callback);
		}

		template <class T_Visitor>
		bool visit_near(size_t index, size_t dist, T_Visitor callback)
		{
			return this->visit_near(this->x(index), this->y(index), this->z(index), dist, callback);
		}

		vector<T*> neighbours(size_t index, size_t dist)
		{
			vector<T*> result;
			this->visit_near(index, dist, [&](T& obj){ result.push_back(&obj); return true; });
			return result;
		}

		vector<T*> neighbours_2d(size_t index, size_t dist)
		{
			vector<T*> result;
			this->visit_near_2d(index, dist, [&](T& obj){ result.push_back(&obj); return true; });
			return result;
		}

	public:
		size_t m_x, m_y, m_z;
		size_t m_sq;

		//enum_array<Side, Dim> m_dims;
		Dim m_dims[6] = {};
	};

	export_ template <class T_Element>
	struct refl_ struct_ Grid : public Grided<vector<T_Element>>
	{
		using Grided<vector<T_Element>>::Grided;
	};


	export_ template <class T_Element>
	struct refl_ struct_ array3d : public vector<T_Element>
	{
	public:
		typedef T_Element T;

	public:
		array3d(size_t x, size_t y, size_t z)
			: vector<T_Element>(x*y*z), m_x(x), m_y(y), m_z(z)
		{}

		array3d(size_t x, size_t y, size_t z, const T& val)
			: vector<T_Element>(x*y*z, val), m_x(x), m_y(y), m_z(z)
		{}

		array3d(size_t s)
			: array3d(s, s, s)
		{}

		array3d()
			: array3d(0, 0, 0)
		{}

		void clear(T val)
		{
			for(size_t i = 0; i < this->size(); ++i)
				(*this)[i] = val;
		}

		void reset(size_t x, size_t y, size_t z)
		{
			m_x = x; m_y = y; m_z = z;
			this->resize(x*y*z);
		}

		void reset(size_t x, size_t y, size_t z, T val)
		{
			reset(x, y, z);
			clear(val);
		}

		inline T& at(size_t x, size_t y, size_t z = 0) { return vector<T_Element>::operator[](x + y*m_x + z*m_x*m_y); }
		inline const T& at(size_t x, size_t y, size_t z = 0) const { return vector<T_Element>::operator[](x + y*m_x + z*m_x*m_y); }
		inline T* safeAt(size_t x, size_t y, size_t z) { if(x > m_x || y > m_y || z > m_z) return nullptr; else return &at(x, y, z); }

		inline size_t indexAt(size_t x, size_t y, size_t z) { return x + y*m_x + z*m_x*m_y; }

		inline size_t x(size_t index) { return index % m_x; }
		inline size_t y(size_t index) { return index % (m_x*m_y) / m_x; }
		inline size_t z(size_t index) { return index / (m_x*m_y); }

	public:
		size_t m_x, m_y, m_z;
	};

	export_ MUD_MATH_EXPORT func_ void grid(const uvec3& size, vector<uvec3>& output_coords);
	export_ MUD_MATH_EXPORT func_ vec3 grid_center(const uvec3& coord, const vec3& cell_size);

	export_ MUD_MATH_EXPORT func_ void index_list(uint32_t size, vector<uint32_t>& output_indices);
}


#include <stl/string.h>

namespace mud
{
	export_ using cstring = const char*;

	export_ struct refl_ MUD_MATH_EXPORT Image
	{
	public:
		Image(const string& name = "", const string& path = "", const uvec2& size = {})
			: d_name(name), d_path(path), d_size(size)
		{}

		attr_ string d_name;
		attr_ string d_path;
		uvec2 d_size;
		uvec2 d_coord = uvec2(0U);

		int d_handle = -1;
		ImageAtlas* d_atlas = nullptr;

		bool d_tile = false;
		bool d_stretch = false;
		bool d_filtering = true;
	};

}


#include <stl/vector.h>

namespace mud
{
	using cstring = const char*;

	export_ enum class refl_ Spectrum : short int
	{
		Value = 0,
		Hue = 1
	};

	export_ struct refl_ MUD_MATH_EXPORT Palette
	{
	public:
		constr_ Palette(Spectrum spectrum, size_t steps);
		constr_ Palette(vector<Colour> colours);
		constr_ Palette();

		void reset();
		void load(cstring file);
		void add(Colour colour);

		size_t find_colour(const Colour& colour);

		void value_spectrum(size_t steps, bool toWhite = false);
		void hue_spectrum(size_t steps);

		vector<Colour> m_colours;
	};

	export_ struct refl_ MUD_MATH_EXPORT Image256
	{
	public:
		constr_ Image256(uint16_t width = 0, uint16_t height = 0, const Palette& palette = Palette());

		bool operator==(const Image256& other) const;

		void resize(uint16_t width, uint16_t height);
		uint32_t& at(uint16_t x, uint16_t y) { return m_pixels[x + y * m_width]; }

		vector<uint8_t> read() const;
		void read(uint8_t* data) const;

		attr_ vector<uint32_t> m_pixels;
		attr_ uint16_t m_width;
		attr_ uint16_t m_height;
		attr_ Palette m_palette;
	};
}


#ifndef MUD_MODULES
#include <stl/decls.h>
#include <stl/vector.h>
#endif

class GuillotineBinPack;

namespace mud
{
	struct StbRectPack;

	export_ MUD_MATH_EXPORT void load_folder_images(vector<Image>& images, const string& path, const string& subfolder);

	export_ class refl_ MUD_MATH_EXPORT ImageAtlas
	{
	public:
		ImageAtlas(uvec2 size);
		~ImageAtlas();

		vector<unsigned char> generate_atlas(vector<Image*>& images);

		bool place_image(Image& image);
		void blit_image(Image& image, vector<unsigned char>& data);

	public:
		uvec2 m_size;
		vec2 m_inverse_size;

		Image m_image;
		vector<Image*> m_images;

	protected:
		//unique<GuillotineBinPack> m_rect_pack;
		unique<StbRectPack> m_rect_pack;
	};

	export_ class refl_ MUD_MATH_EXPORT TextureAtlas : public ImageAtlas
	{
	public:
		TextureAtlas(uvec2 size);

		const Image& find_texture(cstring name) const;
		Image* add_texture(cstring name, uvec2 size);

		vector<Image> m_textures;
	};

	export_ class refl_ MUD_MATH_EXPORT Sprite : public Image
	{
	public:
		Sprite();
		Sprite(cstring name, cstring path, const uvec2& size, const uvec2& frames = uvec2(0U));

		void compute_frames(const vec2& atlas_inverse_size);

		uvec2 m_frames;
		uint m_num_frames;
		uvec2 m_frame_size;
		vector<uvec2> m_frame_coords;
		vector<vec4> m_frame_uvs;
	};

	export_ class refl_ MUD_MATH_EXPORT SpriteAtlas : public ImageAtlas
	{
	public:
		SpriteAtlas(uvec2 size);

		const Sprite& find_sprite(cstring name) const;
		Sprite* add_sprite(cstring name, uvec2 size, uvec2 frames = uvec2(0U));

		vec4 sprite_uv(const Sprite& sprite, uint32_t frame) const;
		vec4 sprite_uv(const Sprite& sprite, float t) const;

		vector<Sprite> m_sprites;
	};
}



namespace mud
{
	export_ template <class T>
	T random_scalar();

	export_ template <class T>
	T random_integer(T min, T max);

	export_ template <class T>
	T random_scalar(T min, T max);

	extern template float random_scalar();

	extern template float random_scalar<float>(float min, float max);
	extern template double random_scalar<double>(double min, double max);

	extern template int random_integer<int>(int min, int max);
	extern template uint random_integer<uint>(uint min, uint max);
	extern template ulong random_integer<ulong>(ulong min, ulong max);
	extern template ullong random_integer<ullong>(ullong min, ullong max);
}



namespace mud
{
	export_ template <class T>
	struct refl_ struct_ Range
	{
		Range() {}
		Range(T min, T max) : m_min(min), m_max(max) {}
		attr_ T m_min = {};
		attr_ T m_max = {};
		bool operator==(const Range<T>& other) const { return m_min == other.m_min && m_max == other.m_max; }
	};

	export_ extern template struct refl_ Range<vec3>;
	export_ extern template struct refl_ Range<quat>;
	export_ extern template struct refl_ Range<float>;
	export_ extern template struct refl_ Range<uint32_t>;
	export_ extern template struct refl_ Range<Colour>;
}


#include <stl/limits.h>
//#include <math/Math.h>

#ifndef MUD_CPP_20
#include <stdint.h>
#include <cfloat>
#endif

namespace mud
{
	export_ template <class T>
	struct StatDef
	{
		T m_min = limits<T>::min();
		T m_max = limits<T>::max();
		T m_step = T(1);

		T rincrement(T& value, T amount) const;
		T rdecrement(T& value, T amount) const;
		void increment(T& value, T amount) const;
		void decrement(T& value, T amount) const;

		void increment(T& value) const;
		void decrement(T& value) const;

		void multiply(T& value, T& base, T multiplier) const;
		
		void modify(T& value, T& base, T val) const;
		void modify(T& value, T val) const;

		void update(T& value) const;
	};

	export_ extern template struct StatDef<int>;
	export_ extern template struct StatDef<float>;

	export_ template <class T>
	struct Stat
	{
	public:
		Stat(T& value, const StatDef<T>& def);

		operator T() const;

		inline T& ref() const;
		inline T value() const;

		inline T min() const;
		inline T max() const;
		inline T step() const;

		inline void modify(T value);

		inline void increment();
		inline void decrement();

		//T m_base;
		T* m_ref;
		const StatDef<T>* m_def;
	};

	export_ extern template struct Stat<int>;
	export_ extern template struct Stat<float>;

	export_ template <class T>
	struct refl_ AutoStat : public Stat<T>
	{
	public:
		AutoStat(T value = T(), T min = limits<T>::min(), T max = limits<T>::max(), T step = T(1));
		AutoStat(T& value, StatDef<T> def);
		AutoStat(const AutoStat& other);

		AutoStat& operator=(const AutoStat& other) = default;

		attr_ T m_value;
		StatDef<T> m_def;
	};

	export_ extern template struct refl_ AutoStat<int>;
	export_ extern template struct refl_ AutoStat<float>;

#if 0
	export_ struct refl_ MUD_MATH_EXPORT Ratio : public Stat<float>
	{
	public:
		constr_ Ratio(float value = 0.f);

		attr_ float m_value;

		void set(float value) { def().modify(m_value, value); }

		const StatDef<float>& def() const { static StatDef<float> df = { 0.f, 1.f, 0.01f }; return df; }
	};

	export_ struct refl_ MUD_MATH_EXPORT Gauge : public Stat<float>
	{
	public:
		constr_ Gauge(float value = 0.f);

		attr_ float m_value;

		void set(float value) { def().modify(m_value, value); }

		const StatDef<float>& def() const { static StatDef<float> df = { 0.f, FLT_MAX, 1.f }; return df; }
	};
#endif
}
//#include <math/Stream.h>





#ifndef MUD_CPP_20
#include <ctime>
#endif

namespace mud
{
	export_ extern MUD_MATH_EXPORT const double c_tick_interval;

	inline size_t globalTick()
	{
		return size_t(clock() / c_tick_interval);
	}

	export_ struct refl_ MUD_MATH_EXPORT Time
	{
	public:
		constr_ Time(double value) : m_value(value) {}
		Time(int days, int hours, int minutes, int seconds) : m_value(days * 86400 + hours * 3600 + minutes * 60 + seconds) {}
		Time(int hours, int minutes, int seconds) : m_value(hours * 3600 + minutes * 60 + seconds) {}
		Time(const Time& other) : m_value(other.m_value) {}
		Time() : m_value(0.f) {}

		operator double() const { return m_value; }

		attr_ double m_value;

		inline int days() { return int(m_value) / 86400; }
		inline int hours() { return int(m_value) % 86400 / 3600; }
		inline int minutes() { return int(m_value) % 3600 / 60; }
		inline int seconds() { return int(m_value) % 60; }
	};

	export_ struct refl_ MUD_MATH_EXPORT TimeSpan
	{
	public:
		constr_ TimeSpan(Time s, Time e) : start(s), end(e) {}
		TimeSpan(int sh, int eh) : start(0, sh, 0, 0), end(0, eh, 0, 0) {}
		TimeSpan() : start(), end() {}

		Time operator [](size_t i) const { return i == 0 ? start : end; }
		Time& operator [](size_t i) { return i == 0 ? start : end; }

		attr_ Time start;
		attr_ Time end;
	};

	export_ class MUD_MATH_EXPORT Clock
    {
    public:
		Clock();

		void update();
        double read();
		double step();

		size_t readTick();
		size_t stepTick();

    private:
        clock_t m_last;
		size_t m_last_tick;
    };
}


#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#endif

#ifndef MUD_MODULES
#endif

#ifndef MUD_CPP_20
#include <stl/string.h>
#include <stl/vector.h>
#include <stdint.h>
#endif


namespace mud
{
    // Exported types
    export_ template <> MUD_MATH_EXPORT Type& type<mud::Axes>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::Axis>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::Clockwise>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::Side>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::SignedAxis>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::Spectrum>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::TrackMode>();
    
    export_ template <> MUD_MATH_EXPORT Type& type<mud::AutoStat<float>>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::AutoStat<int>>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::Colour>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::Image>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::Image256>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::ImageAtlas>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::Palette>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::Range<float>>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::Range<mud::Colour>>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::Range<mud::quat>>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::Range<mud::vec3>>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::Range<uint32_t>>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::Time>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::TimeSpan>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::Transform>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::ValueCurve<float>>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::ValueCurve<mud::Colour>>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::ValueCurve<mud::quat>>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::ValueCurve<mud::vec3>>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::ValueCurve<uint32_t>>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::ValueTrack<float>>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::ValueTrack<mud::Colour>>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::ValueTrack<mud::quat>>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::ValueTrack<mud::vec3>>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::ValueTrack<uint32_t>>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::bvec3>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::bvec4>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::half2>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::half3>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::ivec2>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::ivec3>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::ivec4>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::mat4>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::quat>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::uvec2>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::uvec3>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::uvec4>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::vec2>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::vec3>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::vec4>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::Sprite>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::SpriteAtlas>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::TextureAtlas>();
    
    export_ template <> MUD_MATH_EXPORT Type& type<vector<mud::AutoStat<float>*>>();
    export_ template <> MUD_MATH_EXPORT Type& type<vector<mud::AutoStat<int>*>>();
    export_ template <> MUD_MATH_EXPORT Type& type<vector<mud::Colour*>>();
    export_ template <> MUD_MATH_EXPORT Type& type<vector<mud::Image*>>();
    export_ template <> MUD_MATH_EXPORT Type& type<vector<mud::Image256*>>();
    export_ template <> MUD_MATH_EXPORT Type& type<vector<mud::ImageAtlas*>>();
    export_ template <> MUD_MATH_EXPORT Type& type<vector<mud::Palette*>>();
    export_ template <> MUD_MATH_EXPORT Type& type<vector<mud::Range<float>*>>();
    export_ template <> MUD_MATH_EXPORT Type& type<vector<mud::Range<mud::Colour>*>>();
    export_ template <> MUD_MATH_EXPORT Type& type<vector<mud::Range<mud::quat>*>>();
    export_ template <> MUD_MATH_EXPORT Type& type<vector<mud::Range<mud::vec3>*>>();
    export_ template <> MUD_MATH_EXPORT Type& type<vector<mud::Range<uint32_t>*>>();
    export_ template <> MUD_MATH_EXPORT Type& type<vector<mud::Time*>>();
    export_ template <> MUD_MATH_EXPORT Type& type<vector<mud::TimeSpan*>>();
    export_ template <> MUD_MATH_EXPORT Type& type<vector<mud::Transform*>>();
    export_ template <> MUD_MATH_EXPORT Type& type<vector<mud::ValueCurve<float>*>>();
    export_ template <> MUD_MATH_EXPORT Type& type<vector<mud::ValueCurve<mud::Colour>*>>();
    export_ template <> MUD_MATH_EXPORT Type& type<vector<mud::ValueCurve<mud::quat>*>>();
    export_ template <> MUD_MATH_EXPORT Type& type<vector<mud::ValueCurve<mud::vec3>*>>();
    export_ template <> MUD_MATH_EXPORT Type& type<vector<mud::ValueCurve<uint32_t>*>>();
    export_ template <> MUD_MATH_EXPORT Type& type<vector<mud::ValueTrack<float>*>>();
    export_ template <> MUD_MATH_EXPORT Type& type<vector<mud::ValueTrack<mud::Colour>*>>();
    export_ template <> MUD_MATH_EXPORT Type& type<vector<mud::ValueTrack<mud::quat>*>>();
    export_ template <> MUD_MATH_EXPORT Type& type<vector<mud::ValueTrack<mud::vec3>*>>();
    export_ template <> MUD_MATH_EXPORT Type& type<vector<mud::ValueTrack<uint32_t>*>>();
    export_ template <> MUD_MATH_EXPORT Type& type<vector<mud::bvec3*>>();
    export_ template <> MUD_MATH_EXPORT Type& type<vector<mud::bvec4*>>();
    export_ template <> MUD_MATH_EXPORT Type& type<vector<mud::half2*>>();
    export_ template <> MUD_MATH_EXPORT Type& type<vector<mud::half3*>>();
    export_ template <> MUD_MATH_EXPORT Type& type<vector<mud::ivec2*>>();
    export_ template <> MUD_MATH_EXPORT Type& type<vector<mud::ivec3*>>();
    export_ template <> MUD_MATH_EXPORT Type& type<vector<mud::ivec4*>>();
    export_ template <> MUD_MATH_EXPORT Type& type<vector<mud::mat4*>>();
    export_ template <> MUD_MATH_EXPORT Type& type<vector<mud::quat*>>();
    export_ template <> MUD_MATH_EXPORT Type& type<vector<mud::uvec2*>>();
    export_ template <> MUD_MATH_EXPORT Type& type<vector<mud::uvec3*>>();
    export_ template <> MUD_MATH_EXPORT Type& type<vector<mud::uvec4*>>();
    export_ template <> MUD_MATH_EXPORT Type& type<vector<mud::vec2*>>();
    export_ template <> MUD_MATH_EXPORT Type& type<vector<mud::vec3*>>();
    export_ template <> MUD_MATH_EXPORT Type& type<vector<mud::vec4*>>();
    export_ template <> MUD_MATH_EXPORT Type& type<vector<mud::Sprite*>>();
    export_ template <> MUD_MATH_EXPORT Type& type<vector<mud::SpriteAtlas*>>();
    export_ template <> MUD_MATH_EXPORT Type& type<vector<mud::TextureAtlas*>>();
}
//#include <math/VecJson.h>
//#include <math/Vec.hpp>


#include <stl/vector.h>
#include <stl/unordered_map.h>

#include <stb_rect_pack.h>

namespace stl
{
	using namespace mud;
	export_ extern template class vector<const char*>;
	export_ extern template class vector<char>;
	export_ extern template class vector<uchar>;
	export_ extern template class vector<ushort>;
	export_ extern template class vector<uint>;
	export_ extern template class vector<ulong>;
	export_ extern template class vector<long>;
	export_ extern template class vector<llong>;
	export_ extern template class vector<ullong>;
	export_ extern template class vector<float>;
	export_ extern template class vector<uvec2>;
	export_ extern template class vector<uvec3>;
	export_ extern template class vector<ivec2>;
	export_ extern template class vector<ivec3>;
	export_ extern template class vector<ivec4>;
	export_ extern template class vector<vec2>;
	export_ extern template class vector<vec3>;
	export_ extern template class vector<vec4>;
	export_ extern template class vector<quat>;
	export_ extern template class vector<mat4>;
	export_ extern template class vector<Colour>;
	export_ extern template class vector<Image>;
	export_ extern template class vector<Sprite>;
	export_ extern template class unordered_map<Type*, Colour>;

	export_ extern template class vector<stbrp_node>;
}



namespace mud
{
	export_ template <class T>
	inline T StatDef<T>::rincrement(T& value, T amount) const { T diff = min(m_max - value, amount); value += diff; update(value); return diff; }
	export_ template <class T>
	inline T StatDef<T>::rdecrement(T& value, T amount) const { T diff = max(-m_min + value, amount); value -= diff; update(value); return diff; }

	export_ template <class T>
	inline void StatDef<T>::increment(T& value, T amount) const { value += amount; update(value); }
	export_ template <class T>
	inline void StatDef<T>::decrement(T& value, T amount) const { value -= amount; update(value); }

	export_ template <class T>
	inline void StatDef<T>::increment(T& value) const { value += m_step; update(value); }
	export_ template <class T>
	inline void StatDef<T>::decrement(T& value) const { value -= m_step; update(value); }

	export_ template <class T>
	inline void StatDef<T>::multiply(T& value, T& base, T multiplier) const { T diff = value - base; base *= multiplier; value = base + diff; update(value); }
		
	export_ template <class T>
	inline void StatDef<T>::modify(T& value, T& base, T val) const { value += val - base; base = value; update(value); }
	export_ template <class T>
	inline void StatDef<T>::modify(T& value, T val) const { value = val; update(value); }

	export_ template <class T>
	inline void StatDef<T>::update(T& value) const
	{
		if(value < m_min)
			value = m_min;
		if(value > m_max)
			value = m_max;
	}

	export_ template <class T>
	Stat<T>::Stat(T& value, const StatDef<T>& def)
		//: m_base(base)
		: m_ref(&value)
		, m_def(&def)
	{}

	export_ template <class T>
	Stat<T>::operator T() const { return *m_ref; }

	export_ template <class T>
	inline T& Stat<T>::ref() const { return *m_ref; }
	export_ template <class T>
	inline T Stat<T>::value() const { return *m_ref; }

	export_ template <class T>
	inline T Stat<T>::min() const { return m_def->m_min; }
	export_ template <class T>
	inline T Stat<T>::max() const { return m_def->m_max; }
	export_ template <class T>
	inline T Stat<T>::step() const { return m_def->m_step; }

	export_ template <class T>
	inline void Stat<T>::modify(T value) { m_def->modify(*m_ref, value); }
	export_ template <class T>
	inline void Stat<T>::increment() { m_def->increment(*m_ref); }
	export_ template <class T>
	inline void Stat<T>::decrement() { m_def->decrement(*m_ref); }

	export_ template <class T>
	AutoStat<T>::AutoStat(T value, T min, T max, T step)
		: Stat<T>(m_value, m_def)
		, m_value(value)
		, m_def{ min, max, step }
	{}

	export_ template <class T>
	AutoStat<T>::AutoStat(T& value, StatDef<T> def)
		: Stat<T>(value, m_def)
		, m_def(def)
	{}

	export_ template <class T>
	AutoStat<T>::AutoStat(const AutoStat& other)
		: Stat<T>(&other.m_value == other.m_ref ? m_value : *other.m_ref, m_def)
		, m_value(other.m_value)
		, m_def(other.m_def)
	{}
}


#include <stl/string.h>

#ifndef MUD_CPP_20
#include <sstream>
#endif

namespace mud
{
	export_ inline string read(std::istream& stream, size_t length) { string result; result.resize(length); stream.read(&result[0], length); return result; }

	export_ template <class T>
	inline T read(std::istream& stream) { T result; stream >> result; return result; }

	export_ template <>
	inline vec3 read(std::istream& stream) { vec3 result; stream >> result.x >> result.y >> result.z; return result; }

	export_ template <>
	inline vec2 read(std::istream& stream) { vec2 result; stream >> result.x >> result.y; return result; }

	export_ template <>
	inline quat read(std::istream& stream) { quat result; stream >> result.x >> result.y >> result.z >> result.w; return result; }

	export_ template <>
	inline Colour read(std::istream& stream) { Colour result; stream >> result.m_r >> result.m_g >> result.m_b; return result; }
}


#ifndef MUD_MODULES
#endif

#ifdef MUD_META_GENERATOR
namespace glm
{
	struct vec3; struct quat; struct mat4;
}
#endif

namespace mud
{
	export_ MUD_MATH_EXPORT void from_json(const json& j, vec3& vec);
	export_ MUD_MATH_EXPORT void from_json(const json& j, quat& quat);
	export_ MUD_MATH_EXPORT void from_json(const json& j, mat4& mat);
}

namespace mud
{
	export_ MUD_MATH_EXPORT void from_json(const json& j, Colour& col);
	export_ MUD_MATH_EXPORT void to_json(const Colour& col, json& json);
}
