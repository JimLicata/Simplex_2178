#include "AppClass.h"
void Application::InitVariables(void)
{
	//init the mesh
	m_uMeshCount = 46;
	for (uint i = 0; i < m_uMeshCount; i++)
	{
		MyMesh* pMesh = new MyMesh();
		m_pMeshList.push_back(pMesh);
		m_pMeshList[i]->GenerateCube(1.0f, C_BLACK);
	}



}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	matrix4 m4View = m_pCameraMngr->GetViewMatrix();
	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();

	static float value = 0.0f;
	
	value += 0.01f;

	matrix4 m4Translate = glm::translate(IDENTITY_M4, vector3(0.0f + value, 0.0f, 0.0f));
	matrix4 m4Model = m4Translate;
	m_pMeshList[0]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(-1.0f + value, 0.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList[1]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(-2.0f + value, 0.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList[2]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(-3.0f + value, 0.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList[3]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(-5.0f + value, 0.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList[4]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(-5.0f + value, -1.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList[5]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(-5.0f + value, 1.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList[6]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(-4.0f + value, 1.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList[7]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(-3.0f + value, 1.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList[8]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(-2.0f + value, 1.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList[9]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(-1.0f + value, 1.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList[10]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(0.0f + value, 1.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList[11]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(1.0f + value, 1.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList[12]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(2.0f + value, 1.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList[13]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(3.0f + value, 1.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList[14]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(4.0f + value, 1.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList[15]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(5.0f + value, 1.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList[16]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(1.0f + value, 0.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList[17]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(2.0f + value, 0.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList[18]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(3.0f + value, 0.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList[19]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(5.0f + value, 0.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList[20]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(5.0f + value, -1.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList[21]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(3.0f + value, -1.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList[22]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(-3.0f + value, -1.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList[23]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(-1.0f + value, -2.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList[24]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(-2.0f + value, -2.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList[25]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(1.0f + value, -2.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList[26]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(2.0f + value, -2.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList[27]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(0.0f + value, 2.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList[28]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(-1.0f + value, 2.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList[29]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(1.0f + value, 2.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList[30]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(-3.0f + value, 2.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList[31]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(3.0f + value, 2.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList[32]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(-4.0f + value, 2.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList[33]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(4.0f + value, 2.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList[34]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(0.0f + value, 3.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList[35]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(1.0f + value, 3.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList[36]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(-1.0f + value, 3.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList[37]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(2.0f + value, 3.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList[38]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(-2.0f + value, 3.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList[39]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(3.0f + value, 3.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList[40]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(-3.0f + value, 3.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList[41]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(-2.0f + value, 4.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList[42]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(2.0f + value, 4.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList[43]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(-3.0f + value, 5.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList[44]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(3.0f + value, 5.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList[45]->Render(m4Projection, m4View, m4Model);

	// draw a skybox
	m_pMeshMngr->AddSkyboxToRenderList();

	//render list call
	m_uRenderCallCount = m_pMeshMngr->Render();

	//clear the render list
	m_pMeshMngr->ClearRenderList();

	//draw gui
	DrawGUI();

	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}
void Application::Release(void)
{
	for (uint i = 0; i < m_uMeshCount; i++)
	{
		SafeDelete(m_pMeshList[i]);
	}
	

	//release GUI
	ShutdownGUI();
}