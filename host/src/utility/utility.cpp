#include "utility.h"

using Vector3 = FVector;
using D3DMATRIX = FMatrix;
using Vector2 = FVector2D;

FVector2D utils::world_to_screen( FVector world_position ) {
    camera::update( );

    int screen_center_x = 1920 / 2;
    int screen_center_y = 1080 / 2;

	D3DMATRIX temp_matrix = FMatrix::vector_to_matrix( camera::rotation );
	Vector3 vaxisx = Vector3(temp_matrix.m[0][0], temp_matrix.m[0][1], temp_matrix.m[0][2]);
	Vector3 vaxisy = Vector3(temp_matrix.m[1][0], temp_matrix.m[1][1], temp_matrix.m[1][2]);
	Vector3 vaxisz = Vector3(temp_matrix.m[2][0], temp_matrix.m[2][1], temp_matrix.m[2][2]);
	Vector3 vdelta = world_position - camera::location;
	Vector3 vtransformed = Vector3(vdelta.dot(vaxisy), vdelta.dot(vaxisz), vdelta.dot(vaxisx));
	if (vtransformed.z < 1) vtransformed.z = 1;
	return Vector2(screen_center_x + vtransformed.x * ((screen_center_x / tanf(camera::fov * std::numbers::pi / 360))) / vtransformed.z, screen_center_y - vtransformed.y * ((screen_center_x / tanf(camera::fov *  std::numbers::pi / 360))) / vtransformed.z);
}