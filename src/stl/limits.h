#pragma once

#include <stl/base.h>
#include <climits>
#include <cfloat>

namespace two
{
#if 0
	template <class T>
	T vmin = 0;
	template <class T>
	T vmax = 0;

	template <> bool vmin<bool> = false;
	template <> bool vmax<bool> = true;
#endif

	export_ template <class T>
	struct limits {};

	export_ template <> struct limits<bool> {
		static constexpr bool min() noexcept { return (false); }
		static constexpr bool max() noexcept { return (true); }
	};

	export_ template <> struct limits<char> {
		static constexpr char min() noexcept { return (CHAR_MIN); }
		static constexpr char max() noexcept { return (CHAR_MAX); }
	};

	export_ template <> struct limits<schar> {
		static constexpr schar min() noexcept { return (SCHAR_MIN); }
		static constexpr schar max() noexcept { return (SCHAR_MAX); }
	};

	export_ template <> struct limits<uchar> {
		static constexpr uchar min() noexcept { return (0); }
		static constexpr uchar max() noexcept { return (UCHAR_MAX); }
	};

	export_ template <> struct limits<short> {
		static constexpr short min() noexcept { return (SHRT_MIN); }
		static constexpr short max() noexcept { return (SHRT_MAX); }
	};

	export_ template <> struct limits<ushort> {
		static constexpr ushort min() noexcept { return (0); }
		static constexpr ushort max() noexcept { return (USHRT_MAX); }
	};

	//export_ template <> struct limits<char16_t> {
	//	static constexpr char16_t min() noexcept { return (0); }
	//	static constexpr char16_t max() noexcept { return (USHRT_MAX); }
	//};

	export_ template <> struct limits<int> {
		static constexpr int min() noexcept { return (INT_MIN); }
		static constexpr int max() noexcept { return (INT_MAX); }
	};

	export_ template <> struct limits<uint> {
		static constexpr uint min() noexcept { return (0); }
		static constexpr uint max() noexcept { return (UINT_MAX); }
	};

	export_ template <> struct limits<long> {
		static constexpr long min() noexcept { return (LONG_MIN); }
		static constexpr long max() noexcept { return (LONG_MAX); }
	};

	export_ template <> struct limits<ulong> {
		static constexpr ulong min() noexcept { return (0); }
		static constexpr ulong max() noexcept { return (ULONG_MAX); }
	};

	//export_ template <> struct limits<char32_t> {
	//	static constexpr char32_t min() noexcept { return (0); }
	//	static constexpr char32_t max() noexcept { return (UINT_MAX); }
	//};

	export_ template <> struct limits<llong> {
		static constexpr llong min() noexcept { return (LLONG_MIN); }
		static constexpr llong max() noexcept { return (LLONG_MAX); }
	};

	export_ template <> struct limits<ullong> {
		static constexpr ullong min() noexcept { return (0); }
		static constexpr ullong max() noexcept { return (ULLONG_MAX); }
	};

	export_ template <> struct limits<float> {
		static constexpr float min() noexcept { return (-FLT_MAX); }
		static constexpr float max() noexcept { return (FLT_MAX); }
	};

	export_ template <> struct limits<double> {
		static constexpr double min() noexcept { return (-DBL_MAX); }
		static constexpr double max() noexcept { return (DBL_MAX); }
	};

	export_ template <> struct limits<ldouble> {
		static constexpr ldouble min() noexcept { return (-LDBL_MAX); }
		static constexpr ldouble max() noexcept { return (LDBL_MAX); }
	};
}
