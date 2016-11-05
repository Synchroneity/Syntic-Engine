#pragma once

typedef enum {
	RENDERER_OPENGL,
	RENDERER_DX11,
	RENDERER_DXGI,
} renderer_e;

typedef struct {
	int			width;
	int			height;

	renderer_e	renderer;
} renderSettings_s;