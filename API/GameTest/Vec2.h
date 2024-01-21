#pragma once
#include <iostream>
#include <iomanip>   // to get std::setprecision (for output precision)

namespace ZOE {

	struct Vec2 {

#pragma region xy

		// public  //
		float  x, y;


		/// Setting the values of the attributes
		void set(float x_, float y_) {
			x = x_; y = y_;
		}
#pragma endregion

#pragma region constructors
		// constructors //

		/// Constructor with one float value or no value (i.e., default)
		explicit Vec2(float s = 0.0f) {
			set(s, s);
		}

		/// Constructor with 3 float values
		Vec2(float x, float y) {
			set(x, y);
		}

		/// Constructor with one Vec3 value
		Vec2(const Vec2& v) {
			set(v.x, v.y);
		}

#pragma endregion

#pragma region methods

		// methods //

		/// Print out the coordinates of this vector
		void print() {
			std::cout << std::setprecision(8) << "x: " << x;
			std::cout << ", y: " << y << std::endl;
		}

		Vec2 operator-(Vec2 const& foo) {
			return Vec2(x - foo.x, y - foo.y);
		}
		Vec2 operator+(Vec2 const& foo) {
			return Vec2(x + foo.x, y + foo.y);
		}
		Vec2 operator*(Vec2 const& foo) {
			return Vec2(x * foo.x, y * foo.y);
		}
		Vec2 operator/(Vec2 const& foo) {
			return Vec2(x / foo.x, y / foo.y);
		}
		Vec2 operator*(float const& foo) {
			return Vec2(x * foo, y * foo);
		}

		Vec2 operator/(float const& foo) {
			return Vec2(x / foo, y / foo);
		}
		Vec2& operator-=(const Vec2& foo) {
			x -= foo.x;
			y -= foo.y;
			return *this;
		}

		Vec2& operator+=(const Vec2& foo) {
			x += foo.x;
			y += foo.y;
			return *this;
		}
		// Overloaded subtraction operator
		Vec2 operator-(const Vec2& foo) const {
			return Vec2(x - foo.x, y - foo.y);
		}

		// Overloaded multiplication operator
		Vec2 operator*(const Vec2& foo) const {
			return Vec2(x * foo.x, y * foo.y);
		}

		// Overloaded division operator
		Vec2 operator/(const Vec2& foo) const {
			return Vec2(x / foo.x, y / foo.y);
		}

		// Overloaded multiplication by scalar operator
		Vec2 operator*(float foo) const {
			return Vec2(x * foo, y * foo);
		}

		// Overloaded division by scalar operator
		Vec2 operator/(float foo) const {
			return Vec2(x / foo, y / foo);
		}

		float getMag() {
			return sqrt(x * x + y * y);
		}
		Vec2 normeyes() {
			//return Vec2(x, y) * getMag();
			return Vec2(x, y) / getMag();

		}


		// Overloaded multiplication operator (float * Vec2)
		friend Vec2 operator*(float scalar, const Vec2& vector) {
			return Vec2(scalar * vector.x, scalar * vector.y);
		}

#pragma endregion

#pragma region destructors
		// destructor //
		~Vec2() {}
#pragma endregion

	};
}

#pragma region summary




