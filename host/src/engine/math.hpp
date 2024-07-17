#ifndef MATH_HPP
#define MATH_HPP

#include <cmath>
#include <numbers>
#include <iostream>

struct FVector
{
    FVector( ) : x( ) , y( ) , z( ) { }
    FVector( double x , double y , double z ) : x( x ) , y( y ) , z( z ) { }

    FVector operator + ( const FVector& other ) const { return { this->x + other.x, this->y + other.y, this->z + other.z }; }
    FVector operator - ( const FVector& other ) const { return { this->x - other.x, this->y - other.y, this->z - other.z }; }
    FVector operator * ( double offset ) const { return { this->x * offset, this->y * offset, this->z * offset }; }
    FVector operator / ( double offset ) const { return { this->x / offset, this->y / offset, this->z / offset }; }

    FVector& operator *= ( const double other ) { this->x *= other; this->y *= other; this->z *= other; return *this; }
    FVector& operator /= ( const double other ) { this->x /= other; this->y /= other; this->z /= other; return *this; }

    FVector& operator = ( const FVector& other ) { this->x = other.x; this->y = other.y; this->z = other.z; return *this; }
    FVector& operator += ( const FVector& other ) { this->x += other.x; this->y += other.y; this->z += other.z; return *this; }
    FVector& operator -= ( const FVector& other ) { this->x -= other.x; this->y -= other.y; this->z -= other.z; return *this; }
    FVector& operator *= ( const FVector& other ) { this->x *= other.x; this->y *= other.y; this->z *= other.z; return *this; }
    FVector& operator /= ( const FVector& other ) { this->x /= other.x; this->y /= other.y; this->z /= other.z; return *this; }

    operator bool( ) { return bool( this->x || this->y || this->z ); }
    friend bool operator == ( const FVector& a , const FVector& b ) { return a.x == b.x && a.y == b.y && a.z == b.z; }
    friend bool operator != ( const FVector& a , const FVector& b ) { return !( a == b ); }

    friend std::ostream& operator<<( std::ostream& out, const FVector& vec ) { return out << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")"; }
    double dot( const FVector& V ) { return x * V.x + y * V.y + z * V.z; }
    double sizesquared( ) { return x * x + y * y + z * z; }

    void normalize( )
    {
        while ( this->x > 180.0f )
        {
            this->x -= 360.0f;
        }
        while ( this->x < -180.0f )
        {
            this->x += 360.0f;
        }
        while ( this->y > 180.0f )
        {
            this->y -= 360.0f;
        }
        while ( this->y < -180.0f )
        {
            this->y += 360.0f;
        }

        this->z = 0;
    }

    void clamp( float min, float max )
    {
        if ( this->x < min )
        {
            this->x = min;
        }
        else if ( this->x > max )
        {
            this->x = max;
        }

        if ( this->y < min )
        {
            this->y = min;
        }
        else if ( this->y > max )
        {
            this->y = max;
        }

        this->z = 0;
    }

    
    double distance( const FVector& other ) const {
        return std::sqrt( std::pow( x - other.x, 2 ) + std::pow( y - other.y, 2 ) + std::pow( z - other.z, 2 ) );
    }

    double x, y, z;
};

struct FVector2D
{
    FVector2D( ) : x( ) , y( ) { }
    FVector2D( double x , double y ) : x( x ) , y( y ) { }

    FVector2D operator + ( const FVector2D& other ) const { return { this->x + other.x, this->y + other.y }; }
    FVector2D operator - ( const FVector2D& other ) const { return { this->x - other.x, this->y - other.y }; }
    FVector2D operator * ( double offset ) const { return { this->x * offset, this->y * offset }; }
    FVector2D operator / ( double offset ) const { return { this->x / offset, this->y / offset }; }

    FVector2D& operator *= ( const double other ) { this->x *= other; this->y *= other; return *this; }
    FVector2D& operator /= ( const double other ) { this->x /= other; this->y /= other; return *this; }

    FVector2D& operator = ( const FVector2D& other ) { this->x = other.x; this->y = other.y; return *this; }
    FVector2D& operator += ( const FVector2D& other ) { this->x += other.x; this->y += other.y; return *this; }
    FVector2D& operator -= ( const FVector2D& other ) { this->x -= other.x; this->y -= other.y; return *this; }
    FVector2D& operator *= ( const FVector2D& other ) { this->x *= other.x; this->y *= other.y; return *this; }
    FVector2D& operator /= ( const FVector2D& other ) { this->x /= other.x; this->y /= other.y; return *this; }

