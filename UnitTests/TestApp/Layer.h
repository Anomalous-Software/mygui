#ifndef __LAYER_H__
#define __LAYER_H__

#include "BaseManager.h"
#include "VertexBuffer.h"

namespace demo
{
	class Layer
	{
	public:
		Layer();
		virtual ~Layer();

		VertexBuffer* createVertexBuffer();
		void destroyAllBuffers();

		void doRender(IRenderManager* _renderManager);

	private:
		typedef std::vector<VertexBuffer*> VectorVertexBuffer;
		VectorVertexBuffer mBuffers;
	};

} // namespace demo

#endif // __LAYER_H__
