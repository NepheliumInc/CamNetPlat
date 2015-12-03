#ifndef NODEPARAMETEROBJECT_H
#define NODEPARAMETEROBJECT_H

#include "QtCore\qobject.h"
#include "humanreident_global.h"
#include <stdafx.h>	

class NodeParameterObject
{
public:

	//==BackSubMOG2Params==
	//history – Length of the history.
	//varThreshold – Threshold on the squared Mahalanobis distance to decide whether it is well described by the background model(see Cthr ? ? ).This parameter does not affect the background update.A typical value could be 4 sigma, that is, varThreshold = 4 * 4 = 16; (see Tb ? ? ).
	//bShadowDetection – Parameter defining whether shadow detection should be enabled(true or false).
	struct BackSubMOG2Params
	{
		int history = 300;
		float varThreshold = 32;
		bool bShadowDetection = true;
	};
	BackSubMOG2Params backSubMOG2Params;



	std::string nodeId;
	NodeParameterObject();
	~NodeParameterObject();
};

#endif // MOMENTCALCULATION2_H