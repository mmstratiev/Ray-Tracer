#include <fstream>
#include <string> 

#include "Globals.h"
#include "Pixel.h"
#include "Vector.h"
#include "Triangle.h"
#include "Camera.h"
#include "Renderer.h"

#include "rapidjson/document.h"

CCamera Viewport;

void LoadCrtScene(std::string document);

int main() 
{
	CRenderer renderer(Viewport);
	auto clearScene = [&]()
	{
		Viewport.Reset();
		GeometricObjects.clear();
		Lights.clear();
		Materials.clear();
	};

	renderer.SetBarycentricRender(true);
	renderer.SetLit(true);
	LoadCrtScene("scene0.crtscene");
	renderer.Render("scene_0.ppm");
	clearScene();

	LoadCrtScene("scene1.crtscene");
	renderer.Render("scene_1.ppm");
	clearScene();
	renderer.SetBarycentricRender(false);
	renderer.SetLit(false);

	LoadCrtScene("scene2.crtscene");
	renderer.Render("scene_2.ppm");
	clearScene();
	
	LoadCrtScene("scene3.crtscene");
	renderer.Render("scene_3.ppm");
	clearScene();

	LoadCrtScene("scene4.crtscene");
	renderer.Render("scene_4.ppm");
	clearScene();

	LoadCrtScene("scene5.crtscene");
	renderer.Render("scene_5.ppm");
	clearScene();

	return 0;
}

void LoadCrtScene(std::string documentName)
{
	std::ifstream	inputStream(documentName, std::ios::in | std::ios::binary);
	std::string		json((std::istreambuf_iterator<char>(inputStream)), (std::istreambuf_iterator<char>()));

	rapidjson::Document document;
	document.Parse(json.c_str());
	assert(document.IsObject());

	// I haven't added file validation, I just assume it's always correct format. But it can be added if needed
	// settings
	rapidjson::Value::Object	settingsObj		= document["settings"].GetObject();
	rapidjson::Value::Object	resolutionArr	= settingsObj["image_settings"].GetObject();
	Viewport.SetResolution(resolutionArr["width"].GetInt(), resolutionArr["height"].GetInt());

	rapidjson::Value::Array		backgroundArr	= settingsObj["background_color"].GetArray();
	int R = 256 * backgroundArr[0].GetDouble();
	int G = 256 * backgroundArr[1].GetDouble();
	int B = 256 * backgroundArr[2].GetDouble();
	CRGBColor background(R, G, B);
	Viewport.SetBackground(background);

	// camera
	rapidjson::Value::Object	cameraObj	= document["camera"].GetObject();
	rapidjson::Value::Array		rotationArr	= cameraObj["matrix"].GetArray();
	CMatrix3x3 rotation	( rotationArr[0].GetDouble(), rotationArr[1].GetDouble(), rotationArr[2].GetDouble()
						, rotationArr[3].GetDouble(), rotationArr[4].GetDouble(), rotationArr[5].GetDouble()
						, rotationArr[6].GetDouble(), rotationArr[7].GetDouble(), rotationArr[8].GetDouble());
	Viewport.SetRotation(rotation);

	rapidjson::Value::Array translationArr	= cameraObj["position"].GetArray();
	CVector translation(translationArr[0].GetDouble(), translationArr[1].GetDouble(), translationArr[2].GetDouble());
	Viewport.SetTranslation(translation);

	// lights
	if (document.HasMember("lights"))
	{
		rapidjson::Value::Array lightsArr = document["lights"].GetArray();
		for (auto& lightElement : lightsArr)
		{
			rapidjson::Value::Object lightObj = lightElement.GetObject();

			rapidjson::Value::Array lightTranslationArr = lightObj["position"].GetArray();
			CVector lightTranslation(lightTranslationArr[0].GetDouble(), lightTranslationArr[1].GetDouble(), lightTranslationArr[2].GetDouble());

			int intensity = lightObj["intensity"].GetInt();

			Lights.push_back(CPointLight(lightTranslation, intensity));
		}
	}

	// materials
	rapidjson::Value::Array materialsArr = document["materials"].GetArray();
	for (auto& materialElement : materialsArr)
	{
		rapidjson::Value::Object materialObj = materialElement.GetObject();

		std::string type = materialObj["type"].GetString();
		
		rapidjson::Value::Array albedoArr = materialObj["albedo"].GetArray();
		CVector albedo(albedoArr[0].GetDouble(), albedoArr[1].GetDouble(), albedoArr[2].GetDouble());

		bool smoothShading = materialObj["smooth_shading"].GetBool();

		Materials.push_back(CMaterial(type, albedo, smoothShading));
	}

	// objects
	rapidjson::Value::Array objectsArr = document["objects"].GetArray();
	for (auto& object : objectsArr)
	{
		rapidjson::Value::Object obj		= object.GetObject();
		rapidjson::Value::Array	 vertices	= obj["vertices"].GetArray();
		rapidjson::Value::Array	 triangles	= obj["triangles"].GetArray();
		int materialIndex                   = obj["material_index"].GetInt();

		CGeometricObject newObject(Materials[materialIndex]);

		int trianglesCount = triangles.Size();
		for (int triangleIndex = 0; triangleIndex < trianglesCount; triangleIndex += 3)
		{
			int V0Index = triangles[triangleIndex].GetInt() * 3;
			int V1Index = triangles[triangleIndex + 1].GetInt() * 3;
			int V2Index = triangles[triangleIndex + 2].GetInt() * 3;

			CVector V0Pos(vertices[V0Index].GetDouble(), vertices[V0Index + 1].GetDouble(), vertices[V0Index + 2].GetDouble());
			CVector V1Pos(vertices[V1Index].GetDouble(), vertices[V1Index + 1].GetDouble(), vertices[V1Index + 2].GetDouble());
			CVector V2Pos(vertices[V2Index].GetDouble(), vertices[V2Index + 1].GetDouble(), vertices[V2Index + 2].GetDouble());

			newObject.AddVertex(V0Pos, V0Index);
			newObject.AddVertex(V1Pos, V1Index);
			newObject.AddVertex(V2Pos, V2Index);
			newObject.AddTriangle(V0Index, V1Index, V2Index);
		}

		GeometricObjects.push_back(newObject);
	}
}
