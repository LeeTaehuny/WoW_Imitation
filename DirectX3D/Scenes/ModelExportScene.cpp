#include "Framework.h"
#include "ModelExportScene.h"

ModelExportScene::ModelExportScene()
{
    //string file = "Models/FBX/" + name + ".fbx";
    //ModelExporter* exporter;

    string name = "TownPortal";
    Model_MER_MESH(name);
    ////AnimationClip(name, "Attack_3");
    ////string name = "VAlkier";
    ////string file = "Models/FBX/" + name + ".fbx";
    ////ModelExporter* exporter;
    //
    ////Model_MER_MESH(name);
    ////AnimationClip(name, "Flying");
    ////AnimationClip(name, "Idle_1");
    ////AnimationClip(name, "Idle_2");
    ////AnimationClip(name, "Idle_3");
    ////AnimationClip(name, "Attack_2");
    ////AnimationClip(name, "Attack_3");
    ////AnimationClip(name, "Attack_4");
	//
    //string name = "Tree2";
    //string file = "Models/FBX/" + name + ".fbx";
    //ModelExporter* exporter;
    //exporter = new ModelExporter(name, file);
    //exporter->ExportMaterial();
    //exporter->ExportMesh();
    //delete exporter;   
   
    //clipName = "Dying";
    //file = "Models/Animations/" + name + "/" + clipName + ".fbx";
    //exporter = new ModelExporter(name, file);
    //exporter->ExportMaterial();
    //exporter->ExportMesh();
    //delete exporter;
    //
    //clipName = "Dying";
    //file = "Models/Animations/" + name + "/" + clipName + ".fbx";
    //exporter = new ModelExporter(name, file);
    //exporter->ExportClip(clipName);    
    //delete exporter;
    //
    //clipName = "Run";
    //file = "Models/Animations/" + name + "/" + clipName + ".fbx";
    //exporter = new ModelExporter(name, file);
    //exporter->ExportClip(clipName);
    //delete exporter;
    //
    //clipName = "Walk";
    //file = "Models/Animations/" + name + "/" + clipName + ".fbx";
    //exporter = new ModelExporter(name, file);
    //exporter->ExportClip(clipName);
    //delete exporter;
    //
    //clipName = "Hit";
    //file = "Models/Animations/" + name + "/" + clipName + ".fbx";
    //exporter = new ModelExporter(name, file);
    //exporter->ExportClip(clipName);
    //delete exporter;
    //
    //clipName = "StandUp";
    //file = "Models/Animations/" + name + "/" + clipName + ".fbx";
    //exporter = new ModelExporter(name, file);
    //exporter->ExportClip(clipName);
    //delete exporter;
}



void ModelExportScene::Model_MER_MESH(string name)
{
    string file = "Models/FBX/" + name + ".fbx";

    ModelExporter* exporter;
    exporter = new ModelExporter(name, file);
    exporter->ExportMaterial();
    exporter->ExportMesh();
    delete exporter;
}

void ModelExportScene::AnimationClip(string name, string clipName)
{
    string file = "Models/Animations/" + name + "/" + clipName + ".fbx";

    ModelExporter* exporter;
    exporter = new ModelExporter(name, file);
    exporter->ExportClip(clipName);
    delete exporter; 
	
    //string name = "Robot";
    //string file = "Models/FBX/" + name + ".fbx";
    //ModelExporter* exporter;
    //string clipName;

    //clipName = "Dying";
    //file = "Models/Animations/" + name + "/" + clipName + ".fbx";
    //exporter = new ModelExporter(name, file);
    //exporter->ExportClip(clipName);    
    //delete exporter;
    //
    //clipName = "Run";
    //file = "Models/Animations/" + name + "/" + clipName + ".fbx";
    //exporter = new ModelExporter(name, file);
    //exporter->ExportClip(clipName);
    //delete exporter;
    //
    //clipName = "Walk";
    //file = "Models/Animations/" + name + "/" + clipName + ".fbx";
    //exporter = new ModelExporter(name, file);
    //exporter->ExportClip(clipName);
    //delete exporter;
    //
    //clipName = "Hit";
    //file = "Models/Animations/" + name + "/" + clipName + ".fbx";
    //exporter = new ModelExporter(name, file);
    //exporter->ExportClip(clipName);
    //delete exporter;
    //
    //clipName = "StandUp";
    //file = "Models/Animations/" + name + "/" + clipName + ".fbx";
    //exporter = new ModelExporter(name, file);
    //exporter->ExportClip(clipName);
    //delete exporter;
}

ModelExportScene::~ModelExportScene()
{
}
void ModelExportScene::Update()
{
}
void ModelExportScene::PreRender()
{
}
void ModelExportScene::Render()
{
}
void ModelExportScene::PostRender()
{
}
void ModelExportScene::GUIRender()
{
}