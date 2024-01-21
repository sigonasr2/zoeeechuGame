#pragma once
#include <iostream>
#include <iomanip>   // to get std::setprecision (for output precision)

namespace ZOE {

	struct Vec3 {

#pragma region xyz

		// public  //
		float  x, y, z;


		/// Setting the values of the attributes
		void set(float x_, float y_, float z_) {
			x = x_; y = y_; z = z_;
		}
#pragma endregion

#pragma region constructors
		// constructors //

		/// Constructor with one float value or no value (i.e., default)
		explicit Vec3(float s = 0.0f) {
			set(s, s, s);
		}

		/// Constructor with 3 float values
		Vec3(float x, float y, float z) {
			set(x, y, z);
		}

		/// Constructor with one Vec3 value
		Vec3(const Vec3& v) {
			set(v.x, v.y, v.z);
		}

#pragma endregion

#pragma region methods

		// methods //

		/// Print out the coordinates of this vector
		void print() {
			std::cout << std::setprecision(8) << "x: " << x;
			std::cout << ", y: " << y << ", z: " << z << std::endl;
		}

		Vec3 operator-(Vec3 const& foo) {
			return Vec3(x - foo.x, y - foo.y, z - foo.z);
		}

		Vec3 operator+(Vec3 const& foo) {
			return Vec3(x + foo.x, y + foo.y, z + foo.z);
		}

		Vec3 operator*(float const& foo) {
			return Vec3(x * foo, y * foo, z * foo);
		}

		Vec3 operator/(float const& foo) {
			return Vec3(x / foo, y / foo, z / foo);
		}

		float getMag() {
			return sqrt(x * x + y * y + z * z);
		}

		Vec3 normeyes() {
			return Vec3(x, y, z) / getMag();
		}
#pragma endregion

#pragma region destructors
		// destructor //
		~Vec3() {}
#pragma endregion

	};
}

#pragma region summary




