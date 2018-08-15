#include "AppClass.h"
void Application::InitVariables(void)
{
	//init the mesh
	m_uMeshCount = 46;
	for (uint i = 0; i < m_uMeshCount; i++)
	{
		MyMesh* pMesh = new MyMesh();
		m_pMeshList1.push_back(pMesh);
		m_pMeshList1[i]->GenerateCube(1.0f, C_BLACK);
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
	m_pMeshList1[0]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(-1.0f + value, 0.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList1[1]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(-2.0f + value, 0.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList1[2]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(-3.0f + value, 0.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList1[3]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(-5.0f + value, 0.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList1[4]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(-5.0f + value, -1.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList1[5]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(-5.0f + value, 1.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList1[6]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(-4.0f + value, 1.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList1[7]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(-3.0f + value, 1.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList1[8]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(-2.0f + value, 1.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList1[9]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(-1.0f + value, 1.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList1[10]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(0.0f + value, 1.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList1[11]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(1.0f + value, 1.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList1[12]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(2.0f + value, 1.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList1[13]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(3.0f + value, 1.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList1[14]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(4.0f + value, 1.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList1[15]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(5.0f + value, 1.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList1[16]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(1.0f + value, 0.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList1[17]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(2.0f + value, 0.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList1[18]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(3.0f + value, 0.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList1[19]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(5.0f + value, 0.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList1[20]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(5.0f + value, -1.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList1[21]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(3.0f + value, -1.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList1[22]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(-3.0f + value, -1.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList1[23]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(-1.0f + value, -2.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList1[24]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(-2.0f + value, -2.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList1[25]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(1.0f + value, -2.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList1[26]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(2.0f + value, -2.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList1[27]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(0.0f + value, 2.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList1[28]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(-1.0f + value, 2.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList1[29]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(1.0f + value, 2.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList1[30]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(-3.0f + value, 2.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList1[31]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(3.0f + value, 2.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList1[32]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(-4.0f + value, 2.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList1[33]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(4.0f + value, 2.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList1[34]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(0.0f + value, 3.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList1[35]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(1.0f + value, 3.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList1[36]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(-1.0f + value, 3.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList1[37]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(2.0f + value, 3.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList1[38]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(-2.0f + value, 3.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList1[39]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(3.0f + value, 3.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList1[40]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(-3.0f + value, 3.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList1[41]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(-2.0f + value, 4.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList1[42]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(2.0f + value, 4.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList1[43]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(-3.0f + value, 5.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList1[44]->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(IDENTITY_M4, vector3(3.0f + value, 5.0f, 0.0f));
	m4Model = m4Translate;
	m_pMeshList1[45]->Render(m4Projection, m4View, m4Model);

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
		SafeDelete(m_pMeshList1[i]);
	}
	

	//release GUI
	ShutdownGUI();
}