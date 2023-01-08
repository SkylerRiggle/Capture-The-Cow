#pragma once

#include "GameTypes.h"
#include <queue>
#include <cassert>

/// <summary>
/// A scene is a collection of gameobjects
/// </summary>
class Scene 
{
public:
	/// <summary>
	/// Creates a new scene
	/// </summary>
	Scene() 
	{
		// Create a queue of available id numbers
		for (GameObject gameObject = 0; gameObject < MAX_OBJECTS; gameObject++) 
		{
			availableIds.push(gameObject);
		}

		// Set the active count to 0
		activeCount = 0;
	}

	/// <summary>
	/// Create a new gameobject
	/// </summary>
	/// <returns>The resulting gameobject</returns>
	GameObject Create() 
	{
		// Ensure that there's enough space 
		assert(activeCount < MAX_OBJECTS && "Too many objects currently in the scene!");

		// Get the available id at the head of the queue
		GameObject newId = availableIds.front();

		// Remove the available object id and increment the active count
		availableIds.pop();
		activeCount++;

		// Return the new game object's id
		return newId;
	}

	/// <summary>
	/// Destroys a gameobject
	/// </summary>
	void Destroy(GameObject gameObject) 
	{
		// Ensure that the gameobject feasably came from this scene (does not exceed max)
		assert(gameObject < MAX_OBJECTS && "Object out of scene range!");

		// Add this new id to the list of available ids and decrement the number of active ids
		availableIds.push(gameObject);
		activeCount--;
	}

private:
	std::queue<GameObject> availableIds{};
	uint32_t activeCount{};
};