#include "AppClass.h"
void Application::InitVariables(void)
{
	//Change this to your name and email
	m_sProgrammer = "James Licata - jxl2489@rit.edu";
	
	//Set the position and target of the camera
	//(I'm at [0,0,10], looking at [0,0,0] and up is the positive Y axis)
	m_pCameraMngr->SetPositionTargetAndUp(AXIS_Z * 20.0f, ZERO_V3, AXIS_Y);

	//if the light position is zero move it
	if (m_pLightMngr->GetPosition(1) == ZERO_V3)
		m_pLightMngr->SetPosition(vector3(0.0f, 0.0f, 3.0f));

	//if the background is cornflowerblue change it to black (its easier to see)
	if (vector3(m_v4ClearColor) == C_BLUE_CORNFLOWER)
	{
		m_v4ClearColor = vector4(ZERO_V3, 1.0f);
	}
	
	//if there are no segments create 7
	if(m_uOrbits < 1)
		m_uOrbits = 7;

	float fSize = 1.0f; //initial size of orbits

	//creating a color using the spectrum 
	uint uColor = 650; //650 is Red
	//prevent division by 0
	float decrements = 250.0f / (m_uOrbits > 1? static_cast<float>(m_uOrbits - 1) : 1.0f); //decrement until you get to 400 (which is violet)
	/*
		This part will create the orbits, it start at 3 because that is the minimum subdivisions a torus can have
	*/
	uint uSides = 3; //start with the minimal 3 sides
	for (uint i = uSides; i < m_uOrbits + uSides; i++)
	{
		vector3 v3Color = WaveLengthToRGB(uColor); //calculate color based on wavelength
		m_shapeList.push_back(m_pMeshMngr->GenerateTorus(fSize, fSize - 0.1f, 3, i, v3Color)); //generate a custom torus and add it to the meshmanager
		fSize += 0.5f; //increment the size for the next orbit
		uColor -= static_cast<uint>(decrements); //decrease the wavelength
		
		// path creation
		const float pi = 3.14159265359;
		float step = ((pi * 2) / i);
		float x, y, x2, y2, curr = 0;
		static float radius = 1.0f;

		for (size_t j = 0; j < i; j++)
		{
			x = sin(curr) * radius;
			y = cos(curr) * radius;

			vector3 point(x, y, 0.0f);
			m_stopsList.push_back(point);

			curr += step;
		}
		radius += 0.5f;
	}

	

	
	for (uint i = 0; i < m_uOrbits; i++)
	{
		matrix4 m4Model = matrix4(0.0f);
		m_circleList.push_back(m4Model);

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

	matrix4 m4View = m_pCameraMngr->GetViewMatrix(); //view Matrix
	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix(); //Projection Matrix
	matrix4 m4Offset = IDENTITY_M4; //offset of the orbits, starts as the global coordinate system
	/*
		The following offset will orient the orbits as in the demo, start without it to make your life easier.
	*/
	m4Offset = glm::rotate(IDENTITY_M4, 1.5708f, AXIS_Z);
	uint addNum = 3;
	uint prevNum = 0;
	uint currNum = 0;
	for (uint i = 0; i < m_uOrbits; ++i)
	{
		//calculate the current position
		vector3 v3CurrentPos = ZERO_V3;
		vector3 v3StartPos = ZERO_V3;

		static uint route = 0;

		if (i == 0)
		{
			v3StartPos = m_stopsList[0];
		}

		else
		{
			currNum = addNum + prevNum;
			route = currNum;
			prevNum = currNum;
			addNum++;
		}

		//Get a timer
		static float fTimer = 0;	//store the new timer
		static uint uClock = m_pSystem->GenClock(); //generate a new clock for that timer
		fTimer += m_pSystem->GetDeltaTime(uClock); //get the delta time for that timer

		static vector3 v3Start, v3End;
		
		

		v3Start = m_stopsList[route ];
		if(currNum == 0)
			v3End = m_stopsList[(route + 1) % 3];
		else 
			v3End = m_stopsList[(route + 1) % (i + route + 2)];

		//LERP
		float fTimeBetweenStops = 1.0f;
		float fPercentage = MapValue(fTimer, 0.0f, fTimeBetweenStops, 0.0f, 1.0f);

		v3CurrentPos = glm::lerp(v3Start, v3End, fPercentage);
		m_circleList[i] = glm::translate(glm::rotate(IDENTITY_M4, 4.71239f, AXIS_Z) * m4Offset, v3CurrentPos);

		if (fPercentage >= 1.0f)
		{
			route++;
			fTimer = m_pSystem->GetDeltaTime(uClock);
			if (currNum == 0)
				route %= 3;
			else
			{
				route %= (i + route + 3);
			}
				
		}

	}

	// draw a shapes
	for (uint i = 0; i < m_uOrbits; ++i)
	{
		m_pMeshMngr->AddMeshToRenderList(m_shapeList[i], glm::rotate(m4Offset, 1.5708f, AXIS_X));

		

		//draw spheres
		m_pMeshMngr->AddSphereToRenderList(m_circleList[i] * glm::scale(vector3(0.1)), C_WHITE);
	}

	


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
	//release GUI
	ShutdownGUI();
}