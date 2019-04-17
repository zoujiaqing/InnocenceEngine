#pragma once
#include "../../common/InnoType.h"
#include "../../component/GLTextureDataComponent.h"

INNO_PRIVATE_SCOPE GLEnvironmentRenderPass
{
	void initialize();

	void update();
	void draw();

	GLTextureDataComponent* getBRDFSplitSumLUT();
	GLTextureDataComponent* getBRDFMSAverageLUT();
	GLTextureDataComponent* getConvPassGLTDC();
	GLTextureDataComponent* getPreFilterPassGLTDC();
	GLTextureDataComponent* getVoxelVisualizationPassGLTDC();
}