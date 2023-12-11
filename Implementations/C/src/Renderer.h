#ifndef _Renderer_
#define _Renderer_

#include "Scene/Planet/Planet.h"
#include "Scene/Camera.h"
#include "Textures/TextureManager.h"

void RendererClear();
void RendererSetRenderColor(float r, float g, float b);

void RendererRenderPlanet(PlanetPtr, Point3f, TextureManagerPtr, Camera3DPtr);

#endif