#include "DirectXApp.h"
#include "CubeNode.h"
#include "TCubeNode.h"

using namespace Colors; 

DirectXApp app;

void DirectXApp::CreateSceneGraph()
{
	SceneGraphPointer sceneGraph = GetSceneGraph();
	SceneNodePointer body = make_shared<CubeNode>(L"body", Vector4(Colors::Purple));
	body->SetWorldTransform(Matrix::CreateScale(5.0f, 8.0f, 2.5f) * Matrix::CreateTranslation(0.0f, 23.0f, 0.0f));
	sceneGraph->Add(body);

	SceneNodePointer LeftLeg = make_shared<CubeNode>(L"LeftLeg", Vector4(Colors::Blue));
	LeftLeg->SetWorldTransform(Matrix::CreateScale(1.0f, 7.5f, 1.0f) * Matrix::CreateTranslation(-4.0f, 7.5f, 0.0f));
	sceneGraph->Add(LeftLeg);

	SceneNodePointer RightLeg = make_shared<CubeNode>(L"RightLeg", Vector4(Colors::Blue));
	RightLeg->SetWorldTransform(Matrix::CreateScale(1.0f, 7.5f, 1.0f) * Matrix::CreateTranslation(4.0f, 7.5f, 0.0f));
	sceneGraph->Add(RightLeg);

	SceneNodePointer Head = make_shared<CubeNode>(L"Head", Vector4(Colors::DeepPink));
	Head->SetWorldTransform(Matrix::CreateScale(3.0f, 3.0f, 3.0f) * Matrix::CreateTranslation(0.0f, 34.0f, 0.0f));
	sceneGraph->Add(Head);

	SceneNodePointer LeftArm = make_shared<CubeNode>(L"LeftArm", Vector4(Colors::MediumPurple));
	LeftArm->SetWorldTransform(Matrix::CreateScale(1.0f, 8.5f, 1.0f) * Matrix::CreateTranslation(-6.0f, 22.0f, 0.0f));
	sceneGraph->Add(LeftArm);

	SceneNodePointer RightArm = make_shared<CubeNode>(L"RightArm", Vector4(Colors::MediumPurple));
	RightArm->SetWorldTransform(Matrix::CreateScale(1.0f, 8.5f, 1.0f) * Matrix::CreateTranslation(6.0f, 22.0f, 0.0f));
	sceneGraph->Add(RightArm);

	SceneNodePointer TBox = make_shared<TCubeNode>(L"TBox", Vector4(1.0f, 1.0f, 1.0f, 1.0f), TextureName);
	TBox->SetWorldTransform(Matrix::CreateScale(4.0f, 4.0f, 4.0f) * Matrix::CreateTranslation(10.0f, 10.0f, 10.0f));
	sceneGraph->Add(TBox);



}

void DirectXApp::UpdateSceneGraph()
{
	SceneGraphPointer sceneGraph = GetSceneGraph();
	SceneNodePointer leftArm = sceneGraph->Find(L"LeftArm");
	SceneNodePointer rightArm = sceneGraph->Find(L"RightArm");
	SceneNodePointer TBox = sceneGraph->Find(L"TBox");
	leftArm->SetWorldTransform(Matrix::CreateScale(1.0f, 8.5f, 1.0f) * Matrix::CreateTranslation(-6.0f, 8.5f, 0.0f) * Matrix::CreateRotationX(-_rotationAngle * XM_PI / 100.0f) * Matrix::CreateTranslation(0.0f, 30.5f, 0.0f));
	rightArm->SetWorldTransform(Matrix::CreateScale(1.0f, 8.5f, 1.0f) * Matrix::CreateTranslation(6.0f, 8.5f, 0.0f) * Matrix::CreateRotationX(_rotationAngle * XM_PI / 100.0f) * Matrix::CreateTranslation(0.0f, 30.5f, 0.0f));
	sceneGraph->SetWorldTransform(Matrix::CreateRotationY(_rotationAngle * XM_PI / 100.0f));
	TBox->SetWorldTransform(Matrix::CreateScale(4.0f, 4.0f, 4.0f) * Matrix::CreateRotationY(-_rotationAngle*2 * XM_PI / 100.0f) * Matrix::CreateTranslation(10.0f, 10.0f, 10.0f));
	_rotationAngle = (_rotationAngle + 1) % 360;
}
