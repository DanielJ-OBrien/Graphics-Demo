#pragma once
#include "SimpleMath.h"
#include <d3d11.h>
#include <array>
using namespace DirectX::SimpleMath;

#define ShaderFileName		L"Tshader.hlsl"
#define VertexShaderName	"VS"
#define PixelShaderName		"PS"
#define TextureName			L"Woodbox.bmp"

//// Format of the constant buffer. This must match the format of the
//// cbuffer structure in the shader

struct CBuffer
{
	Matrix		WorldViewProjection;
	Matrix		World;
	Vector4		AmbientLightColour;
	Vector4		DirectionalLightColour;
	Vector4		DirectionalLightVector;
};

// Structure of a single vertex.  This must match the
// structure of the input vertex in the shader

struct Vertex
{
	Vector3		InputPosition;
	Vector2		TextureCoordinate;
	Vector3		Normal = {0.0f, 0.0f, 0.0f};
};

// The description of the vertex that is passed to CreateInputLayout.  This must
// match the format of the vertex above and the format of the input vertex in the shader

D3D11_INPUT_ELEMENT_DESC TvertexDesc[] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
};

// This example uses hard-coded vertices and indices for a cube. Usually, you will load the verticesa and indices from a model file. 
// We will see this later in the module. 


Vertex Tvertices[] =
{
	{ Vector3(-1.0f, -1.0f, 1.0f), Vector2(0.0f, 0.0f)  },    // side 1
	{ Vector3(1.0f, -1.0f, 1.0f), Vector2(0.0f, 1.0f)   },
	{ Vector3(-1.0f, 1.0f, 1.0f), Vector2(1.0f, 0.0f)   },
	{ Vector3(1.0f, 1.0f, 1.0f), Vector2(1.0f, 1.0f)   },

	{ Vector3(-1.0f, -1.0f, -1.0f), Vector2(0.0f, 0.0f)   },    // side 2
	{ Vector3(-1.0f, 1.0f, -1.0f), Vector2(0.0f, 1.0f)   },
	{ Vector3(1.0f, -1.0f, -1.0f), Vector2(1.0f, 0.0f)   },
	{ Vector3(1.0f, 1.0f, -1.0f), Vector2(1.0f, 1.0f)  },

	{ Vector3(-1.0f, 1.0f, -1.0f), Vector2(0.0f, 0.0f)   },    // side 3
	{ Vector3(-1.0f, 1.0f, 1.0f), Vector2(0.0f, 1.0f)   },
	{ Vector3(1.0f, 1.0f, -1.0f), Vector2(1.0f, 0.0f)   },
	{ Vector3(1.0f, 1.0f, 1.0f), Vector2(1.0f, 1.0f)  },

	{ Vector3(-1.0f, -1.0f, -1.0f), Vector2(0.0f, 0.0f)   },    // side 4
	{ Vector3(1.0f, -1.0f, -1.0f), Vector2(0.0f, 1.0f)  },
	{ Vector3(-1.0f, -1.0f, 1.0f), Vector2(1.0f, 0.0f)   },
	{ Vector3(1.0f, -1.0f, 1.0f), Vector2(1.0f, 1.0f)   },

	{ Vector3(1.0f, -1.0f, -1.0f), Vector2(0.0f, 0.0f)   },    // side 5
	{ Vector3(1.0f, 1.0f, -1.0f), Vector2(0.0f, 1.0f)   },
	{ Vector3(1.0f, -1.0f, 1.0f), Vector2(1.0f, 0.0f)   },
	{ Vector3(1.0f, 1.0f, 1.0f), Vector2(1.0f, 1.0f)   },

	{ Vector3(-1.0f, -1.0f, -1.0f), Vector2(0.0f, 0.0f)  },    // side 6
	{ Vector3(-1.0f, -1.0f, 1.0f), Vector2(0.0f, 1.0f)   },
	{ Vector3(-1.0f, 1.0f, -1.0f), Vector2(1.0f, 0.0f)   },
	{ Vector3(-1.0f, 1.0f, 1.0f), Vector2(1.0f, 1.0f)   }
};

UINT Tindices[] = {
			0, 1, 2,       // side 1
			2, 1, 3,
			4, 5, 6,       // side 2
			6, 5, 7,
			8, 9, 10,      // side 3
			10, 9, 11,
			12, 13, 14,    // side 4
			14, 13, 15,
			16, 17, 18,    // side 5
			18, 17, 19,
			20, 21, 22,    // side 6
			22, 21, 23,
};

Vector3 TNormalCalculator(int i) {

	int i0 = Tindices[i];
	int i1 = Tindices[i + 1];
	int i2 = Tindices[i + 2];

	Vector3 v0 = Tvertices[i0].InputPosition;
	Vector3 v1 = Tvertices[i1].InputPosition;
	Vector3 v2 = Tvertices[i2].InputPosition;

	Vector3 a = v1 - v0;
	Vector3 b = v2 - v0;

	return a.Cross(b);

}

void TVertexNormal() {
	printf("hia");
	int vCount[ARRAYSIZE(Tvertices)];
	printf("hia2");
	for (int i = 0; i < size(vCount); i++) {

		vCount[i] = 0;
	}

	for (int i = 0; i < size(Tindices); i += 3) {

		int i0 = Tindices[i];
		int i1 = Tindices[i + 1];
		int i2 = Tindices[i + 2];

		Vector3 normal = TNormalCalculator(i);

		Tvertices[i0].Normal += normal;
		Tvertices[i1].Normal += normal;
		Tvertices[i2].Normal += normal;

		vCount[i0] ++;
		vCount[i1] ++;
		vCount[i2] ++;
	}

	for (int i = 0; i < ARRAYSIZE(Tvertices); i++) {

		Tvertices[i].Normal /= (float)vCount[i];
		Tvertices[i].Normal.Normalize();
	}
}