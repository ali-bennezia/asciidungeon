#include "geo.h"

#include <stddef.h>


// output verts count: 8
void asciidng_geo_parallelepiped( fvec3 size, fvec3 *vertices )
{
	fvec3 half_size = fvec3_scalar_divide( size, 2 );
	size_t index = 0;
	for ( int x = 0; x < 2; ++x ){
		int x_coord = x <= 0 ? -1 : x;
		for ( int y = 0; y < 2; ++y ){
			int y_coord = y <= 0 ? -1 : y;
			for ( int z = 0; z < 2; ++z ){
				int z_coord = z <= 0 ? -1 : z;
				fvec3 vert = {
					half_size.x * x_coord,
					half_size.y * y_coord,
					half_size.z * z_coord
				};
				*( vertices + index ) = vert;
				++index;
			}
		}
	}
}