    operator bool( ) { return bool( this->x || this->y ); }
    friend bool operator == ( const FVector2D& A, const FVector2D& B ) { return A.x == B.x && A.y == A.y; }
    friend bool operator != ( const FVector2D& A, const FVector2D& B ) { return !( A == B ); }
    friend std::ostream& operator<<( std::ostream& out, const FVector2D& vec ) { return out << "(" << vec.x << ", " << vec.y << ")"; }

    double x, y;
};

struct FRotator
{
    FRotator( ) : pitch( ) , yaw( ) , roll( ) { }
    FRotator( double pitch , double yaw , double roll ) : pitch( pitch ) , yaw( yaw ) , roll( roll ) { }

    FRotator operator + ( const FRotator& other ) const { return { this->pitch + other.pitch, this->yaw + other.yaw, this->roll + other.roll }; }
    FRotator operator - ( const FRotator& other ) const { return { this->pitch - other.pitch, this->yaw - other.yaw, this->roll - other.roll }; }
    FRotator operator * ( double offset ) const { return { this->pitch * offset, this->yaw * offset, this->roll * offset }; }
    FRotator operator / ( double offset ) const { return { this->pitch / offset, this->yaw / offset, this->roll / offset }; }

    FRotator& operator *= ( const double other ) { this->pitch *= other; this->yaw *= other; this->roll *= other; return *this; }
    FRotator& operator /= ( const double other ) { this->pitch /= other; this->yaw /= other; this->roll /= other; return *this; }

    FRotator& operator = ( const FRotator& other ) { this->pitch = other.pitch; this->yaw = other.yaw; this->roll = other.roll; return *this; }
    FRotator& operator += ( const FRotator& other ) { this->pitch += other.pitch; this->yaw += other.yaw; this->roll += other.roll; return *this; }
    FRotator& operator -= ( const FRotator& other ) { this->pitch -= other.pitch; this->yaw -= other.yaw; this->roll -= other.roll; return *this; }
    FRotator& operator *= ( const FRotator& other ) { this->pitch *= other.pitch; this->yaw *= other.yaw; this->roll *= other.roll; return *this; }
    FRotator& operator /= ( const FRotator& other ) { this->pitch /= other.pitch; this->yaw /= other.yaw; this->roll /= other.roll; return *this; }

    operator bool( ) { return bool( this->pitch || this->yaw || this->roll ); }
    friend bool operator == ( const FRotator& a , const FRotator& b ) { return a.pitch == b.pitch && a.yaw == b.yaw && a.roll == b.roll; }
    friend bool operator != ( const FRotator& a , const FRotator& b ) { return !( a == b ); }

    FRotator operator/( double Scalar )
    {
        return FRotator( this->pitch / Scalar , this->yaw / Scalar , this->roll / Scalar );
    }

    FVector euler( ) const
    {
        return FVector( pitch , yaw , roll );
    }



    FRotator normalize( )
    {
        while ( this->yaw > 180.0 )
            this->yaw -= 360.0;
        while ( this->yaw < -180.0 )
            this->yaw += 360.0;

        while ( this->pitch > 180.0 )
            this->pitch -= 360.0;
        while ( this->pitch < -180.0 )
            this->pitch += 360.0;

        this->roll = 0.0;
        return *this;
    }

    double pitch, yaw, roll;
};

class FMatrix {
public:
    union {
        struct {
            float        _11, _12, _13, _14;
            float        _21, _22, _23, _24;
            float        _31, _32, _33, _34;
            float        _41, _42, _43, _44;

        };
        float m[4][4];
    };

    // stolen from github
    static FMatrix vector_to_matrix( FVector rotation, FVector origin = FVector( 0, 0, 0 ) ) {
        float radpitch = (rotation.x * M_PI / 180);
		float radyaw = (rotation.y * M_PI / 180);
		float radroll = (rotation.z * M_PI / 180);
		float sp = sinf(radpitch);
		float cp = cosf(radpitch);
		float sy = sinf(radyaw);
		float cy = cosf(radyaw);
		float sr = sinf(radroll);
		float cr = cosf(radroll);

		FMatrix matrix{};
		matrix.m[0][0] = cp * cy;
		matrix.m[0][1] = cp * sy;
		matrix.m[0][2] = sp;
		matrix.m[0][3] = 0.f;
		matrix.m[1][0] = sr * sp * cy - cr * sy;
		matrix.m[1][1] = sr * sp * sy + cr * cy;
		matrix.m[1][2] = -sr * cp;
		matrix.m[1][3] = 0.f;
		matrix.m[2][0] = -(cr * sp * cy + sr * sy);
		matrix.m[2][1] = cy * sr - cr * sp * sy;
		matrix.m[2][2] = cr * cp;
		matrix.m[2][3] = 0.f;
		matrix.m[3][0] = origin.x;
		matrix.m[3][1] = origin.y;
		matrix.m[3][2] = origin.z;
		matrix.m[3][3] = 1.f;
		return matrix;
    }

