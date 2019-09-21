#pragma once

namespace ALightCreator {
	class Panel
	{
	public:
		bool enabled = true;
		// virtual ~Panel();
		virtual void Render() {}
		virtual void Terminate() {};
	};

}