#pragma once

#include "Pipeline.h"

class VertexPositionColorEffect
{
public:
	class Vertex
	{
	public:
		Vertex() = default;
		Vertex(const Vec3& pos)
			:
			pos(pos)
		{}
		Vertex(const Vec3& pos, const Vertex& src)
			:
			pos(pos)
		{}
		Vertex& operator+=(const Vertex& rhs)
		{
			pos += rhs.pos;
			return *this;
		}
		Vertex operator+(const Vertex& rhs) const
		{
			return Vertex(*this) += rhs;
		}
		Vertex& operator-=(const Vertex& rhs)
		{
			pos -= rhs.pos;
			return *this;
		}
		Vertex operator-(const Vertex& rhs) const
		{
			return Vertex(*this) -= rhs;
		}
		Vertex& operator*=(const float rhs)
		{
			pos *= rhs;
			return *this;
		}
		Vertex operator*(const float rhs) const
		{
			return Vertex(*this) *= rhs;
		}
		Vertex& operator/=(const float rhs)
		{
			pos /= rhs;
			return *this;
		}
		Vertex operator/(const float rhs) const
		{
			return Vertex(*this) /= rhs;
		}
	public:
		Vec3 pos;
	};
	// use x, y, z position components to determine color
	class VertexShader
	{
	public:
		class Output
		{
		public:
			Output() = default;
			Output(const Vec3& pos)
				:
				pos(pos)
			{}
			Output(const Vec3& pos, const Output& src)
				:
				color(src.color),
				pos(pos)
			{}
			Output(const Vec3& pos, const Vec3& color)
				:
				color(color),
				pos(pos)
			{}
			Output& operator+=(const Output& rhs)
			{
				pos += rhs.pos;
				color += rhs.color;
				return *this;
			}
			Output operator+(const Output& rhs) const
			{
				return Output(*this) += rhs;
			}
			Output& operator-=(const Output& rhs)
			{
				pos -= rhs.pos;
				color -= rhs.color;
				return *this;
			}
			Output operator-(const Output& rhs) const
			{
				return Output(*this) -= rhs;
			}
			Output& operator*=(float rhs)
			{
				pos *= rhs;
				color *= rhs;
				return *this;
			}
			Output operator*(float rhs) const
			{
				return Output(*this) *= rhs;
			}
			Output& operator/=(float rhs)
			{
				pos /= rhs;
				color /= rhs;
				return *this;
			}
			Output operator/(float rhs) const
			{
				return Output(*this) /= rhs;
			}
		public:
			Vec3 pos;
			Vec3 color;
		};
	public:
		void BindRotation(const Mat3& rotation_in)
		{
			rotation = rotation_in;
		}
		void BindTranslation(const Vec3& translation_in)
		{
			translation = translation_in;
		}
		Output operator()(const Vertex& in) const
		{
			const auto pos = in.pos * rotation + translation;
			return {
				pos,
				Vec3(abs(pos.x), abs(pos.y), abs(pos.z)) * 255.0f
			};
		}
	private:
		Mat3 rotation;
		Vec3 translation;
	};
	class PixelShader
	{
	public:
		template<class Input>
		Color operator()(const Input& in) const
		{
			return Color(in.color);
		}
	};
public:
	VertexShader vs;
	PixelShader ps;
};