    FMatrix operator* (const FMatrix pm2) {
        FMatrix pout{};
        pout._11 = this->_11 * pm2._11 + this->_12 * pm2._21 + this->_13 * pm2._31 + this->_14 * pm2._41;
        pout._12 = this->_11 * pm2._12 + this->_12 * pm2._22 + this->_13 * pm2._32 + this->_14 * pm2._42;
        pout._13 = this->_11 * pm2._13 + this->_12 * pm2._23 + this->_13 * pm2._33 + this->_14 * pm2._43;
        pout._14 = this->_11 * pm2._14 + this->_12 * pm2._24 + this->_13 * pm2._34 + this->_14 * pm2._44;
        pout._21 = this->_21 * pm2._11 + this->_22 * pm2._21 + this->_23 * pm2._31 + this->_24 * pm2._41;
        pout._22 = this->_21 * pm2._12 + this->_22 * pm2._22 + this->_23 * pm2._32 + this->_24 * pm2._42;
        pout._23 = this->_21 * pm2._13 + this->_22 * pm2._23 + this->_23 * pm2._33 + this->_24 * pm2._43;
        pout._24 = this->_21 * pm2._14 + this->_22 * pm2._24 + this->_23 * pm2._34 + this->_24 * pm2._44;
        pout._31 = this->_31 * pm2._11 + this->_32 * pm2._21 + this->_33 * pm2._31 + this->_34 * pm2._41;
        pout._32 = this->_31 * pm2._12 + this->_32 * pm2._22 + this->_33 * pm2._32 + this->_34 * pm2._42;
        pout._33 = this->_31 * pm2._13 + this->_32 * pm2._23 + this->_33 * pm2._33 + this->_34 * pm2._43;
        pout._34 = this->_31 * pm2._14 + this->_32 * pm2._24 + this->_33 * pm2._34 + this->_34 * pm2._44;
        pout._41 = this->_41 * pm2._11 + this->_42 * pm2._21 + this->_43 * pm2._31 + this->_44 * pm2._41;
        pout._42 = this->_41 * pm2._12 + this->_42 * pm2._22 + this->_43 * pm2._32 + this->_44 * pm2._42;
        pout._43 = this->_41 * pm2._13 + this->_42 * pm2._23 + this->_43 * pm2._33 + this->_44 * pm2._43;
        pout._44 = this->_41 * pm2._14 + this->_42 * pm2._24 + this->_43 * pm2._34 + this->_44 * pm2._44;

	    return pout;
    }


};

class FPlane {
public:
    double x, y, z, w;
};

class FTransform
{
public:
    FPlane  Rotation; // 0x0
    FVector Translation; // 0x20 
    char    cPad[ 8 ];
    FVector Scale;

    auto to_matrix( ) 
    {
        FMatrix m;
        m._41 = Translation.x;
        m._42 = Translation.y;
        m._43 = Translation.z;

        double x2 = Rotation.x + Rotation.x;
        double y2 = Rotation.y + Rotation.y;
        double z2 = Rotation.z + Rotation.z;

        double xx2 = Rotation.x * x2;
        double yy2 = Rotation.y * y2;
        double zz2 = Rotation.z * z2;
        m._11 = ( 1.0f - ( yy2 + zz2 ) ) * Scale.x;
        m._22 = ( 1.0f - ( xx2 + zz2 ) ) * Scale.y;
        m._33 = ( 1.0f - ( xx2 + yy2 ) ) * Scale.z;

        double yz2 = Rotation.y * z2;
        double wx2 = Rotation.w * x2;
        m._32 = ( yz2 - wx2 ) * Scale.z;
        m._23 = ( yz2 + wx2 ) * Scale.y;

        double xy2 = Rotation.x * y2;
        double wz2 = Rotation.w * z2;
        m._21 = ( xy2 - wz2 ) * Scale.y;
        m._12 = ( xy2 + wz2 ) * Scale.x;

        double xz2 = Rotation.x * z2;
        double wy2 = Rotation.w * y2;
        m._31 = ( xz2 + wy2 ) * Scale.z;
        m._13 = ( xz2 - wy2 ) * Scale.x;

        m._14 = 0.0f;
        m._24 = 0.0f;
        m._34 = 0.0f;
        m._44 = 1.0f;

        return m;
    }
};

#endif