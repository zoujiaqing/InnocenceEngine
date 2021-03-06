#include "../Core/InnoLogger.h"

template <>
inline void InnoLogger::Log(LogLevel logLevel, const Vec2& values)
{
	InnoLogger::Log(logLevel, "Vec2(x: ", values.x, ", y: ", values.y, ")");
}

template <>
inline void InnoLogger::Log(LogLevel logLevel, const Vec4& values)
{
	InnoLogger::Log(logLevel, "Vec4(x: ", values.x, ", y: ", values.y, ", z: ", values.z, ", w: ", values.w, ")");
}

template <>
inline void InnoLogger::Log(LogLevel logLevel, const Mat4& values)
{
	InnoLogger::Log(logLevel,
		"Mat4: \n|",
		values.m00, "", values.m10, "", values.m20, "", values.m30, "|\n|",
		values.m01, "", values.m11, "", values.m21, "", values.m31, "|\n|",
		values.m02, "", values.m12, "", values.m22, "", values.m32, "|\n|",
		values.m03, "", values.m13, "", values.m23, "", values.m33, "|\n");
}