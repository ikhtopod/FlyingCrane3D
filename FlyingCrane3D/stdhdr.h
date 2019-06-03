#pragma once

#ifndef STDHDR_H
#define STDHDR_H

#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/normal.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/matrix_decompose.hpp>

#include <imgui.h>
#include <imgui_dock.h>
#include <imgui_impl_glfw.h>

#undef IMGUI_IMPL_OPENGL_LOADER_GL3W
#undef IMGUI_IMPL_OPENGL_LOADER_GLEW
#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include <imgui_impl_opengl3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <numeric>
#include <functional>
#include <algorithm>
#include <vector>
#include <map>
#include <unordered_map>
#include <cstdlib>
#include <cstddef>
#include <cmath>
#include <exception>
#include <stdexcept>
#include <type_traits>
#include <memory>
#include <filesystem>
#include <chrono>
#include <thread>


/* app headers */

#include "ITriada.h"

#include "Util.h"

#include "DeltaTime.h"
#include "ScreenResolution.h"
#include "Application.h"
#include "Window.h"
#include "Texture.h"
#include "GUI.h"
#include "CameraSwitcher.h"
#include "Camera.h"
#include "TargetCamera.h"
#include "FreeCamera.h"
#include "Scene.h"
#include "Vertex.h"
#include "Point.h"
#include "Edge.h"
#include "Face.h"
#include "PolymeshRepresentation.h"
#include "SelectionInfo.h"
#include "SelectionSwitcher.h"
#include "Selection.h"
#include "SelectionObject.h"
#include "SelectionElement.h"
#include "SelectionElementPoint.h"
#include "SelectionElementEdge.h"
#include "SelectionElementFace.h"
#include "MeshBase.h"
#include "Mesh.h"
#include "MeshElement.h"
#include "MeshElementPoint.h"
#include "MeshElementEdge.h"
#include "MeshElementFace.h"
#include "Object.h"
#include "ObjectScene.h"
#include "ObjectSceneGrid.h"
#include "ObjectShape.h"
#include "ObjectShapePlane.h"
#include "ObjectShapeCube.h"
#include "ObjectShapePyramid.h"
#include "MeshElementManager.h"
#include "Axis.h"
#include "Shader.h"
#include "Projection.h"
#include "Model.h"


#endif // !STDHDR_H
