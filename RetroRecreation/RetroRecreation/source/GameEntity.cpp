#include "..\include\GameEntity.h"

/// <summary>
/// creates new instance of game entity
/// </summary>
GameEntity::GameEntity(float a_fX, float a_fY)
{
	// sets its position and rotation
	m_vPos.x = a_fX;
	m_vPos.y = a_fY;
	m_fRotation = 0.0f;

	m_bActive = true;

	m_oParent = NULL;
}

/// <summary>
/// Destrutor
/// </summary>
GameEntity::~GameEntity()
{
	m_oParent = NULL;
}

/// <summary>
/// sets the position of the game entity to a specified position
/// </summary>
void GameEntity::Pos(Vector2 a_vPos)
{
	m_vPos = a_vPos;
}

/// <summary>
/// returns the position of the game entity
/// </summary>
Vector2 GameEntity::GetPos()
{
	return m_vPos;
}

/// <summary>
/// increment the x and y position of the game entity by the given amount
/// </summary>
void GameEntity::TranslatePos(float a_fX, float a_fY)
{
	m_vPos.x += a_fX;
	m_vPos.y -= a_fY;
}

/// <summary>
/// returns the position of the game entity in the given space
/// </summary>
Vector2 GameEntity::Pos(SPACE a_eSpace)
{
	if (a_eSpace == local || m_oParent == NULL)
	{
		return m_vPos;
	}

	return m_oParent->Pos(world) + RotateVector(m_vPos, m_oParent->Rotation(local));
}

/// <summary>
/// rotates the game entity by the given angle
/// </summary>
void GameEntity::Rotation(float a_fRot)
{
	m_fRotation = a_fRot;

	if (m_fRotation > 360.0f)
	{
		m_fRotation -= 360.0f;
	}
	if (m_fRotation < 0.0f)
	{
		m_fRotation += 360.0f;
	}
}

/// <summary>
/// returns the rotation in the world space
/// </summary>
float GameEntity::Rotation(SPACE a_eSpace)
{
	if (a_eSpace == local || m_oParent == NULL)
	{
		return m_fRotation;
	}

	return m_oParent->Rotation(world) + m_fRotation;
}

/// <summary>
/// Sets the game entity as active
/// </summary>
void GameEntity::SetActive(bool a_bActive)
{
	m_bActive = a_bActive;
}

/// <summary>
/// returns whether the entity is active
/// </summary>
bool GameEntity::IsActive()
{
	return m_bActive;
}

/// <summary>
/// Sets a specified entity as the current entity's parent object
/// </summary>
/// <param name="a_oParent"></param>
void GameEntity::Parent(GameEntity* a_oParent)
{
	m_vPos = Pos(world) - a_oParent->Pos(world);

	m_oParent = a_oParent;
}

/// <summary>
/// Returns the parent of the entity
/// </summary>
GameEntity* GameEntity::Parent()
{
	return m_oParent;
}


void GameEntity::Update()
{
}


void GameEntity::Render()
{
}
