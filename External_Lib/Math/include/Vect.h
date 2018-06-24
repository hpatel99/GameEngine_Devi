//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2018
// Gam575
//----------------------------------------------------------------------------- 

#ifndef ENGINE_MATH_VECT_H
#define ENGINE_MATH_VECT_H

// Includes to handle SIMD register types
#include <xmmintrin.h>
#include <smmintrin.h>

#include "Align16.h"
#include "Constants.h"
#include "Enum.h"

// forward declare
class Matrix;
class Quat;

class Vect final : public Align16
{
public:


	// Big 4
	Vect(); 
	Vect( const Vect &inV ); 
	const Vect &operator=(const Vect &v);
	~Vect();

	// Constructors
	Vect(const float in_x, const float in_y, const float in_z,  const float in_w = 1.0f);

	// Bracket
	float &operator[] (const enum x_enum);
	float &operator[] (const enum y_enum);
	float &operator[] (const enum z_enum);
	float &operator[] (const enum w_enum);

	const float operator[] (const enum x_enum ) const;
	const float operator[] (const enum y_enum ) const;
	const float operator[] (const enum z_enum ) const;
	const float operator[] (const enum w_enum ) const;


	// Accessors 
	float &x();
	float &y();
	float &z();
	float &w();

	const float x()const;
	const float y()const;
	const float z()const;
	const float w()const;

	// add/sub operators
	Vect operator + (void) const;
	Vect operator + (const Vect &inV) const;
	void operator += (const Vect &inV);
	Vect operator - (const Vect &inV) const ;
	void operator -= (const Vect &inV);
	Vect operator - (void) const;

	// Multiply operators
	Vect operator * (const float scale) const;
	friend Vect operator *(const float scale, const Vect &inV ); 
	void operator *= (const float scale);
	
	// Vect * Matrix
	Vect operator* ( const Matrix &m ) const;
	Vect operator*= (  const Matrix &m );

	// Vect * Quat
	Vect operator* (const Quat &q) const;
	Vect operator*= (const Quat &q);

	// Vector functions
	Vect &norm( void );
	Vect getNorm( void ) const;
	const float dot( const Vect &vIn ) const;
	const Vect cross( const Vect &vIn ) const;
	const float mag( void ) const;
	const float magSqr( void ) const;
	const float getAngle( const Vect &vIn ) const;

	// set
	void set(const float inX, const float inY, const float inZ, const float inW = 1.0f );
	void set( const Vect &A);

	// comparison
	bool isEqual( const Vect &v, const float epsilon = MATH_TOLERANCE) const;
	bool isZero( const float epsilon = MATH_TOLERANCE) const;

private:

	union 
	{
		__m128	_mv;

		// anonymous struct
		struct 
			{
			float _vx;
			float _vy;
			float _vz;
			float _vw;
			};
	};

};


#endif

// ---  End of File ---------------
