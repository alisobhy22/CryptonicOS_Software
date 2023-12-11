/**
 * @file
 * @brief Declarations for operating system resource management functions.
 *
 * This file contains declarations for functions related to managing resources in the operating system.
 * The functions include acquiring (getting) and releasing resources.
 *
 * @author Your Name
 * @date YYYY-MM-DD HH:MM:SS
 */

#ifndef Headers_APIs_Headers_Resources_H
#define Headers_APIs_Headers_Resources_H

#include "Defines.h"

/**
 * @brief Acquire a resource.
 *
 * This function is used to acquire (get) a specified resource identified by its ID.
 *
 * @param[in] ResID The ID of the resource to be acquired.
 * @return StatusType E_OK if the resource is successfully acquired, or an error code if unsuccessful.
 */
StatusType GetResource(ResourceType ResID);

/**
 * @brief Release a resource.
 *
 * This function is used to release a previously acquired resource identified by its ID.
 *
 * @param[in] ResID The ID of the resource to be released.
 * @return StatusType E_OK if the resource is successfully released, or an error code if unsuccessful.
 */
StatusType ReleaseResource(ResourceType ResID);

#endif
