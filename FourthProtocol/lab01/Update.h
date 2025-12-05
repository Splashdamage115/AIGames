// ***************************************************************************
// 
//									HOW TO USE
// 
// ***************************************************************************
//
// 
// 1.	Include this header in the top of the cpp file :
//			#include "Update.h"
// 
// 2.	use the following to append its own "Update" function :
//			Update::append([this]() { this->update(); });
//
//
// Implement:
// 1.	Include this header in the top of the cpp file :
//			#include "Update.h"
// 
// 2.	call the 'Update::update();' function	
//
//
// ***************************************************************************

#pragma once

#include "Library.h"
#include <functional>

class Update
{
public:
	/*! \brief add new update function
	*
	*	add new function to list of update functions, this decouples updates from main game loop
	*/
	static void append(const std::function<void(void)>& t_func);
	/*! \brief update all updates
	*
	*	call all update functions
	*/
	static void update();
private:
	static std::vector < std::function<void(void)> > m_updateFunctions;
};

